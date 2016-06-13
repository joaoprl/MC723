
MC723a - Laboratório de Projetos de Sistemas Computacionais
====
###### 2016-06-12
#### Professor: Lucas Wanner
#### 139546 - João Lopes

Exercício 4 - Plataformas e Periféricos
====

## Objetivo
Utilizando um simulador de arquitetura _MIPS_, criar um periférico de lock que delimita regiões críticas de um programa em um sistema que integra processador, memória e periféricos através de um roteador. Configurar um novo core para o simulador e, utilizando o periférico criado, testar a performance de um código paralelizado.

## Periférico 
O periférico instanciado é do tipo lock. É capaz de separar regiões críticas, garantindo que apenas um núcleo adquira o direito a estar em uma dada região crítica. Para isso, alterou-se o código do arquivo [_ac_tlm_peripheral.cpp_](mips-tlm/ac_tlm_peripheral.cpp) conforme segue: 

```cpp
uint32_t data = 0;
ac_tlm_rsp_status ac_tlm_peripheral::writem( const uint32_t &a , const uint32_t &d )
{
  //  cout << "addr: " <<  std::hex  << a << " data: " << d << endl;
  data = d;
  return SUCCESS;
}
ac_tlm_rsp_status ac_tlm_peripheral::readm( const uint32_t &a , uint32_t &d )
{
  d = data;
  data = 1;
  return SUCCESS;
}
```

Para testar, executou-se o código [_test.c_](mips-tlm/test.c), conforme a seguir:
````c
volatile int *lock = (int *) ENDERECO_LOCK;
int main(){
  int t;
  while ((t = *lock));
  printf("lock adquirido: %d\n", t >> 24);
  printf("lock realizado: %d\n", (*lock) >> 24);
  *lock = 0;
  printf("lock solto\n");
  return 0;
}
````
A saída encontrada, conforme esperado, foi
````
lock adquirido: 0
lock realizado: 1
lock solto
````

Utilizando o periférico de lock (que simula um hardware) é possível criar diversos locks locais (em software) que delimitam diversas regiões críticas em um código.

````cpp
volatile int *global_lock = (int *) ENDERECO_LOCK; // should not be used in the program
acquireLock(int *lock){
  while(*global_lock || *lock); // acquire global_lock
  *lock = 1; // acquire given lock
  *global_lock = 0; // release global_lock
}
releaseLock(int *lock){
  *lock = 0;
}
````
## Plataforma multicore
Para que o lock possa executar a sua função, é necessário que o simulador seja capaz de executar tarefas paralelas. Para isso, deve-se instanciar um novo processador no simulador. Alterando-se o código do arquivo [_main.cpp_](mips-tlm/main.cpp):
````cpp
int sc_main(int ac, char *av[])
{

  //!  ISA simulator
  mips mips_proc1("mips1");
  mips mips_proc2("mips2");
  ac_tlm_mem mem("mem", 100*1024*1024);
  ac_tlm_router router("router");
  ac_tlm_peripheral peripheral("peripheral");

  router.MEM_port(mem.target_export);
  router.PERIPHERAL_port(peripheral.target_export); 

  mips_proc1.DM_port(router.target_export);
  mips_proc2.DM_port(router.target_export);


#ifdef AC_DEBUG
  ac_trace("mips_proc1.trace");
  ac_trace("mips_proc2.trace");
#endif
  int ac1 = ac;
  char **av1;
  av1 = (char**)calloc(ac, sizeof(char*));
  for(int i = 0; i < ac; i++)
    av1[i] = av[i];

  mips_proc1.init(ac, av);
  mips_proc2.init(ac1, av1);

  mips_proc1.set_instr_batch_size(1);
  mips_proc2.set_instr_batch_size(1);
  cerr << endl;

  sc_start();

  mips_proc1.PrintStat();
  mips_proc2.PrintStat();
  cerr << endl;

#ifdef AC_STATS
  ac_stats_base::print_all_stats(std::cerr);
#endif 

#ifdef AC_DEBUG
  ac_close_trace();
#endif 

  return mips_proc1.ac_exit_status + mips_proc2.ac_exit_status;
}
````

É necessário também separar as pilhas de cada processador. Para isso, deve-se alterar o arquivo [_mips_isa.cpp_](mips-tlm/mips_isa.cpp):
````cpp
static int processors_started = 0;
#define DEFAULT_STACK_SIZE (256*1024)
void ac_behavior(begin)
{
  dbg_printf("@@@ begin behavior @@@\n");
  RB[0] = 0;
  npc = ac_pc + 4;

  // Is is not required by the architecture, but makes debug really easier
  for (int regNum = 0; regNum < 32; regNum ++)
    RB[regNum] = 0;
  hi = 0;
  lo = 0;

  RB[29] =  AC_RAM_END - 1024 - processors_started++ * DEFAULT_STACK_SIZE;
}
````

Entretanto, diferentemente do que era esperado, o código acima não separou as pilhas de execução de cada core. 
Utilizando o código a seguir para testar:
````cpp
int main1(){
  int t;
  while(*lock);
  printf("addr: %d", &t);
  *lock = 0;
}
int main(){
  return main1();
}
````
Obteve-se o seguinte resultado:
````
addr: 5241816
addr: 5241816
````
Para variáveis que deveriam ser locais e terem endereços diferentes para cada core. Assim, não foi possível realizar o teste de funcionamento paralelo.


## Referências
1. http://www.ic.unicamp.br/~lucas/teaching/mc723/2016-1/ex4.html
2. R. Azevedo, S. Rigo (2011) _Electronic System Level Design: An Open-Source Approach_


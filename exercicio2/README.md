MC723 - Laboratório de Projetos de Sistemas Computacionais
====
Campinas, 07 de abril de 2016
####Professor: Lucas Wanner
####Nome: João Pedro Ramos Lopes - RA: 139546

Exercicio 2 - Configuração de Cache
====
Objetivos:
----
1. Utilizar o software dineroIV e trace de programas previamente gerados e disponibilizados para definir através de simulações a melhor configuração de cache.
2. Simular um programa com dois níveis de cache e achar a melhor configuração para os dois níveis (L1 de instruções, L1 de dados e L2 unificado). Você pode usar qualquer um dos 46 traces que estão disponíveis (cada programa tem dois traces, f2b e m2b, veja informações sobre isso na página dos traces).

Resumo
----
Foi disponibilizado o software de simulação e os traces a serem utilizados. Como programa de teste, foi escolhido o arquivo 183.equake.m2b.tar contendo traces para equake_m2b.
Como base de limitações de um processador atual, foi utilizado um i7 Haswell da intel, conforme segue:
![alt text](https://github.com/jpedrorl/MC723/blob/master/exercicio2/haswell.png "Haswell i7")
Para determinar um processador foi considerado que um ótimo determinado por flag geraria um ótimo global (guloso).

O comando foi utilizado conforme a seguir:

* dineroIV -informat s -trname equake_m2b -maxtrace 20 -l1-isize L1IS -l1-dsize L1DS -l1-ibsize L1IB -l1-dbsize L1DB -l2-usize L2US -l2-ubsize L2UB

Onde,

* L1IS é o tamanho do cache de instruções L1;
* L1DS é o tamanho do cache de dados L1;
* L1IB é o tamanho do bloco de intruções L1;
* L1DB é o tamanho do bloco de dados L1;
* L2US é o tamanho do cache compartilhado (dados + instruções) L2;
* L2UB é o tamanho do bloco de instruções e dados L2;

Os dados colhidos foram:
* L1 instr b: total de cache miss de instruções na L1;
* L1 instr: percentual de cache miss de instruções;
* L1 data: percentual de cache miss de dados na L1;
* L1 read: percentual de cache miss em tentativas de leitura na L1 de dados;
* % read(L1): percentual de leitura na L1 de dados;
* L1 write: percentual de cache miss em tentativas de escrita na L1 de dados;
* % write(L1): percentual de tentativas de escrita  na L1 de dados;
* L2 instr: total de cache miss na cache L2;
* L2 data: percentual de cache miss para dados na L2;
* L2 read: percentual de cache miss para leitura de dados na L2;
* % read(L2): percentual de escrita na L2 de dados;
* L2 write: percentual de cache miss para escrita de dados na L2;
* % write(L2): percentual de leitura na L2 de dados;

Os resultados encontrados podem ser encontrado na tabela presente na referência [[1]](https://github.com/jpedrorl/MC723/blob/master/exercicio2/rawData.pdf).


Testes
----
Alguns dos dados coletados se mantiveram constantes, pois são relativos ao programa e não à estrutura das caches. Tais dados foram omitidos mas podem ser encontrados na tabela de dados.

Inicialmente, executou-se o comando com valores baixos para cada variável, que foram aumentados conforme os gráficos que seguem. 

* dineroIV -informat s -trname equake_m2b -maxtrace 20 -l1-isize 4K -l1-dsize 4K -l1-ibsize 16 -l1-dbsize 16 -l2-usize 32K -l2-ubsize 16


Gráficos
----
####Cache de instruções da L1
![alt text](https://github.com/jpedrorl/MC723/blob/master/exercicio2/image0.png "L1 instruções")

####Cache de dados da L1
![alt text](https://github.com/jpedrorl/MC723/blob/master/exercicio2/image1.png "L1 dados")
![alt text](https://github.com/jpedrorl/MC723/blob/master/exercicio2/image2.png "L1 read write dados")

####Bloco de instruções da L1
![alt text](https://github.com/jpedrorl/MC723/blob/master/exercicio2/image3.png "L1 instruções bloco")

####Bloco de dados da L1
![alt text](https://github.com/jpedrorl/MC723/blob/master/exercicio2/image4.png "L1 dados bloco")

####Cache compartilhado L2
![alt text](https://github.com/jpedrorl/MC723/blob/master/exercicio2/image5.png "L2 tamanho1")
![alt text](https://github.com/jpedrorl/MC723/blob/master/exercicio2/image6.png "L2 tamanho2")

####Bloco compartilhado L2
![alt text](https://github.com/jpedrorl/MC723/blob/master/exercicio2/image7.png "L2 bloco1")
![alt text](https://github.com/jpedrorl/MC723/blob/master/exercicio2/image8.png "L2 bloco2")
![alt text](https://github.com/jpedrorl/MC723/blob/master/exercicio2/image9.png "L2 bloco3")

Referências
----
1. https://github.com/jpedrorl/MC723/blob/master/exercicio2/rawData.pdf
2. http://www.notebookcheck.net/Intel-Core-i7-4940MX-Notebook-Processor.109619.0.html
3. http://www.notebookcheck.net/AMD-FX-Series-Desktop-FX-8350-Notebook-Processor.91968.0.html
4. http://www.notebookcheck.net/AMD-Athlon-II-P340-Notebook-Processor.37883.0.html
5. http://hothardware.com/reviews/amd-fx-8350-vishera-8core-cpu-review?page=3
6. http://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-optimization-manual.pdf

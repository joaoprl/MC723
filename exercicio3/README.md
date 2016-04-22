MC723 - Laboratório de Projetos de Sistemas Computacionais
====
Campinas, 22 de abril de 2016
####Professor: Lucas Wanner
####Nome: João Pedro Ramos Lopes - RA: 139546

Exercício 3 - Contagem de ciclos
====
Objetivos:
----
1. Aprender noções básicas do ambiente de simulação.
2. Relembrar conceitos sobre medida de desempenho, em especial CPI.
3. Avaliar o desempenho de um processador baseado no tempo de execução de um conjunto de programas.

Resumo
----
Utilizando os software de simulação de processador MIPS (contruído em ArchC) e o pacote SystemC deve se analisar e avaliar o desempenho de um processador.

Atividade
----
####Contando instruções
Para um programa simples Hello World em C, deseja-se contar o número de chamadas à função add. Para isso, adicionou-se um contador (variável global) inicializado em ac_behavior(begin), incrementado em ac_behavior(add) e impresso na saída padrão na chamada ac_behavior(end) do arquivo mips_isa.cpp.
Também adicionou-se um contador para o número de chamadas addu, visto que usualmente é a operação utilizada para operações aritméticas no MIPS[[1]](http://stackoverflow.com/questions/16634110/difference-between-add-and-addu).
O resultado para add foi 0, entretanto, o resultado para addu foi de 176. Analisando o obj-dump, percebe-se que a instrução addu é utilizada para imprimir os resultados e operações básicas do funcionamento do programa.


####Avaliando o desempenho
Para obter o número de execução de cada instrução, compilou-se e executou-se o simulador conforme segue:

````Bash
acsim mips.ac -abi -s 
make -f Makefile.archc clean
make -f makefile.archc
mips.x --load=[file]
````

Onde [file] é o caminho arquivo a ser analisado.

Utilizando a tabela de CPI médio por categoria de instruções abaixo, pode se calcular o número de ciclos necessários para a execução de 3 programas.

| Categoria              | CPI Médio |
|------------------------|-----------|
| Acesso à memória       | 10        | 
| Controle (branch/jump) | 3         | 
| Outras                 | 1         |

Executou-se então 3 programas do pacote MiBench e o Hello World e calulou-se o número de ciclos gastos em cada um. A fim de conta, instruções do tipo sys_call e do tipo instr_break foram consideradas de controle, dado que possuem custo de ciclos elevados. Os dados encontrados estão dispostos abaixo.

| Categoria              | Hello | jpeg coder (small) | adpcm encoder (small) | gsm coder (large) |
|------------------------|-------|--------------------|-----------------------|-------------------|
| Instruções             | 2708  | 29857502           | 35739021              | 1484477204        |
| SYSCALLS               | 19    | 250                | 1381                  | 1714              |
| lb                     | 12    | 24201              | 746                   | 181680            |
| lbu                    | 22    | 427634             | 14                    | 1336809           |
| lh                     | 20    | 531003             | 685183                | 52437731          |
| lhu                    | 0     | 515                | 0                     | 2571546           |
| lw                     | 552   | 5568788            | 1371652               | 209932566         |
| lwl                    | 0     | 49232              | 0                     | 463619            |
| lwr                    | 0     | 49232              | 0                     | 463619            |
| sb                     | 38    | 254658             | 342935                | 516254            |
| sh                     | 17    | 98613              | 703                   | 22173746          |
| sw                     | 379   | 2707732            | 1916                  | 63720986          |
| swl                    | 0     | 49272              | 0                     | 434643            |
| swr                    | 0     | 49272              | 0                     | 434643            |
| Operações de memória   | 10400 | 98101520	          | 24031490	          | 3546678420        |
| addi                   | 1     | 1                  | 1                     | 1                 |
| addiu                  | 299   | 4628068            | 2868068               | 84599882          |
| slti                   | 1     | 117568             | 1368870               | 6679982           |
| sltiu                  | 15    | 6010               | 23                    | 684230            |
| andi                   | 26    | 45230              | 114                   | 4964293           |
| ori                    | 21    | 601                | 288290                | 633958            |
| xori                   | 1     | 32781              | 684432                | 65039             |
| lui                    | 47    | 13911              | 1417                  | 1302171           |
| add                    | 0     | 0                  | 0                     | 0                 |
| addu                   | 175   | 4089708            | 4250091               | 258460109         |
| sub                    | 0     | 0                  | 0                     | 0                 |
| subu                   | 18    | 893530             | 1746950               | 33740973          |
| slt                    | 3     | 726929             | 2737732               | 11131024          |
| sltu                   | 15    | 17489              | 41                    | 22094712          |
| instr_and              | 13    | 20728              | 7                     | 232272            |
| instr_or               | 2     | 38034              | 1026693               | 652752            |
| instr_xor              | 4     | 19                 | 0                     | 115920            |
| instro_nor             | 2     | 20188              | 0                     | 57969             |
| nop                    | 666   | 2506141            | 5478478               | 144823577         |
| sll                    | 39    | 2023905            | 1711836               | 120313047         |
| srl                    | 3     | 9389               | 20                    | 22742             |
| sra                    | 36    | 545185             | 2054713               | 92728242          |
| sllv                   | 1     | 57485              | 30                    | 532615            |
| srlv                   | 0     | 0                  | 25                    | 0                 |
| srav                   | 0     | 349936             | 0                     | 1593680           |
| mult                   | 0     | 38505              | 20                    | 126222369         |
| multu                  | 0     | 0                  | 0                     | 0                 |
| div                    | 0     | 13176              | 0                     | 0                 |
| divu                   | 0     | 87                 | 40                    | 0                 |
| mfhi                   | 0     | 78                 | 20                    | 0                 |
| mthi                   | 0     | 0                  | 0                     | 0                 |
| mflo                   | 0     | 51700              | 40                    | 126215143         |
| mtlo                   | 0     | 0                  | 0                     | 0                 |
| Outras operações       | 1388	 | 16246382	          | 24217951	            | 1037866702        |
| j                      | 23    | 301917             | 1581734               | 8127627           |
| jal                    | 51    | 34673              | 2125                  | 2017908           |
| jr                     | 52    | 49962              | 2138                  | 2026828           |
| jalr                   | 1     | 15284              | 13                    | 8918              |
| beq                    | 47    | 1797828            | 2054175               | 39594437          |
| bne                    | 108   | 1109799            | 4107477               | 33350780          |
| blez                   | 0     | 39123              | 690                   | 159085            |
| bgtz                   | 3     | 1934               | 8                     | 2720              |
| bltz                   | 2     | 447745             | 1368866               | 4817588           |
| bgez                   | 2     | 2703               | 695                   | 1836769           |
| bltzal                 | 0     | 0                  | 0                     | 0                 |
| bgezal                 | 0     | 0                  | 0                     | 0                 |
| sys_call               | 0     | 0                  | 0                     | 0                 |
| instr_break            | 0     | 0                  | 0                     | 0                 |
| Operações de controle  | 867	 | 11402904	          | 27353763	          | 275827980         |
| TOTAL                  | 12655 | 125750806	      | 75603204	          | 4860373102        |

Ou, de forma mais enxuta, conforme segue:

| Categoria              | Hello | jpeg coder (small) | adpcm encoder (small) | gsm coder (large) |
|------------------------|-------|--------------------|-----------------------|-------------------|
| Instruções             | 2708  | 29857502           | 35739021              | 1484477204        |
| SYSCALLS               | 19    | 250                | 1381                  | 1714              |
| Operações de memória   | 10400 | 98101520	          | 24031490	            | 3546678420        |
| Outras operações       | 1388	 | 16246382	          | 24217951	            | 1037866702        |
| Operações de controle  | 867	 | 11402904	          | 27353763	            | 275827980         |
| TOTAL                  | 12655 | 125750806	        | 75603204	            | 4860373102        |


Referências
----
1. http://stackoverflow.com/questions/16634110/difference-between-add-and-addu
2. http://www.ic.unicamp.br/~lucas/teaching/mc723/2016-1/ex3.html

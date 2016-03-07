**Autor: João Pedro R Lopes**
**RA: 139546**


1. Não notou-se variações significativas entre as diversas formas de otimização OX, conforme valores que seguem:

*gcc primo.c -o primo*
real	0m0.315s
user	0m0.312s
sys	0m0.000s

*gcc -O0 primo.c -o primo*
real	0m0.343s
user	0m0.340s
sys	0m0.000s

*gcc -O1 primo.c -o primo*
real	0m0.341s
user	0m0.340s
sys	0m0.000s

*gcc -O2 primo.c -o primo* 
real	0m0.349s
user	0m0.348s
sys	0m0.000s

*gcc -O3 primo.c -o primo* 
real	0m0.350s
user	0m0.348s
sys	0m0.000s

2. Entretanto, notou-se melhoria utilizando a otimização mtune=corei7. Outras alterações (como -m64)

*gcc -mtune=corei7 primo.c -o primo* 
real	0m0.317s
user	0m0.316s
sys	0m0.000s


3. Usando dois arquivos e mtune=corei7 não alterou significativamente o tempo médio de execução.
*Makefile:*
*all: gcc -mtune=corei7	 main.c calc_primo.c -o main*
real	0m0.327s
user	0m0.324s
sys	0m0.000s

4. Utilizando o cálculo de 1 a N, com N = 1000000 mostrou que a utilização de arquivos separados é a provável causa do aumento do tempo.
*1 arquivo até 1M*
real	2m4.757s
user	2m4.824s
sys	0m0.000s

*2 arquivos até 1M*
real	2m5.264s
user	2m5.264s
sys	0m0.064s

5. Decidiu-se utilizar apenas um arquivo com parâmetro mtune=corei7 por ter apresentado maior desempenho anteriormente. O tempo de execução para N = 1000000 onde a função primo verifica apenas número ímpares (3, 5, 7...) foi notavelmente (menos da metade) do valor anterior.
*gcc -mtune=corei7 primo.c -o primo*
real	1m20.816s
user	1m20.856s
sys	0m0.004s

6. Utilizando gprof para analisar o tempo gasto no programa, constatou-se que a função primo foi a que passou maior tempo executando (*arquivo gprof.out*).
index % time    self  children    called     name
               82.01    0.00  999999/999999      main [2]
[1]    100.0   82.01    0.00  999999         primo [1]
-----------------------------------------------
                                                 <spontaneous>
[2]    100.0    0.00   82.01                 main [2]
               82.01    0.00  999999/999999      primo [1]
-----------------------------------------------

7. Utilizando openmp para paralelizar o cálculo de primos (no loop da main), obteve-se o seguinte tempo de execução
* gcc -mtune=corei7 -fopenmp primo.c -o primo *
real	0m26.751s
user	2m9.620s
sys	0m0.016s

8. Para melhorar mais ainda o tempo de execução, o melhor candidato seria o laço de cálculo de números primos, por exemplo, substituir o limite superior, de N, pela sua raiz quadrada.






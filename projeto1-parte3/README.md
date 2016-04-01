MC723 - Laboratório de Projetos de Sistemas Computacionais
====
Campinas, 31 de março de 2016
####Professor: Lucas Wanner
####Nome: João Pedro Ramos Lopes - RA: 139546

Projeto 1: Benchmarking - Relatório
====
Objetivos:
----
1. Criar um benchmark e medir o desempenho de vários computadores
2. Definir critérios para medir o desempenho de um computador
3. Analisar resultados obtidos

Resumo
----
####Parte 1: Definição de um benchmark

O grupo (grupo 3) fez teste de benchmarking para análise do desempenho de um processador baseado em convoluções de imagens (dado o grande número de operaçõe matemáticas e a disponibilidade de paralelização) e leitura e escrita em disco utilizando a gravação e leitura no disco das imagens produzidas, obtendo as seguintes medidas:
* melhor tempo (s)	
* tempo médio (s)	
* melhor escrita (MB/s)	
* escrita média (MB/s)	
* melhor leitura (MB/s)	
* leitura média (MB/s)

####Parte 2: Medições de desempenho
Para as medições de desempenho, o grupo (grupo A) utilizou suas máquinas de configurações próximas, conforme a seguir:

1. Intel(R) Core(TM) i7-3610QM CPU 4 cores, 8 threads @ 2.30GHz, 750GB @ 5400rpm [[1]](http://www.notebookcheck.net/Intel-Core-i7-3610QM-Notebook-Processor.72681.0.html)

2. Intel(R) Core(TM) i7-3612QM CPU @ 2.10GHz x 4, 8 threads, 8GB, 64-bit, SSD 32GB, HDD1TB (5400rpm), Debian [[2]](http://www.notebookcheck.net/Intel-Core-i7-3612QM-Notebook-Processor.73465.0.html)

3. Intel(R) Core(TM) i7-4510U CPU @ 2.00GHz x 2, 4 threads, 64-bit; Memory 8 GB DDR3; HD SATA 5400rpm;Ubuntu  15.10 [[3]](http://www.notebookcheck.net/Intel-Core-i7-4510U-Notebook-Processor.115083.0.html)

Para analisar o desempenho das máquinas, utilizamos os benchmarks desenvolvidos na etapa anterior:
 * [Benchmark 1: Genetic[6]](https://github.com/pedrogrijo/MC723/tree/master/projeto1) - utiliza algoritmos genéticos para análise de processamento e teste de leitura/gravação de arquivos para velocidade de disco.
 * [Benchmark 2: ffmpeg[7]](https://github.com/RodolfoSeki/MC723/tree/master/projeto1) - utiliza um algoritmo de conversão de vídeo para análise de desempenho do processador
 * [Benchmark 3: convolução[8]](https://github.com/yugo4k/2016s1.mc723a.projeto1.parte1) - utiliza convoluções de imagens e armazenamento e leitura das imagens convoluídas para testar desempenho do disco

Análise e avaliação de desempenho (parte 3)
----
Nos gráficos a seguir, o topo da barra azul representa a média dos valores de todos os computadores que rodaram um dado benchmark [5](https://docs.google.com/spreadsheets/d/1c9JP7p0yYadZqwHrJEReNS8knAeSaMRDabaCDr-fwjg/edit#gid=0) e as cores verde, vermelho e amarelo representam respectivamente os computadores 1, 2 e 3.
####Tempo de processamento

Os resultados de tempo de processamento obtidos foram conforme esperado, dado que os três processadores possuem desempenhos próximos [[4]](http://cpuboss.com/compare-cpus). A discrepância de resulados encotrados no segundo benchmark (ffmpeg) pode ser atribuído ao fato de que o algoritmo utilizado é otimizado para certas placas de vídeo, que possivelmente influenciou no tempo de processamento. A diferença da média de desempenho encontrada no terceiro benchmark pode ser atribuída a execução de tarefas do sistema, dado que, conforme esperado, o desempenho máximo foi próximo para os 3 computadores.

[Valores menores indicam melhor desempenho]
![alt text](https://github.com/jpedrorl/MC723/blob/master/projeto1-parte3/Benchmark1(tempo).png "Benchmark1(tempo)")
![alt text](https://github.com/jpedrorl/MC723/blob/master/projeto1-parte3/Benchmark2(tempo).png "Benchmark2(tempo)")
![alt text](https://github.com/jpedrorl/MC723/blob/master/projeto1-parte3/Benchmark3(tempo).png "Benchmark3(tempo)")

####Desempenho de disco

No terceiro benchmark, o desempenho de disco foi próximo para as 3 máquinas, que possuem um HDD de 5400rpm como disco principal. Entretando, no primeiro benchmark encontramos um pico em uma das máquinas, que pode ser atribuído ao fato de utilizar apenas uma amostra na medida do desempenho do disco, podendo gerar desempenhos variados quando comparados com os valores esperados.

[Valores maiores indicam melhor desempenho]
![alt text](https://github.com/jpedrorl/MC723/blob/master/projeto1-parte3/Benchmark1(disco).png "Benchmark1(disco)")
![alt text](https://github.com/jpedrorl/MC723/blob/master/projeto1-parte3/Benchmark3(disco).png "Benchmark3(disco)")


Referências
----
1. http://www.notebookcheck.net/Intel-Core-i7-3610QM-Notebook-Processor.72681.0.html
2. http://www.notebookcheck.net/Intel-Core-i7-3612QM-Notebook-Processor.73465.0.html
3. http://www.notebookcheck.net/Intel-Core-i7-4510U-Notebook-Processor.115083.0.html
4. http://cpuboss.com/compare-cpus
5. https://docs.google.com/spreadsheets/d/1c9JP7p0yYadZqwHrJEReNS8knAeSaMRDabaCDr-fwjg/edit#gid=0
6. https://github.com/pedrogrijo/MC723/tree/master/projeto1
7. https://github.com/RodolfoSeki/MC723/tree/master/projeto1
8. https://github.com/yugo4k/2016s1.mc723a.projeto1.parte1

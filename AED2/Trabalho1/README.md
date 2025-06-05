Grupo: Letícia Souza de Souza, Marcos Paulo Vieira Pedrosa, Mikaelle Costa de Santana, Michael Willian Pereira Vieira 

Este repositório contém a implementação de três programas principais desenvolvidos como parte do Trabalho 01 da disciplina de Algoritmos e Estruturas de Dados II (AED2). Cada programa aborda um dos três primeiros tópicos solicitados, sendo eles implementados nos arquivos questao01.c, questao02.c e questao03.c, localizados na pasta src/.

A estrutura do projeto é organizada de forma modular, separando os arquivos-fonte em uma pasta src/, os arquivos de cabeçalho em include/ e os binários gerados na pasta bin/. Além dos programas principais, o projeto conta com arquivos auxiliares que implementam tipos abstratos de dados utilizados em comum pelas três questões. Esses arquivos incluem listaEncadeada.c/.h, vet.c/.h e ferramentas.c/.h, responsáveis respectivamente pelas operações com listas encadeadas, manipulação de vetores e funções de apoio.

A compilação de todos os programas pode ser feita por meio do comando make no terminal (no diretorio em que está armazenado o projeto), que utiliza o Makefile incluso no repositório. Os executáveis gerados serão armazenados na pasta bin/. Para executá-los no diretorio do projeto, basta utilizar o comando bin/questao01 ou bin/questao02 ou bin/questao03. Caso seja necessário limpar os arquivos compilados, basta executar make clean.

Cada questão ao ser executada, gerará respectivamente estes três arquivos CSV: dados_1.csv, dados_2.csv e dados_3.csv. Esses arquivos conterão os dados de cada simulação, que poderão ser usados para gerar gráficos e tabelas.

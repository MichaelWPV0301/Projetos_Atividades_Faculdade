#include "../include/arquivo.h"
#include "../include/hash.h"

// Inclui bibliotecas padrão
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Função para abrir o arquivo
FILE* abrirArquivo(const char* nomeArquivo, const char* modo) {
    FILE *arquivo = fopen(nomeArquivo, modo);
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    return arquivo;
}

// Função para fechar o arquivo
void fecharArquivo(FILE* ponteiroArquivo) {
    if (fclose(ponteiroArquivo) != 0) {
        perror("Erro ao fechar o arquivo");
        exit(1);
    }
}

// Função para escrever um registro em uma posição específica
void escreverRegistro(FILE* arquivo, Registro *reg, long offset) {
    fseek(arquivo, offset * sizeof(Registro), SEEK_SET);
    size_t tamanhoEscrito = fwrite(reg, sizeof(Registro), 1, arquivo);
    if (tamanhoEscrito != 1) {
        perror("Erro ao escrever registro no arquivo");
        exit(1);
    }
}

// Função para adicionar um registro no final do arquivo
void adicionarRegistro(FILE* arquivo, Registro *reg) {
    fseek(arquivo, 0, SEEK_END); // Mover ponteiro para o final do arquivo
    size_t tamanhoEscrito = fwrite(reg, sizeof(Registro), 1, arquivo);
    if (tamanhoEscrito != 1) {
        perror("Erro ao adicionar registro no arquivo");
        exit(1);
    }
}

// Função para ler um registro em uma posição específica
Registro lerRegistro(FILE* arquivo, long offset) {
    Registro reg;
    fseek(arquivo, offset * sizeof(Registro), SEEK_SET);
    size_t tamanhoLido = fread(&reg, sizeof(Registro), 1, arquivo);
    if (tamanhoLido != 1) {
        perror("Erro ao ler registro do arquivo");
        exit(1);
    }
    return reg;
}

// Função para ler um registro pelo número (índice)
Registro lerRegistroPorNumero(FILE* arquivo, int numeroRegistro) {
    return lerRegistro(arquivo, numeroRegistro); // reutilizando a função de ler por offset
}

// Função para obter o número total de registros no arquivo
int obterNumeroRegistros(FILE* arquivo) {
    fseek(arquivo, 0, SEEK_END); // Mover ponteiro para o final do arquivo
    long tamanhoArquivo = ftell(arquivo); // Pega o tamanho total do arquivo
    return tamanhoArquivo / sizeof(Registro); // Retorna o número de registros
}

// Popula um vetor de registros com dados aleatórios e o atributo chave único
void geraAlunos(Registro alunos[], int qtd) {
    const char *nomes[] = {"Ana", "Carlos", "Fernanda", "João", "Mariana", "Lucas", "Camila", "Gabriel", "Beatriz", "Abel",
                           "Paula", "Ricardo", "Juliana", "Pedro", "David", "Rafael", "Sophia", "Felipe", "Isabela", "Eduardo",
                           "Claudia", "Felipe", "Thiago", "Michael", "Mikaelly", "Marcos", "Natasha", "Victor", "Leticia", "Julia", "Airton"};
    const char *sobrenomes[] = {"Silva", "Souza", "Costa", "Oliveira", "Pereira", "Almeida", "Santos", "Lima", "Rocha", "Martins",
                                "Gomes", "Carvalho", "Dias", "Ferreira", "Ribeiro", "Fernandes", "Mendes", "Barbosa", "Pinto", "Nascimento",
                                "Pedrosa", "Vieira", "Sena", "Mendonça", "Medeiros", "Chaparro", "Barreto", "Moura", "Bragas Caldas", "Saraiva"};
    const char *cursos[] = {"Engenharia", "Direito", "Medicina", "Arquitetura", "Psicologia", "Sistemas de Informacao",
                            "Biologia", "Quimica", "Fisica", "Administracao", "Matematica", "Farmacia", "Enfermagem", "Pedagogia",
                            "Publicidade", "Economia", "Sociologia", "Design", "Veterinaria", "Ciencia da Computacao"};

    snprintf(alunos[0].nome, NOME_TAM, "%s %s", nomes[rand() % 31], sobrenomes[rand() % 30]);
    strcpy(alunos[0].curso, cursos[rand() % 20]);
    alunos[0].matricula = 20000000;
    alunos[0].idade = 18 + rand() % 13;
    alunos[0].coeficiente = (rand() % 1001);
    alunos[0].anoIngresso = 2015 + rand() % 10;
    for (int i = 1; i < qtd; i++) {
        // Matrícula única (exemplo: começa em 20000000 e vai incrementando)
        alunos[i].matricula = alunos[i-1].matricula + rand()%10000;
        // Nome aleatório (nome + sobrenome)
        snprintf(alunos[i].nome, NOME_TAM, "%s %s", nomes[rand() % 31], sobrenomes[rand() % 30]);
        // Curso aleatório
        strcpy(alunos[i].curso, cursos[rand() % 20]);
        // Idade entre 18 e 30 anos
        alunos[i].idade = 18 + rand() % 13;

        // Coeficiente de rendimento (CR) entre 0 e 10
        alunos[i].coeficiente = (rand() % 1001);

        // Ano de ingresso entre 2010 e 2023
        alunos[i].anoIngresso = 2010 + rand() % 14;
    }
}

void imprimeAlunos(Registro alunos[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("Matrícula: %d\n", alunos[i].matricula);
        printf("Nome: %s\n", alunos[i].nome);
        printf("Curso: %s\n", alunos[i].curso);
        printf("Idade: %d\n", alunos[i].idade);
        printf("Coeficiente de Rendimento: %.2f\n", alunos[i].coeficiente/100.0);
        printf("Ano de Ingresso: %d\n", alunos[i].anoIngresso);
        printf("------------------------------------\n");
    }
}

void imprimeAluno(Registro aluno) {
    printf("Matrícula: %d\n", aluno.matricula);
    printf("Nome: %s\n", aluno.nome);
    printf("Curso: %s\n", aluno.curso);
    printf("Idade: %d\n", aluno.idade);
    printf("Coeficiente de Rendimento: %.2f\n", aluno.coeficiente/100.0);
    printf("Ano de Ingresso: %d\n", aluno.anoIngresso);
    printf("------------------------------------\n");
}

void salvarVetorEmArquivo(Registro alunos[], FILE* arquivo, int qtd){
    for(int x = 0; x<qtd; x++){
        adicionarRegistro(arquivo, &(alunos[x]));
    }
}
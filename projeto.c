#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_ALUNOS 50

typedef struct{
        char nome[50];
        int matricula;
        float n1;
        float n2;
        float media;
} Aluno;

int menu(int qtdAlunos){
    int opcao;

    do{
        printf("======= Gerenciador de Notas =======\n");
        printf("(01) Cadastrar alunos\n");
        printf("(02) Imprimir alunos cadastrados\n");
        printf("(03) Lançar N1\n");
        printf("(04) Lançar N2\n");
        printf("(05) Calcular média\n");
        printf("(06) Calcular resultado\n");
        printf("(07) Imprimir maior nota\n");
        printf("(08) Imprimir menor nota\n");
        printf("(09) Imprimir notas em ordem crescente\n");
        printf("(10) Imprimir notas em ordem decrescente\n");
        printf("(00) Encerrar o programa\n");

        printf("Sua opção: ");
        scanf(" %d", &opcao );

        if(opcao < 0 || opcao > 10){
            printf("Opção Inválida\n\n");
        }

        if(qtdAlunos == 0 && opcao > 1 && opcao < 11){
            printf("Cadastre pelo menos um aluno antes de usar essa opção!\n");
            printf("\n\n");
            continue;
        }
        printf("\n\n");

    }while(opcao < 0 || opcao > 10);

    return opcao;

}

void cadastrarAlunos(Aluno *aluno){
    getchar();
    printf("=======Cadastro de Aluno========\n");
    printf("Pressione 0 para encerrar o cadastro.\n\n");

    do{
        printf("Digite o nome completo do aluno: ");
        fgets(aluno->nome, 50, stdin);
        do{
            printf("Digite a matrícula (4 dígitos): ");
            scanf("%d", &aluno->matricula);


            if(aluno->matricula < 1000 || aluno->matricula > 9999){
                printf("\nMatricula Inválida\n");
            }

        }while(aluno->matricula < 1000 || aluno->matricula > 9999);
    }while(aluno->matricula != 0);
}

int main(){
    int opcao;

    Aluno alunos[MAX_ALUNOS];
    int qtdAlunos = 0;

    setlocale(LC_ALL, "portuguese");

    do{
        opcao = menu(qtdAlunos);

        switch(opcao){
            case 1: cadastrarAlunos(&alunos[qtdAlunos]); break;
            case 0: printf("Programa encerrado!"); break;
        }



    }while(opcao != 0);



    return 0;
}

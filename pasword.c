//HEADER
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MIN_SENHA 5
#define MAX_SENHA 15
//

//STRUCT COM AS CATEGORIAS//
////////////////////////////

typedef struct {
    int caracteres;
    bool maiuscula;
    bool minuscula;
    bool numeros;
    bool simbolos;
} ConfigSenha;

///////////////////////////


//Fun��o para validar a op��o selecionada pelo usu�rio no menu.
bool validar_opcao_menu(int opcao){
    return(opcao != 1 && opcao!= 0);
}

//Fun��o para imprimir o menu.
void menu(){
    printf("=== GERADOR DE SENHA ===\n\n");
    printf("Por favor informe uma op��o abaixo.\n");
}

//Fun��o para capturar a op��o do usu�rio.
int capturar_opcao_menu(){
    int opcao;
    bool invalida;

    do{
        printf("Gerar nova senha (1)\n");
        printf("Encerrar programa (0)\n");
        printf("Op��o: ");
        scanf("%d", &opcao);
        invalida = validar_opcao_menu(opcao);

        if(invalida){
            printf("Op��o Inv�lida! Tente Novamente.\n\n");
        }

    }while(invalida);

    return opcao;
}

//Fun��o para validar a quantidade de caracteres min e max.
bool validar_caracteres(int caracteres){
        return (caracteres < MIN_SENHA || caracteres > MAX_SENHA);
}

//Fun��o para validar sim ou nao.
bool validar_yes_not(char opcao){
    return !(opcao == 'S' || opcao == 's' || opcao == 'N' || opcao == 'n');
}

//Fun��o para transformar a resposta do usu�rio em um booleano.
bool sim_ou_nao(char opcao) {
    return (opcao == 'S' || opcao == 's');
}

//Fun��o para o usuario personalizar a senha.
void personalizar_senha(ConfigSenha *config){
    char opcao;
    bool invalida;

    printf("\nEste programa ir� gerar uma senha segura para voc�.\n");
    printf("Basta informar as prefer�ncias abaixo.\n\n");

//Quantidade de Caracteres.
    do{
        printf("1) Quantos caracteres a senha deve ter? ");
        scanf("%d", &config->caracteres);
        invalida = validar_caracteres(config->caracteres);

        if(invalida){
            printf("O n�mero de caracteres deve ser maior que 4 e menor que 16\n\n");
        }

    }while(invalida);

//Incluir Maiusculas.
    do{
        printf("2) Incluir letras mai�sculas? (S/N): ");
        scanf(" %c", &opcao);
        invalida = validar_yes_not(opcao);

        if(invalida){
            printf("A resposta deve ser S/s ou N/n.\n\n");
        }

    }while(invalida);
    config->maiuscula = sim_ou_nao(opcao);

//Incluir Minusculas.
    do{
        printf("3) Incluir letras min�sculas? (S/N): ");
        scanf(" %c", &opcao);
        invalida = validar_yes_not(opcao);

        if(invalida){
            printf("A resposta deve ser S/s ou N/n.\n\n");
        }

    }while(invalida);
    config->minuscula = sim_ou_nao(opcao);

//Incluir N�meros.
    do{
        printf("4) Incluir n�meros? (S/N): ");
        scanf(" %c", &opcao);
        invalida = validar_yes_not(opcao);

        if(invalida){
            printf("A resposta deve ser S/s ou N/n.\n\n");
        }

    }while(invalida);
    config->numeros = sim_ou_nao(opcao);

//Incluir Simbolos.
    do{
        printf("5) Incluir s�mbolos especiais? (S/N): ");
        scanf(" %c", &opcao);
        invalida = validar_yes_not(opcao);

        if(invalida){
            printf("A resposta deve ser S/s ou N/n.\n\n");
        }

    }while(invalida);
    config->simbolos = sim_ou_nao(opcao);
}

//Fun��o para gerar a senha.
void gerar_senha(ConfigSenha *config){
    char senha[MAX_SENHA + 1] = {0};
    char pool[100] = {0};
    int pool_len = 0;

    if(config->maiuscula){
        strcat(pool, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    }

    if(config->minuscula){
        strcat(pool, "abcdefghijklmnopqrstuvwxyz");
    }

    if(config->numeros){
        strcat(pool, "0123456789");
    }

    if(config->simbolos){
        strcat(pool, "!@#$%^&*()-_=+[]{}|;:',.<>/?");
    }

    pool_len = strlen(pool);

    if(pool_len == 0){
        printf("Erro: Nenhum tipo de caractere selecionado para gerar a senha.\n");
        return;
    }

    srand(time(NULL));

    for(int i = 0; i < config->caracteres; i++){
        int pos = rand() % pool_len;
        senha[i] = pool[pos];
    }

    senha[config->caracteres] = '\0';

    printf("\nSenha gerada: %s\n", senha);

}

//Executar a opcao selecionada pelo usuario.
void executar_opcao(int opcao){
    if(opcao == 1){
        ConfigSenha config;
        personalizar_senha(&config);
        gerar_senha(&config);
    }
    else{
        printf("Programa Encerrado.\n");
    }

}

//Fun��o Principal.
int main(){
    setlocale(LC_ALL, "Portuguese");
    system("color 0A");
    int opcao;

    do{
        menu();
        opcao = capturar_opcao_menu();
        executar_opcao(opcao);
    }while(opcao != 0);

    return 0;
}

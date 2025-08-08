#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SENHA 15

//Validar a opcao do usuario
int validar_opcao_menu(int opcao){
    if(opcao > 1 || opcao < 0){
        return true;
    }else{
        return false;
    }
}

//Capturar opcao do usuario
int menu(){
    int opcao;
    bool invalida;

    printf("=== GERADOR DE SENHA ===\n\n");
    printf("Por favor informe uma opção.\n");

    do{
        printf("Gerar nova senha (1)\n");
        printf("Encerrar programa (0)\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        invalida = validar_opcao_menu(opcao);

        if(invalida){
            printf("Opção Inválida! Tente Novamente.\n\n");
        }

    }while(invalida);

    return opcao;
}

//Validar caracteres
bool validar_caracteres(int caracteres){
    if(caracteres < 1 || caracteres > 15){
        return true;
    }else{
        return false;
    }
}

//Validar sim ou não
bool validar_yes_not(int opcao){
    if(opcao == 'S' || opcao == 's' || opcao == 'N' || opcao == 'n'){
        return false;
    } else{
        return true;
    }
}

//Personalização de senha
void personalizar_senha(){
    int caracteres;
    char maiuscula, minuscula, numeros, simbolos, opcao;
    bool invalida;

    printf("\nEste programa irá gerar uma senha segura para você.\n");
    printf("Basta informar as preferências abaixo.\n\n");

    do{
        printf("1) Quantos caracteres a senha deve ter? ");
        scanf("%d", &caracteres);
        invalida = validar_caracteres(caracteres);

        if(invalida){
            printf("O número de caracteres deve ser maior que 0 e menor que 16\n\n");
        }

    }while(invalida);

    do{
        printf("2) Incluir letras maiúsculas? (S/N): ");
        scanf(" %c", &maiuscula);
        opcao = maiuscula;
        invalida = validar_yes_not(opcao);

        if(invalida){
            printf("A resposta deve ser S/s ou N/n.\n\n");
        }

    }while(invalida);

    do{
        printf("3) Incluir letras minúsculas? (S/N): ");
        scanf(" %c", &minuscula);
        opcao = minuscula;
        invalida = validar_yes_not(opcao);

        if(invalida){
            printf("A resposta deve ser S/s ou N/n.\n\n");
        }

    }while(invalida);

    do{
        printf("4) Incluir números? (S/N): ");
        scanf(" %c", &numeros);
        opcao = numeros;
        invalida = validar_yes_not(opcao);

        if(invalida){
            printf("A resposta deve ser S/s ou N/n.\n\n");
        }

    }while(invalida);

    do{
        printf("5) Incluir símbolos especiais? (S/N): ");
        scanf(" %c", &simbolos);
        opcao = simbolos;
        invalida = validar_yes_not(opcao);

        if(invalida){
            printf("A resposta deve ser S/s ou N/n.\n\n");
        }

    }while(invalida);
}

//Executar a opcao do usuario
void executar_opcao(int opcao){
    if(opcao == 1){
        personalizar_senha();
        gerar_senha();
    }
    else{
        printf("Programa Encerrado.\n");
    }

}

//Gerar senhar
void gerar_senha(){
    char senha[MAX_SENHA + 1] = {0};


}


//MAIN
int main(){
    setlocale(LC_ALL, "Portuguese");
    system("color 0A");

    int opcao = menu();
    executar_opcao(opcao);
    return 0;
}

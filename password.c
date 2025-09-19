#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>

#define MIN_SENHA 5
#define MAX_SENHA 15


// Estrutura de configuração da senha
typedef struct {
    int caracteres;
    bool maiuscula;
    bool minuscula;
    bool numeros;
    bool simbolos;
} ConfigSenha;

// Limpar o buffer do teclado(evita sujeira no scanf)
void limpar_stdin(void){
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF){ /* vazio */ }
}


// Valida opção do menu
bool validar_opcao_menu(int opcao){
    return(opcao != 1 && opcao!= 0);
}

// Menu inicial
int capturar_opcao_menu(){
    int opcao;
    bool invalida;
    int res;

    printf("=== GERADOR DE SENHA ===\n\n");
    printf("Por favor informe uma opção abaixo.\n");

    do{
        printf("Gerar nova senha (1)\n");
        printf("Encerrar programa (0)\n");
        printf("Opção: ");
        res = scanf("%d", &opcao);
        limpar_stdin();

        if(res != 1){
            invalida = true;
        } else{
            invalida = validar_opcao_menu(opcao);
        }

        if(invalida){
            printf("Opção Inválida! Tente Novamente.\n\n");
        }

    }while(invalida);

    return opcao;
}

// Valida o número de caracteres
bool validar_caracteres(int caracteres){
        return (caracteres < MIN_SENHA || caracteres > MAX_SENHA);
}

// Valida resposta S/N
bool validar_yes_not(char opcao){
    return !(opcao == 'S' || opcao == 's' || opcao == 'N' || opcao == 'n');
}

//Converte S/N em booleano
bool sim_ou_nao(char opcao) {
    return (opcao == 'S' || opcao == 's');
}

//Configuração personalizada da senha
void personalizar_senha(ConfigSenha *config){
    char opcao;
    bool invalida;
    int res;

    printf("\nEste programa irá gerar uma senha segura para você.\n");
    printf("Basta informar as preferências abaixo.\n\n");

    // Quantidade de Caracteres.
    do{
        printf("1) Quantos caracteres a senha deve ter? ");
        res = scanf("%d", &config->caracteres);
        limpar_stdin();

        if(res != 1){
            invalida = true;
        } else{
            invalida = validar_caracteres(config->caracteres);
        }

        if(invalida){
            printf("O número de caracteres deve ser maior que 4 e menor que 16\n\n");
        }

    }while(invalida);

    //Incluir Maiúsculas.
    do{
        printf("2) Incluir letras maiúsculas? (S/N): ");
        res = scanf(" %c", &opcao);
        limpar_stdin();

        if(res != 1){
            invalida = true;
        } else {
            invalida = validar_yes_not(opcao);
        }

        if(invalida){
            printf("A resposta deve ser S/s ou N/n.\n\n");
        }

    }while(invalida);
    config->maiuscula = sim_ou_nao(opcao);

    // Incluir Minúsculas.
    do{
        printf("3) Incluir letras minúsculas? (S/N): ");
        res = scanf(" %c", &opcao);
        limpar_stdin();

        if(res != 1){
            invalida = true;
        } else {
            invalida = validar_yes_not(opcao);
        }

        if(invalida){
            printf("A resposta deve ser S/s ou N/n.\n\n");
        }

    }while(invalida);
    config->minuscula = sim_ou_nao(opcao);

    // Incluir Números.
    do{
        printf("4) Incluir números? (S/N): ");
        res = scanf(" %c", &opcao);
        limpar_stdin();

        if(res != 1){
            invalida = true;
        } else {
            invalida = validar_yes_not(opcao);
        }

        if(invalida){
            printf("A resposta deve ser S/s ou N/n.\n\n");
        }

    }while(invalida);
    config->numeros = sim_ou_nao(opcao);

    //Incluir Símbolos.
    do{
        printf("5) Incluir símbolos especiais? (S/N): ");
        res = scanf(" %c", &opcao);
        limpar_stdin();

        if(res != 1){
            invalida = true;
        } else {
            invalida = validar_yes_not(opcao);
        }

        if(invalida){
            printf("A resposta deve ser S/s ou N/n.\n\n");
        }

    }while(invalida);
    config->simbolos = sim_ou_nao(opcao);
}

// Salvar senha em arquivo txt
void salvar_em_arquivo(const char *senha, const char *identificador){
    FILE *f = fopen("senhas.txt", "a");
    if(f == NULL){
        printf("Erro ao abrir arquivo para salvar senha.\n");
        return;
    }
    fprintf(f, "%s: %s\n", identificador, senha);
    fclose(f);
    printf("Senha salva em 'senhas.txt'.\n\n");
}

// Copia senha para área de transferência
void copiar_para_clipboard(const char *senha){
    #ifdef _WIN32
        char comando[300];
        snprintf(comando, sizeof(comando), "echo %s | clip", senha);
        system(comando);
        printf("Senha copiada para a área de transferência (Windows). \n\n");

    #else
        char comando[300];
        snprintf(comando, sizeof(comando), "echo -n '%s' | xclip -selection clipboard", senha);
        system(comando);
        printf("Senha copiada para a área de transferência (Linux).\n\n");
    #endif
}

// Mede a força da senha
const char* medir_forca_senha(const char *senha, ConfigSenha *config){
    int tipos = 0;

    if(config->maiuscula) tipos++;
    if(config->minuscula) tipos++;
    if(config->numeros) tipos++;
    if(config->simbolos) tipos++;

    int tamanho = strlen(senha);

    if(tipos <= 1 || tamanho < 8) return "Fraca";
    else if(tipos == 2 || tamanho < 12) return "Média";
    else return "Forte";
}

//Gera a senha com base na configuração
void gerar_senha(ConfigSenha *config, char *senha_out){
    char pool[200];
    int pool_len = 0;
    int pos = 0;

    if(config->maiuscula){
         for(char c = 'A'; c <= 'Z'; c++){
            pool[pool_len++] = c;
        }
    }

    if(config->minuscula){
        for(char c = 'a'; c <= 'z'; c++){
            pool[pool_len++] = c;
        }
    }

    if(config->numeros){
         for(char c = '0'; c <= '9'; c++){
            pool[pool_len++] = c;
        }
    }

    if(config->simbolos){
        const char simbolos[] = "!@#$%^&*?";
        for(int i = 0; i < strlen(simbolos); i++){
            pool[pool_len++] = simbolos[i];
        }
    }

    if(pool_len == 0){
        printf("Erro: Nenhum tipo de caractere selecionado para gerar a senha.\n");
        senha_out[0] = '\0';
        return;
    }

    // Garante pelo menos 1 de cada tipo escolhido
    if(config->maiuscula) senha_out[pos++] = 'A' + (rand() % 26);
    if(config->minuscula) senha_out[pos++] = 'a' + (rand() % 26);
    if(config->numeros) senha_out[pos++] = '0' + (rand() % 10);
    if(config->simbolos){
        const char simbolos[] = "!@#$%^&*?";
        senha_out[pos++] = simbolos[rand() % strlen(simbolos)];
    }

    //Preenche o resto
    while(pos < config->caracteres){
        senha_out[pos++] = pool[rand() % pool_len];
    }

    //Embaralha a senha
    for(int i = config->caracteres - 1; i > 0; i--){
        int j = rand() % (i + 1);
        char temp = senha_out[i];
        senha_out[i] = senha_out[j];
        senha_out[j] = temp;
    }

    senha_out[config->caracteres] = '\0';

    printf("\n| Senha gerada: %s |\n\n", senha_out);

    const char *forca = medir_forca_senha(senha_out, config);
    printf("Força da senha: %s\n\n", forca);

    //Opções pós-criação
    char escolha;
    printf("O que deseja fazer com a senha?\n");
    printf("[S] Salvar em arquivo\n");
    printf("[C] Copiar para área de transferência\n");
    printf("[N] Nada\n");
    printf("Opção: ");
    scanf(" %c", &escolha);
    limpar_stdin();

    if(escolha == 'S' || escolha == 's'){
        char identificador[100];
        printf("Identificador da senha: ");
        fgets(identificador, sizeof(identificador), stdin);

        identificador[strcspn(identificador, "\n")] = '\0';

        salvar_em_arquivo(senha_out, identificador);

    } else if(escolha == 'C' || escolha == 'c'){
        copiar_para_clipboard(senha_out);
    }

    else{
        printf("Senha descartada.\n\n");
    }

}

// Executa a opção do menu
void executar_opcao(int opcao){
    if(opcao == 1){
        ConfigSenha config;
        char senha[MAX_SENHA + 1];
        personalizar_senha(&config);
        gerar_senha(&config, senha);

    }
    else{
        printf("Programa Encerrado.\n");
    }

}

// Função Principal
int main(){
    setlocale(LC_ALL, "Portuguese");
    system("color 0A");
    srand(time(NULL));
    int opcao;

    do{
        opcao = capturar_opcao_menu();
        executar_opcao(opcao);
    }while(opcao != 0);

    return 0;
}

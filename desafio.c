/*
Escreva um programa que tem a estrutura de dados abaixo:
- Nome.
- Data de nascimento.
- Estado civil.
- Salário.

O programa tem as seguintes opções de menu:
1.  Entrar dados.
2.  Listar dados na tela.
3.  Pesquisar um usuário por nome.
4.  Pesquisar um usuário por estado civil
5.  Pesquisar os aniversariantes de um determinado mês.
6.  Pesquisar um usuário por faixa salarial
7.  Alterar valor do salário de um usuário
8.  Alterar dados de um usuário.
9.  Excluir dados de um usuário.
10. Saída

Todas as operações devem ser feitas direto no arquivo. (utilize a função fseek).

**Obs.:** a estrutura de dados deve ser variável local na função main().

**Obs.:** o programa deve ser finalizado pelo usuário.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dados
{
    char nome[20];
    char estado_civil[20];
    int dia_nasc;
    int mes_nasc;
    int ano_nasc;
    float salario;
};

void incluir_usuario(struct dados *inf_a_gravar, int tam);
void listar_usuarios(struct dados *inf_a_gravar, int tam);
int pesq_por_nome(struct dados *inf_a_gravar, int tam);
int pesq_por_ec(struct dados *inf_a_gravar, int tam);
int pesq_por_aniv(struct dados *inf_a_gravar, int tam);
int pesq_por_sal(struct dados *inf_a_gravar, int tam);
void alterar_usuario(struct dados *inf_a_gravar, int tam);
void alterar_salario(struct dados *inf_a_gravar, int tam);
void excluir_usuario(struct dados *inf_a_gravar, int tam);

int main()
{

    struct dados infos;    // Estrutura de dados.
    struct dados *p_infos; // Ponteiro para a struct de informações do usuário.
    int operacao;          // Operacao a ser realizada pelo usuario.
    int tam;               // N. de bytes da estrutura.

    p_infos = &infos;
    tam = sizeof(infos);

    while (1)
    {

        printf("**********************************************************************************\n");
        printf("*                    DESAFIO DE LP - REGISTROS EM ARQUIVOS                       *\n");
        printf("**********************************************************************************\n");
        printf(" 1 -Incluir usuario\n");
        printf(" 2 -Listar usuarios cadastrados\n");
        printf(" 3 -Pesquisar por nome \n");
        printf(" 4 -Pesquisar por estado civil\n");
        printf(" 5 -Pesquisar por aniversario\n");
        printf(" 6 -Pesquisar por salario\n");
        printf(" 7 -Alterar valor do salário de um usuario\n");
        printf(" 8 -Alterar dados de um usuario\n");
        printf(" 9 -Excluir usuario\n");
        printf(" 10 -Sair\n");
        scanf("%d", &operacao);
        getchar();

        switch (operacao)
        {
        case 1:
            incluir_usuario(p_infos, tam);

            system("cls");
            break;

        case 2:
            listar_usuarios(p_infos, tam);
            break;

        case 3:
            pesq_por_nome(p_infos, tam);

            printf("Digite enter para voltar ao menu:");
            getchar();

            system("cls");
            break;

        case 4:
            pesq_por_ec(p_infos, tam);
            break;

        case 5:
            pesq_por_aniv(p_infos, tam);
            break;

        case 6:
            pesq_por_sal(p_infos, tam);
            break;

        case 7:
            alterar_salario(p_infos, tam);
            break;

        case 8:
            alterar_usuario(p_infos, tam);
            break;

        case 9:
            excluir_usuario(p_infos, tam);
            break;

        case 10:
            exit(0);
            break;

        default:
            printf("\nOpcao invalida. Tente novamente.\n");
        }
    };
}

void incluir_usuario(struct dados *inf_a_gravar, int tam)
{
    FILE *arquivo, *arq_contador;
    int cont = 0;
    int i;

    arq_contador = fopen("contador.txt", "r");
    fscanf(arq_contador, "%d", &cont);
    fclose(arq_contador);

    //zera os dados da estrutura

    arquivo = fopen("usuarios.txt", "a");

    if (arquivo == NULL)
    {
        printf("\nERRO NA ABERTURA DO ARQUIVO");
        exit(1);
    }

    system("cls");

    printf("**********************************************************************************\n");
    printf("*                           INCLUIR NOVO USUARIO                                 *\n");
    printf("**********************************************************************************\n");

    //aqui os dados sao recebidos via teclado
    printf("Digite o nome do usuario:");
    gets(inf_a_gravar->nome);

    printf("Digite o estado civil do usuario:");
    gets(inf_a_gravar->estado_civil);

    do
    {
        printf("Digite o dia de nascimento do usuario:");
        scanf("%d", &inf_a_gravar->dia_nasc);
    } while (inf_a_gravar->dia_nasc > 31 || inf_a_gravar->dia_nasc <= 0);

    do
    {
        printf("Digite o mes de nascimento do usuario:");
        scanf("%d", &inf_a_gravar->mes_nasc);
    } while (inf_a_gravar->mes_nasc > 12 || inf_a_gravar->mes_nasc <= 0);

    do
    {
        printf("Digite o ano de nascimento do usuario:");
        scanf("%d", &inf_a_gravar->ano_nasc);
    } while (inf_a_gravar->ano_nasc > 2019 || inf_a_gravar->ano_nasc <= 0);

    do
    {
        printf("Digite o salario do usuario:");
        scanf("%f", &inf_a_gravar->salario);
        fflush(stdin);
    } while (inf_a_gravar->salario < 0);

    printf("\nUsuario cadastrado!\n");

    fwrite(inf_a_gravar, tam, 1, arquivo);
    fclose(arquivo);

    cont++;

    arq_contador = fopen("contador.txt", "w");
    fprintf(arq_contador, "%d", cont);
    fclose(arq_contador);
}

void listar_usuarios(struct dados *inf_a_gravar, int tam)
{
    FILE *arquivo, *arq_contador;
    int cont, comp;

    arq_contador = fopen("contador.txt", "r");
    fscanf(arq_contador, "%d", &cont);
    printf("%d\n", cont);
    fclose(arq_contador);

    arquivo = fopen("usuarios.txt", "r"); /*r" --> Abre o arquivo apenas para leitura.*/

    if (arquivo == NULL)
    {
        puts("\nERRO\n");
        exit(1);
    }

    system("cls");

    printf("**********************************************************************************\n");
    printf("*                           USUARIOS CADASTRADOS                                 *\n");
    printf("**********************************************************************************\n");
    printf("\nN. Reg\t| Nome\t\t| Estado Civil\t\t| Data de Nascimento \t| Salario \t|\n");
    printf("---------------------------------------------------------------------------------\n");

    for (int i = 0; i < cont; i++)
    {
        // Calcula o n. de bytes para posicionar o ponteiro do arquivo:
        comp = i * tam;

        // Posiciona o ponteiro no inicio do registro dentro do arquivo:
        fseek(arquivo, comp, 0);

        // Le o registro:
        fread(inf_a_gravar, tam, 1, arquivo);

        // Verifica se o mesmo esta apagado:
        if (inf_a_gravar->nome[0] != '\0')
        {
            // Imprime o registro na tela:
            printf("%-5d\t %-16s %-10s\t\t %5d/%d/%d\t\t %10.2f\n\n", i, inf_a_gravar->nome, inf_a_gravar->estado_civil, inf_a_gravar->dia_nasc, inf_a_gravar->mes_nasc, inf_a_gravar->ano_nasc, inf_a_gravar->salario);
        }
    }

    printf("Digite enter para voltar ao menu:");
    getchar();

    system("cls");

    fclose(arquivo);
}

int pesq_por_nome(struct dados *inf_a_gravar, int tam)
{
    FILE *arquivo;
    FILE *arq_contador;

    char nome1[20];
    int cont, letra;

    system("cls");

    printf("**********************************************************************************\n");
    printf("*                        PESQUISA DE USUARIO POR NOME                            *\n");
    printf("**********************************************************************************\n");

    printf("Informe um nome para pesquisar:");
    gets(nome1);

    arq_contador = fopen("contador.txt", "r");
    fscanf(arq_contador, "%d", &cont);
    fclose(arq_contador);

    arquivo = fopen("usuarios.txt", "r");

    printf("\nN. Reg\t| Nome\t\t| Estado Civil\t\t| Data de Nascimento \t| Salario \t|\n");
    printf("---------------------------------------------------------------------------------\n");

    for (int registro = 0; registro < cont; registro++)
    {
        fread(inf_a_gravar, tam, 1, arquivo);
        for (letra = 0; nome1[letra] != '\0'; letra++)
        {
            if (nome1[letra] != inf_a_gravar->nome[letra])
            {
                break;
            }
        }

        if (nome1[letra] == '\0' && inf_a_gravar->nome[letra] == '\0')
        {
            printf("%-5d\t %-16s %-10s\t\t %5d/%d/%d\t\t %10.2f\n\n", registro, inf_a_gravar->nome, inf_a_gravar->estado_civil, inf_a_gravar->dia_nasc, inf_a_gravar->mes_nasc, inf_a_gravar->ano_nasc, inf_a_gravar->salario);

            fclose(arquivo);

            return registro;
        }
    }
    printf("O registro nao existe!\n");

    return -1;
}

int pesq_por_ec(struct dados *inf_a_gravar, int tam)
{
    FILE *arquivo;
    FILE *arq_contador;

    char ec[20];
    int cont, letra;
    int registro_escolhido;
    int achou = 0;

    system("cls");

    printf("**********************************************************************************\n");
    printf("*                PESQUISA DE USUARIO POR ESTADO CIVIL                            *\n");
    printf("**********************************************************************************\n");

    printf("Informe um estado civil para pesquisar:");
    gets(ec);

    arq_contador = fopen("contador.txt", "r");
    fscanf(arq_contador, "%d", &cont);
    fclose(arq_contador);

    arquivo = fopen("usuarios.txt", "r");

    printf("\nN. Reg\t| Nome\t\t| Estado Civil\t\t| Data de Nascimento \t| Salario \t|\n");
    printf("---------------------------------------------------------------------------------\n");

    for (int registro = 0; registro < cont; registro++)
    {
        fread(inf_a_gravar, tam, 1, arquivo);
        for (letra = 0; ec[letra] != '\0'; letra++)
        {
            if (ec[letra] != inf_a_gravar->estado_civil[letra])
            {
                break;
            }
        }

        if (ec[letra] == '\0' && inf_a_gravar->estado_civil[letra] == '\0')
        {
            printf("%-5d\t %-16s %-10s\t\t %5d/%d/%d\t\t %10.2f\n\n", registro, inf_a_gravar->nome, inf_a_gravar->estado_civil, inf_a_gravar->dia_nasc, inf_a_gravar->mes_nasc, inf_a_gravar->ano_nasc, inf_a_gravar->salario);
            achou = 1;
        }
    }

    fclose(arquivo);

    if (!achou)
    {
        printf("Nao existem registros com o estado civil solicitado!\n");
        printf("Digite enter para voltar ao menu:");
        getchar();

        system("cls");
        return -1;
    }

    printf("Digite o numero do registro do usuario selecionado:");
    scanf("%d", &registro_escolhido);
    getchar();

    printf("Digite enter para voltar ao menu:");
    getchar();

    system("cls");

    return registro_escolhido;
}

int pesq_por_aniv(struct dados *inf_a_gravar, int tam)
{
    FILE *arquivo;
    FILE *arq_contador;

    int mes_aniv;
    int cont, letra;
    int registro_escolhido;
    int achou = 0;

    system("cls");

    printf("**********************************************************************************\n");
    printf("*                PESQUISA DE USUARIO POR ANIVERSARIO                             *\n");
    printf("**********************************************************************************\n");

    printf("Informe um mes (MM) para pesquisar usuarios que facam aniversario:");
    scanf("%d", &mes_aniv);
    fflush(stdin);

    arq_contador = fopen("contador.txt", "r");
    fscanf(arq_contador, "%d", &cont);
    fclose(arq_contador);

    arquivo = fopen("usuarios.txt", "r");

    printf("\nN. Reg\t| Nome\t\t| Estado Civil\t\t| Data de Nascimento \t| Salario \t|\n");
    printf("---------------------------------------------------------------------------------\n");

    for (int registro = 0; registro < cont; registro++)
    {
        fread(inf_a_gravar, tam, 1, arquivo);

        if (mes_aniv != inf_a_gravar->mes_nasc)
        {
            continue;
        }

        else
        {
            printf("%-5d\t %-16s %-10s\t\t %5d/%d/%d\t\t %10.2f\n\n", registro, inf_a_gravar->nome, inf_a_gravar->estado_civil, inf_a_gravar->dia_nasc, inf_a_gravar->mes_nasc, inf_a_gravar->ano_nasc, inf_a_gravar->salario);
            achou = 1;
        }
    }

    fclose(arquivo);

    if (!achou)
    {
        printf("Nao existem registros com o mes solicitado!\n");
        printf("Digite enter para voltar ao menu:");
        getchar();

        system("cls");
        return -1;
    }

    printf("Digite o numero do registro do usuario selecionado:");
    scanf("%d", &registro_escolhido);
    getchar();

    printf("Digite enter para voltar ao menu:");
    getchar();

    system("cls");

    return registro_escolhido;
}

int pesq_por_sal(struct dados *inf_a_gravar, int tam)
{
    FILE *arquivo;
    FILE *arq_contador;

    int sal_min, sal_max;
    int cont, letra;
    int registro_escolhido;
    int achou = 0;

    system("cls");

    printf("**********************************************************************************\n");
    printf("*                PESQUISA DE USUARIO POR SALARIO                             *\n");
    printf("**********************************************************************************\n");

    printf("Informe uma faixa salarial para realizar a pesquisa dos usuarios.\n");
    printf("Limite minimo:");
    scanf("%d", &sal_min);
    fflush(stdin);

    printf("Limite maximo:");
    scanf("%d", &sal_max);
    fflush(stdin);

    arq_contador = fopen("contador.txt", "r");
    fscanf(arq_contador, "%d", &cont);
    fclose(arq_contador);

    arquivo = fopen("usuarios.txt", "r");

    printf("\nN. Reg\t| Nome\t\t| Estado Civil\t\t| Data de Nascimento \t| Salario \t|\n");
    printf("---------------------------------------------------------------------------------\n");

    for (int registro = 0; registro < cont; registro++)
    {
        fread(inf_a_gravar, tam, 1, arquivo);

        if (inf_a_gravar->salario < sal_min || inf_a_gravar->salario > sal_max)
        {
            continue;
        }

        else
        {
            printf("%-5d\t %-16s %-10s\t\t %5d/%d/%d\t\t %10.2f\n\n", registro, inf_a_gravar->nome, inf_a_gravar->estado_civil, inf_a_gravar->dia_nasc, inf_a_gravar->mes_nasc, inf_a_gravar->ano_nasc, inf_a_gravar->salario);
            achou = 1;
        }
    }

    fclose(arquivo);

    if (!achou)
    {
        printf("Nao existem registros com o limite solicitado!\n");
        printf("Digite enter para voltar ao menu:");
        getchar();

        system("cls");
        return -1;
    }

    printf("Digite o numero do registro do usuario selecionado:");
    scanf("%d", &registro_escolhido);
    getchar();

    printf("Digite enter para voltar ao menu:");
    getchar();

    system("cls");

    return registro_escolhido;
}

void alterar_salario(struct dados *inf_a_gravar, int tam)
{
    FILE *arquivo;
    int n_reg;
    int n_bytes;

    // Pesquisa pelo nome o registro do usuario no arquivo:
    n_reg = pesq_por_nome(inf_a_gravar, tam);

    // Se o registro for encontrado:
    if (n_reg != -1)
    {
        // Determina o numero de bits para posterior uso na fseek:
        n_bytes = tam * n_reg;

        arquivo = fopen("usuarios.txt", "r+");

        // Posiciona o ponteiro do arquivo no inicio do regisro a ser alterado:
        fseek(arquivo, n_bytes, 0);

        // Le o registro do arquivo:
        fread(inf_a_gravar, tam, 1, arquivo);

        // Novos dados para o registro:
        do
        {
            printf("Digite o novo salario do usuario:");
            scanf("%f", &inf_a_gravar->salario);
            fflush(stdin);
        } while (inf_a_gravar->salario < 0);

        // Posiciona o ponteiro do arquivo no inicio do regisro a ser alterado:
        fseek(arquivo, n_bytes, 0);

        // Escreve o registro no arquivo:
        fwrite(inf_a_gravar, tam, 1, arquivo);

        fclose(arquivo);

        printf("\nUsuario alterado!\n");
        printf("Digite enter para confirmar e voltar ao menu:");
        getchar();

        system("cls");
    }
}

void alterar_usuario(struct dados *inf_a_gravar, int tam)
{
    FILE *arquivo;
    int n_reg;
    int n_bytes;

    // Pesquisa pelo nome o registro do usuario no arquivo:
    n_reg = pesq_por_nome(inf_a_gravar, tam);

    // Se o registro for encontrado:
    if (n_reg != -1)
    {
        // Determina o numero de bits para posterior uso na fseek:
        n_bytes = tam * n_reg;

        arquivo = fopen("usuarios.txt", "r+");

        // Posiciona o ponteiro do arquivo no inicio do regisro a ser alterado:
        fseek(arquivo, n_bytes, 0);

        // Le o registro do arquivo:
        fread(inf_a_gravar, tam, 1, arquivo);

        // Novos dados para o registro:
        printf("Digite o novo nome do usuario:");
        gets(inf_a_gravar->nome);

        printf("Digite o novo estado civil do usuario:");
        gets(inf_a_gravar->estado_civil);

        do
        {
            printf("Digite o novo dia de nascimento do usuario:");
            scanf("%d", &inf_a_gravar->dia_nasc);
        } while (inf_a_gravar->dia_nasc > 31 || inf_a_gravar->dia_nasc <= 0);

        do
        {
            printf("Digite o novo mes de nascimento do usuario:");
            scanf("%d", &inf_a_gravar->mes_nasc);
        } while (inf_a_gravar->mes_nasc > 12 || inf_a_gravar->mes_nasc <= 0);

        do
        {
            printf("Digite o novo ano de nascimento do usuario:");
            scanf("%d", &inf_a_gravar->ano_nasc);
        } while (inf_a_gravar->ano_nasc > 2019 || inf_a_gravar->ano_nasc <= 0);

        do
        {
            printf("Digite o novo salario do usuario:");
            scanf("%f", &inf_a_gravar->salario);
            fflush(stdin);
        } while (inf_a_gravar->salario < 0);

        // Posiciona o ponteiro do arquivo no inicio do regisro a ser alterado:
        fseek(arquivo, n_bytes, 0);

        // Escreve o registro no arquivo:
        fwrite(inf_a_gravar, tam, 1, arquivo);

        fclose(arquivo);

        printf("\nUsuario alterado!\n");
        printf("Digite enter para confirmar e voltar ao menu:");
        getchar();

        system("cls");
    }
}

void excluir_usuario(struct dados *inf_a_gravar, int tam)
{
    FILE *arquivo;
    int n_reg, n_bytes;
    char resposta;


    arquivo = fopen("usuarios.txt", "r+");

    // Pesquisa pelo nome o registro do usuario no arquivo:
    n_reg = pesq_por_nome(inf_a_gravar, tam);

    // Determina o numero de bits para posterior uso na fseek:
    n_bytes = tam * n_reg;

    // Posiciona o ponteiro do arquivo no inicio do regisro a ser alterado:
    fseek(arquivo, n_bytes, 0);

    // Le o registro do arquivo:
    fread(inf_a_gravar, tam, 1, arquivo);
    printf("O usuario a ser apagado e' %s. Confirma? (S/N)\n", inf_a_gravar->nome);
    scanf("%c", &resposta);
    fflush(stdin);

    if (resposta == 'S' || resposta ==  's')
    {
            inf_a_gravar->nome[0] = '\0';
            inf_a_gravar->estado_civil[0] = '\0';
            inf_a_gravar->dia_nasc = 0;
            inf_a_gravar->mes_nasc = 0;
            inf_a_gravar->ano_nasc = 0;
            inf_a_gravar->salario = 0;

            // Posiciona o ponteiro do arquivo no inicio do regisro a ser alterado:
            fseek(arquivo, n_bytes, 0);

            // Escreve o registro no arquivo:
            fwrite(inf_a_gravar, tam, 1, arquivo);

            fclose(arquivo);

            system("cls");


    }

    else
    {
        printf("Deseja procurar outro usuario para excluir ao inves desse? (S/N)");
        scanf("%c", &resposta);
        fflush(stdin);

        if (resposta == 'S' || resposta ==  's')
        {
            fclose(arquivo);

            excluir_usuario(inf_a_gravar, tam);
        }

        else
        {

            fclose(arquivo);

            system("cls");
        }
        
    }

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dados {
            char nome[20];
            //elementos da estrutura
            };

void inclui();
void lista();
int pesquisa();
void altera();
void exclui();

int main()
{
        struct dados info;
        struct dados *p;
        int op;
        int i;
        int tam;    //n. de bytes da estrutura

        p = & info;
        tam = sizeof(info);

        while(1){
        printf(" 1 -Inclua dados  \n");
        printf(" 2 -Lista dados  \n");
        printf(" 3 -Pesquisa dados  \n");
        printf(" 4 -Altera dados  \n");
        printf(" 5 -Exclui dados  \n");
        printf(" 6 -Saida\n");
        scanf("%d", &op);
        getchar();


    switch(op)
                {
                case 1 : inclui(p, tam);   //passa como parametro o ponteiro para a estrutura e o n. de bytes da desta
                break;

                case 2: lista(p, tam);
                break;

                case 3: pesquisa(p, tam);
                break;

                case 4: altera(p, tam);
                break;

                case 5: exclui(p, tam);
                break;

                case 6: exit(0);
                break;

                default: printf("\n opcao invalida\n");
                }
    };

}

void inclui(struct dados *ps, int tam)
{
    FILE *p, *p1;
    int cont = 0;
    int i;

    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    printf("contador antes %d\n",cont);
    fclose(p1);

    //zera os dados da estrutura

    p = fopen("arquivo.txt", "a");

    if( p == NULL){
        printf("\nERRO");
        exit(1);
    }

   //aqui os dados sao recebidos via teclado

    fwrite(ps, tam,1,p);
    fclose(p);

    cont++;

    p1 = fopen("contador.txt", "w");
    fprintf(p1,"%d",cont);
    printf("contador depois %d\n",cont);
    fclose(p1);
}

void lista(struct dados *ps, int tam)
{
    FILE *p, *p1;
    int i;
    int cont,comp;

    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    printf("%d\n",cont);
    fclose(p1);

    p = fopen("arquivo.txt", "r"); /*r" --> Abre o arquivo apenas para leitura.*/

    if( p== NULL)
        {
        puts("\nERRO\n");
        exit(1);
    }

    for(i=0;i<cont; i++){
        comp = i*tam;   //calcula o n. de bytes para posicionar o ponteiro do arquivo

    fseek(p,comp,0);    //posiciona o ponteiro no inicio do registro dentro do arquivo
    fread(ps,tam,1,p);   //le o registro
    if(ps -> nome[0] != '*'){     //verifica se esta apagado
        //imprimi registro na tela
        }
    }
        fclose(p);
}

int pesquisa(struct dados *ps, int tam)
{
    FILE *p;
    FILE *p1;

    char nome1[20];
    int i=0,y, x;
    int cont;

    printf("Informe um nome para pesquisa: ");
    gets(nome1);

    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    fclose(p1);
    printf("%d\n",cont);

    p = fopen("arquivo.txt", "r");

    for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);
        for(x = 0; nome1[x] != '\0';x++){
            if(nome1[x] != ps -> nome[x]){
                break;
            }
        }

    if(nome1[x] == '\0' && ps -> nome[x] == '\0')
    {
        printf("n. do reg.: %d\n",y);
        return y;
    }
    }
    printf("reg. nao existe\n");
    return -1;
}



void altera(struct dados *ps, int tam)
{
    FILE *p;
    int n_reg;;
    int n_bytes;

    n_reg = pesquisa(ps, tam);     //pesquisa o registro no arquivo
    printf("altera reg n.: %d\n",n_reg);
    n_bytes = tam * n_reg;

    p = fopen("arquivo.txt", "r+");

    fseek(p,n_bytes,0);       //posioiona o ponteiro do arquivo no registro a ser alterado
    fread(ps, tam, 1, p );  //le registro do arquivo

    printf("recebe os dados para alteracao: ");
    //recebe via teclado todos os dados do registro

    fseek(p,n_bytes,0);    //posiciona o ponteiro do arquivo no inicio do regisro a ser alterado
    fwrite(ps, tam,1,p);  //escreve o registro no arquivo

    fclose(p);
}

void exclui(struct dados *ps, int tam)
{
    FILE *p;
    p = fopen("arquivo.txt", "r+");
    int n_reg;
    int n_bytes;

    n_reg = pesquisa(ps, tam);  //pesquisa o registro no arquivo
    n_bytes = tam * n_reg;

    fseek(p,n_bytes,0);       //posioiona o ponteiro do arquivo no registro a ser apagado
    fread(ps, tam, 1, p );   //le o registro do arquivo
    printf("nome para apagar e' %s\n",ps -> nome);
    //apaga o registro do arquivo

    printf("nome para apagar e' %s\n",ps -> nome);

    fseek(p,n_bytes,0);  //posiciona o ponteiro do arquivo no inicio do regisro a ser apagado
    fwrite(ps,tam,1,p);  //escreve o registro

    fclose(p);

}

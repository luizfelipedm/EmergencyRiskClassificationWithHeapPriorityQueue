#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAI(i) ((i-1)/2)		    //Pai de i é i-1 divido por 2
#define F_ESQ(i) (2*i+1)                    //Filho esquerdo de i
#define F_DIR(i) (2*i+2)                    //Filho direito de i


typedef struct 
{
    char nome[20];                          //dado do item
    int chave;                              //chave do item
} Item;


typedef struct
{
    Item *v;                                // ponteiro para Item[dado,chave]
    int n, tamanho;                         // inteiros contador de Items(n) e o tamanho da estrutura alocada dinamicamente
}FP;

typedef FP * p_fp;                          // ponteiro pra FP{n,tamanho, *Item[dado,chave]}




p_fp criar_filaprio(int tam) 
 {
    p_fp fprio = malloc(sizeof(FP));        // aloca um ponteiro pra FP de tamanho (FP)
    fprio->v = malloc(tam * sizeof(Item));        // aloca um ponteiro para Item[dado,chave] dentro do FP
    fprio->n = 0;                           // inicializa contador n
    fprio->tamanho = tam;                   //define o tamanho da fila
    return fprio;                           //retorna a fila
 }

void troca(Item *x, Item *y)  // Faz a troca de dois ponteiros
{
    Item z = *x;
    *x = *y;
    *y = z;
}


void sobe_no_heap(p_fp fprio, int x) 
{
    if (x > 0 && fprio->v[PAI(x)].chave < fprio->v[x].chave) 
    {
        troca(&(fprio->v[x]), &(fprio->v[PAI(x)]));
        sobe_no_heap(fprio, PAI(x));
    }
}

void desce_no_heap(p_fp fprio, int x) 
{
 int maior_filho;
    if (F_ESQ(x) < fprio->n) {
        maior_filho = F_ESQ(x);
        if (F_DIR(x) < fprio->n && fprio->v[F_ESQ(x)].chave < fprio->v[F_DIR(x)].chave)
        {
            maior_filho = F_DIR(x);
        }
        if (fprio->v[x].chave < fprio->v[maior_filho].chave) 
        {
            troca(&(fprio->v[x]), &(fprio->v[maior_filho]));
            desce_no_heap(fprio, maior_filho);
        }
    }
}

Item extrai_maximo(p_fp fprio) 
{
    Item item = fprio->v[0];
    troca(&(fprio->v[0]), &(fprio->v[fprio->n - 1]));
    fprio->n--;
    desce_no_heap(fprio, 0);
    return item;
}


void muda_prioridade(p_fp fprio, int k, int valor) 
{
    if (fprio->v[k].chave < valor) 
    {
        fprio->v[k].chave = valor;
        sobe_no_heap(fprio, k);
    } else 
      {
        fprio->v[k].chave = valor;
        desce_no_heap(fprio, k);
      }
}

void insere_fp(p_fp fprio, Item item) 
{
    fprio->v[fprio->n] = item; //insere no final da fila
    fprio->n++;                //incrementa o contador
    sobe_no_heap(fprio, fprio->n - 1);
}


/* 
void tabela_de_cores()
{
    
    
    strcpy(cor.nome, "azul");
    cor.digcor = 1;
    cor.ini_interval = 1;
    cor.fim_interval = 99;
    cor.tmp_atend = 240;        //240 min = 4 horas
    insere_cor(cores,cor);

    strcpy(cor.nome, "verde");
    cor.digcor = 2;
    cor.ini_interval = 100;
    cor.fim_interval = 199;
    cor.tmp_atend = 120;        //120 min = 2 horas
    insere_cor(cores,cor);

    strcpy(cor.nome, "amarelo");
    cor.digcor = 3;
    cor.ini_interval = 200;
    cor.fim_interval = 299;
    cor.tmp_atend = 60;         // 60 min = 1 hora
    insere_cor(cores,cor);

    strcpy(cor.nome, "laranja");
    cor.digcor = 4;
    cor.ini_interval = 300;
    cor.fim_interval = 399;
    cor.tmp_atend = 10;         //10 min
    insere_cor(cores,cor);

}

*/

/*
int cor_atendimento(int x)
{   
    switch (x)
    {
    case 1:
        /* code */
        break;
    
    default:
        break;
    }
return x;
}
*/

void free_memo_fp(p_fp fprio)
{
    free(fprio->v);
    free(fprio);
}


int main ()
{
    int dig_cor;
    Item item;
    p_fp fp = criar_filaprio(10);
    
    
    printf("Nome do Paciente: ");
    scanf("%s",item.nome);
    printf("Cores de Atendimento: 1-Azul, 2-Verde, 3-Amarelo, 4-Laranja\n");
    printf("Opcao de Cor: ");
    scanf("%d",dig_cor);
    //cor_atendimento(dig_cor);

    free_memo_fp(fp);
    
    

    // item.chave = 1;
    // insere_fp(fp,item);


   return 0;
}


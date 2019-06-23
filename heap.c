#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAI(i) ((i-1)/2)

typedef struct
{
    char nome[20];                          //dado do Paciente
    int cor;
    int chave;                              //chave do Paciente
} Paciente;


typedef struct
{
    Paciente *p;                            // ponteiro para Paciente[dado,chave]
    int n, tamanho;                         // inteiros contador de Pacientes(n) e o tamanho da estrutura alocada dinamicamente
}PQ;

typedef PQ *P_PQ;

P_PQ criar_filaprio(int tam)
 {

    P_PQ p_pq = malloc(sizeof(PQ));            // aloca um ponteiro pra PQ de tamanho (PQ)
    p_pq->p = malloc(tam * sizeof(Paciente));  // aloca um ponteiro para Paciente[dado,chave] dentro do PQ
	p_pq->p->chave = 0;                        // inicializa a primeira chave
    p_pq->n = 0;                               // inicializa contador n
    p_pq->tamanho = tam;                       // define o tamanho da fila
    return p_pq;                               // retorna a fila
 }

void max_heapify(Paciente *vet, int i, int f)
{
    int aux = vet[i].chave;
    int j = (i * 2) + 1;
    while( j <= f )
    {
        if( j < f )
        {
            if( vet[j].chave < vet[j + 1].chave )
            {
                j = j + 1;
            }
        }
        if( aux < vet[j].chave)
        {
            vet[i].chave = vet[j].chave;
            i = j;
            j = (2 * i) + 1;
        }else
            j = f + 1;
    }
    vet[i].chave = aux;
}

void heapSort(Paciente *vet, int n)
{
    int i, aux;
    for( i = (n-1)/2; i >= 0; i--)
    {
        max_heapify(vet, i, n-1);
    }
    for( i = n-1; i >= 1; i-- )
    {
        aux = vet[0].chave;
        vet[0].chave = vet[i].chave;
        vet[i].chave = aux;
        max_heapify(vet, 0, i-1);
    }
}

int verifica_cor(int cor, int k)
{

    switch (cor)
    {
    case 1:
        k = k+800;
        break;
    case 2:
        k = k+400;
        break;
    case 3:
        k = k+200;
        break;
    default:
        break;
    }

    return k;
}

void inserir_chave(Paciente *vet,int index, int *n, int chave)
{
    
    vet[*n].chave = chave;
    (*n)++;
    max_heapify(vet,index,*n);
    heapSort(vet,*n);

}

void free_memo_fp(P_PQ p_pq)
{
    free(p_pq->p);
    free(p_pq);
}

/* 
void menu(P_PQ p_pq){
    Paciente paciente;
    paciente.chave = 0;
    int k;
    puts("\nMenu");
    puts("1- Cad Pacientes");
    puts("2- Mostrar Prox da Fila");
    puts("3- Mostrar Fila");
    puts("Pressione qualquer numero para encerrar...");
    scanf("%d",&k);
    switch (k)
    {
    case 1:
        printf("\nNome do Paciente: ");
        scanf("%s",&paciente.nome);
		p_pq->p[p_pq->n].chave = p_pq->n;
        printf("Cores de Atendimento: 1-Azul, 2-Verde, 3-Amarelo, 4-Laranja\n");
        printf("Opcao de Cor: ");
        scanf("%d", &paciente.cor);
        insere_fp(p_pq, paciente);
        menu(p_pq);
        break;
    case 2:
       // puts("mostrar proximo da fila: ");
        //printf("%d \n",remove_fp(p_pq));
        menu(p_pq);
        break;
    case 3:
        mostra_fp(p_pq);
        menu(p_pq);
        break;
    case 4:
        break;
    default:
        break;
    }
}
*/

int main()
{
    P_PQ p_pq = criar_filaprio(5);
    Paciente *pac = p_pq->p;
    int *n = &p_pq->n;

    for(int i=0; i < p_pq->tamanho; i++)
    {
        printf("Nome do paciente: ");
        scanf("%s",pac[i].nome);
        printf("Cor: ");
        scanf("%d",&(pac[i].cor));
        inserir_chave( pac, i, n, verifica_cor(pac[i].cor,i+1) );
    }

    printf("\n\nHeap Ordenada: \n");


    for(int i=0; i < p_pq->tamanho; i++)
    {
        (i > 0) ?
         printf("P[%d] index[%d]: (%d) \n", PAI(i),i,pac[i].chave)
        :printf("      Raiz[%d]: (%d) \n", i,pac[i].chave);

    }

    free(p_pq);
    return 0;
}

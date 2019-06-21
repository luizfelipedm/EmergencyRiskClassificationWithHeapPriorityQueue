#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PAI(i) ((i-1)/2)		            //Pai de i er i-1 divido por 2
#define F_ESQ(i) (2*i+1)                    //Filho esquerdo de i
#define F_DIR(i) (2*i+2)                    //Filho direito de i


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

typedef PQ *P_PQ;                          // ponteiro pra PQ{n,tamanho, *Paciente[dado,chave]}



P_PQ criar_filaprio(int tam)
 {
    P_PQ p_pq = malloc(sizeof(PQ));            // aloca um ponteiro pra PQ de tamanho (PQ)
    p_pq->p = malloc(tam * sizeof(Paciente));  // aloca um ponteiro para Paciente[dado,chave] dentro do PQ
	p_pq->p->chave = 0;                        // inicializa a primeira chave
    p_pq->n = 0;                               // inicializa contador n
    p_pq->tamanho = tam;                       // define o tamanho da fila
    return p_pq;                               // retorna a fila
 }

int irmao(int index)
{
    if(index % 2 == 0)
    {
        return index = F_ESQ(PAI(index));
    }else
    {
        return index = F_DIR(PAI(index));
    }

}


void troca(P_PQ p_pq, int index, int x)
{
    int aux;
    aux = p_pq->p[index].chave;
    p_pq->p[index].chave = p_pq->p[x].chave;
    p_pq->p[x].chave = aux;
}


void sobe_no_heap(P_PQ p_pq, int x)
{
    int index;
    index = PAI(x);
    while (index >= 0)
    {
        if(p_pq->p[x].chave < p_pq->p[index].chave)
        {
            troca(p_pq, index, x);
            x = index;
            index = PAI(x);
        }else if(p_pq->p[x].chave < p_pq->p[irmao(index)].chave)
        {
            troca(p_pq, irmao(index), x);
            x = irmao(index);
            index = PAI(x);
        }

    }

}

void desce_no_heap(P_PQ p_pq, int x)
{
 int maior_filho;
    if (F_ESQ(x) < p_pq->n) {
        maior_filho = F_ESQ(x);
        if (F_DIR(x) < p_pq->n && p_pq->p[F_ESQ(x)].chave < p_pq->p[F_DIR(x)].chave)
        {
            maior_filho = F_DIR(x);
        }
        if (p_pq->p[x].chave < p_pq->p[maior_filho].chave)
        {
            //troca(&(p_pq->v[x]), &(p_pq->v[maior_filho]));
            desce_no_heap(p_pq, maior_filho);
        }
    }
}


void muda_prioridade(P_PQ p_pq, int k, int valor)
{
    if (p_pq->p[k].chave < valor)
    {
        p_pq->p[k].chave = valor;
        sobe_no_heap(p_pq, k);
    } else
      {
        p_pq->p[k].chave = valor;
        desce_no_heap(p_pq, k);
      }
}

int verifica_cor(int cor, int k)
{

    switch (cor)
    {
    case 1:
        k = k+1500;
        break;
    case 2:
        k = k+1000;
        break;
    case 3:
        k = k+500;
        break;
    default:
        break;
    }

    return k;
}

void mostrar_k(int x, int y)
{
     printf("K:%d C:%d",x,y);
}

void insere_fp(P_PQ p_pq, Paciente paciente)
{
    (p_pq->p[p_pq->n].chave)++;
    paciente.chave = verifica_cor(paciente.cor,
    p_pq->p[p_pq->n].chave);                                        //verifica que cor a chave é
    p_pq->p[p_pq->n] = paciente;                                    //insere no final da fila
    mostrar_k((p_pq->p[p_pq->n]).chave,(p_pq->p[p_pq->n]).cor);
    (p_pq->n)++;
    sobe_no_heap(p_pq, p_pq->n-1);


}

int remove_fp(P_PQ p_pq)
{

    if (p_pq->n == 0)
    {
        perror("Fila esta vazia : ");
        return -1;
    }

    //troca(&(p_pq->v[0]), &(p_pq->v[p_pq->n - 1]));
    p_pq->n--;
    //desce_no_heap(p_pq, 0);
	printf("\nCOR: %u\n\n", p_pq->p->chave);
    return p_pq->p->chave;
}


void mostra_fp(P_PQ p_pq)
{
    printf("Fp =[ ");
    for(int i=0;i<p_pq->n;i++)
    {
        printf("K:%d C:%d ",p_pq->p[i].chave,p_pq->p[i].cor);
    }
    puts(" ]");
}


void free_memo_fp(P_PQ p_pq)
{
    free(p_pq->p);
    free(p_pq);
}


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
        puts("mostrar proximo da fila: ");
        printf("%d \n",remove_fp(p_pq));
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



int main ()
{

    P_PQ p_pq = criar_filaprio(10);
    menu(p_pq);
   // Desaloca a fila de prioridade
   free_memo_fp(p_pq);



   return 0;
}


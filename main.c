#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Tamanho do vetor 50 mil
#define TAMANHO50MIL 50000
// Tamanho do vetor 100 mil
#define TAMANHO100MIL 100000
// Tamanho do vetor 150 mil
#define TAMANHO150MIL 150000
// Tamanho do vetor 200 mil
#define TAMANHO200MIL 200000

// Função que responsável por imprimir os valores do vetor [vetor]
void escreve_vetor(int vetor[], char *msg, int tamanho) {
    int i;
    printf("*********** %i ***********\n", tamanho);
    printf("*********** %s ***********\n", msg);
    //Imprime os 10 primeiros valores do vetor
    printf("Primeiros 10 valores: \n");
    for (i=0; i<10; i++)
        printf("%d ", vetor[i]);
    printf("\n");
    //Imprime os 10 últimos valores do vetor
     printf("Ultimos 10 valores: \n");
    for (i=0; i<10; i++){
    	int j = tamanho - 1 - i;
        printf("%d ", vetor[j]);
	}
    printf("\n\n");
}

// Função responsável por gerar um vetor de tamanho [tamanho]
int *gerarVetorAleatorio(int tamanho) {
	 // Aloca memória para o vetor
    int *v = (int *)malloc(tamanho * sizeof(int));
    if (v == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
	// Inicializa a semente para gerar números aleatório
    srand(time(NULL));
    int i;
    // Preenche o vetor com valores aleatórios entre 1 e 10
    for (i = 0; i < tamanho; ++i) {
    	v[i] = rand() % 10 + 1;
    }
    // Imprime o vetor criado
    escreve_vetor(v, "VETOR CRIADO", tamanho);
	// Retorna o ponteiro para o vetor gerado
    return v;
}

void escreve_relatorio(clock_t inicio, clock_t fim, char *metodo, int tamanho) {
	double diferenca = (fim - inicio) / (CLOCKS_PER_SEC/1000);
	printf("Vetor %i metodo: %s\n", tamanho, metodo);
	printf("Tempo de execucao: %10.4f ms\n", diferenca);
}

// Função responsável por ordenar vetor através do método bubble sort
void bubble_sort(int vetor[], int tamanho) {
	clock_t inicio, fim;
	// Captura o tempo inicial
	inicio = clock();
    int i,j,aux;
    for (i=1; i < tamanho; i++) {
       for (j=0; j< tamanho-i;j++) {
          if (vetor[j]>vetor[j+1]) {
             aux = vetor[j];
             vetor[j] = vetor[j+1];
             vetor[j+1] = aux;
          }
       }
   }
   // Captura o tempo final
   fim = clock();  
   escreve_relatorio(inicio, fim, "Bubble Sort", tamanho);
}


// Função responsável por ordenar vetor através do método selection sort
void selection_sort(int vetor[], int tamanho) {
	clock_t inicio, fim;
	// Captura o tempo inicial
	inicio = clock();
     int i, j, menor, aux;
     for (i=0; i< tamanho; i++) {
          menor  = i;
          for (j=i+1; j< tamanho; j++) {
            if (vetor[j] < vetor[menor])
              menor = j;
          }
          aux = vetor[menor];
          vetor[menor] = vetor[i];
          vetor[i] = aux;
     }
    // Captura o tempo final
   	fim = clock();
   	escreve_relatorio(inicio, fim, "Selection Sort", tamanho);
}

// Função responsável por ordenar vetor através do método insertion sort
void insertion_sort(int vetor[], int tamanho) {
    clock_t inicio, fim;
    inicio = clock();
    int i,j,key;
    for (j=1; j<tamanho; j++) {
      key = vetor[j];
      i = j-1;
      while (i >= 0 && vetor[i] > key) {
        vetor[i+1] = vetor[i];
        i = i-1;
      }
      vetor[i+1] = key;
    }
    fim = clock();
   	escreve_relatorio(inicio, fim, "Insertion Sort", tamanho);
}

// Algoritmo que utiliza a estrategia do merge para ordenar o vetor.
void merge(int A[], int p, int q, int r) {
  int i,j,k,n1,n2;
  n1 = q - p + 1;
  n2 = r - q;

  int L[n1+1];
  int R[n2+1];

  for (i=0; i<n1; i++)
    L[i] = A[p+i];

  for (j=0; j<n2; j++)
    R[j] = A[q+j+1];

  L[n1] = 999999;
  R[n2] = 999999;

  i = 0; j = 0;
  for (k=p; k<=r; k++) {
    if (L[i] <= R[j]) {
        A[k] = L[i];
        i++;
    }
    else {
        A[k] = R[j];
        j++;
    }
  }
}

// Função responsável por ordenar vetor através do método merge sort
void merge_sort(int A[], int p, int r) {
  	int q;
  	q = (p+r)/2;
  	if (p < r) {
	    merge_sort(A,p,q);
	    merge_sort(A,q+1,r);
	    merge(A,p,q,r);
	}
}

// Função responsável por realizar a chamado do merge_sort e registra período de execução
// Motivo de não ser chamado o merge_sort de forma direta: Por existir uma recursividade o timer implementado dentro do método iria gerar problemas.
void chama_merge_sort(int vetor[], int p, int r, int tamanho) {
	clock_t inicio, fim;
	inicio = clock();
	merge_sort(vetor, p, r);
	fim = clock();
	escreve_relatorio(inicio, fim, "Merge Sort", tamanho);
}

// Função responsável por ordenar vetor através do método shell sort
// Vetor a ser ordenado [vetor]
// Tamanho do vetor [tamanho]
void shell_sort(int vetor[], int tamanho) {
	clock_t inicio, fim;
	inicio = clock();
    int intervalo, i, j, temp;
    // Inicializa o intervalo como metade do tamanho do array e divide por dois até que intervalo == 1
    for (intervalo = tamanho / 2; intervalo > 0; intervalo /= 2) {
    	// Percorre o array a partir do intervalo, ou seja, divide o vetor em sub vetores os quais terão os valores das posições nos intervalos de n
        for (i = intervalo; i < tamanho; i++) {
        	// Move os elementos maiores que o valor atual para a frente
            temp = vetor[i];
            for (j = i; j >= intervalo && vetor[j - intervalo] > temp; j -= intervalo) {
                vetor[j] = vetor[j - intervalo];
            }
             // Insere o valor atual na posição correta
            vetor[j] = temp;
        }
    }
    fim = clock();
    escreve_relatorio(inicio, fim, "Shell Sort", tamanho);
}

/**
* Projeto final da cadeira de Banco de Dados 1
* Este arquivo é o responsável por realizar a execução do métodos de ordenação e de registro de tempo de execução.
*/
int main(int argc, char *argv[]) {
	//Realiza a criação do vetores
    int *vetor50Mil = gerarVetorAleatorio(TAMANHO50MIL);
    int *vetor100Mil = gerarVetorAleatorio(TAMANHO100MIL);
    int *vetor150Mil = gerarVetorAleatorio(TAMANHO150MIL);
    int *vetor200Mil = gerarVetorAleatorio(TAMANHO200MIL);
	int vetorExemplo[] = {9,8,7,6,5,4,3,2,1,0};
	
/**
* MÉTODOS COMENTADOS PARA QUE ORDERANEMENTO ANTERIOR NÃO INFLUENCIE OS POSTERIORES
*/

    //Realiza o ordenamento através do método bubble sort
//	bubble_sort(vetor50Mil, TAMANHO50MIL);
//	bubble_sort(vetor100Mil, TAMANHO100MIL);
//	bubble_sort(vetor150Mil, TAMANHO150MIL);
//	bubble_sort(vetor200Mil, TAMANHO200MIL);
    
    //Realiza o ordenamento através do método selection sort
//	selection_sort(vetor50Mil, TAMANHO50MIL);
//	selection_sort(vetor100Mil, TAMANHO100MIL);
//	selection_sort(vetor150Mil, TAMANHO150MIL);
//	selection_sort(vetor200Mil, TAMANHO200MIL);
	
	//Realiza o ordenamento através do método insertion sort
//	insertion_sort(vetor50Mil, TAMANHO50MIL);
//	insertion_sort(vetor100Mil, TAMANHO100MIL);
//	insertion_sort(vetor150Mil, TAMANHO150MIL);
//	insertion_sort(vetor200Mil, TAMANHO200MIL);

    //Realiza o ordenamento através do método insertion sort
//    chama_merge_sort(vetor50Mil, 0, TAMANHO50MIL-1, TAMANHO50MIL);
//    chama_merge_sort(vetor100Mil, 0, TAMANHO100MIL-1, TAMANHO100MIL);
//    chama_merge_sort(vetor150Mil, 0, TAMANHO150MIL-1, TAMANHO150MIL);
//    chama_merge_sort(vetor200Mil, 0, TAMANHO200MIL-1, TAMANHO200MIL);

    //Realiza o ordenamento através do método shell sort
    shell_sort(vetor50Mil, TAMANHO50MIL);
    shell_sort(vetor100Mil, TAMANHO100MIL);
    shell_sort(vetor150Mil, TAMANHO150MIL);
    shell_sort(vetor200Mil, TAMANHO200MIL);
    
    return 0;
}

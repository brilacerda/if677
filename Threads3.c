#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t sinal[10000000];
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;

int nArquivos, nThreads, nProdutos, cont = 1;
int armazena[10000000];

//vai receber o número do arquivo que vai ler
//transformar o número do arquivo em string
//abre e lê
void ler (int a){
	FILE* va;
	int n, aux, pos;
	char nome[14];
	int leitura;
	nome[10]='.';
	nome[11]='i';
	nome[12]='n';
	nome[13]='\0';
	
	pos=9;
	n=a;
	while(n>0){
		aux=n%10;	
		n = n/10;
		nome[pos]=aux+'0';
		pos--;
	
	   va=fopen(nome+pos+1,"r");
	
	   while(fscanf(va,"%d", &leitura) > 0)
	   {
	      pthread_mutex_lock(&sinal[leitura]);
	      armazena[leitura]++; 
	      pthread_mutex_unlock(&sinal[leitura]); 
	      //printf("no arquivo %d eu li: %d\n",a,leitura);
	   }
	   fclose(va);
	}
	return;
}

//lê da variável global pra saber qual o próximo arquivo poderá ser lido
//trava essa variável pra que apenas uma thread pegue determinado número
void * f(void * arg){
	int n;
	
	pthread_mutex_lock(&mymutex); 
		
	while(cont < nArquivos){
		n = cont;
		cont++;
		pthread_mutex_unlock(&mymutex);
		ler(n);
		
		pthread_mutex_lock(&mymutex); 
	}
	pthread_mutex_unlock(&mymutex);
}
 
 

//lê entraada, cria threads e mutexes e printa a saída
int main(){
	int i, arquivos;
	scanf(" %d %d %d", &arquivos, &nThreads, &nProdutos);

	nArquivos = arquivos;
	
	pthread_t thread[nThreads];
	
	for(i=0; i< 10000000;i++){
	   pthread_mutex_init(&sinal[i], NULL);
	}
	
	for(i=0; i<nThreads; i++) {
	   pthread_create(&thread[i], NULL, f, NULL);
	}
	for(i=0; i<nThreads; i++) {
	   pthread_join(thread[i], NULL);
	}
	
	int sum = 0, percent = 0;
	for(i=0; i<=nProdutos; i++){
	    sum += armazena[i];
	    //printf("%d ", armazena[i]);
	}
	
	for(i=0; i<=nProdutos; i++){
	    printf("%05.2lf%% (%d itens) do produto %d\n",
	         (armazena[i] * 100.0)/sum,
	         armazena[i],
	         i);
	    //printf("%d \n", sum);
	}
	
	puts("");
	printf("Sum: %d\n", sum);
		
	//quando terminar tudo imprime na tela o total de produtos lidos e o percentual de cada tipo de produto vendido
	
	return 0;
}
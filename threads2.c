#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int nThreads;
int n1, n2, qtdEquipe, qtdMembro;
int array[10000000][2];
pthread_mutex_t mymutex;
pthread_t* thread;

//pelo algoritmo de euclídes

int mdc (int n1, int n2){
   int  resto;
   //garantindo que o maior vai ser dividido pelo menor
   
   if(n2 > n1){
      resto = n1;
      n1 = n2;
      n2 = resto;
   }
    resto = n1%n2;
   
   //O resultado é o divisor da divisão cujo resto é zero.
   while(resto!=0)
   {
      n1    = n2;
      n2    = resto;
      resto = n1%n2;        
   }
   return  n2;
}

//calcula o mdc e retorna o resultado da soma do turno.
void * aux (void * arg){
	int id = (int) arg;

	pthread_mutex_lock(&mymutex); 
	 
	int k, result = 0;	  
   
   for(k = id; k < (qtdEquipe*qtdMembro); k+=qtdMembro)
   {	
		result += mdc (array[k][0], array[k][1]);
   }
	id++;
	
	if(id != 0)
      pthread_join(thread[id-1], NULL);
	
	//printf("%dº turno: %d\n", id, result);
	pthread_mutex_unlock(&mymutex); 
	
	return result;
}

//foi criado um array de duas posições pra guardar todas as entradas e só depois calcular o mdc
int main (int argc, char **argv){
   
   int result, i, k;
   
   scanf ("%d %d", &qtdEquipe, &qtdMembro);
   nThreads = qtdMembro;
   
   thread = (pthread_t*) malloc(nThreads * sizeof(pthread_t));
      
   for (i = 0;i < qtdEquipe*qtdMembro;i++) 
   { 
        scanf("%d %d", &array[i][0], &array[i][1]); 
   }
	
	pthread_mutex_init(&mymutex, NULL);

   for(i=0; i<nThreads; i++) {
        pthread_create(&thread[i], NULL, aux, (void*) i);
    }
    
    //foi pesquisado e visto que o segundo parâmetro do join é o retorno da tarefa das threads.
    for(i=0; i<nThreads; i++) {
        void* ans;
        pthread_join(thread[i], &ans);
        printf("%dº turno: %d\n", i, (int)ans);
    }
    
    free(thread);
      
    pthread_exit(NULL);

   return 0;
}


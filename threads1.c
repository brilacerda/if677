#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
Testes de tempo com números de Threads diferentes.

senha: 3465926403
#threads 10
real	0m5.406s

senha: 3465926403
#threads 1
real	0m21.7566s

senha: 3465926403
#threads 4
real	0m5.577s

senha: 3465926403
#threads 8
real	0m5.179s
*/

char password[] = "9999999999";
long long size = 10000000000;
long long senhaInt = 0;
long long resDiv = 0;
#define nThreads 8
pthread_t thread[nThreads];
long long limit;

//através do número da thread foi criado um limite superior e um inferior de busca da senha
void * f (void *arg)
{
	long long numT = (long long) arg;
	long long j;
	long long inf = resDiv*numT;
	long long sup = inf + resDiv-1;
   printf("Testei de %lld ate %lld senha=%lld\n",inf,sup,senhaInt);
	if(numT==nThreads-1){
		sup = 9999999999;
	}

	for (j = inf; (j <= sup); j++)
	{
		if (senhaInt == j){
		printf ("YAY! A Thread %lld encontrou a senha %lld \n", numT, j);
		}
	}
	printf ("Não encontrei nada. sou # %lld\n", numT);
}

char transformIntToChar(int val)
{
	val = val + 48;
	return (0 + val);
}

/*	
//eleva as coisas
long long power (int pow)
{
	int j;
	if (pow == 0)
	{
		return 1;
	} else {
		long long result = 1;

	   for (j = 0; j < pow; j++)
	   {
		   result = result * 10LL;
	   }

      return result;
   }
} */

long long transformPassWordToInt (){
	long long i;
   senhaInt = 0;
	for (i = 0; i < password[i]!='\0'; i++)
	{
	   senhaInt*=10LL;
	   senhaInt+=(long long)(password[i]-'0');
		// if(i != 10) senhaInt = senhaInt + ((long long int) (password[i] - '0'))*(power (9-i));
		
	}
}

void criaThreads (){
	
	long long i;
	for (i = 0; i < nThreads; i++)
	{
		pthread_create(&thread[i], NULL, *f, (void *) i);
	}

	for (i = 0; i < nThreads; i++)
	{
		pthread_join(thread[i], NULL);
	}
}

int main()
{
	int i;

	resDiv = (size/nThreads);

	transformPassWordToInt();

	criaThreads();

	pthread_exit(NULL);

	return 0;
}

//#48-57 == 0-9 em ascii
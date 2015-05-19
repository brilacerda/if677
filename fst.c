#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_THREADS 10
#define PASSWORD "8"

pthread_t pt1;

void try1 (){
	int i;
	for (i = 0; i < 10; ++i)
	{
		printf("%c\n", toString(i));
	}
}

//mensagens de erro creio eu
char *msg1 = "Problema na pt1"

int main(){
	pthread_create(&pt1, NULL, (void*)try1, &msg1)
	t1.join(); 

	//pthread_t thread[NUMBER_OF_THREADS];

	return 0;
}
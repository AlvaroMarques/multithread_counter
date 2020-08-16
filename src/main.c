/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int e_primo(unsigned int n){
	if (n == 1) return 0;
	if (n == 2) return 1;
	if (n % 2 == 0) return 0;
	unsigned int tmp = n/3;
	while (tmp > 2){
		if (n % tmp == 0){
			return 0;
		}
		tmp--;
	}
	return 1;
}

typedef struct {
	int *n;
	int *primes;
	int size;
} Args;

void *thread_function(void *args);

int main() {

  int x;
  int *nums = (int*) malloc(0 * sizeof(int));
  int size = 0;
  int *n = malloc(0 * sizeof(int));
  int *primes = malloc(0*sizeof(int));
  while (scanf("%d", &x) != EOF) {
	  n = realloc(n, ++size * sizeof(int));
	  n[size-1] = x;		
	  primes = realloc(primes, size * sizeof(int));
	  primes[size-1] = -1;		
  }
  
  Args *args = malloc(sizeof(Args));

  args->n = n;
  args->primes = primes;
  args->size = size;

  pthread_t threads[4];

  pthread_create(&(threads[0]), NULL, thread_function,(void*) args); 
  pthread_create(&(threads[1]), NULL, thread_function,(void*) args); 
  pthread_create(&(threads[2]), NULL, thread_function,(void*) args); 
  pthread_create(&(threads[3]), NULL, thread_function,(void*) args); 

  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  pthread_join(threads[2], NULL);
  pthread_join(threads[3], NULL);

  unsigned int c = 0;
  int i;
  for (i = 0; i < size; i++){
	  c += primes[i];
  }
  printf("%u\n", c);

  free(n);
  free(primes);
  return 0;
}

void *thread_function(void *args){
	int *n = ((Args*) args)->n;
	int *primes = ((Args*) args)->primes;
	int size = ((Args*) args)->size;
	int i;
	for (i = 0; i < size; i++){
	  if (primes[i] == -1){
		primes[i] = e_primo(n[i]);
	  }
	}
	return NULL;

}

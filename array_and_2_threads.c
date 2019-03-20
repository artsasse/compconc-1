#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMERO 15

typedef struct {
   int inicio, fim;
   int *myArray;
} t_Args;

void *soma (void *arg) {
  t_Args* args = (t_Args*)arg;
  int i = args->inicio;
  int f = args->fim;
  args->myArray = args->myArray + i;
  printf("COMEÇOU a thread de %d a %d\n", args->inicio, f);
  for(i; i < f; i++){
    //printf("era %d\n", *args->myArray);
    *args->myArray = *args->myArray + 1;
    //printf("agora ficou %d\n", *args->myArray);
    args->myArray++;
  }
  free(arg);
  printf("TERMINOU a thread de %d a %d\n", args->inicio, f);
  pthread_exit(NULL);
}

int main(){
  pthread_t tid_sistema[2];
  t_Args *arg;
  int myArray[NUMERO] = {};
  int i;

  for(i = 0; i < NUMERO; i++){
    myArray[i] = i;
    printf("%d\n", myArray[i]);
  }
  printf("------\n");

  //calcula uma metade
  arg = malloc(sizeof(t_Args));
  if (arg == NULL) {
    printf("--ERRO: malloc()\n"); exit(-1);
  }
  arg->inicio = 0;
  arg->fim = NUMERO/2;
  arg->myArray = (int*)myArray;

  if (pthread_create(&tid_sistema[0], NULL, soma, (void*) arg)) {
    printf("--ERRO: pthread_create()\n"); exit(-1);
  }

  //calcula outra metade
  arg = malloc(sizeof(t_Args));
  if (arg == NULL) {
    printf("--ERRO: malloc()\n"); exit(-1);
  }
  arg->inicio = NUMERO/2;
  arg->fim = NUMERO;
  arg->myArray = (int*)myArray;

  if (pthread_create(&tid_sistema[1], NULL, soma, (void*) arg)) {
    printf("--ERRO: pthread_create()\n"); exit(-1);
  }

  //confirma que as threads terminaram
  for (i=0; i<2; i++) {
    if (pthread_join(tid_sistema[i], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1);
    }
  }

  //imprime os numeros alterados
  for(i = 0; i < NUMERO; i++){
    printf("%d\n", myArray[i]);
  }
  printf("------\n");

  printf("--Thread principal terminou\n");
  pthread_exit(NULL);
}

//Modificacoes a fazer:
//- criar um for pra nao repetir a parte de criar uma thread
//- permitir que o programa divida a soma em N threads, em vez de apenas 2.

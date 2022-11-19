#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


long double fatorial(int n){
    if (n == 0){
        return 1;
    }
    long double res = 1;
    for (long double i = 1; i <= n; i++){
            res *= i;
        }
    return res;
}

int main(int  argc, char *argv[])
{
    long double res = 0.0; //inicializando res
    
    int iteracoes = atoi(argv[1]);
    int qtd_thread = atoi(argv[2]);
    
    // ZONA PARALELA ABAIXO
    #pragma omp parallel num_threads(qtd_thread) reduction(+: res) //diretiva de compilação do openmp com a qtd de threads e o reduction para a zona crítica
    {   
      
      int id_thread = omp_get_thread_num();
      int qtd_thread = omp_get_num_threads();
    
    
      long int i;
    
      // As threads vão intercalar o cálculo baseado em seu id
      for(i = id_thread; i < iteracoes; i = i+qtd_thread){
          res += 1.0/fatorial(i);   
          if (res == 2.718281828459045235645008542491){ // Limite do fatorial para long double 
              printf("\nA iteração em que res converge é %ld",i);
          }    
      }
    }
    // SAIU DA ZONA PARALELA
    printf("\nResultado com %d iteracoes: %0.30Lf\n", iteracoes, res);   
}

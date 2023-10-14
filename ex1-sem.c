/*
 * Trabalho 2 PCD - Ex 1 - Seção Crítica por espera ocupada (sem controle de seção crítica)
 * Nome: Rodrigo Peixe Oliveira
 * RA: 147873
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void) {
    int SOMA = 0, finished = 0, request = 0, respond = 0;
    int total_threads = 6, target_number = 10000;

    omp_set_num_threads(total_threads);
    omp_set_nested(1);

    #pragma omp parallel num_threads(2)
    {

        if (omp_get_thread_num() == 0) {
            // Thread servidor
            while (finished == 0) {
                while (request == 0 && finished == 0);
                if (finished == 1) {
                    break;
                }
                respond = request;
                while (respond != 0);
                request = 0;
            }
        }

        else {
            #pragma omp parallel num_threads(total_threads-1)
            {
                // Thread cliente
                int thread_id = omp_get_thread_num() + 1;
                int local;
                int i, j;
                
                #pragma omp for private (i, j, local)
                for (i = 0; i < target_number; i++) {
                    local = SOMA;
                    for (j = 0; j < 100; j++) {
                        SOMA = j;
                    }
                    SOMA = local + 1;
                }
            }

            finished = 1;
        }
    }

    printf("Soma: %d\n", SOMA);

    return 0;
}
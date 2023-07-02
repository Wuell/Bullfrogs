#include <stdio.h>
#include <stdlib.h>
#include "../matrizes/Matrizes.h"
#include "Pds_telecom.h"
#include <time.h>

void rx_qam_demapper(bfgs_vector complex_vector)
{
    int *int_vector = malloc(sizeof(int)*4);

    for (int i = 0;i < 4; i++)
    {
        if(vector_get(complex_vector,i).re != 0 && vector_get(complex_vector,i).im != 0)
        {

            if(vector_get(complex_vector,i).re == -1 && vector_get(complex_vector,i).im == 1)
                int_vector[i] = 0;

                else if(vector_get(complex_vector,i).re == -1 && vector_get(complex_vector,i).im == -1)
                    int_vector[i] = 1;

                    else if(vector_get(complex_vector,i).re == 1 && vector_get(complex_vector,i).im == 1)
                        int_vector[i] = 2;

                        else if (vector_get(complex_vector,i).re == 1 && vector_get(complex_vector,i).im == -1)
                            int_vector[i] = 3;
        }
        else
        {
            printf ("A função QAM_MAPPER não conseguiu rodar devido a falta de dados\n"); 
            break;   
        }
    }

    for (int j = 0;j < 4; j++)
        printf("%d\n",int_vector[j]);
}
 
void verify_nstreams(int Nt,int Nr, int Nstreams)
{

    int aux;

    aux = Nt;

    if(Nr <= Nt)
        aux = Nr;

    if(aux < Nstreams){
        printf("O Numero de stream nao pode ser maior que o valor minimo entre Nt e Nr. Altere o valor de Nstreams.\n");
        exit(0);
    }

}

void tx_layer_mapper(bfgs_vector Vector_QAM,int Nstreams,int NTransmissions)
{

    bfgs_matrix Matrix_QAM = matrix_alloc(Nstreams,NTransmissions);
    int index = 0;

        for(int i = 0; i < Nstreams ; i++){
            for(int j = 0; j < NTransmissions; j++)
            {

                matrix_change(Matrix_QAM,i,j,Vector_QAM.data[index]);
                index++;
            }            
        }

    matrix_print(Matrix_QAM);
    matrix_free(Matrix_QAM);
} 

bfgs_vector random_vector_com(int len,int intervalMod){

    bfgs_vector vector;
    srand(time(0));
    int range = intervalMod*2 + 1;

    vector = vector_alloc(len);

    for(int i = 0; i < len; i++){
        vector_change(vector,i,(complexo){rand() % (range - intervalMod),rand() % range - intervalMod});

    }
    return vector;
}
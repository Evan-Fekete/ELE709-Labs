#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

int matrix_A[18][16];
int matrix_B[16][18];
int matrix_C[18][18];


struct thread_info {
    int row, column; // row and column
};

typedef struct thread_info thread_info_t;

void *func(void *arg)
    {

	thread_info_t *info;

	info = (thread_info_t *)arg;

	int row, column;

	row = info->row;
	column = info->column;
	compute_C_ij(row, column);


    pthread_exit(NULL);
    
}

void compute_C_ij(int row, int column){

	matrix_C[row][column] = 0;

	for(int k = 0; k < 16;k++){

	matrix_C[row][column] += matrix_A[row][k] * matrix_B[k][column];

}

}

void matrix()
{
printf("Matrix A: \n");
for(int i=0; i < 18; i++){
	for(int j=0; j < 16; j++){
	
	matrix_A[i][j] = (i+1)+(j+1);
	printf("%d ", matrix_A[i][j]);
	}
printf("\n");
}

printf("****************************************************\n");
printf("Matrix B: \n");
for(int i=0; i < 16; i++){
	for(int j=0; j < 18; j++){
	
	matrix_B[i][j] = (i+1)+2*(j+1);
	printf("%d ", matrix_B[i][j]);
	}
printf("\n");

}


}

int main(void)
{
    pthread_t thread[18][18];
    thread_info_t *info[18][18];

    matrix();

   for(int i = 0; i < 18;i++){

	for(int j = 0; j < 18;j++){

	info[i][j] = malloc(sizeof(thread_info_t));
	info[i][j]->row = i;
	info[i][j]->column = j;
	

	if (pthread_create(&thread[i][j], NULL, &func, info[i][j]) != 0) {
            printf("Error in creating thread [%d][%d]\n",i,j);
            exit(1);
        }

	}

	}

 for(int i = 0; i < 18;i++){

	for(int j = 0; j < 18;j++){
	pthread_join(thread[i][j], NULL);
	}
 }
printf("****************************************************\n");
printf("Matrix C: \n");
 for(int i = 0; i < 18;i++){

	for(int j = 0; j < 18;j++){
	printf("%d ", matrix_C[i][j]);
	}
 printf("\n");
 }

 for(int i = 0; i < 18;i++){

	for(int j = 0; j < 18;j++){
	free(info[i][j]);
	}
 }


    return 0;
}

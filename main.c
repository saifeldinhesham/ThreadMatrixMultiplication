#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int x,r1,r2,c1,c2;


            int **a;
	    int  **b;
	    int **mult; //dynamic allocation to matrix as global variables
           
 

void *runner(void *param); 


int main() {

   int i,j, count = 0;

printf("enter rows of first matrix: ");
scanf("%d",&r1);

printf("enter columns of first matrix: ");
scanf("%d",&c1);
printf("enter rows of second matrix: ");

scanf("%d",&r2);
printf("enter columns of second matrix: ");
scanf("%d",&c2);


	a=(int **)malloc( r1*sizeof(int *));// creation of matrix according to input rows and columns
	for(i=0;i<r1;i++){
	a[i]=(int *)malloc( c1*sizeof(int ));

	}

	b=(int **)malloc( r2*sizeof(int *));
	for(i=0;i<r2;i++){
	b[i]=(int *)malloc( c2*sizeof(int ));

	}

        mult=(int **)malloc( r1*sizeof(int *));
	for(i=0;i<r1;i++){
	mult[i]=(int *)malloc( c2*sizeof(int ));
	}
//creating matrix A and B
 for(i = 0; i < c1; i++) {
      for(j = 0; j < r1; j++) {
srandom(time(NULL));
a[i][j]=rand()%10;
}
}

for(i = 0; i < c1; i++) {
      for(j = 0; j < r1; j++) {
srandom(time(NULL));
b[i][j]=rand()%10;
}
}


//print matrix A and B
printf("Matrix A: \n");
for(i = 0; i < r1; i++) {
      for(j = 0; j < c2; j++) {
         printf("%d ",a[i][j]);
      }
      printf("\n");
   }


printf("Matrix B: \n");

for(i = 0; i < r2; i++) {
      for(j = 0; j < c2; j++) {
         printf("%d ", b[i][j]);
      }
      printf("\n");
   }

// calculation of time before prog
struct timespec starttime, endtime, ttime;
    double timeinterval;
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &starttime);

int size;
   for(i = 0; i < r1; i++) {
  
         pthread_t tid;       //Thread ID
         pthread_attr_t attr; //Set of thread attributes
         //Get the default attributes
         pthread_attr_init(&attr);
         //Create the thread
	x=i;

         pthread_create(&tid,&attr,runner,NULL);//thread creation
         //Make sure the parent waits for all thread to complete
         pthread_join(tid, NULL);

         count++;
      
   }
//time after
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endtime);
    ttime.tv_sec = endtime.tv_sec - starttime.tv_sec;
    ttime.tv_nsec = endtime.tv_nsec - starttime.tv_nsec;
    timeinterval = ttime.tv_sec * 1000000000 + ttime.tv_nsec;

   
   //Print out the resulting matrix
printf("number of threads : %d \n",count);// no if threads ie equal no of rows
   printf("Time in milliseconds %lf ms \n", (double) timeinterval/1000000);
// output matrix
printf("Result matrix : \n");

   for(i = 0; i < r1; i++) {
      for(j = 0; j < c2; j++) {
         printf("%d ", mult[i][j]);
      }
      printf("\n");
   }
}


void *runner(void *param) {
   int n, sum = 0;

   //row multiplied by column
int j;
for(j = 0; j < c2; j++) {
   for(n = 0; n< c1; n++){
      mult[x][j]= mult[x][j]+ a[x][n] * b[n][j];
   }
 
}
   
   pthread_exit(0);
}

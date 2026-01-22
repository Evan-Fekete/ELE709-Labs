#include <stdio.h>
#include <time.h>

int main()
{
   int i, maxitr;
   char op,again;
   struct timespec start_time, stop_time, sleep_time, res;
   double tmp, elapsed_time, a, b, c;
   while(again != 'q'){

	/*Prompt user for the numbers a and b, and the mathematical operation to be
	timed.*/
	   printf("Choose two values: ");
	   scanf("%lf %lf",&a,&b);
	   printf("Value A: %lf Value B: %lf\n",a,b);
	   printf("Choose a mathematical operation (+,-,*,/): ");
	   scanf(" %c",&op);
	    
	 
	   maxitr = 500000000; // Set the number of iterations: maxitr = 500000000.
	   clock_gettime(CLOCK_REALTIME, &start_time); // Time 1
	   //Repeat the selected mathematical operation maxitr times
	   for(i = 0; i < maxitr; i++)
	   {


	      if(op == '+'){
		c = a + b;
		}

	   	else if(op == '-'){
		c = a - b;
		}

	   	else if(op == '*'){
		c = a * b;
		}

	   	else if(op == '/'){
		c = a / b;
		}
	  
	   	else {
		printf("operation does not exist");
		break;
		}
	   }

	      clock_gettime(CLOCK_REALTIME, &stop_time);// Time 2

	      tmp = (stop_time.tv_sec - start_time.tv_sec)*1e9; //ELAPSED TIME = TIME2 - TIME1
	      tmp  += (stop_time.tv_nsec - start_time.tv_nsec);
	      elapsed_time = tmp/maxitr;//ELAPSED TIME/maxitr
	      printf("Time per iteration: %lf nsec\n",elapsed_time);

	      printf("Again (c or q): ");
	      scanf(" %c",&again);
	      while (again != 'q' && again != 'c'){
		
		printf("invalid charcter\n");
		printf("Again (c or q): ");
	   	scanf(" %c",&again);

		}
		
	}
   return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Joseph Sindelar

int divide(int, int, int, int);
int main (){
	int i, counter, divisor, dividend, quotient;
	counter=0;
	srand ((int) time (NULL));
	for (i=0;i<10;i++){
		divisor = rand() % 12 + 1;
		quotient = rand () % 13;
		dividend =  (quotient * divisor);
		printf("%d / %d = ?\n", dividend, divisor);
		counter += divide(counter, divisor, dividend, quotient);
		printf("%d Correct\n", counter);
	}
}
int divide(counter, divisor, dividend, quotient){
	int tempquo;
	scanf("%d", &tempquo);
	if (tempquo == quotient){
		printf("Another perfect answer");
		return 1;
	}
	else{
		printf("Incorrect the answer was %d\n", quotient);
		return 0;
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int sorted = 1;

void fillArray(int array[],int top){//Fills array with values up to the desired value
	for(int i = 0; i <= top; i++){
		array[i] = i+1;
	}
}

void printArray(int array[],int top){//simple function to print arrays
	for(int i = 0; i < top; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}

void bubbleSort(int array[], int top){//bubblesort algorithm that iterates through arrays and compares values. If the value on the left is bigger than the value on the right, the values are flipped. This happens until the array has been sorted.
	for(int i = 0; i < top; i ++){
		for(int j = 0; j < top - i - 1; j++){
			if(array[j] > array[j + 1]){
				int temp = array[j];
     		                array[j] = array[j+1];
				array[j+1] = temp;
                        }
		}
	}
}
void randomizeArray(int array[], int top){//Uses Fischer Yates Shuffle to randomize array after fillArray function is called. Also is the same randomiser used in the bogosort algorithm. May not be totally random because bogosort orders the array much faster than it should. 
	srand(time(NULL));
	for(int i = top - 1; i > 0; i--){
		int j = rand() % (i + 1);
		unsigned int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}

int checkArray(int array[],int top, int *true){//Checks if the bogosort array is sorted
	for(int i = 0; i < top; i++){
		if(array[i] > array[i + 1]){
			//printf("not in order");
			*true = 1;
			return 1;
		}
	}
	*true = 0;
	return 0;
}


int main(int argc, char *argv[]){
	int true = 1;
	int top =  atoi(argv[1]);
	unsigned int array[top];
	unsigned int array2[top];
	unsigned int total = 0;

	fillArray(array, top);
	randomizeArray(array,top);
	printf("This is the starting Array: ");
	printArray(array,top);
	printf("\n\n");
	checkArray(array, top, &true);
	memcpy(array2, array, sizeof(array));//method of copy/pasting values from one array to another

	clock_t startTimeBubble = clock();//start of bubblesort
	bubbleSort(array2,top);
	clock_t endTimeBubble = clock();//end of bubblesort
	printf("This is the array sorted with bubble sort:\n");
        printArray(array2, top);
	double elapsed_timeBubble = ((double)(endTimeBubble - startTimeBubble)) / CLOCKS_PER_SEC;
	printf("It took bubble sort %f seconds to sort the array\n\n",elapsed_timeBubble);

	printf("Starting the bogosort alogrithm\n");
	clock_t startTimeBogo = clock();//start of the bogosort alorithm
	while(true == 1){
		checkArray(array,top,&true);
		if(checkArray(array,top,&true) == 0){
			break;
		}
		randomizeArray(array,top);//This randmizing alogrithm is not completely randmizing the array because in an array of length t, there should be 5! or 120 possibilities. However when the program runs it takes less than 10 on average. This could be a few things such as the random number generator or the randomizing alogrithm its self. 
		//checkArray(array,top,&true); Could check if the array is sorted after randomizing, however if the array is already sorted before entered into the bogosort algorithm, then it will randomize an already sorted array making its fastest run time of O(1) (already sorted array) be O(n!).
		total++;
		if(total == 1000000){
			printf("Bogosort failed to sort the array.\n");
			break;
		}
	}
	clock_t endTimeBogo = clock();
	double elapsed_time = ((double)(endTimeBogo - startTimeBogo)) / CLOCKS_PER_SEC;
	printf("Elapsed time: %f seconds\n", elapsed_time);
	printArray(array,top);
	printf("The array was shuffled %d times\n", total);


}

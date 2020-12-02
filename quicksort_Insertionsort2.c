#include<stdio.h>
#include<stdlib.h>
#include<time.h>

time_t quicksort_time, insertion_time, qend, iend;

int *number1, *number2;

void quicksort(int * number, int first, int last) {
	quicksort_time = time(NULL);
		int i, j, pivot, temp;
	if (first < last) {
		pivot = first;
		i = first;
		j = last;
		while (i < j) {//i와 j가 교차하지 않는 동안에 진행
			while (number[i] <= number[pivot] && i < last) //기준값보다 작은 값을 갖는 index 찾기
				i++;
			while (number[j] > number[pivot]) // 기준값보다 큰값을 갖는 index를 찾기
				j--;
			if (i < j) { //서로 교차하지 않았다면, 값을 교환해줌.
				temp = number[i];
				number[i] = number[j];
				number[j] = temp;
			}
		}


		//i와 j가 교차(같아지는)되는 지점에서 loop이 멈춤. 
		//따라서, 아래에서는 i와 j가 같은 값이므로 둘중 어느것을 써도 같은 값이 나옴.
		temp = number[pivot];//기준값 임시저장
		number[pivot] = number[j]; //j위치(i와 교차된 위치)에 있는 값은 맨 앞(pivot값의 위치)으로 보내고
		number[j] = temp; // 기준값을 교차된 위치로 보냄

		quicksort(number, first, j - 1);
		quicksort(number, j + 1, last);
	}
	qend = time(NULL);
}

void insertionSort(int * number, int n)
{
	insertion_time = time(NULL);
	int i, key, j;
	for (i = 1; i <= n; i++) { //loop 내의 연산횟수를 비교하기
		key = number[i];
		j = i - 1;

		/* number[0..i-1]의 원소의 값과 key로 정한 number[i]와 비교하여
		이보다 더 큰수가 있는경우 1 칸 이동 시킨다.*/
		while (j >= 0 && number[j] > key) {
			number[j + 1] = number[j];
			j = j - 1;
		}
		number[j + 1] = key;
	}
	iend = time(NULL);
}

void generateRandom(int n) {
	int i;
	srand((unsigned int)time(NULL));

	number1 = (int *)malloc(n * sizeof(int));
	number2 = (int *)malloc(n * sizeof(int));

	for (i = 0; i < n; i++) {
		number1[i] = rand();
		number2[i] = number1[i];
	}


	/*printf("\n \n \n  Original Data : ");
	for (i = 0; i < n; i++)
		printf(" %d", number1[i]);*/


}


int main() {
	int i = 0, count = 0;

	printf_s("Enter some elements: ");
	scanf_s("%d", &count);

	generateRandom(count);

	quicksort(number1, 0, count - 1);
	insertionSort(number2, count - 1);

	/*printf("\n \n \n  Quick Sort Result : ");
	for (i = 0; i < count; i++)
		printf(" %d", number1[i]);

	printf("\n \n \n  Insertion Sort Result : ");
	for (i = 0; i < count; i++)
		printf(" %d", number2[i]);*/

	double result1 = quicksort_time - qend;
	double result2 = insertion_time - iend;
	printf_s("Quicksort 걸린 시간 = %f", result1);
	printf_s("Insertionsort 걸린 시간 = %f", result2);

	getchar();

	return 0;
}
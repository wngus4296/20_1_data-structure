#include<stdio.h>
#include<stdlib.h>
#include<time.h>

unsigned long long int quicksort_op_num = 0;
unsigned long long int insertionsort_op_num = 0;

int *number1, *number2;

void quicksort(int * number, int first, int last) {
	int i, j, pivot, temp;
	if (first < last) {
		pivot = first;  //지나다니면서 비교하는 값(기준값)
		i = first;
		j = last;
		quicksort_op_num += 4; //값 대입과 if문 비교
		while (i < j) {//i와 j가 교차하지 않는 동안에 진행
			quicksort_op_num++; //while 비교연산 1회
			while (number[i] <= number[pivot] && i < last) { //기준값보다 작은 값을 갖는 index 찾기
				i++;
				quicksort_op_num += 3; // while문을 들어왔으니 전자, 후자 모두 참이다. 따라서 비교연산 2회와 i++까지 3번의 과정을 실행한다.
			}
			quicksort_op_num++; // while문 나올 때 전자가 거짓인 경우 비교 연산
			if (number[i] <= number[pivot])
				quicksort_op_num++; // &&연산은 쇼트 서킷으로 인해 만약 전자의 경우가 거짓이면 후자의 연산을 하지 않는다. 
									// 따라서 전자의 경우가 참이면 후자의 경우도 계산(전자가 참인데 while문을 안돌았으니 후자가 거짓인 것)
			
			while (number[j] > number[pivot]) { // 기준값보다 큰값을 갖는 index를 찾기
				j--;
				quicksort_op_num += 2; //while 비교 연산과 j--
			}
			quicksort_op_num++; //while 비교연산 거짓일 경우 1회

			if (i < j) { //서로 교차하지 않았다면, 값을 교환해줌.
				temp = number[i];
				number[i] = number[j];
				number[j] = temp;
				quicksort_op_num += 4;
			}
			quicksort_op_num++;
		}
		quicksort_op_num++; //i와 j비교해서 거짓일 때는 안에 들어가지 못해서 비교연산 +할 수 없으니 밖에서 연산 1회 더해준다.


		//i와 j가 교차(같아지는)되는 지점에서 loop이 멈춤. 
		//따라서,l 아래에서는 i와 j가 같은 값이므로 둘중 어느것을 써도 같은 값이 나옴.
		temp = number[pivot];//기준값 임시저장
		number[pivot] = number[j]; //j위치(i와 교차된 위치)에 있는 값은 맨 앞(pivot값의 위치)으로 보내고
		number[j] = temp; // 기준값을 교차된 위치로 보냄
		quicksort_op_num += 3;

		quicksort(number, first, j - 1);
		quicksort(number, j + 1, last);
		quicksort_op_num += 2;
	}
	quicksort_op_num++; // if문 못들어갔을 때 비교연산
}

void insertionSort(int * number, int n)
{
	int i, key, j;
	for (i = 1; i <= n; i++) { //loop 내의 연산횟수를 비교하기
		key = number[i];
		j = i - 1;
		insertionsort_op_num += 4; //for문 안의 연산과 비교, i++

		/* number[0..i-1]의 원소의 값과 key로 정한 number[i]와 비교하여
		이보다 더 큰수가 있는경우 1 칸 이동 시킨다.*/
		while (j >= 0 && number[j] > key) {
			number[j + 1] = number[j];
			j = j - 1;
			insertionsort_op_num += 4;
		}
		insertionsort_op_num++; // while문에서 나올 때 전자가 거짓인 경우 비교 연산
		if (j >= 0)
			insertionsort_op_num++; // &&연산은 쇼트 서킷으로 인해 만약 전자의 경우가 거짓이면 후자의 연산을 하지 않는다. 
									// 따라서 전자의 경우가 참이면 후자의 경우도 계산(전자가 참인데 while문을 안돌았으니 후자가 거짓인 것)
		number[j + 1] = key;
		insertionsort_op_num += 2; // j+1하고 number[j+1]에 key넣음
	}
	insertionsort_op_num += 2; //for문에서 나올 때 마지막 i와 n비교, 처음 for문 돌릴 때 i값 대입
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
	while (true) {
		quicksort_op_num = 0;
		insertionsort_op_num = 0;
		int i, count;

		printf_s("Enter number of elements: ");
		scanf_s("%d", &count);

		generateRandom(count);

		quicksort(number1, 0, count - 1);
		insertionSort(number2, count - 1);

		/*printf_s("\n \n \n  Quick Sort Result : ");
		for (i = 0; i < count; i++)
			printf_s(" %d", number1[i]);

		printf_s("\n \n \n  Insertion Sort Result : ");
		for (i = 0; i < count; i++)
			printf_s(" %d", number2[i]);*/

		printf_s("\n\n\n\n\n  Quick Sort : [[%llu]] operation", quicksort_op_num);

		printf_s("\n \n \n  Insertion Sort : [[%llu]] operation\n", insertionsort_op_num);

		getchar();
	}
		return 0;
	
}
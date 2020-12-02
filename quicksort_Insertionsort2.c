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
		while (i < j) {//i�� j�� �������� �ʴ� ���ȿ� ����
			while (number[i] <= number[pivot] && i < last) //���ذ����� ���� ���� ���� index ã��
				i++;
			while (number[j] > number[pivot]) // ���ذ����� ū���� ���� index�� ã��
				j--;
			if (i < j) { //���� �������� �ʾҴٸ�, ���� ��ȯ����.
				temp = number[i];
				number[i] = number[j];
				number[j] = temp;
			}
		}


		//i�� j�� ����(��������)�Ǵ� �������� loop�� ����. 
		//����, �Ʒ������� i�� j�� ���� ���̹Ƿ� ���� ������� �ᵵ ���� ���� ����.
		temp = number[pivot];//���ذ� �ӽ�����
		number[pivot] = number[j]; //j��ġ(i�� ������ ��ġ)�� �ִ� ���� �� ��(pivot���� ��ġ)���� ������
		number[j] = temp; // ���ذ��� ������ ��ġ�� ����

		quicksort(number, first, j - 1);
		quicksort(number, j + 1, last);
	}
	qend = time(NULL);
}

void insertionSort(int * number, int n)
{
	insertion_time = time(NULL);
	int i, key, j;
	for (i = 1; i <= n; i++) { //loop ���� ����Ƚ���� ���ϱ�
		key = number[i];
		j = i - 1;

		/* number[0..i-1]�� ������ ���� key�� ���� number[i]�� ���Ͽ�
		�̺��� �� ū���� �ִ°�� 1 ĭ �̵� ��Ų��.*/
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
	printf_s("Quicksort �ɸ� �ð� = %f", result1);
	printf_s("Insertionsort �ɸ� �ð� = %f", result2);

	getchar();

	return 0;
}
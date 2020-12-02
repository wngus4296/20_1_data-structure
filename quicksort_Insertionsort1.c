#include<stdio.h>
#include<stdlib.h>
#include<time.h>

unsigned long long int quicksort_op_num = 0;
unsigned long long int insertionsort_op_num = 0;

int *number1, *number2;

void quicksort(int * number, int first, int last) {
	int i, j, pivot, temp;
	if (first < last) {
		pivot = first;  //�����ٴϸ鼭 ���ϴ� ��(���ذ�)
		i = first;
		j = last;
		quicksort_op_num += 4; //�� ���԰� if�� ��
		while (i < j) {//i�� j�� �������� �ʴ� ���ȿ� ����
			quicksort_op_num++; //while �񱳿��� 1ȸ
			while (number[i] <= number[pivot] && i < last) { //���ذ����� ���� ���� ���� index ã��
				i++;
				quicksort_op_num += 3; // while���� �������� ����, ���� ��� ���̴�. ���� �񱳿��� 2ȸ�� i++���� 3���� ������ �����Ѵ�.
			}
			quicksort_op_num++; // while�� ���� �� ���ڰ� ������ ��� �� ����
			if (number[i] <= number[pivot])
				quicksort_op_num++; // &&������ ��Ʈ ��Ŷ���� ���� ���� ������ ��찡 �����̸� ������ ������ ���� �ʴ´�. 
									// ���� ������ ��찡 ���̸� ������ ��쵵 ���(���ڰ� ���ε� while���� �ȵ������� ���ڰ� ������ ��)
			
			while (number[j] > number[pivot]) { // ���ذ����� ū���� ���� index�� ã��
				j--;
				quicksort_op_num += 2; //while �� ����� j--
			}
			quicksort_op_num++; //while �񱳿��� ������ ��� 1ȸ

			if (i < j) { //���� �������� �ʾҴٸ�, ���� ��ȯ����.
				temp = number[i];
				number[i] = number[j];
				number[j] = temp;
				quicksort_op_num += 4;
			}
			quicksort_op_num++;
		}
		quicksort_op_num++; //i�� j���ؼ� ������ ���� �ȿ� ���� ���ؼ� �񱳿��� +�� �� ������ �ۿ��� ���� 1ȸ �����ش�.


		//i�� j�� ����(��������)�Ǵ� �������� loop�� ����. 
		//����,l �Ʒ������� i�� j�� ���� ���̹Ƿ� ���� ������� �ᵵ ���� ���� ����.
		temp = number[pivot];//���ذ� �ӽ�����
		number[pivot] = number[j]; //j��ġ(i�� ������ ��ġ)�� �ִ� ���� �� ��(pivot���� ��ġ)���� ������
		number[j] = temp; // ���ذ��� ������ ��ġ�� ����
		quicksort_op_num += 3;

		quicksort(number, first, j - 1);
		quicksort(number, j + 1, last);
		quicksort_op_num += 2;
	}
	quicksort_op_num++; // if�� ������ �� �񱳿���
}

void insertionSort(int * number, int n)
{
	int i, key, j;
	for (i = 1; i <= n; i++) { //loop ���� ����Ƚ���� ���ϱ�
		key = number[i];
		j = i - 1;
		insertionsort_op_num += 4; //for�� ���� ����� ��, i++

		/* number[0..i-1]�� ������ ���� key�� ���� number[i]�� ���Ͽ�
		�̺��� �� ū���� �ִ°�� 1 ĭ �̵� ��Ų��.*/
		while (j >= 0 && number[j] > key) {
			number[j + 1] = number[j];
			j = j - 1;
			insertionsort_op_num += 4;
		}
		insertionsort_op_num++; // while������ ���� �� ���ڰ� ������ ��� �� ����
		if (j >= 0)
			insertionsort_op_num++; // &&������ ��Ʈ ��Ŷ���� ���� ���� ������ ��찡 �����̸� ������ ������ ���� �ʴ´�. 
									// ���� ������ ��찡 ���̸� ������ ��쵵 ���(���ڰ� ���ε� while���� �ȵ������� ���ڰ� ������ ��)
		number[j + 1] = key;
		insertionsort_op_num += 2; // j+1�ϰ� number[j+1]�� key����
	}
	insertionsort_op_num += 2; //for������ ���� �� ������ i�� n��, ó�� for�� ���� �� i�� ����
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
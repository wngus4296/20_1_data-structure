#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
#include<time.h> //���� ����

typedef struct person //��û�� ���� ���� ����ü
{
	char name[20]; //�̸�
	int gender; //���ڴ� 1, ���ڴ� 2
	int age; //����
	struct person *link; //�ڱ� ����(���� ���� ����鳢�� ������ ��)
}person;

typedef struct node //����Ʈ���� ���� ����
{
	int key; //����(=person�� age)
	struct person *p; //�ش� ���̸� ���� ������� ���Ḯ��Ʈ�� ó���� ����ų ������
	struct node *left, *right;
}  NODE;


void printAllPerson(NODE *node) { //Ư�� ���̸� ���� ��û�� ��� ���
	person *here;
	here = node->p;
	printf("\n%d�� �糭 ������ ��û�� ���(�ֽ� ��� ��)\n", node->key);
	printf("�̸�, ����\n");
	while (here != NULL) { //���Ḯ��Ʈ ������ ���
		char gd = 'M'; //����-1 ����-2�� �Է¹޾ұ� ������ �⺻ �� M���� ����
		if (here->gender == 2) { gd = 'W'; } //�����̸� W�� �ٲ�
		printf("%s, %c\n", here->name, gd); //�̸��� ���� ���
		here = here->link; //���� person ����Ŵ
	}
}

void InSertPerson(NODE *per, int age, char *name, int gender) { //��û�� ���� ����
	person *newPer;

	newPer = (person *)malloc(sizeof(person)); //���Ӱ� ���� �Ҵ� �� ���� �Է�
	newPer->age = age;
	newPer->gender = gender;
	strcpy(newPer->name, name);

	newPer->link = per->p; //�ֽż����� �����ϱ� ���� ���� �տ� ����
	per->p = newPer; //Ư�� ���̰� ���� �ֽ� ��û�ڸ� ����Ŵ
}

int cnt = 0; //ã�� �� ��ġ�� ȸ�� ��

NODE* search(NODE* root, int key) //Ư�� ���� ã��
{
	cnt++;

	if (root == NULL) //���� Ʈ��
		return root;

	if (root->key == key) { //Ư�� ���� ã��
		printAllPerson(root);
		printf("\n\n%d���� ���̸� ���� ��û�ڵ��� ã�� �� �ɸ� ��ȸ Ƚ���� %d���Դϴ�.", key, cnt);
	}

	if (root->key < key) //Ư�� ���̰� Ŭ ���
		return search(root->right, key);

	return search(root->left, key); //Ư�� ���̰� ���� ���
}

NODE *newNode(int age, char *name, int gender) //���ο� ��� ����(����)
{
	NODE *temp = (NODE *)malloc(sizeof(NODE));
	temp->key = age;
	temp->left = temp->right = NULL;
	temp->p = NULL;
	InSertPerson(temp, age, name, gender); //�������� ������ ��û�� ���� ����
	return temp;
}

void inorder(NODE *root) //���� Ʈ�� ������������ ������(���� ��ȸ)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%d \n", root->key);
		inorder(root->right);
	}
}

NODE* insert(NODE* node, int key, char *name, int gender) //���̸� �������� Ʈ�� ����
{
	if (node == NULL) return newNode(key, name, gender); //����Ʈ���� ��� ���ο� ��� ����

	if (key < node->key)
		node->left = insert(node->left, key, name, gender);
	else if (key > node->key)
		node->right = insert(node->right, key, name, gender);
	else if (key == node->key) //�̹� �ִ� ������ ��� ���� ���̸� ���� ������ ����
		InSertPerson(node, key, name, gender);

	return node;
}


int main()
{
	printf("�������. �糭 �������� �ް��� �ϴ� ������� �Ż� ������ �Է����ּ���.\n\n");
	srand((unsigned int)time(NULL)); //���� �ʱ�ȭ
	NODE *root = NULL;
	for (int i = 0; i < 80; i++) {
		int newAge;
		char newName[20] = "�ֹ�";
		int newGender;

		/* ����, �̸�, ������ �Է¹޴� ���
		printf("����: ");
		scanf("%d", &newAge);
		while (newAge < 20 || newAge > 100) {
			printf("�糭 ������ ��û �ڰ��� 20�� �̻� 100�� �����Դϴ�. �ٽ��Է����ּ���.\n");
			printf("����: ");
			scanf("%d", &newAge);
		}
		printf("�̸�: ");
		scanf("%s", newName);
		printf("����(��-1, ��-2): ");
		scanf("%d", &newGender);
		while (newGender < 1 || newGender > 2) {
			printf("������ �ùٸ��� �ʽ��ϴ�. ���ڴ� 1, ���ڴ� 2�� �Է����ּ���.\n");
			printf("����(��-1, ��-2): ");
			scanf("%d", &newGender);
		}
		*/

		//�������� ����, �̸�, ������ ���ϴ� ���
		newAge = rand() % 81 + 20; //20�� �̻� 100�� ����
		printf("����: %d\n", newAge);
		char n[10]; //�̸��� ���Ƿ� ��û ��ȣ�� �����ϱ� ����
		sprintf(n, "%d", i+1); //��û�� ��ȣ�� ���ڿ��� ��ȯ
		strcat(newName, n); //�ֹ�+��û�� ��ȣ�� �̸��� ����  ��)�ֹ�1, �ֹ�2, ... �ֹ�79, �ֹ�80
		printf("�̸�: %s\n", newName);
		newGender = rand() % 2 + 1; //����-1 ����-2
		char gd = 'M'; //�⺻ �� M���� ����
		if (newGender == 2) { gd = 'W'; } //�����̸� W�� �ٲ�
		printf("����: %c\n", gd);

		if (root == NULL) root = insert(root, newAge, newName, newGender); //�����̸� root�ٲ������
		else insert(root, newAge, newName, newGender); //����ƴϸ� root�� �״�� ������ ����

		printf("\n%s���� �����Է��� �Ϸ�Ǿ����ϴ�.\n\n", newName);
	}

	printf("\n\n80���� �����Է��� �Ϸ�Ǿ����ϴ�.\n");
	printf("\n���� ��û�� ���� ���\n");
	printf("==========================\n");
	inorder(root); //��û�� ��� ���� ������ ������
	printf("==========================\n\n");

	int findAge = 1;
	while (findAge != 0) {
		cnt = 0;
		printf("\n\nã�� ���̸� �Է��ϼ���(�����Ϸ��� 0�� �Է��ϼ���.): ");
		scanf("%d", &findAge);
		if (findAge == 0) printf("\n���α׷��� �����մϴ�.");
		else if (findAge < 20 || findAge > 100) printf("�糭 ������ ��û�ڴ� 20�� �̻� 100�� �����Դϴ�. �ٽ� �Է����ּ���.");
		else {
			search(root, findAge);
		}
	}

	return 0;
}
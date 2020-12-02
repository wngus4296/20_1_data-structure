#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>

typedef struct node //����Ʈ���� ���� ����
{
	int age; //���� Ʈ���� ����
	char name[20]; //�̸�
	int gender; //���ڴ� 1, ���ڴ� 2
	struct node *left, *right;
}  NODE;


int cnt = 0; //ã�� �� ��ġ�� ȸ�� ��

NODE* search(NODE* root, int key)
{
	cnt++;

	// Base Cases: root is null or key is present at root 
	if (root == NULL || root->age == key)
		return root;

	// key is greater than root's key 
	if (root->age < key)
		return search(root->right, key);

	// key is smaller than root's key 
	return search(root->left, key);
}

// A utility function to create a new BST node 
NODE *newNode(int item)
{
	NODE *temp = (NODE *)malloc(sizeof(NODE));
	temp->age = item;
	temp->left = temp->right = NULL;
	return temp;
}

// A utility function to do inorder traversal of BST
void inorder(NODE *root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%d \n", root->age);
		inorder(root->right);
	}
}

void showPerson(NODE *node)
{
	printf("%d ���̸� ���� �糭 ������ ��û��\n", node->age);
	printf("�̸�, ����: ");
	char gd = 'M';
	if (node->gender == 2) { gd = 'W'; }
	printf("%s, %c", node->name, gd);
}

/* A utility function to insert a new node with given key in BST */
NODE* insert(NODE* node, int key) //key�� age
{
	/* If the tree is empty, return a new node */
	if (node == NULL) return newNode(key);

	/* Otherwise, recur down the tree */
	if (key < node->age)
		node->left = insert(node->left, key);
	else if (key > node->age)
		node->right = insert(node->right, key);

	/* return the (unchanged) node pointer */
	return node;
}


int main()
{
	NODE *root = NULL;
	while (sizeof(root) <= 80) {
		printf("�������. �糭 �������� �ް��� �ϴ� ������� �Ż� ������ �Է����ּ���.\n");
		int newAge;
		char newName[20];
		int newGender;
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

		if (root == NULL) root = insert(root, newAge); //�����̸� root�ٲ������
		else insert(root, newAge); //����ƴϸ� �ٿ������
		printf("\n%s���� �����Է��� �Ϸ�Ǿ����ϴ�.\n\n", newName);
		inorder(root);
	}

	printf("\n\n80���� �����Է��� �Ϸ�Ǿ����ϴ�.\n");
	cnt = 0;
	int findAge;
	printf("\n\nã�� ���̸� �Է��ϼ���: ");
	scanf("%d", &findAge);

	showPerson(search(root, findAge));

	printf("\n%d���̸� ���� ��û�ڸ� ã�� �� �ɸ� ��ȸ Ƚ��: %d", findAge, cnt);

	return 0;
}
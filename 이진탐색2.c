#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>

typedef struct node //이진트리로 만들 것임
{
	int age; //이진 트리의 나이
	char name[20]; //이름
	int gender; //남자는 1, 여자는 2
	struct node *left, *right;
}  NODE;


int cnt = 0; //찾을 때 거치는 회선 수

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
	printf("%d 나이를 가진 재난 지원금 신청자\n", node->age);
	printf("이름, 성별: ");
	char gd = 'M';
	if (node->gender == 2) { gd = 'W'; }
	printf("%s, %c", node->name, gd);
}

/* A utility function to insert a new node with given key in BST */
NODE* insert(NODE* node, int key) //key가 age
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
		printf("어서오세요. 재난 지원금을 받고자 하는 사람들은 신상 정보를 입력해주세요.\n");
		int newAge;
		char newName[20];
		int newGender;
		printf("나이: ");
		scanf("%d", &newAge);
		while (newAge < 20 || newAge > 100) {
			printf("재난 지원금 신청 자격은 20세 이상 100세 이하입니다. 다시입력해주세요.\n");
			printf("나이: ");
			scanf("%d", &newAge);
		}
		printf("이름: ");
		scanf("%s", newName);
		printf("성별(남-1, 여-2): ");
		scanf("%d", &newGender);
		while (newGender < 1 || newGender > 2) {
			printf("성별이 올바르지 않습니다. 남자는 1, 여자는 2를 입력해주세요.\n");
			printf("성별(남-1, 여-2): ");
			scanf("%d", &newGender);
		}

		if (root == NULL) root = insert(root, newAge); //공백이면 root바꿔줘야함
		else insert(root, newAge); //공백아니면 붙여줘야함
		printf("\n%s님의 정보입력이 완료되었습니다.\n\n", newName);
		inorder(root);
	}

	printf("\n\n80명의 정보입력이 완료되었습니다.\n");
	cnt = 0;
	int findAge;
	printf("\n\n찾을 나이를 입력하세요: ");
	scanf("%d", &findAge);

	showPerson(search(root, findAge));

	printf("\n%d나이를 갖는 신청자를 찾는 데 걸린 순회 횟수: %d", findAge, cnt);

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
#include<time.h> //난수 생성

typedef struct person //신청자 정보 담을 구조체
{
	char name[20]; //이름
	int gender; //남자는 1, 여자는 2
	int age; //나이
	struct person *link; //자기 참조(같은 나이 사람들끼리 연결할 것)
}person;

typedef struct node //이진트리로 만들 것임
{
	int key; //나이(=person의 age)
	struct person *p; //해당 나이를 가진 사람들의 연결리스트의 처음을 가리킬 포인터
	struct node *left, *right;
}  NODE;


void printAllPerson(NODE *node) { //특정 나이를 가진 신청자 목록 출력
	person *here;
	here = node->p;
	printf("\n%d세 재난 지원금 신청자 목록(최신 등록 순)\n", node->key);
	printf("이름, 성별\n");
	while (here != NULL) { //연결리스트 끝까지 출력
		char gd = 'M'; //남성-1 여성-2로 입력받았기 때문에 기본 값 M으로 설정
		if (here->gender == 2) { gd = 'W'; } //여성이면 W로 바꿈
		printf("%s, %c\n", here->name, gd); //이름과 성별 출력
		here = here->link; //다음 person 가리킴
	}
}

void InSertPerson(NODE *per, int age, char *name, int gender) { //신청자 정보 생성
	person *newPer;

	newPer = (person *)malloc(sizeof(person)); //새롭게 동적 할당 및 정보 입력
	newPer->age = age;
	newPer->gender = gender;
	strcpy(newPer->name, name);

	newPer->link = per->p; //최신순으로 유지하기 위해 가장 앞에 삽입
	per->p = newPer; //특정 나이가 가장 최신 신청자를 가리킴
}

int cnt = 0; //찾을 때 거치는 회선 수

NODE* search(NODE* root, int key) //특정 나이 찾기
{
	cnt++;

	if (root == NULL) //공백 트리
		return root;

	if (root->key == key) { //특정 나이 찾음
		printAllPerson(root);
		printf("\n\n%d세의 나이를 갖는 신청자들을 찾는 데 걸린 순회 횟수는 %d번입니다.", key, cnt);
	}

	if (root->key < key) //특정 나이가 클 경우
		return search(root->right, key);

	return search(root->left, key); //특정 나이가 작을 경우
}

NODE *newNode(int age, char *name, int gender) //새로운 노드 생성(나이)
{
	NODE *temp = (NODE *)malloc(sizeof(NODE));
	temp->key = age;
	temp->left = temp->right = NULL;
	temp->p = NULL;
	InSertPerson(temp, age, name, gender); //정보들을 가지고 신청자 정보 연결
	return temp;
}

void inorder(NODE *root) //현재 트리 오름차순으로 보여줌(중위 순회)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%d \n", root->key);
		inorder(root->right);
	}
}

NODE* insert(NODE* node, int key, char *name, int gender) //나이를 기준으로 트리 생성
{
	if (node == NULL) return newNode(key, name, gender); //공백트리일 경우 새로운 노드 생성

	if (key < node->key)
		node->left = insert(node->left, key, name, gender);
	else if (key > node->key)
		node->right = insert(node->right, key, name, gender);
	else if (key == node->key) //이미 있는 나이일 경우 같은 나이를 가진 사람들과 연결
		InSertPerson(node, key, name, gender);

	return node;
}


int main()
{
	printf("어서오세요. 재난 지원금을 받고자 하는 사람들의 신상 정보를 입력해주세요.\n\n");
	srand((unsigned int)time(NULL)); //난수 초기화
	NODE *root = NULL;
	for (int i = 0; i < 80; i++) {
		int newAge;
		char newName[20] = "주민";
		int newGender;

		/* 나이, 이름, 성별을 입력받는 경우
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
		*/

		//랜덤으로 나이, 이름, 성별을 정하는 경우
		newAge = rand() % 81 + 20; //20세 이상 100세 이하
		printf("나이: %d\n", newAge);
		char n[10]; //이름을 임의로 신청 번호로 지정하기 위함
		sprintf(n, "%d", i+1); //신청자 번호를 문자열로 변환
		strcat(newName, n); //주민+신청자 번호로 이름을 생성  예)주민1, 주민2, ... 주민79, 주민80
		printf("이름: %s\n", newName);
		newGender = rand() % 2 + 1; //남성-1 여성-2
		char gd = 'M'; //기본 값 M으로 설정
		if (newGender == 2) { gd = 'W'; } //여성이면 W로 바꿈
		printf("성별: %c\n", gd);

		if (root == NULL) root = insert(root, newAge, newName, newGender); //공백이면 root바꿔줘야함
		else insert(root, newAge, newName, newGender); //공백아니면 root는 그대로 정보만 삽입

		printf("\n%s님의 정보입력이 완료되었습니다.\n\n", newName);
	}

	printf("\n\n80명의 정보입력이 완료되었습니다.\n");
	printf("\n현재 신청자 나이 목록\n");
	printf("==========================\n");
	inorder(root); //신청자 목록 나이 순으로 보여줌
	printf("==========================\n\n");

	int findAge = 1;
	while (findAge != 0) {
		cnt = 0;
		printf("\n\n찾을 나이를 입력하세요(종료하려면 0을 입력하세요.): ");
		scanf("%d", &findAge);
		if (findAge == 0) printf("\n프로그램을 종료합니다.");
		else if (findAge < 20 || findAge > 100) printf("재난 지원금 신청자는 20세 이상 100세 이하입니다. 다시 입력해주세요.");
		else {
			search(root, findAge);
		}
	}

	return 0;
}
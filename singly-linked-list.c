/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */


typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("[----- [Park Younghyeon] [2021041019] -----]\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;
	free(node);

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* new = (listNode*)malloc(sizeof(listNode));
	listNode* now;
	listNode* prev;
	new->key = key;

	now = h->first;
	prev = NULL;

	while (now != NULL) { 	// key보다 큰 값이 나오는 노드 바로 앞에 삽입
		prev = now;  // 이전 노드를 현재 노드로 변경
		now = now->link; // 현재 노드를 다음 노드로 변경
		if(now->key > key){	// key보다 큰 값이 나오면
			prev->link = new;	// 이전 노드의 링크를 새로운 노드로 변경
			new->link = now;	// 새로운 노드의 링크를 현재 노드로 변경
			return 0;
		}
		else if(now->link == NULL) {	// 마지막 노드일 경우
			break;	// 반복문 종료
		}
		
	}
	// key보다 큰 값이 없을 경우 마지막에 삽입
	now->link = new;
	new->link = NULL;
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	for(listNode* p = h->first; p != NULL; p = p->link) { // 마지막 노드를 찾기 위해 반복
		if(p->link == NULL) { // 마지막 노드일 경우
			listNode* Last = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 생성
			Last->key = key; // 새로운 노드의 key값을 입력받은 key값으로 설정
			Last->link = NULL; // 새로운 노드의 link를 NULL로 설정
			p->link = Last; 	// 마지막 노드의 link를 새로운 노드로 설정
			free(Last);	// 새로운 노드 메모리 해제
			return 0;
		}
	}
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
    
	listNode* temp = h->first; // 삭제할 노드를 임시로 저장
    h->first = h->first->link; // 첫 번째 노드를 두 번째 노드로 변경
    free(temp); // 삭제할 노드 메모리 해제

    return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	for(listNode* p = h->first; p != NULL; p = p->link) { // key에 대한 노드를 찾기 위해 반복
		if(p->link->key == key) { // key에 대한 노드일 경우
			listNode* node = p->link; // 삭제할 노드를 임시로 저장
			p->link = p->link->link; // 삭제할 노드를 건너뛰어 다음 노드로 변경
			free(node); // 삭제할 노드 메모리 해제
			return 0;
		}
	}
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
    for(listNode* p = h->first; p != NULL; p = p->link) { // 마지막 노드를 찾기 위해 반복
        if(p->link->link == NULL) { // 마지막 노드일 경우
            free(p->link); // 마지막 노드 메모리 해제
            p->link = NULL; // 마지막 노드를 NULL로 변경
            return 0; 
        }
    }
    return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) { 
	listNode* prev = NULL;
	listNode* now = h->first;
	listNode* next = NULL;

	while (now != NULL) {	// 현재 노드가 NULL이 아닐 때까지 반복 
		next = now->link; // 다음 노드를 임시로 저장
		now->link = prev; // 현재 노드의 링크를 이전 노드로 변경
		prev = now;	// 이전 노드를 현재 노드로 변경
		now = next;	// 현재 노드를 다음 노드로 변경
	}

	h->first = prev;	// 헤드 노드를 역순으로 변경
	return 0;

}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}


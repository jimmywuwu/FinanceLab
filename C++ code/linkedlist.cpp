#include "stdio.h"
#include "iostream"

typedef struct t_List{
	int id;
	char str[10];
	struct t_List *next;
}List;

typedef struct{
	List* first;
	List* last;
}Head;

List* getData(void);
Head addToLast(Head head,List* np);
void showList(Head head);
Head removeFirst(Head head);
Head freeList(Head head);
int main(int argc, char const *argv[])
{
	List* np;
	Head head={NULL,NULL};
	int i=0;
	while((np=getData())!=NULL && i<8){
		head = addToLast(head,np);
		showList(head);
		i++;
	}
	head=freeList(head);
	showList(head);

	

	return 0;
}

List* getData(void){
	static int ID;
	List* ptr;
	ptr =(List*)malloc(sizeof(List));
	if(ptr==NULL){
		return NULL;
	}else{
		printf("Enter a name: \n");
		if(scanf("%9s",ptr->str)==1){
			ptr->id=ID++;
			ptr->next=ptr;
		}else{
			free(ptr);
			ptr=NULL;
		}
	}
	return ptr;
}

Head addToLast(Head head,List* np){
	List* ptr;

	if(head.first==NULL){
		head.first = head.last =np;
	}else{
		(head.last)->next =np;
		np ->next =head.first;
		head.last = np;
	}
	return head;
}

void showList(List* Head){
	List* ptr=head;
	while(ptr!=NULL){
		printf("%d:%s,",ptr->id,ptr->str);
		ptr=ptr->next;
	}
	printf("\n");
}

Head removeFirst(Head head){
	List* ptr =head;
	if(head==NULL) return NULL;
	else{
		head = head->next;
		free(ptr);
		return head;
	}
}

Head freeList(Head head){
	while(head != NULL){
		head = removeFirst(head);
	}
	return head;
}
#include "iostream"
#include "stdio.h"

typedef struct t_List{
	int id;
	char str[10];
	struct t_List* next;
}List;

List* getData(void);
List* addToLast(List* head,List* np);
void showList(List* head);

int main(int argc, char const *argv[])
{
	List* np;
	List* head=NULL;
	while((np=getData())!=NULL){
		head=addToLast(head,np);
		showList(head);
	}

	return 0;
}


List* getData(void){
	static int ID;
	List* ptr;
	ptr = (List*)malloc(sizeof(List));
	if(ptr==NULL){
		return NULL;
	}else{
		printf("請輸入名稱： ");
		if(scanf("%9s",ptr->str)==1){
			ptr->id=ID++;
			ptr->next=NULL;
		}else{
			free(ptr);
			ptr=NULL;
		}
	}
	return ptr;
}

List* addToLast(List* head,List* np){
	List* ptr;
	ptr = head;

	if(head==NULL){
		head = np;
		np->next=NULL;
	}else{
		while(ptr->next!=NULL){
			ptr=ptr->next;
		}
		ptr->next=np;
	}
	return head;

}

void showList(List* head){
	List* ptr;
	ptr=head;
	printf("[");
	while(ptr->next!=NULL){
		printf("ID %d:%s",ptr->id,ptr->str);
		ptr=ptr->next;
	}
	printf("]");
}
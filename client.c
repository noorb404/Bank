#include "client.h"
#include "bank.h"
#include "branch.h"
/*----------------------------Help Functions-----------------------------*/
Client * ClientTree_find(Client *t, int bankAccount, Client **parent) {
	if (!t)
		return NULL;
	if (bankAccount > t->bankAccount) {
		if(parent)
			*parent = t;
		return ClientTree_find(t->right,bankAccount, parent);
	} else if (bankAccount < t->bankAccount) {
		if(parent)
			*parent = t;
		return ClientTree_find(t->left,bankAccount, parent);
	} else {
		return t;
	}
}
/*----------------------------Help Functions-----------------------------*/
Client *ClientTree_find_min(Client *t, Client **parent) {
	if(!t)
		return NULL;
	if(t->left) {
		if (parent) *parent = t;
		return ClientTree_find_min(t->left, parent);
	}else{
		return t;
	}
}
/*----------------------------Help Functions-----------------------------*/
Client *ClientTree_find_max(Client *t, Client **parent) {
	if(!t)
		return NULL;
	if(t->right) {
		if (parent) *parent = t;
		return ClientTree_find_max(t->right, parent);
	}else{
		return t;
	}
}
/*----------------------------Help Functions-----------------------------*/
void clientSwap(Client *clientHead,int bankAccount1,int bankAccount2){
	Client *temp,*copy1,*copy2;
	copy1=malloc(sizeof(struct client));
	copy2=malloc(sizeof(struct client));
	temp=clientHead;
	while(temp->bankAccount!=bankAccount1){
		if(temp->bankAccount>bankAccount1)
			temp=temp->left;
		if(temp->bankAccount<bankAccount1)
			temp=temp->right;
	}
	if(temp->bankAccount==bankAccount1){
		copy1->balance=temp->balance;
		copy1->bankAccount=temp->bankAccount;
		copy1->deposits=temp->deposits;
		copy1->deviation=temp->deviation;
		copy1->duty=temp->duty;
		copy1->id=temp->id;
		copy1->number_of_branch=temp->number_of_branch;
		copy1->first_name=(char*)malloc(strlen(temp->first_name)*sizeof(char));
		copy1->last_name=(char*)malloc(strlen(temp->last_name)*sizeof(char));
		strcpy(copy1->first_name,temp->first_name);
		strcpy(copy1->last_name,temp->last_name);

	}

	while(temp->bankAccount!=bankAccount2){
		if(temp->bankAccount>bankAccount2)
			temp=temp->left;
		if(temp->bankAccount<bankAccount2)
			temp=temp->right;
	}
	if(temp->bankAccount==bankAccount2){
		copy2->balance=temp->balance;
		copy2->bankAccount=temp->bankAccount;
		copy2->deposits=temp->deposits;
		copy2->deviation=temp->deviation;
		copy2->duty=temp->duty;
		copy2->id=temp->id;
		copy2->number_of_branch=temp->number_of_branch;
		copy2->first_name=(char*)malloc(strlen(temp->first_name)*sizeof(char));
		copy2->last_name=(char*)malloc(strlen(temp->last_name)*sizeof(char));
		strcpy(copy2->first_name,temp->first_name);
		strcpy(copy2->last_name,temp->last_name);
/*---------------------------------------------------------------------------------*/
		temp->balance=copy1->balance;
		temp->bankAccount=copy1->bankAccount;
		temp->deposits=copy1->deposits;
		temp->deviation=copy1->deviation;
		temp->duty=copy1->duty;
		temp->id=copy1->id;
		temp->number_of_branch=copy1->number_of_branch;
		temp->first_name=(char*)malloc(strlen(copy1->first_name)*sizeof(char));
		temp->last_name=(char*)malloc(strlen(copy1->last_name)*sizeof(char));
		strcpy(temp->first_name,copy1->first_name);
		strcpy(temp->last_name,copy1->last_name);

	}
	temp=clientHead;
	while(temp->bankAccount!=bankAccount1){
		if(temp->bankAccount>bankAccount1)
			temp=temp->left;
		if(temp->bankAccount<bankAccount1)
			temp=temp->right;
	}
	if(temp->bankAccount==bankAccount1){
		temp->balance=copy2->balance;
		temp->bankAccount=copy2->bankAccount;
		temp->deposits=copy2->deposits;
		temp->deviation=copy2->deviation;
		temp->duty=copy2->duty;
		temp->id=copy2->id;
		temp->number_of_branch=copy2->number_of_branch;
		temp->first_name=(char*)malloc(strlen(copy2->first_name)*sizeof(char));
		temp->last_name=(char*)malloc(strlen(copy2->last_name)*sizeof(char));
		strcpy(temp->first_name,copy2->first_name);
		strcpy(temp->last_name,copy2->last_name);
	}
}
/**********************************************************************/
void depositMoneyToClientAccount()
{
	int branchNum,bankAccount,money,bankAccountFlag,branchFlag;
	Branch *temp;
	Client *t;/*to not lose the pointer of branch->client*/
	temp=branchTree;
	bankAccountFlag=0;
	branchFlag=0;
	if(branchTree==NULL){
		printf("You have to create Branch's and client's first\n");
		return;
	}
	printf("Enter your branch number(1 to 500): \n");
	/*Checking the branch number*/
	while(1)
	{
		scanf("%d",&branchNum);
		if(temp->right==NULL && temp->left==NULL){
			if(temp->serial_number!=branchNum){
				branchFlag=1;
				printf("ERROR wrong serial number\nTry Again: ");
			}
		}
		else{
			while(temp->serial_number!=branchNum){             /*Checking if the branch*/
				if(temp->right==NULL && temp->left==NULL){     /*      does exist      */
					branchFlag=1;
					printf("ERROR wrong serial number\nTry Again: ");
					break;
				}
				if(temp->serial_number<branchNum)
					temp=temp->right;
				if(temp->serial_number>branchNum)
					temp=temp->left;
			}
		}
		if(temp->serial_number==branchNum)       /* and checking if the serial */
			branchFlag=0;                        /*    is between 1 and 500    */
		if(branchNum>=1 && branchNum<=500 && branchFlag==0)
			break;
		if(!(branchNum>=1 && branchNum<=500))
			printf("BETWEEN 1 TO 500 !\nTry Again: ");
		temp=branchTree;
	}
	while(temp->serial_number!=branchNum){
		if(temp->serial_number>branchNum)
			temp=temp->left;
		if(temp->serial_number<branchNum)
			temp=temp->right;
	}
	t=temp->Client;
	printf("Enter your bank account: \n");
	while(1){
		scanf("%d",&bankAccount);
		while(t->bankAccount!=bankAccount){/* CHECKING through bankAccount if the client exist */
			if(t->right==NULL && t->left==NULL){
				bankAccountFlag=1;
				printf("There is no client in this branch with that bank account\nTry Again: ");
				break;
			}
			if(t->bankAccount<bankAccount)
				t=t->right;
			else if(t->bankAccount>bankAccount)
				t=t->left;
		}
		if(t->bankAccount==bankAccount)
			bankAccountFlag=0;
		if(bankAccountFlag==0)
			break;
	}
	printf("How much to deposit: \n");
	scanf("%d",&money);
	t->balance+=money;
	Baank.sum+=money;
	temp->sum+=money;
	printf("DONE!\n");
}
/**********************************************************************/
void loanToClient()
{
	int branchNum,bankAccount,money,bankAccountFlag,branchFlag;
	Branch *temp;
	Client *t;/*to not lose the pointer*/
	temp=branchTree;
	bankAccountFlag=0;branchFlag=0;
	if(branchTree==NULL){
		printf("You have to create branch's and client's first\n");
		return;
	}
	printf("Enter your branch number(1 to 500): \n");
	/*Checking the branch number*/
	while(1)
	{
		scanf("%d",&branchNum);
		if(temp->right==NULL && temp->left==NULL){
			if(temp->serial_number!=branchNum){
				branchFlag=1;
				printf("ERROR wrong serial number\nTry Again: ");
			}
		}
		else{
			while(temp->serial_number!=branchNum){             /*Checking if the branch*/
				if(temp->right==NULL && temp->left==NULL){     /*      does exist      */
					branchFlag=1;
					printf("ERROR wrong serial number\nTry Again: ");
					break;
				}
				if(temp->serial_number<branchNum)
					temp=temp->right;
				if(temp->serial_number>branchNum)
					temp=temp->left;
			}
		}
		if(temp->serial_number==branchNum)       /* and checking if the serial */
			branchFlag=0;                        /*    is between 1 and 500    */
		if(branchNum>=1 && branchNum<=500 && branchFlag==0)
			break;
		if(!(branchNum>=1 && branchNum<=500))
			printf("BETWEEN 1 TO 500 !\nTry Again: ");
		temp=branchTree;
	}
	while(temp->serial_number!=branchNum){
		if(temp->serial_number>branchNum)
			temp=temp->left;
		if(temp->serial_number<branchNum)
			temp=temp->right;
	}
	t=temp->Client;
	printf("Enter your bank account: \n");
	while(1){
		scanf("%d",&bankAccount);
		while(t->bankAccount!=bankAccount){/* CHECKING through bankAccount if the client exist */
			if(t->right==NULL && t->left==NULL){
				bankAccountFlag=1;
				printf("There is no client in this branch with that bank account\nTry Again: ");
				break;
			}
			if(t->bankAccount<bankAccount)
				t=t->right;
			else if(t->bankAccount>bankAccount)
				t=t->left;
		}
		if(t->bankAccount==bankAccount)
			bankAccountFlag=0;
		if(bankAccountFlag==0)
			break;
	}
	printf("How much to loan(1$ to 200000$): \n");
	while(1)
	{                                     /*          */
		scanf("%d",&money);               /*          */
		if(money<=200000)                 /* CHECKING */
			break;                        /*          */
		printf("1$ to 200000$! : \n");
	}
	t->duty+=money;
	Baank.loans_num++;
	temp->loans++;
	printf("DONE!\n");
}
/**********************************************************************/
Client* deleteClient(Client *t,int i)
{
	Client *node, *node2, *parent;
	parent = NULL;
	node=ClientTree_find(t,i,&parent);
	if (!node)
		return t;
	if (node->right==NULL && node->left==NULL) {
		if (parent) {
			if (parent->left == node) parent->left=NULL;
			else parent->right=NULL;
			free(node);
			return t;
		} else {
			free(node);
			return NULL;
		}
	}
	if (node->left) {
		node2 = ClientTree_find_max(node->left, NULL);
		clientSwap(t,node->bankAccount, node2->bankAccount);
		node->left = deleteClient(node->left, i);
	} else {
		node2 = ClientTree_find_min(node->right, NULL);
		clientSwap(t,node->bankAccount, node2->bankAccount);
		node->right = deleteClient(node->right, i);
	}
	return t;
}

#include "branch.h"
#include "bank.h"
/******************************************************************************
 *******************************************************************************/
/*----------------------------Help Functions-----------------------------*/
int checkBankAccount(int count,int bankAccount,Client *c,Branch *temp){
	if(temp==NULL)
		return 0;
	if(c==NULL)
		return 0;
	if(c->bankAccount==bankAccount)
		count++;
	count+=checkBankAccount(0,bankAccount,c->right,temp);
	count+=checkBankAccount(0,bankAccount,c->left,temp);
	if(temp->right!=NULL)
		count+=checkBankAccount(0,bankAccount,temp->right->Client,temp->right);
	if(temp->left!=NULL)
		count+=checkBankAccount(0,bankAccount,temp->left->Client,temp->left);
	return count;
}
/*----------------------------Help Functions-----------------------------*/
Branch *tree_find_max(Branch *t, Branch **parent) {
	if(!t)
		return NULL;
	if(t->right) {
		if (parent) *parent = t;
		return tree_find_max(t->right, parent);
	}else{
		return t;
	}
}
/*----------------------------Help Functions-----------------------------*/
Branch *tree_find_min(Branch *t, Branch **parent) {
	if(!t)
		return NULL;
	if(t->left) {
		if (parent) *parent = t;
		return tree_find_min(t->left, parent);
	}else{
		return t;
	}
}
/*----------------------------Help Functions-----------------------------*/
Branch * tree_find(Branch *t, int serialNum, Branch **parent) {
	if (!t)
		return NULL;
	if (serialNum > t->serial_number) {
		if(parent)
			*parent = t;
		return tree_find(t->right,serialNum, parent);
	} else if (serialNum < t->serial_number) {
		if(parent)
			*parent = t;
		return tree_find(t->left,serialNum, parent);
	} else {
		return t;
	}
}
/*----------------------------Help Functions-----------------------------*/
void swap(int serial1,int serial2){
	Branch *temp,*copy1,*copy2;
	copy1=malloc(sizeof(struct branch));
	copy2=malloc(sizeof(struct branch));
	temp=branchTree;
	while(temp->serial_number!=serial1){
		if(temp->serial_number>serial1)
			temp=temp->left;
		if(temp->serial_number<serial1)
			temp=temp->right;
	}
	if(temp->serial_number==serial1){
		copy1->NUMBER_OF_BRANCH_ACCOUNTS=temp->NUMBER_OF_BRANCH_ACCOUNTS;
		copy1->closing=temp->closing;
		copy1->gains=temp->gains;
		copy1->Client=temp->Client;
		copy1->loans=temp->loans;
		copy1->opening=temp->opening;
		copy1->serial_number=temp->serial_number;
		copy1->sum=temp->sum;
		copy1->name=(char*)malloc(strlen(temp->name)*sizeof(char));
		strcpy(copy1->name,temp->name);
	}

	while(temp->serial_number!=serial2){
		if(temp->serial_number>serial2)
			temp=temp->left;
		if(temp->serial_number<serial2)
			temp=temp->right;
	}
	if(temp->serial_number==serial2){
		copy2->NUMBER_OF_BRANCH_ACCOUNTS=temp->NUMBER_OF_BRANCH_ACCOUNTS;
		copy2->closing=temp->closing;
		copy2->gains=temp->gains;
		copy2->Client=temp->Client;
		copy2->loans=temp->loans;
		copy2->opening=temp->opening;
		copy2->serial_number=temp->serial_number;
		copy2->sum=temp->sum;
		copy2->name=(char*)malloc(strlen(temp->name)*sizeof(char));
		strcpy(copy2->name,temp->name);
		/**************************************************************/
		temp->NUMBER_OF_BRANCH_ACCOUNTS=copy1->NUMBER_OF_BRANCH_ACCOUNTS;
		temp->closing=copy1->closing;
		temp->gains=copy1->gains;
		temp->Client=copy1->Client;
		temp->loans=copy1->loans;
		temp->opening=copy1->opening;
		temp->serial_number=copy1->serial_number;
		temp->sum=copy1->sum;
		temp->name=(char*)malloc(strlen(copy1->name)*sizeof(char));
		strcpy(temp->name,copy1->name);
	}
	temp=branchTree;
	while(temp->serial_number!=serial1){
		if(temp->serial_number>serial1)
			temp=temp->left;
		if(temp->serial_number<serial1)
			temp=temp->right;
	}
	if(temp->serial_number==serial1){
		temp->NUMBER_OF_BRANCH_ACCOUNTS=copy2->NUMBER_OF_BRANCH_ACCOUNTS;
		temp->closing=copy2->closing;
		temp->gains=copy2->gains;
		temp->Client=copy2->Client;
		temp->loans=copy2->loans;
		temp->opening=copy2->opening;
		temp->serial_number=copy2->serial_number;
		temp->sum=copy2->sum;
		temp->name=(char*)malloc(strlen(copy2->name)*sizeof(char));
		strcpy(temp->name,copy2->name);
	}
}
/*******************************************************************************
 *******************************************************************************/
void createBranchTree()
{
	branchTree=malloc(sizeof(struct branch));
	branchTree->serial_number=-1;
	printf("DONE!\n");
}
/**********************************************************************/
void addNewBranch()
{
	Branch *temp;
	int serialCheck,serialFlag,sideFlag;
	serialFlag=0;sideFlag=0;
	if(branchTree==NULL){
		printf("You have to Create BranchTree First\n");
		return;
	}
	temp=branchTree;
	printf("enter branch serial number(1 to 500): \n");
	while(1)
	{
		scanf("%d",&serialCheck);
		if(!(serialCheck>=1 && serialCheck<=500)){
			printf("BETWEEN 1 TO 500 !\nTry Again: ");
			continue;
		}
		serialFlag=0;
		sideFlag=0;
		if(temp->serial_number==-1){
			temp->serial_number=serialCheck;
		}
		else{
			while(1){
				if(temp->serial_number==serialCheck){
					serialFlag=1;
					printf("There's another branch with this number\nTry Again:\n");
					break;
				}
				if(temp->serial_number<serialCheck){
					if(temp->right!=NULL)
						temp=temp->right;
					else{
						sideFlag=1;
						break;
					}
				}
				if(temp->serial_number>serialCheck){
					if(temp->left!=NULL)
						temp=temp->left;
					else
						break;
				}
			}
			if(serialFlag==1)
				continue;
			if(sideFlag==1){
				temp->right=malloc(sizeof(struct branch));
				temp->right->serial_number=serialCheck;
			}
			else{
				temp->left=malloc(sizeof(struct branch));
				temp->left->serial_number=serialCheck;
			}
		}
		break;
	}
	printf("enter Branch name: \n");
	temp->name=(char*)malloc(maxSize*sizeof(char));
	scanf("%s",temp->name);
	temp->name=(char*)realloc(temp->name,strlen(temp->name)*sizeof(char));
	printf("enter the branch gains: \n");
	scanf("%d",&temp->gains);
	printf("enter the branch loans: \n");
	scanf("%d",&temp->loans);
	printf("enter the sum: \n");
	scanf("%d",&temp->sum);
	printf("enter the opening time: \n");
	scanf("%d",&temp->opening);
	printf("enter the closing time: \n");
	scanf("%d",&temp->closing);
	Baank.branchs++;
	temp->NUMBER_OF_BRANCH_ACCOUNTS=0;
	printf("DONE!\n");
}
/**********************************************************************/
void createBranchClientTree(int serial_number)
{
	Branch *temp;
	int branchFlag;
	branchFlag=0;
	if(branchTree==NULL){
		printf("You have to Create BranchTree and Branch first\n");
		return;
	}
	temp=branchTree;
	if(temp->right==NULL && temp->left==NULL){
		if(temp->serial_number!=serial_number)
			branchFlag=1;
	}
	else{
		while(temp->serial_number!=serial_number){
			if(temp->right==NULL && temp->left==NULL){
				branchFlag=1;
				printf("Can't find your branch\nThe function didn't worked.\n");
				break;
			}
			if(temp->serial_number<serial_number)
				temp=temp->right;
			else if(temp->serial_number>serial_number)
				temp=temp->left;
		}
	}
	if(branchFlag==1)
		return;
	temp->Client=malloc(sizeof(struct client));
	printf("DONE!\n");
}
/**********************************************************************/
void addNewClientToBranch()
{
	int i,tmp,flag,serialFlag,clientFlag,sideFlag;
	Client *newClient,*c;
	Branch *temp;
	serialFlag=0;clientFlag=0;sideFlag=0;
	if(branchTree==NULL){
		printf("You have to Create BranchTree and Branch first\n");
		return;
	}
	temp=branchTree;
	newClient=malloc(sizeof(struct client));
	printf("enter your first name: \n");
	newClient->first_name=(char *)malloc(maxSize*sizeof(char));
	scanf("%s",newClient->first_name);
	newClient->first_name=(char *)realloc(newClient->first_name,strlen(newClient->first_name)*sizeof(char));
	printf("enter your last name: \n");
	newClient->last_name=(char *)malloc(maxSize*sizeof(char));
	scanf("%s",newClient->last_name);
	newClient->first_name=(char *)realloc(newClient->first_name,strlen(newClient->first_name)*sizeof(char));
	printf("enter your id(9 numbers): \n");
	/*Checking if the ID is a nine numbers ID! */
	while(1)
	{
		flag=0;
		scanf("%d",&newClient->id);
		tmp=newClient->id;
		for(i=0;i<8;i++)
		{
			tmp/=10;
			if(tmp==0)
			{
				printf("Your ID have to be 9 numbers!\n Try again: \n");
				flag=1;
				break;
			}
		}
		if(tmp>9)
		{
			printf("Your ID have to be 9 numbers!\n Try again: \n");
			flag=1;
		}
		if(flag!=1)
			break;
	}
	/*END OF CHECKING*/
	printf("Enter your account number: \n");
	do{
		temp=branchTree;
		scanf("%d",&newClient->bankAccount);
		if(checkBankAccount(0,newClient->bankAccount,temp->Client,temp)==0)
			break;
		else
			printf("Try another account number: \n");
	}while(1);
	printf("Enter the number of the branch(1 to 500): \n");
	/*CHECKING THE BRANCH NUMBER*/
	temp=branchTree;
	while(1)
	{
		scanf("%d",&newClient->number_of_branch);
		if(temp->right==NULL && temp->left==NULL){
			if(temp->serial_number!=newClient->number_of_branch){
				serialFlag=1;
				printf("ERROR wrong serial number\nTry Again: ");
			}
		}
		else{
			while(temp->serial_number!=newClient->number_of_branch){   /*Checking if the branch*/
				if(temp->right==NULL && temp->left==NULL){           /*      does exist      */
					serialFlag=1;
					printf("ERROR wrong serial number\nTry Again: ");
					break;
				}
				if(newClient->number_of_branch>temp->serial_number)
					temp=temp->right;
				if(newClient->number_of_branch<temp->serial_number)
					temp=temp->left;
			}
		}
		if(temp->serial_number==newClient->number_of_branch)       /* and checking if the serial */
			serialFlag=0;                                          /*    is between 1 and 500    */
		if(newClient->number_of_branch>=1 && newClient->number_of_branch<=500 && serialFlag==0)
			break;
		if(!(newClient->number_of_branch>=1 && newClient->number_of_branch<=500))
			printf("BETWEEN 1 TO 500 !\n Try Again: ");
		temp=branchTree;

	}
	printf("Please enter how much is your balance: \n");
	scanf("%d",&newClient->balance);
	printf("enter your deposits: \n");
	scanf("%d",&newClient->deposits);
	printf("enter your deviation: \n");
	scanf("%d",&newClient->deviation);
	printf("enter your duty: \n");
	scanf("%d",&newClient->duty);
	while((newClient->number_of_branch)!=(temp->serial_number)){
		if(temp->serial_number<newClient->number_of_branch)
			temp=temp->right;
		if(temp->serial_number>newClient->number_of_branch)
			temp=temp->left;
	}
	if(temp->Client==NULL){
		temp->Client=newClient;
	}
	else
	{
		c=temp->Client;
		while(1){
			if(c->bankAccount<newClient->bankAccount){
				if(c->right!=NULL)
					c=c->right;
				else{
					sideFlag=1;
					break;
				}
			}
			if(c->bankAccount>newClient->bankAccount){
				if(c->left!=NULL)
					c=c->left;
				else
					break;
			}
		}
		if(sideFlag==1){
			c->right=malloc(sizeof(struct client));
			c->right=newClient;
		}else{
			c->left=malloc(sizeof(struct client));
			c->left=newClient;
		}
	}
	Baank.bank_accounts++;
	Baank.sum+=newClient->balance;
	temp->sum+=newClient->balance;
	temp->NUMBER_OF_BRANCH_ACCOUNTS++;
	printf("DONE!\n");
}
/**********************************************************************/
#ifdef BANK
void printClientAccountsNumberAndBalance(Client *c){
	if(c==NULL)
		return;
	printClientAccountsNumberAndBalance(c->left);
	printf("ID:%d\nBalance:%d\n\n",c->id,c->balance);
	printClientAccountsNumberAndBalance(c->right);
}
#endif
/**********************************************************************/
#ifdef BANK
int clientNumberWithGivenBalance(int count,int num,Client *c){
	if(c==NULL)
		return 0;
	if(c->balance>num)
		count++;
	count+=clientNumberWithGivenBalance(0,num,c->right);
	count+=clientNumberWithGivenBalance(0,num,c->left);
	return count;

}
#endif
/**********************************************************************/
void deleteAllBranchClients()
{
	Branch *temp;
	int serialNum,branchFlag=0;
	temp=branchTree;
	if(branchTree==NULL){
		printf("You have to create branch first\n");
		return;
	}
	printf("Enter the branch number\n");
	/*Checking the branch number*/
	while(1)
	{
		scanf("%d",&serialNum);
		if(temp->right==NULL && temp->left==NULL){
			if(temp->serial_number!=serialNum){
				branchFlag=1;
				printf("ERROR wrong serial number\nTry Again: ");
			}
		}
		else{
			while(temp->serial_number!=serialNum){   /*Checking if the branch*/
				if(temp->right==NULL && temp->left==NULL){                /*      does exist      */
					branchFlag=1;
					printf("ERROR wrong serial number\nTry Again: ");
					break;
				}
				if(temp->serial_number>serialNum)
					temp=temp->left;
				if(temp->serial_number<serialNum)
					temp=temp->right;
			}
		}
		if(temp->serial_number==serialNum)       /* and checking if the serial */
			branchFlag=0;                        /*    is between 1 and 500    */
		if(serialNum>=1 && serialNum<=500 && branchFlag==0)
			break;
		if(!(serialNum>=1 && serialNum<=500))
			printf("BETWEEN 1 TO 500 !\nTry Again: ");
		temp=branchTree;
	}
	/*END OF CHECKING THE BRANCH*/
	temp=branchTree;
	while(temp->serial_number!=serialNum){
		if(serialNum>temp->serial_number)
			temp=temp->right;
		if(serialNum>temp->serial_number)
			temp=temp->right;
	}
	temp->Client=NULL;
	printf("DONE!\n");

}
/**********************************************************************/
Branch *deleteBranch(Branch *t, int i) {
	Branch *node, *node2, *parent;
	parent = NULL;
	node=tree_find(t,i,&parent);
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
		node2 = tree_find_max(node->left, NULL);
		swap(node->serial_number, node2->serial_number);
		node->left = deleteBranch(node->left, i);
	} else {
		node2 = tree_find_min(node->right, NULL);
		swap(node->serial_number, node2->serial_number);
		node->right = deleteBranch(node->right, i);
	}
	return t;
}
/***********************************************************************/
void deleteAllBranches(Branch *root){
	if(root==NULL)
		return;
	deleteAllBranches(root->right);
	deleteAllBranches(root->left);
	free(root);
}

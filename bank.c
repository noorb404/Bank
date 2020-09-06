/*
 * bank.c
 *
 *  Created on: Apr 15, 2016
 *      Author: nor
 */
#include "bank.h"
#include "client.h"
/**************************************************************************
**************************************************************************/
/*----------------------------Help Functions-----------------------------*/
/* rec finding client function */
Client* findAccordingToId(int id,Client *c,Branch *temp){
	if(temp==NULL)
		return NULL;
	if(c==NULL)
		return NULL;
	if(c->id==id)
		return c;
	if(temp->right!=NULL){
		return findAccordingToId(id,temp->right->Client,temp->right);
	}
	if(temp->left!=NULL){
		return findAccordingToId(id,temp->left->Client,temp->left);
	}
	return findAccordingToId(id,c->right,temp);
	return findAccordingToId(id,c->left,temp);
}
/*----------------------------Help Functions-----------------------------*/
/* Rec function.. find the client have the same balance and sorting into a list*/
ClientList* findAccordingToBalance(int balance,ClientList *node,Client *client,Branch *temp){
	if(temp==NULL)
		return node;
	if(client==NULL)
		return node;
	if(client->balance==balance){   /* inserting the client into the list in sorted way. */
		int flag=0;
		ClientList *temp2,*node2;
		if(node==NULL){
			node=malloc(sizeof(struct ClientList));
			node->balance=client->balance;
			node->bankAccount=client->bankAccount;
			node->deposits=client->deposits;
			node->deviation=client->deviation;
			node->duty=client->duty;
			node->id=client->id;
			node->number_of_branch=client->number_of_branch;
			node->first_name=(char*)malloc(strlen(client->first_name)*sizeof(char));
			node->last_name=(char*)malloc(strlen(client->last_name)*sizeof(char));
			strcpy(node->first_name,client->first_name);
			strcpy(node->last_name,client->last_name);
		}
		else{
			temp2=malloc(sizeof(struct ClientList));
			temp2->balance=client->balance;
			temp2->bankAccount=client->bankAccount;
			temp2->deposits=client->deposits;
			temp2->deviation=client->deviation;
			temp2->duty=client->duty;
			temp2->id=client->id;
			temp2->number_of_branch=client->number_of_branch;
			temp2->first_name=(char*)malloc(strlen(client->first_name)*sizeof(char));
			temp2->last_name=(char*)malloc(strlen(client->last_name)*sizeof(char));
			strcpy(temp2->first_name,client->first_name);
			strcpy(temp2->last_name,client->last_name);

			if(node->id < client->id){
				node2=node;     /* node2 is to not destroy the original one*/
				if(node2->next!=NULL){
					while(node2->next->id < client->id){
							node2=node2->next;
						if(node2->next==NULL){
							flag=1;
							break;
						}
					}
				}
				if(flag==1){
					node2->next=temp2;
				}else{
					if(node2->next==NULL){
                      node2->next=temp2;
					}
					else{
						temp2->next=node2->next;
						node2=temp2;
					}
				}
			}
			else{
				temp2->next=node;  /* adding the client to the first node in the list */
				node=temp2;
			}
		}
	}
	if(temp->right!=NULL){
		return findAccordingToBalance(balance,node,temp->right->Client,temp->right);
	}
	if(temp->left!=NULL){
		return findAccordingToBalance(balance,node,temp->left->Client,temp->left);
	}
	return findAccordingToBalance(balance,node,client->right,temp);
	return findAccordingToBalance(balance,node,client->left,temp);
}
/**************************************************************************
**************************************************************************/
int clientNumberOfBank(int Lcount,int count,Client *c,Branch *temp){
	int x;
	if(temp==NULL)
		return 0;
	if(c==NULL)
		return 0;
	if(temp->right!=NULL && count==0){
		count+=clientNumberOfBank(0,0,temp->right->Client,temp->right);
	}
	if(temp->left!=NULL && Lcount==0){
		count+=clientNumberOfBank(0,0,temp->left->Client,temp->left);
	}
	count++;
	Lcount++;
	x=clientNumberOfBank(1,1,c->right,temp);
	if(x!=0)
		count+=x-1;
	else
		count+=x;
	x=clientNumberOfBank(1,1,c->left,temp);
	if(x!=0)
		count+=x-1;
	else
		count+=x;
	return count;

}
/**********************************************************************/
int clientNumberWithBiggerLoansThanBalance(Client *c,int count){
	if(c==NULL)
		return 0;
	if(c->balance<c->duty)
		count++;
	count+=clientNumberWithBiggerLoansThanBalance(c->right,0);
	count+=clientNumberWithBiggerLoansThanBalance(c->left,0);
	return count;
}
/**********************************************************************/
/* in the first time I made the function without using numberOfAccount's
 * but i had to divide the function in the main by branchNumber */
double averageNumberOfAccountsInBranches(int *count,Branch *head){
	int count_l=0,count_r=0;
	double avg_l=0,avg_r=0;
	if(head==NULL){
		*count=0;
		return 0;
	}
	if(head->left==NULL && head->right==NULL){
		*count=1;
		return head->NUMBER_OF_BRANCH_ACCOUNTS;
	}
	avg_r=averageNumberOfAccountsInBranches(&count_r,head->right);
	avg_l=averageNumberOfAccountsInBranches(&count_l,head->left);
	*count=1+count_l+count_r;
	return (avg_l*count_l+avg_r*count_r+head->NUMBER_OF_BRANCH_ACCOUNTS)/(*count);
}
/**************************************************************************/
ClientList* findClient(){
	int option,id,balance;
	Client *clientTemp;
	Branch *branchTemp;
	ClientList *client,*temp;
	branchTemp=branchTree;
	printf("Find a client according to?\n");
	printf("1.ID\n");
	printf("2.Balance\n");
	printf("3.exit\n");
	printf("Choose an option\n");
	scanf("%d",&option);
	if(option==1){
		printf("Enter the ID: ");
		scanf("%d",&id);    /* Help rec function */
		client=(ClientList *)findAccordingToId(id,branchTemp->Client,branchTemp);
		printf("Found!\n");
		printf("ID: %d\nBalance: %d\n",client->id,client->balance);
		return client;
	}
	else if(option==2){
		printf("Enter the Balance: ");
		scanf("%d",&balance);   /* Help rec function */
		client=findAccordingToBalance(balance,client,branchTemp->Client,branchTemp);
		printf("DONE!\n");
		printf("Print the List?\n");
		printf("1.Yes\n");
		printf("2.No\n");
		printf("Choose an option\n");
		scanf("%d",&option);
		if(option==1){
			temp=client;
			while(temp!=NULL){
				printf("ID: %d\nBalance: %d\n\n",temp->id,temp->balance);
				temp=temp->next;
			}
		}
		return client;
	}
	return NULL;
}

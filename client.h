#ifndef _client_h
#define _client_h
#include <stdio.h>
#include <stdlib.h>
typedef struct client{
	char* first_name;
	char* last_name;
	int id;
	int number_of_branch;
	int bankAccount;
	int deviation;
	int balance;
	int duty;
	int deposits;
	struct client *right;
	struct client *left;
}Client;
/* A node struct used for find client..*/
/* made it cause of the next pointer. MORE COMFORTABLE */
typedef struct ClientList{
	char* first_name;
	char* last_name;
	int id;
	int number_of_branch;
	int bankAccount;
	int deviation;
	int balance;
	int duty;
	int deposits;
	struct ClientList *next;
}ClientList;

/************************************************
************************************************/
Client* ClientTree_find_min(Client*,Client**);            /* Help functions used */
Client* ClientTree_find_max(Client*,Client**);            /* in delete function */
Client* ClientTree_find(Client*,int,Client**);
void clientSwap(Client *,int,int);
/************************************************
************************************************/

Client* deleteClient(Client *,int);
/*depositing money function*/
void depositMoneyToClientAccount();
void loanToClient();

#endif

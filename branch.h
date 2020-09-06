#ifndef _branch_h
#define _branch_h
#include <string.h>
#include "client.h"
#define maxSize 30
typedef struct branch{
	int serial_number;
	char* name;
	int NUMBER_OF_BRANCH_ACCOUNTS;
	int sum;
	int gains;
	int loans;
	int opening;
	int closing;
	Client *Client;
	struct branch *right;
	struct branch*left;
}Branch;
Branch *branchTree;
#define BANK
/************************************************
************************************************/
Branch *tree_find_max(Branch *t, Branch **parent);           /*     help function's     */
Branch *tree_find_min(Branch *t, Branch **parent);           /* used in delete function */
int checkBankAccount(int,int,Client*,Branch*);
Branch *tree_find(Branch *t, int serialNum, Branch **parent);
void swap(int,int);
/************************************************
************************************************/
/*Print rec function*/
#ifdef BANK
 void printClientAccountsNumberAndBalance(Client *);
#endif
 void createBranchTree();
/*add new branch*/
void addNewBranch();
void createBranchClientTree(int);
/*add new client*/
void addNewClientToBranch();
/*client's above the given balance.*/
#ifdef BANK
 int clientNumberWithGivenBalance(int,int,Client*);
#endif
void deleteAllBranchClients();
Branch* deleteBranch(Branch*,int);
void deleteAllBranch(Branch*);
#endif

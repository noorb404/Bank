#ifndef _bank_h
#define _bank_h
#include "branch.h"
typedef struct bank{
	char *name;
	int branchs;
	int bank_accounts;
	int sum;
	int gains;
	int loans_num;
}bank;

bank Baank;/*struct that used in the code (global one) */
ClientList* findClient();

/*  help functions for find client  */
Client *findAccordingToId(int,Client*,Branch*);
ClientList* findAccordingToBalance(int,ClientList*,Client*,Branch*);
/************************************/

/*count how much Client's in the branch*/
int clientNumberOfBank(int,int,Client*,Branch*);
/*count the client's that having loans bigger than balance rec*/
int clientNumberWithBiggerLoansThanBalance(Client*,int);
/*average of clients account in the branch's rec. */
double averageNumberOfAccountsInBranches(int*,Branch*);
#endif


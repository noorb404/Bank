#include "bank.h"
#include "branch.h"
#include "client.h"
int main()
{
	int bankAccount,quit,option,serialNum,count,max,x,branchFlag,branchCount;
	Branch *temp;
	Client *c;
	ClientList *b;
	quit=1;count=0;max=-1;
	printf("++++++++++++++++++++++++++++++++++++++++\n");
	printf("Welcome to computerScience bank!\n");
	printf("How we can help you today: ?\n");
	while(1)
	{
		printf("----------------------------------------\n");
		printf("----------------------------------------\n");
		printf("1.Create new branch Tree\n");
		printf("2.Add new branch\n");
		printf("3.Create branch client Tree \n");
		printf("4.Add new client to a branch\n");
		printf("5.Deposit money to client account\n");
		printf("6.Loan to client\n");
		printf("7.Client number of bank\n");
		printf("8.client's in branch that their duty bigger than their balance\n");
		printf("9.Client's number with given balance\n");
		printf("10.Find Client\n");
		printf("11.Delete client\n");
		printf("12.Delete all branch client's\n");
		printf("13.Delete branch\n");
		printf("14.Delete All branches\n");
		printf("15.Average number of account's in branch's\n");
		printf("16.Print branch Client (Id and Balance)\n");
		printf("enter 0 to quit \n");
		printf("----------------------------------------\n");
		printf("----------------------------------------\n");
		printf("Choose an option:\n");
		scanf("%d",&option);
		switch (option){
		case 0:
			break;
		/*CreateBranchTree*/
		case 1:
			createBranchTree();
			break;
		/*add new branch*/
		case 2:
			addNewBranch();
			break;
		/*createBranchClientTree*/
		case 3:
		{
			printf("Enter branch serial number: \n");
			scanf("%d",&serialNum);
			createBranchClientTree(serialNum);
			break;
		}
		/*add new CLient*/
		case 4:
			addNewClientToBranch();
			temp=branchTree;
			break;
		/*deposit money*/
		case 5:
			depositMoneyToClientAccount();
			break;
		/*loan to client*/
		case 6:
			loanToClient();
			break;
		/*ClientNumberOfBranch*/
		case 7:{
			temp=branchTree;
			if(branchTree!=NULL)
				printf("the bank have %d client's\n",clientNumberOfBank(0,0,temp->Client,temp));
			else
				printf("You have to create branch's an client's first\n");
			break;
		}
		/*clientNumberWithBiggerLoansThanBalance*/
		case 8:
		{
			temp=branchTree;
			if(branchTree!=NULL){
				printf("Enter the branch serial number to check\n");
				scanf("%d",&serialNum);
				while(temp->serial_number!=serialNum){
					if(temp->serial_number>serialNum)
						temp=temp->left;
					if(temp->serial_number<serialNum)
						temp=temp->right;
				}
				printf("this branch have %d client's that their duty bigger than their balance\n",clientNumberWithBiggerLoansThanBalance(temp->Client,count));
			}else
				printf("You have to create branch's an client's first\n");
			break;
		}
		/*ClientNumberWithGivenBalance*/
#ifdef BANK
		case 9:{
			if(branchTree!=NULL){
				printf("Enter your branch number (between 1 to 500)\n");
				while(1)
				{
					scanf("%d",&serialNum);
					if(!(serialNum>=1 && serialNum<=500)){
						printf("BETWEEN 1 TO 500 !\nTry Again: ");
						continue;
					}
					if(temp->right==NULL && temp->left==NULL){
						if(temp->serial_number!=serialNum){
							branchFlag=1;
							printf("There is no branch with this number or have been deleted\nTry Again:\n");
						}
					}
					else{
						while(temp->serial_number!=serialNum){           /*Checking if the branch*/
							if(temp->right==NULL && temp->left==NULL){   /*      does exist      */
								branchFlag=1;
								printf("There is no branch with this number or have been deleted\nTry Again:\n");
								break;
							}
							if(temp->serial_number>serialNum)
								temp=temp->left;
							if(temp->serial_number<serialNum)
								temp=temp->right;
						}
					}
					if(temp->serial_number==serialNum){
						branchFlag=0;
						break;
					}
				}
				printf("Enter the number you want to check: \n");
				scanf("%d",&x);
				printf("The bank have %d Client's that their balance above that number\n",clientNumberWithGivenBalance(0,x,temp->Client));
			}else
				printf("You have to create branch's and client's first\n");
			break;
		}
#endif
		/*finding client's*/
		case 10:
			b=findClient();
			break;
		/*delete Client*/
		case 11:
			printf("Enter your branch number(1 to 500): \n");
			/*Checking The branch Number*/
			temp=branchTree;
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
					while(temp->serial_number!=serialNum){           /*Checking if the branch*/
						if(temp->right==NULL && temp->left==NULL){   /*      does exist      */
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
			printf("Enter the bankAccount: ");
			scanf("%d",&bankAccount);
			if((temp->Client->right==NULL && temp->Client->left==NULL) && temp->Client->bankAccount==bankAccount)
			   temp->Client=NULL;
			else
			   deleteClient(temp->Client,bankAccount);
			printf("DONE!\n");
			break;
		/*delete all client's in branch*/
		case 12:
		{
			deleteAllBranchClients();
			break;
		}
		/*delete branch*/
		case 13:{
			printf("Enter your branch number(1 to 500): \n");
			/*Checking The branch Number*/
			temp=branchTree;
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
					while(temp->serial_number!=serialNum){           /*Checking if the branch*/
						if(temp->right==NULL && temp->left==NULL){   /*      does exist      */
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
			temp=branchTree;
			/*END OF CHECKING THE BRANCH*/
			deleteBranch(temp,serialNum);
			printf("DONE!\n");
			break;
		}
		/*delete all branch's*/
		case 14:
			deleteAllBranches(branchTree);
			branchTree=NULL;
			printf("DONE!\n");
			break;
		/*averageNumberOfAccountInBranch's*/
		case 15:{
			temp=branchTree;
			printf("The average is: %g \n",averageNumberOfAccountsInBranches(&branchCount,temp));
			break;
		}
		/*the print function*/
#ifdef BANK
		case 16:{
			/* I did in the main some check's about the branch if exist and if there's no Client.
			 * before calling the function because it's a REC one.*/
			temp=branchTree;
			if(branchTree==NULL){
				printf("You have no Branch's\n");
				break;
			}
			printf("enter the branch number(-1 to get out): ");
			if(branchTree!=NULL){
				while(1)
				{
					scanf("%d",&serialNum);
					if(serialNum==-1)
						break;
					if(!(serialNum>=1 && serialNum<=500)){
						printf("BETWEEN 1 TO 500 !\nTry Again: ");
						continue;
					}
					if(temp->right==NULL && temp->left==NULL){
						if(temp->serial_number!=serialNum){
							branchFlag=1;
							printf("There is no branch with this number or have been deleted\nTry Again:\nPress -1 to Get out\n");
						}
					}
					else{
						while(temp->serial_number!=serialNum){   /*Checking if the branch*/
							if(temp->right==NULL && temp->left==NULL){                /*      does exist      */
								branchFlag=1;
								printf("There is no branch with this number or have been deleted\nTry Again:\nPress -1 to Get out\n");
								break;
							}
							if(temp->serial_number>serialNum)
								temp=temp->left;
							if(temp->serial_number<serialNum)
								temp=temp->right;
						}
					}
					if(temp->serial_number==serialNum){
						branchFlag=0;
						break;
					}
				}
				if(serialNum!=-1){
					temp=branchTree;
					while(temp->serial_number!=serialNum){
						if(temp->serial_number>serialNum)
							temp=temp->left;
						if(temp->serial_number<serialNum)
							temp=temp->right;
					}
					if(temp->Client!=NULL)
						printClientAccountsNumberAndBalance(temp->Client);
					else
						printf("There is no client's in this branch\n");
				}
			}else
				printf("There is no branch with that serial number\n");
			break;
		}
#endif
		}

		if(option==0)
			break;
		while(1){
			printf("******************\n");
			printf("enter 0 to quit \n");
			printf("or 1 to continue\n");
			printf("******************\n");
			scanf("%d",&quit);
			if(quit==0 || quit==1)
				break;

		}
		if(quit==0)
			break;
	}
	printf("Nice to see you! Good bye\n");
	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "stdlist.h"
void printMenu()
{
    printf("USER MANAGEMENT PROGRAM\n");
    printf("--------------------------\n");
    printf("\t1.Register\n");
    printf("\t2.Active\n");
    printf("\t3.Sign in\n");
    printf("\t4.Search\n");
    printf("\t5.Change password\n");
    printf("\t6.Sign out\n");
    printf("\t7.Homepage with domain name\n");
    printf("\t8.Homepage with IP address\n");
    printf("Your choice (1-6, other to quit): ");
}
int readFile(LIST *list, char *file)
{
    FILE *fptr;
    if((fptr=fopen(file,"r")) == NULL)
    {
        printf("File %s is not found\n",file);
        return 0;
    }
    else
    {
        listStudentType temp;
        while (1)
        {
            fscanf(fptr,"%s",temp.name);
            fscanf(fptr,"%s",temp.pass);
            fscanf(fptr,"%d",&temp.status);
            if(feof(fptr)) break;
            insertAfterCurrent(list,temp);
        }
        
    }
    fclose(fptr);
    return 1;
}
void saveFile(LIST *list, char *file)
{
    FILE *fptr = fopen(file,"wb");
    if(list ->root==NULL) return;
    listNode *p;
    for(p=list->root;p!=NULL;p = p->next)
    { 
        fprintf(fptr,"%s %s %d\n", p->frt.name,p->frt.pass,p->frt.status );
    }
    fclose(fptr);
}
int logIn(LIST *list, LIST *listLogin, int *k){
	char tempUser[20];
	char tempPass[20];
    listNode* tempnode;

	do{
		printf("Username: ");
		scanf("%s",tempUser);
		tempnode = searchList(list,tempUser);
		if(tempnode==NULL) printf("Cannot find account\n");
		else if(tempnode->frt.status == 0) printf("Account is blocked\n");
        	else if(tempnode->frt.status == 2) printf("Account need active\n");
	}while(tempnode==NULL||tempnode->frt.status == 0 ||tempnode->frt.status == 2);
	do{
		printf("Password: ");
		scanf("%s",tempPass);
		if(strcmp(tempPass,tempnode->frt.pass)!=0){
			printf("Password is incorrected\n");
			*k+=1;
		}
		else *k=0;
	}while(strcasecmp(tempPass,tempnode->frt.pass)!=0 && *k<3);
	if(*k>=3) {
		tempnode->frt.status = 0;
		printf("Password is incorrected. Account is blocked\n");
		return 0;
	}
	else {
		insertAfterCurrent(listLogin,tempnode->frt);
		printf("Hello %s\n",tempnode->frt.name );
	}
	return 1;
}
void active(LIST *list,  int *k){
	char tempUser[20];
	char tempPass[20];
    char tempCode[20];
    listNode* tempnode;
		printf("Username: ");
		scanf("%s",tempUser);
		tempnode = searchList(list,tempUser);	
	    printf("Password: ");
		scanf("%s",tempPass);
        if(strcmp(tempnode->frt.pass,tempPass)!=0)
        {
            printf("%s","Wrong password!!!\n");
        }
        else
        {
            printf("Code: ");
		    scanf("%s",tempCode);
            if(strcmp(tempCode,"20181234")!=0 )
            {
                	if(*k>=5) {
		            tempnode->frt.status = 0;
		            printf("Activation code is incorrect. Account is blocked\n");
		            return ;
	            }
                else{
                     printf("Account is not activated\n");
			        *k+=1;}
            }	  
		       else *k=0;
        }
    }
        
      
void logOut(LIST *list,LIST *listLogin){
	char tempUser[20];
	listNode* tempnode;

	printf("Username: ");
	scanf("%s",tempUser);
	tempnode = searchList(list,tempUser);
	if(tempnode==NULL) printf("Cannot find account\n");
	else{
		tempnode = searchList(listLogin,tempUser);
		if(tempnode==NULL) printf("Account is not sign in\n");
		else{
			printf("Goodbye %s\n", tempUser);
			deleteNode(listLogin,tempUser);
		}
	}
}
void searchUser(LIST *list){
	char tempUser[20];
	listNode* tempnode;

	printf("Username: ");
	scanf("%s",tempUser);
	tempnode = searchList(list,tempUser);
	if(tempnode==NULL) printf("Cannot find account\n");
	else if(tempnode->frt.status == 0) printf("Account is blocked\n");
    else if(tempnode->frt.status == 2) printf("Account need active\n");
	else printf("Account is active\n");
}
void changePass(LIST *list)
{
    char tempUser[20];
    char tempPass[20];
    char tempNewPass[20];
    listNode *tempnode;

    printf("Username: ");
	scanf("%s",tempUser);
	tempnode = searchList(list,tempUser);
    printf("Password: ");
	scanf("%s",tempPass);
    printf("NewPassword: ");
	scanf("%s",tempNewPass);
    if(strcmp(tempnode->frt.pass,tempPass)!=0)
    {
        printf("Current password is incorrect. Please try again\n");
    }
    else
        {
             memset(tempnode->frt.pass,0,strlen(tempnode->frt.pass));
             strcpy(tempnode->frt.pass,tempNewPass);
             printf("Password is changed\n");
        }


}
int main()
{
    int n;
    LIST *list = newList();
    LIST *listLogin = newList();

    int k=0;
    int k1=0;
    int loginStt=0;
    if(readFile(list,"nguoidung.txt"))
    {
        do
        {
            printMenu();
            scanf("%d",&n);
            switch (n)
            {
            case 1:
                {
                    insertAfterCurrent(list,registerAcc(list));
                }
                break;
            case 2:
                {
                  active(list,&k1);
                }
                break;
            case 3:
			    {
				loginStt=logIn(list,listLogin,&k);
			    }
			    break;
            case 5:
            {
               changePass(list);
            }
            break;
            case 4:
			{
				if (listLogin->root == NULL) loginStt = 0;
				if(loginStt==0) printf("Account is not sign in\n");
				else{
					searchUser(list);
				}
			}
			break;
			case 6:
			{
				if (listLogin->root == NULL) loginStt = 0;
				if(loginStt==0) printf("Account is not sign in\n");
				else{
					logOut(list,listLogin);
				}
			}
            case 7:
            {   
                break;
            }
            case 8:
            {
                break;
            }
            default:
                break;
            }
           
        } while (n==1 || n==2 || n==3 || n==4||n==5||n==6 || n==7 || n==8);
        saveFile(list,"nguoidung.txt");
    }
    return 0;
}

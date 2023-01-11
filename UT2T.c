/*All the "includes needed"*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
/*The main starts*/
void main(void)
{
    int true = ONE, application_flag = ZERO;
    int *app_flag = &application_flag;
    acc_node *head_of_account = (acc_node *)malloc(sizeof(acc_node));
    post_node *post_store;
    acc_node *acc_store;
    head_of_account->next = NULL;
    printf("-----WELCOME TO YOUTI2TI-----");
    printf("-----A place to share ideas-----\n");
    printf("In order to exit, type 'exit' and then press enter.\n");
    printf("You can enter your commands each time!\n");
    while (true)
    {
        switch (commanddecoder())
        {
        case 0:
            printf("Please type commands correctly!\n");
            fflush(stdin);
            break;
        case 1:
            acc_store = signup(head_of_account, app_flag);
            break;
        case 2:
            post_store = login(head_of_account, app_flag);
            break;
        case 3:
            logout(app_flag);
            break;
        case 4:
            info(head_of_account, post_store, app_flag);
            break;
        case 5:
            find_user(head_of_account, app_flag);
            break;
        case 6:
            post(post_store, app_flag);
            break;
        case 7:
            like(post_store, head_of_account, app_flag);
            break;
        case 8:
            del_post(post_store, app_flag);
            break;
        case 9:
            printf("Have a good day!\n");
            true = ZERO;
            break;
        default:
            break;
        }
    }
}
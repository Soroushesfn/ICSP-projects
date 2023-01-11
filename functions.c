/*All the "includes needed"*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
/*definitions of functions*/
int commanddecoder(void)
{
    char *com_holder[] = {COM_ONE, COM_TWO, COM_THREE, COM_FOUR, COM_FIVE,
                          COM_SIX, COM_SEVEN, COM_EIGHT, COM_NINE};
    char *str_store = (char *)malloc(sizeof(char));
    int i = ZERO, decoderflag = ZERO;
    /*To store the first word*/
    while (str_store[i - ONE] != ' ' && str_store[i - 1] != '\n')
    {
        str_store[i] = getchar();
        str_store = (char *)realloc(str_store, sizeof(char) * (i + TWO));
        i++;
    }
    str_store[i] = '\0';
    /*this loop is used for decoding each command*/
    for (i = 0; i < 9; i++)
    {
        if (strcmp(str_store, com_holder[i]) == ZERO)
        {
            decoderflag = ONE;
            free(str_store);
            return i + ONE;
        }
    }
    /*To free up*/
    if (decoderflag == ZERO)
    {
        free(str_store);
        return 0;
    }
}
acc_node *signup(acc_node *head_of_accounts, int *app_flag)
{
    /*To check wether we're signed in or not*/
    if (*app_flag == ZERO)
    {
        acc_node *new_user_acc = (acc_node *)malloc(sizeof(acc_node));
        post_node *new_head_post = (post_node *)malloc(sizeof(post_node));
        acc_node *cur_node = head_of_accounts;
        int signupflag = ZERO, examiner = ZERO;
        char *forbidennames[] = {"login ", "info ", "signup ", "logout ",
                                 "delete ", "post ", "find_user ", "like "};
        char *str_store = (char *)malloc(sizeof(char));
        char *pass_store = (char *)malloc(sizeof(char));
        int i = ZERO;
        /*To store username*/
        while (str_store[i - ONE] != ' ')
        {
            str_store[i] = getchar();
            str_store = (char *)realloc(str_store, sizeof(char) * (i + TWO));
            i++;
        }
        str_store[i] = '\0';
        int num_of_chars = (i + ONE);
        /*To see if the username is allowed*/
        for (int j = 0; j < 8; j++)
        {
            examiner = strcmp(str_store, forbidennames[j]);
            if (examiner == ZERO)
            {
                printf("Can't have this username!\n");
                fflush(stdin);
                signupflag = ONE;
                break;
            }
        }
        /*To check wether the username is take or not*/
        if (signupflag == ZERO)
        {
            while (cur_node != NULL)
            {
                examiner = strcmp(str_store, cur_node->username);
                if (examiner == ZERO)
                {
                    printf("Username already taken!\n");
                    fflush(stdin);
                    signupflag = ONE;
                    break;
                }
                cur_node = cur_node->next;
            }
        }
        /*In order to create a new node*/
        if (signupflag == ZERO)
        {
            new_head_post->like = ZERO;
            new_head_post->post_id = ZERO;
            new_user_acc->username = (char *)malloc(sizeof(char) * num_of_chars);
            new_head_post->username = (char *)malloc(sizeof(char) * num_of_chars);
            new_head_post->next = NULL;
            strcpy(new_user_acc->username, str_store);
            strcpy(new_head_post->username, str_store);
            free(str_store);
            i = ZERO;
            while (pass_store[i - 1] != '\n')
            {
                pass_store[i] = getchar();
                pass_store = (char *)realloc(pass_store, sizeof(char) * (i + TWO));
                i++;
            }
            pass_store[i] = '\0';
            new_user_acc->password = (char *)malloc(sizeof(char) * (i + ONE));
            strcpy(new_user_acc->password, pass_store);
            free(pass_store);
            new_user_acc->head_of_posts = new_head_post;
        }
        cur_node = head_of_accounts;
        /*To add the created node to the linked list*/
        if (signupflag == ZERO)
        {
            acc_node *temp;
            while (cur_node != NULL)
            {
                temp = cur_node->next;
                if (cur_node->next == NULL)
                {
                    cur_node->next = new_user_acc;
                    new_user_acc->next = NULL;
                    printf("New account successfully added!\n");
                    return new_user_acc;
                }
                cur_node = temp;
            }
        }
    }
    else
    {
        printf("You should logout first!\n");
        fflush(stdin);
    }
}
post_node *login(acc_node *head_of_accounts, int *app_flag)
{
    /*to check wether we are signed in or not*/
    if (*app_flag == ZERO)
    {
        acc_node *cur_node = head_of_accounts;
        acc_node *store_node = head_of_accounts;
        int loginflag = ZERO;
        char *username_store = (char *)malloc(sizeof(char));
        char *password_store = (char *)malloc(sizeof(char));
        int i = ZERO;
        int examiner = ZERO;
        /*to store the given username*/
        while (username_store[i - ONE] != ' ')
        {
            username_store[i] = getchar();
            username_store = (char *)realloc(username_store, sizeof(char) * (i + TWO));
            i++;
        }
        username_store[i] = '\0';
        /*To search for the username*/
        while (cur_node != NULL)
        {
            examiner = strcmp(username_store, cur_node->username);
            if (examiner == ZERO)
            {
                store_node = cur_node;
                loginflag = ONE;
                free(username_store);
                break;
            }
            cur_node = cur_node->next;
        }
        /*if the given username is not found*/
        if (loginflag == ZERO)
        {
            printf("Username not found!\n");
            fflush(stdin);
        }
        if (loginflag == ONE)
        {
            i = ZERO;
            /*To store the password*/
            while (password_store[i - ONE] != '\n')
            {
                password_store[i] = getchar();
                password_store = (char *)realloc(password_store, sizeof(char) * (i + TWO));
                i++;
            }
            password_store[i] = '\0';
            examiner = strcmp(store_node->password, password_store);
            /*To examine the password*/
            if (examiner == ZERO)
            {
                *app_flag = ONE;
                printf("Successfully logged in!\n");
                free(password_store);
                return store_node->head_of_posts;
            }
            /*If password is wrong*/
            else
            {
                printf("Wrong password!\n");
                return NULL;
            }
        }
    }
    else
    {
        printf("You should logout first!\n");
        fflush(stdin);
    }
}
void post(post_node *head_of_post, int *app_flag)
{
    /*To check wether we're logged in or not*/
    if (*app_flag == ONE)
    {
        post_node *new_post = (post_node *)malloc(sizeof(post_node));
        post_node *cur_node = head_of_post;
        post_node *temp = NULL;
        char *post_store = (char *)malloc(sizeof(char));
        new_post->username = (char *)malloc(sizeof(char) * (strlen(head_of_post->username)));
        int i = ZERO;
        /*To store the post text*/
        while (post_store[i - 1] != '\n')
        {
            post_store[i] = getchar();
            post_store = (char *)realloc(post_store, sizeof(char) * (i + TWO));
            i++;
        }
        /*To create a new post node*/
        post_store[i] = '\0';
        int number_of_chars = i;
        new_post->post_text = (char *)malloc(sizeof(char) * number_of_chars);
        strcpy(new_post->post_text, post_store);
        free(post_store);
        new_post->liked_accs = (char **)malloc(sizeof(char *));
        strcpy(new_post->username, head_of_post->username);
        new_post->like = ZERO;
        i = ZERO;
        /*In order to add post to the following linked list*/
        while (cur_node != NULL)
        {
            temp = cur_node->next;
            if (cur_node->next == NULL)
            {
                cur_node->next = new_post;
                new_post->next = NULL;
                new_post->post_id = i + ONE;
                printf("New post added to library!\n");
                break;
            }
            i++;
            cur_node = temp;
        }
    }
    /*If not logged in:*/
    else
    {
        printf("You have to be logged in to create a new post!\n");
        fflush(stdin);
    }
}
void logout(int *app_flag)
{
    /*To check wether we're logged in or not*/
    if (*app_flag == ONE)
    {
        *app_flag = ZERO;
        printf("Successfully logged out!\n");
    }
    /*If already logged out:*/
    else
    {
        printf("You are already logged out!\n");
        fflush(stdin);
    }
}
void info(acc_node *head_of_accounts, post_node *head_of_posts, int *app_flag)
{
    /*To check wether we're logged in or not*/
    if (*app_flag == ONE)
    {
        acc_node *cur_acc_node = head_of_accounts->next;
        post_node *cur_node = head_of_posts->next;
        /*To print username:*/
        printf("\nusername: %s\n", head_of_posts->username);
        while (cur_acc_node != NULL)
        {
            /*To print password*/
            if (strcmp(cur_acc_node->username, head_of_posts->username) == ZERO)
            {
                printf("password: %s\n", cur_acc_node->password);
                break;
            }
            cur_acc_node = cur_acc_node->next;
        }
        /*A loop for printing posts' contexts*/
        while (cur_node != NULL)
        {
            printf("Post text: %s", cur_node->post_text);
            printf("Post id: %d\n", cur_node->post_id);
            printf("Number of likes: %d\n", cur_node->like);
            cur_node = cur_node->next;
        }
    }
    else
    /*If not logged in:*/
    {
        printf("You should login first!\n");
        fflush(stdin);
    }
}
void find_user(acc_node *head_of_accounts, int *app_flag)
{
    /*To check wether we're logged in or not*/
    if (*app_flag == ONE)
    {
        int findflag = ZERO, examiner;
        acc_node *cur_node = head_of_accounts;
        acc_node *node_store = NULL;
        post_node *cur_post_node = NULL;
        post_node *head_of_posts = NULL;
        /*To store the given username*/
        char *str_store = (char *)malloc(sizeof(char));
        int i = ZERO;
        while (str_store[i - ONE] != '\n')
        {
            str_store[i] = getchar();
            str_store = (char *)realloc(str_store, sizeof(char) * (i + TWO));
            i++;
        }
        str_store[i - ONE] = ' ';
        str_store[i] = '\0';
        /*To examine wether the following username exists or not*/
        while (cur_node != NULL)
        {
            examiner = strcmp(cur_node->username, str_store);
            if (examiner == ZERO)
            {
                node_store = cur_node;
                findflag = ONE;
                free(str_store);
                break;
            }
            cur_node = cur_node->next;
        }
        /*If the username is found*/
        if (findflag == ONE)
        {
            head_of_posts = node_store->head_of_posts;
            cur_post_node = head_of_posts->next;
            /*To print username*/
            printf("\nUsername: %s\n", head_of_posts->username);
            /*To print posts' contexts*/
            while (cur_post_node != NULL)
            {
                printf("Post text: %s", cur_post_node->post_text);
                printf("Post id: %d\n", cur_post_node->post_id);
                printf("Number of likes: %d\n", cur_post_node->like);
                cur_post_node = cur_post_node->next;
            }
        }
        /*If username wasn't found*/
        else
        {
            printf("Username not found!\n");
        }
    }
    /*If not logged in:*/
    else
    {
        printf("You should be logged in!\n");
        fflush(stdin);
    }
}
void like(post_node *head_of_posts, acc_node *head_of_accounts, int *app_flag)
{
    /*To check wether we're logged in or not*/
    if (*app_flag == ONE)
    {
        int likeflag = ZERO, sec_likeflag = ZERO;
        int i = ZERO, examiner;
        int user_post_id = ZERO;
        acc_node *cur_node = head_of_accounts;
        post_node *cur_post_node = NULL;
        acc_node *node_store = NULL;
        post_node *sec_head_of_posts = NULL;
        /*To store the given username*/
        char *username_store = (char *)malloc(sizeof(char));
        while (username_store[i - ONE] != ' ')
        {
            username_store[i] = getchar();
            username_store = (char *)realloc(username_store, sizeof(char) * (i + TWO));
            i++;
        }
        username_store[i] = '\0';
        scanf("%d", &user_post_id);
        getchar();
        /*To check wether the username exists or not*/
        while (cur_node != NULL)
        {
            examiner = strcmp(cur_node->username, username_store);
            if (examiner == ZERO)
            {
                node_store = cur_node;
                likeflag = ONE;
                free(username_store);
                break;
            }
            cur_node = cur_node->next;
        }
        /*If username exists:*/
        if (likeflag == ONE)
        {
            sec_head_of_posts = node_store->head_of_posts;
            cur_post_node = sec_head_of_posts->next;
            while (cur_post_node != NULL)
            {
                /*for matching the post ids*/
                if (cur_post_node->post_id == user_post_id)
                {
                    likeflag = TWO;
                    for (i = 0; i < cur_post_node->like; i++)
                    /*For checking wether the user has already liked this post or not*/
                    {
                        /*If  it was already liked*/
                        if ((strcmp(head_of_posts->username, cur_post_node->liked_accs[i])) == ZERO)
                        {
                            printf("You have already liked this post!\n");
                            sec_likeflag = ONE;
                            break;
                        }
                        
                    }
                    /*If it was the first time for the user to like this post*/
                    if (sec_likeflag == ZERO)
                    {
                        cur_post_node->like = cur_post_node->like + ONE;
                        cur_post_node->liked_accs = (char **)realloc(cur_post_node->liked_accs, sizeof(char*) * cur_post_node->like);
                        cur_post_node->liked_accs[(cur_post_node->like) - ONE] = head_of_posts->username;
                        printf("Like was added!\n");
                    }
                    break;
                }
                cur_post_node = cur_post_node->next;
            }
            /*If the given id was not found*/
            if (likeflag == ONE)
            {
                printf("A post with the following id was not found!\n");
            }
        }
        /*If username was not found*/
        else
        {
            printf("Username not found!\n");
        }
    }
    /*If not logged in*/
    else
    {
        printf("You should be logged in first!\n");
        fflush(stdin);
    }
}
void del_post(post_node *head_of_posts, int *app_flag)
{
    if (*app_flag == ONE)
    {
        /*To check wether we're logged in or not*/
        post_node *cur_post_node = head_of_posts->next;
        post_node *prev_post_node = head_of_posts;
        int user_post_id = ZERO, del_flag = ZERO;
        /*To scan the given id*/
        scanf("%d", &user_post_id);
        /*Seeking the list untill ids are matched*/
        while (cur_post_node != NULL)
        {
            /*If the ids matched*/
            if (cur_post_node->post_id == user_post_id)
            {
                del_flag = ONE;
                prev_post_node->next = cur_post_node->next;
                free(cur_post_node);
                printf("Post with post_id:%d removed!\n", user_post_id);
                fflush(stdin);
                break;
            }
            cur_post_node = cur_post_node->next;
            prev_post_node = prev_post_node->next;
        }
        /*If the id was not matched:*/
        if (del_flag == ZERO)
        {
            printf("The following post_id doesn't exist!\n");
            fflush(stdin);
        }
    }
    /*If not logged in:*/
    else
    {
        printf("You have to login first!\n");
        fflush(stdin);
    }
}
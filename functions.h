/*All the "define"s needed*/
#define COM_ONE "signup "
#define COM_TWO "login "
#define COM_THREE "logout\n"
#define COM_FOUR "info\n"
#define COM_FIVE "find_user "
#define COM_SIX "post "
#define COM_SEVEN "like "
#define COM_EIGHT "delete "
#define COM_NINE "exit\n"
#define TWO 2
#define ONE 1
#define ZERO 0
/*structures plus there type definitions*/
typedef struct userposts post_node;
struct userposts
{
    char *username;
    int post_id;
    int like;
    char *post_text;
    char **liked_accs;
    struct userposts *next;
};
typedef struct account acc_node;
struct account
{
    char *username;
    char *password;
    post_node *head_of_posts;
    struct account *next;
};
/*declarations of functions*/
int commanddecoder(void);
acc_node *signup(acc_node *head_of_accounts, int *app_flag);
post_node *login(acc_node *head_of_accounts, int *app_flag);
void post(post_node *head_of_post, int *app_flag);
void logout(int *app_flag);
void info(acc_node *head_of_accounts, post_node *head_of_posts, int *app_flag);
void find_user(acc_node *head_of_accounts, int *app_flag);
void like(post_node *head_of_posts, acc_node *head_of_accounts, int *app_flag);;
void del_post(post_node *head_of_posts, int *app_flag);

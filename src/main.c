/******************************************************************************
* Fundamentals of C Programming 
* Group: 37   Lab: 4
* Members:
*     Timothy Gibson    [Removed]
*     [Removed]		[Removed]
*     [Removed]         [Removed]
******************************************************************************/

/***********************PROGRAM INFORMATION***********************************/

/******************************************************************************
* Main file for program execution.
* Defines program specific feature functions - eg. display, search, update ect.
******************************************************************************/

/******************************************************************************
* Compilation:
* In order to compile, use the make file supplied. Simply type "make" into the
* terminal in the root directory. This will compile all the files into object 
* files and create an executable file named "main.out" in the root directory.
******************************************************************************/

/*****************************************************************************
* How to run: 
* Run with "./main add" for the add member mode, "./main edit" for the edit
* member mode, and "./main print_encrypted" to see program's 
* encryption capabilities. 
*******************************************************************************/


/**********************PROGRAM SOURCE CODE*************************************/

/******************************************************************************
header files
******************************************************************************/
#include <stdlib.h>     
/* malloc(), free(), atoi(), atol() */

#include <stdio.h>      
/* printf(), fopen(), fclose(), fseek(), ftell(), rewind(), fwrite(), 
fread(), scanf(), sscanf(), fgets() */

#include <string.h>     
/* strcmp(), strncpy(), strlen(), strstr()*/

#include "../include/member_linked_list.h"      
/* get_member_at_index(), add_member(), add_member_at_index(), del_member(),
del_member_at_index(), clear_all_members() */ 

/******************************************************************************
Constants
******************************************************************************/

#define DATABASE_PATH "outputs/database.b"

#define MODE_ADD 1
#define MODE_DISPLAY_A 2
#define MODE_SAVE_A 3
#define MODE_EXIT_A 4

#define MODE_READ 1
#define MODE_SEARCH 2
#define MODE_DISPLAY_E 3
#define MODE_UPDATE 4
#define MODE_DELETE_INDEX 5
#define MODE_SAVE_E 6
#define MODE_EXIT_E 7

/******************************************************************************
Prototypes
******************************************************************************/
/* Linked List functions TIM */ 

/* Linked List extra features - Mitch */
member_t get_member_data();

void disp_member(memberNode_t* cur_node);
void disp_members(memberNode_t* head_node_p);
void disp_members_encrypted();

int search_members(memberNode_t* head_node_p, int search_category, 
    char search_input[]);
int update_member_details(memberNode_t* cur_node_p, 
    int update_category, char update_input[]);

int save_members_binary(memberNode_t** head_node_p_p, char mode[2]);

int read_members_binary(memberNode_t **head_node_p_p);

void clear(void);

/* Encryption/Decryption - Mitch */
member_t encrypt_decrypt_member(member_t data); 
void xor_cipher(int id, char *string_p);

/* Menu functions - Mitch */ 
int printmenu_add();
int menu_tree_add(int selection, memberNode_t **head_node_p_p); 
int printmenu_edit();
int menu_tree_edit(int selection, memberNode_t **head_node_p_p);

int print_options_update();
int print_options_search();

/******************************************************************************
Main code
******************************************************************************/
int main(int argc, char* argv[]) 
{ 
    memberNode_t* head_node_p = NULL;
    if (argc != 2)
    {
        printf("Invalid number of arguments passed to main.\n");
        printf("Please enter add, edit, or print_encrypted.\n");
        printf("Alternatively, read the README for more instructions.\n");
        return 0; 
    }

    else if (!(strcmp(argv[1], "add")))
    { 
        /* menu_tree_add returns 0 if exit is selected */ 
        /* if exit is selected, break from the while loop */ 
        while(1)
        {
            /*printmenu_add will print the options for the add mode and
            will then return the selected option */
           if (!(menu_tree_add(printmenu_add(), &head_node_p))) 
           {
               break;
           }  
        }
        clear_all_members(&head_node_p);
    }

    else if (!(strcmp(argv[1], "edit")))
    {
        /* menu_tree_edit returns 0 if exit is selected */ 
        /* if exit is selected, break from the while loop */ 
        while(1)
        {
            /*printmenu_edit will print the options for the edit mode and
            will then return the selected option */
           if (!(menu_tree_edit(printmenu_edit(), &head_node_p)))break;  
        }
        clear_all_members(&head_node_p);
    }

    else if (!(strcmp(argv[1], "print_encrypted")))
    {
        disp_members_encrypted();
        return 0;
    }

    else
    {
        printf("Invalid argument. Please enter add or edit.\n");
        printf("Alternatively, read the README for more instructions.\n");
        return 0;
    }
    return 1; 
}

/******************************************************************************
Functions
******************************************************************************/
/******************************************************************************
 * menu_tree_add(): runs functions in correct order to perform selected
 * procedure from 'add' print menu.
 * inputs:
 * - selection: int for selection 
 * outputs:
 * - 0 if exit
 * - 1 if successful procedure execution
*******************************************************************************/
int menu_tree_add(int selection, memberNode_t **head_node_p_p)
{
    if (selection == MODE_EXIT_A)
    {
        return 0; 
    }
    switch(selection)
    {
        case MODE_ADD:
            add_member(head_node_p_p, get_member_data(*head_node_p_p));
            break;
        case MODE_DISPLAY_A:
            disp_members(*head_node_p_p);
            break; 
        case MODE_SAVE_A:
            /* in the add mode, new members should be appended to the existing
            list, this is why "a" is passed as an argument to this function*/
            save_members_binary(head_node_p_p, "a");
            break; 
        default: 
            printf("Invalid choice.");
            break;
    }
    return 1; 
}

/*******************************************************************************
 * menu_tree_edit(): runs functions in correct order to perform selected
 * procedure from 'edit' print menu.
 * inputs:
 * - selection: int for selection 
 * outputs:
 * - 0 if exit
 * - 1 if successful procedure execution
*******************************************************************************/
int menu_tree_edit(int selection, memberNode_t **head_node_p_p)
{
    if (selection == MODE_EXIT_E)
    {
        return 0; 
    }
    int category;
    char input[MAX_PHONE_LEN];
    int index;

    switch(selection)
    {
        case MODE_READ:
            read_members_binary(head_node_p_p);
            break;
        
        case MODE_SEARCH:
            /* print the search options and store the selected category */
            category = print_options_search(); 
            
            printf("Please enter search input> ");
            scanf("%s", input);
            
            index = search_members(*head_node_p_p, category, input);
            if (index > -1)
            {
                printf("Member located at index: %d", index);
            } 
            else
            {
                printf("Member cannot be located");
            }
            break; 
        
        case MODE_DISPLAY_E:
            disp_members(*head_node_p_p);
            break; 

        case MODE_UPDATE:
            printf("Please enter index for member to update> ");
            scanf("%d", &index);

            /* print the update options and store the selected category */
            category = print_options_update(); 

            printf("Please enter update input> ");
            scanf("%s", input);
            
            /* obtain a pointer to the member at a certain index in the Linked
            list */
            memberNode_t* member_node_p = get_member_at_index(*head_node_p_p, index);
            
            update_member_details(member_node_p, category, input);
            break; 

        case MODE_DELETE_INDEX:
             printf("Please enter index for member to delete> ");
             scanf("%d", &index);

             del_member_at_index(head_node_p_p, index);
             break; 
        case MODE_SAVE_E:
        /* in the edit mode, the database is read first in entirety
            then the edited list must overwrite the old database.
            This is why "w" is passed as an argument to this function*/
            save_members_binary(head_node_p_p, "w");
            break; 
        default: 
            printf("Invalid choice.");
            break;
    }
    return 1; 
}

/*******************************************************************************
 * print_options_update(): print update options
 * inputs:
 * - nil  
 * outputs:
 * - select: the selected option
*******************************************************************************/
int print_options_update()
{
    printf("Update one the following categories:\n");
    printf("1. First name\n");
    printf("2. Last name\n");
    printf("3. Phone number\n");
    printf("4. Date of Birth\n");
    printf("5. Subscription\n> ");
    int select = 0; 
    scanf("%d", &select);
    return select; 
}

/*******************************************************************************
 * print_options_search(): print search options
 * inputs:
 * - nil  
 * outputs:
 * - select: the selected option 
*******************************************************************************/
int print_options_search()
{
    printf("Search one of the following categories:\n");
    printf("1. ID number\n");
    printf("2. First Name\n");
    printf("3. Last Name\n");
    printf("4. Phone Number\n> ");
    int select = 0; 
    scanf("%d", &select);
    return select; 
}

/*******************************************************************************
 * printmenu_add(): print a menu to add new members
 * inputs:
 * - nil  
 * outputs:
 * - select: the selected option 
*******************************************************************************/
int printmenu_add()
{
    printf("\n\nSelect from the following options: \n");
    printf("1. Add Member\n");
    printf("2. Display Members\n");
    printf("3. Save Members\n");
    printf("4. Exit\n> ");
    int select = 0; 
    scanf("%d", &select);
    return select; 
}

/*******************************************************************************
 * printmenu_edit(): print a menu to edit existing database
 * inputs:
 * - nil  
 * outputs:
 * - select: the selected option 
*******************************************************************************/
int printmenu_edit()
{
    printf("\n\nSelect from the following options: \n");
    printf("1. Read database\n");
    printf("2. Search for member\n");
    printf("3. Display members\n");
    printf("4. Update member details\n");
    printf("5. Delete member at index\n");
    printf("6. Save members\n");
    printf("7. Exit\n> ");
    int select = 0; 
    scanf("%d", &select);
    return select; 
}

/*******************************************************************************
 * xor_cipher(): apply a xor cipher to a string to encrypt/decrypt the string
 * inputs:
 * - id: the id number of the member to be used as their cipher key. 
 * - string_p: a pointer to the string to be ciphered
 * outputs:
 * - nil
*******************************************************************************/
void xor_cipher(int id, char *string_p)
{
    /* cast the id to a char to have an 8 bit key to use as the xor cipher key*/ 
    char key = (char)id;

    int i = 0; 

    /* iterate through the string applying a xor cipher to each element */
    while(string_p[i] != '\0')
    {
        string_p[i] ^= key;
        i++;
    }
}

/*******************************************************************************
 * encrypt_member(): takes a member's data and returns an encrypted copy
 * inputs:
 * - data: a member_t struct with all of the member's data
 * outputs:
 * - data: a member_t struct with an encrypted version of the input data
*******************************************************************************/
member_t encrypt_decrypt_member(member_t data)
{
    char *first_name_p = data.first_name; 
    char *last_name_p = data.last_name;
    char *phone_number_p = data.phonenumber;
    char *birthday_p = data.dob.day;
    char *birthmonth_p = data.dob.month;
    char *birthyear_p = data.dob.year;
    char *subscription_p = data.subscription;

    xor_cipher(data.id, first_name_p);
    xor_cipher(data.id, last_name_p);
    xor_cipher(data.id, phone_number_p);
    xor_cipher(data.id, birthday_p);
    xor_cipher(data.id, birthmonth_p);
    xor_cipher(data.id, birthyear_p);
    xor_cipher(data.id, subscription_p);

    return data; 
}

/******************************************************************************
* search_members: searches through the linked list to find an exact match of 
  a search term. Will return the first match found in the list. 
* inputs:
* - memberNode_t* head_node_p: pointer to head node of list
* - search_category: integer representing search category 
* - search_input: string containing search input
* output:
* - index: index beginning at 0 of where the sought for record is
* - -1: if record cannot be found, return 0 
******************************************************************************/
int search_members(memberNode_t* head_node_p, int search_category, 
    char search_input[])
{
    memberNode_t* cur_node = head_node_p;
    int index = 0; 

    /* each node points to the next node, the final node points to null.
    this iterates through the linked list until there is a match or the
    list ends */ 
    while (cur_node != NULL)
    {
        /*access current data */
        member_t data = cur_node->data;
        switch(search_category)
        {
            /* depending on search category, make a comparison between the 
            appropriate data*/

            case 1: 
            {   /* as the search term is a string, it must be converted 
                to an int for comparison */ 
                int search_id;
                search_id = atoi(search_input);
                
                /* if there is an exact match, return the while loop's 
                iteration this will represent the index of the member
                in the list */
                if (search_id == data.id)
                {
                    return index;
                }
                break;
            }
            case 2: 
                /* strstr is used to find partial matches in the search
                term and the data */ 
                if (strstr(search_input, data.first_name) != NULL)
                {
                    return index;
                }
                break;

            case 3: 
                if (strstr(search_input, data.last_name) != NULL)
                {
                    return index;
                }
                break;

            case 4: 
                if (strstr(search_input, data.phonenumber) != NULL)
                {
                    return index;
                }
                break;

        }
        index++; 
        cur_node = cur_node->next_p; 
    }
    return -1; 
}

/******************************************************************************
* update_member_details(): update an attribute of a member in the linked list
* inputs:
* - memberNode_t* cur_node_p: pointer to node to edit in list
* - update_category: integer representing update category 
* - update_input: string containing update input
* output:
* - 0: if update failed
* - 1: if update successful 
******************************************************************************/
int update_member_details(memberNode_t* cur_node_p, int update_category,
     char update_input[])
{  
    int birthday; 
    int month; 
    int year; 
    
    /* if no data to update, return 0 */
    if (cur_node_p == NULL)
    {
        return 0; 
    }
    
    switch(update_category)
    {
        /* strncpy used to overwrite string with the update input */
        case 1: 
            strncpy(cur_node_p->data.first_name, update_input, MAX_NAME_LEN);
            break;

        case 2: 
            strncpy(cur_node_p->data.last_name, update_input, MAX_NAME_LEN);
            break;

        case 3:
            strncpy(cur_node_p->data.phonenumber, update_input, MAX_PHONE_LEN); 
            break;

        case 4: 
            /* data validation */ 
            sscanf(update_input, "%d/%d/%d", &birthday, &month, &year); 
            int fail = 0; 
            if (birthday > 31 || birthday < 1)
            {
                fail = 1; 
            }
            if (month > 12 || month < 1)
            {
                fail = 1; 
            }
            if (year > 2017 || year < 1800)
            {
                fail = 1; 
            }
            if (fail)
            {
                printf("Invalid DOB\n");
            }
            else
            {
                char birthday_str[MAX_BDAY_LEN]; 
                sprintf(birthday_str, "%d", birthday);
                char birthmonth_str[MAX_BMON_LEN];
                sprintf(birthmonth_str, "%d", month);
                char birthyear_str[MAX_BYEAR_LEN]; 
                sprintf(birthyear_str, "%d", year);

                strncpy(cur_node_p->data.dob.day, birthday_str, MAX_BDAY_LEN); 
                strncpy(cur_node_p->data.dob.month,birthmonth_str,MAX_BMON_LEN); 
                strncpy(cur_node_p->data.dob.year, birthyear_str, MAX_SUB_LEN); 
            }
            break;

        case 5: 
            strncpy(cur_node_p->data.subscription, update_input, MAX_SUB_LEN); 
            break;
    }
    return 1; 
}

/******************************************************************************
* get_member_data: function used to receive user input for a member's data
* inputs:
* - head_node_p: pointer to the head node
* output:
* - data: a member_t struct containing valid member data 
******************************************************************************/
member_t get_member_data(memberNode_t *head_node_p)
{
    member_t data;

    while(1)
    {
        printf("Enter first name>"); 
        scanf("%10s", data.first_name);
        break;
    }
    
    while(1)
    {
        clear(); /* used to clear stdin to prevent reading previous inputs */
        printf("Enter last name>"); 
        scanf("%10s", data.last_name);
        break;
    }

    while(1)
    {
        clear();
        printf("Enter phone number>");
        scanf("%10s", data.phonenumber);
        break;
    }

    while(1)
    {
        int day;
        clear();
        printf("Enter birthday: day>");
        scanf("%d", &day);
        if (day <= 31 && day >= 1)
        {
            char birthday_str[MAX_BDAY_LEN]; 
            sprintf(birthday_str, "%d", day);
            strncpy(data.dob.day, birthday_str, MAX_BDAY_LEN);
            break;
        }
        printf("Invalid day. ");
    }

    while(1)
    {
        int month;
        clear();
        printf("Enter birthday: month>");
        scanf("%d", &month);
        if (month <= 12 && month >= 1)
        {
            char birthmonth_str[MAX_BMON_LEN]; 
            sprintf(birthmonth_str, "%d", month);
            strncpy(data.dob.month, birthmonth_str, MAX_BMON_LEN);
            break;
        }
        printf("Invalid month. ");
    }
    
    while(1)
    {
        int year; 
        clear();
        printf("Enter birthday: year>");
        scanf("%d", &year);
        if (year <= 2017 && year >= 1800)
        {
            char birthyear_str[MAX_BYEAR_LEN]; 
            sprintf(birthyear_str, "%d", year);
            strncpy(data.dob.year, birthyear_str, MAX_BYEAR_LEN);
            break;
        }
        printf("Invalid year. ");
    }
    
    while(1)
    {
        int sub; 
        clear();
        printf("Enter member level>");
        scanf("%d", &sub);
        if (sub <= 3 && sub >= 1)
        {
            char sub_str[3]; 
            sprintf(sub_str, "%d", sub);
            strncpy(data.subscription, sub_str, MAX_SUB_LEN);
            break;
        }
        printf("Invalid member level. ");
    }
    
    /* create an integer from the first name of the user */
    int i; 
    int sum = 0; 
    for (i = 0; i < 3; i++)
    {
        sum += (int)data.first_name[i]; 
    }

    /* check if this integer is already used in the linked list
    increase by 1 and call recursively until the id hasnt been used */ 
    char sumStr[32];
    sprintf(sumStr, "%d", sum);
    while ((search_members(head_node_p, 1, sumStr)) != -1)
    {
        sprintf(sumStr, "%d", ++sum);
    }
    data.id = sum; 
    return data; 
}

/******************************************************************************
* save_members_binary: save the members of the linked list encrypted
* to the database, then clear the linked list 
* inputs:
* - memberNode_t* head_node_p: pointer to head node of list
* - mode: a string to choose between appending or overwriting
* output:
* - int: flag declaring if db was saved to properly or not 
******************************************************************************/
int save_members_binary(memberNode_t** head_node_p_p, char mode[2])
{
    FILE *db = fopen(DATABASE_PATH, mode);
    memberNode_t* cur_node_p = *head_node_p_p;
    member_t data[1];

    if (db == NULL)
    {
        printf("Save error");
        return 0; 
    }

    while (cur_node_p != NULL)
    {
        data[0] = encrypt_decrypt_member(cur_node_p->data);
        if(fwrite(data, sizeof(member_t), 1, db) != 0)
            printf("contents to file written successfully !\n");
        else
            printf("error writing file !\n");
        cur_node_p = cur_node_p->next_p; 
    }
    fclose(db);
    if (!(strcmp(mode, "a"))) clear_all_members(head_node_p_p);
    return 1; 
}

/******************************************************************************
* read_members_binary: decrypt and save the members of the
* database to a linked list 
* inputs:
* - memberNode_t** head_node_p_p: pointer to head node of list
* output:
* - int: flag declaring if db was read properly or not
******************************************************************************/
int read_members_binary(memberNode_t** head_node_p_p)
{
    FILE *db = fopen(DATABASE_PATH, "r");
    member_t data;

    if (db == NULL)
    {
        printf("Read error");
        return 0; 
    }

    fseek(db, 0, SEEK_END);
    int file_len = ftell(db);
    if (file_len == 0) return 0;
    rewind(db);
    
    while (ftell(db)!= file_len)
    {
        fread(&data, sizeof(member_t), 1, db);
        data = encrypt_decrypt_member(data);
        add_member(head_node_p_p, data);
    }
    fclose(db);
    return 1; 
}

/******************************************************************************
* disp_member: print a member's data to stdout
* inputs:
* - cur_node_p: a pointer to the member to print 
* output:
* - nil
******************************************************************************/
void disp_member(memberNode_t *cur_node_p)
{
    printf("%03d %-10s %-10s %010ld %02d/%02d/%04d %03d\n",
    cur_node_p->data.id, cur_node_p->data.first_name, 
    cur_node_p->data.last_name, atol(cur_node_p->data.phonenumber), 
    atoi(cur_node_p->data.dob.day), atoi(cur_node_p->data.dob.month), 
    atoi(cur_node_p->data.dob.year), atoi(cur_node_p->data.subscription)); 
}

/******************************************************************************
* disp_members: print boilerplate and then 
* iteratively call disp_member for all members of list
* inputs:
* - memberNode_t* head_node_p: pointer to head node of list
* output:
* - nil
******************************************************************************/
void disp_members(memberNode_t* head_node_p)
{
    memberNode_t* cur_node_p = head_node_p;

    printf("ID  First Name Last Name  Phone      DOB        Sub\n");
    printf("--- ---------- ---------- ---------- ---------- ---\n");
    while (cur_node_p != NULL)
    {
        disp_member(cur_node_p);
        
        cur_node_p = cur_node_p->next_p; 
    }
}

/*******************************************************************************
 * clear(): clears the input buffer (stdin) to ensure that whatever is
 * read from stdin is accurate. 
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void clear(void)
{
    char input[MAX_NAME_LEN]; 
    fgets(input, MAX_NAME_LEN, stdin); /* store a string from stdin in input*/
    /* continue to read stdin until the last character is '\n'*/
    while (input[strlen(input)-1] != '\n') 
    {
        fgets(input, MAX_NAME_LEN, stdin);
    }
}

void disp_members_encrypted()
{
    FILE *db = fopen(DATABASE_PATH, "r");
    memberNode_t data;

    if (db == NULL)
    {
        printf("No active database found, run `add` to create a database");
        return;
    }

    fseek(db, 0, SEEK_END);
    int file_len = ftell(db);
    if (file_len == 0) 
    {
        printf("No database entrys, run `add` to create a member");
        return;
    }
    rewind(db);

    printf("ID  First Name Last Name  Phone      DOB        Sub\n");
    printf("--- ---------- ---------- ---------- ---------- ---\n");

    while (ftell(db)!=file_len)
    {
        fread(&data.data, sizeof(member_t), 1, db);
        disp_member(&data);
    }

    return;
}

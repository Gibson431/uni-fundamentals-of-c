/******************************************************************************
 * Source file for member linked list
 * Contains all functions that make up the linked list functionality
******************************************************************************/

#include <stdlib.h> 
/* malloc(), free() */

#include <stdio.h>  
/* printf() */

#include "../include/member_linked_list.h"
/* memberNode_t */

/******************************************************************************
* get_member_at_index:
* - retrives a pointer to a node in the linked list at a given index
* inputs:   
* - (memberNode_t*) head_node_p: pointer to head node of list  
* - (int) index: index of member to get
* output:
* - (memberNode_t*): pointer to member at index
******************************************************************************/
memberNode_t* get_member_at_index(memberNode_t* head_node_p, int index)
{
    int current_index;

    /* set current node to the start of list (head node) */
    memberNode_t* current_node_p = head_node_p;

    /* iterate through to find the requested node */
    for (current_index=0; current_index != index && 
        current_node_p != NULL; current_index++)
    {
        current_node_p = current_node_p->next_p;
    }

    if (current_node_p == NULL)
    {
        printf("Error in get_member_at_index, index %d doesn't exist.", index);
    }
    return current_node_p;
}

/******************************************************************************
* add_member:
* - adds an employee node to the list
* inputs:
* - memberNode_t** head_node_p_p: pointer to variable of pointer to head node
* - member_t data: data to put into new node
* output:
* - memberNode_t*: pointer to head node
******************************************************************************/
memberNode_t* add_member(memberNode_t** head_node_p_p, member_t data)
{
    memberNode_t* new_member_node_p = 
        (memberNode_t*) malloc(sizeof(memberNode_t));

    new_member_node_p->next_p = NULL;
    new_member_node_p->data = data;

    if(*head_node_p_p == NULL)
    {   /* If this is first node in list */

        new_member_node_p->head_p = new_member_node_p;
        new_member_node_p->previous_p = NULL;
        *head_node_p_p = new_member_node_p;
        /* return head */
        return new_member_node_p;
    }
    memberNode_t* current_node_p = *head_node_p_p;
    while(current_node_p->next_p != NULL)
    {   /* while not last node */
        /* go to next node */
        current_node_p = current_node_p->next_p;
    }
    /* set tail to new node */
    current_node_p->next_p = new_member_node_p;
    /* set head_p to head_node_p */
    new_member_node_p->head_p = *head_node_p_p;
    /* set previous_p to current_node_p */
    new_member_node_p->previous_p = current_node_p; 
    return *head_node_p_p;
}

/******************************************************************************
* add_member_at_index:
* - adds a member node to the list in the give position
* inputs:
* - memberNode_t** head_node_p_p: pointer to variable of pointer to head node
* - member_t data: data to put into new node
* - int index: index to insert new member
* output:
* - memberNode_t*: pointer to head node
******************************************************************************/
memberNode_t* add_member_at_index(
    memberNode_t** head_node_p_p, 
    member_t data, 
    int index
    )
{
    
    memberNode_t* new_member_p = (memberNode_t*) malloc(sizeof(memberNode_t));

    /* if memory allocation unsuccessful, return error case */
    if (new_member_p == NULL)
        return NULL;

    /* fill out node with general info */
    new_member_p->data = data;
    new_member_p->head_p = *head_node_p_p;

    /* if requested index is head */
    if (index == 0)
    {   /* set new node's next to previous head */
        new_member_p->next_p = *head_node_p_p;
        /* set new node's prev to null */
        new_member_p->previous_p = NULL;
        /* set old head's prev to new node */
        (*head_node_p_p)->previous_p = new_member_p;
        /* make new node the head node */
        *head_node_p_p = new_member_p;

        return *head_node_p_p;
    }

    /* get node at current index */
    memberNode_t* target_node_p = get_member_at_index(*head_node_p_p, index);

    /* if there is currently no member at requested location */
    if (target_node_p == NULL)
    {   /* clear memory saved for new node */
        free(new_member_p);
        /* add node to end of list */
        add_member(head_node_p_p, data);
        return *head_node_p_p;
    }

    /* set up linking between previous and next node */
    new_member_p->next_p = target_node_p;
    new_member_p->previous_p = target_node_p->previous_p;
    target_node_p->previous_p->next_p = new_member_p;
    target_node_p->previous_p = new_member_p;
    return *head_node_p_p;
}

/******************************************************************************
* del_member:
* - deletes a given node based on an input pointer to target
* inputs:
* - memberNode_t** head_node_p_p: pointer to variable of pointer to head node
* - memberNode_t* target_p: pointer to member to delete
******************************************************************************/
memberNode_t* del_member(memberNode_t** head_node_p_p, memberNode_t* target_p)
{
    if (target_p->previous_p == NULL)
    {   /* target is head */
        /* set head to second node */
        *head_node_p_p = target_p->next_p;
    } 
    else if (target_p->next_p == NULL)
    {   /* target is tail */
        /* set second last node to show no next node */
        target_p->previous_p->next_p = NULL;
    }
    else
    {
        /* set previous node to show it's next node as target's next node */
        target_p->previous_p->next_p = target_p->next_p;
        /* set next node to show it's previous node as target's previous node*/
        target_p->next_p->previous_p = target_p->previous_p;
    }

    /* remove node from memory */
    free(target_p);
    return *head_node_p_p;
}

/******************************************************************************
* del_member_at_index:
* inputs:
* - (memberNode_t**) head_node_p_p: 
* - (int) index: index of member to delete
******************************************************************************/
memberNode_t* del_member_at_index(memberNode_t** head_node_p_p, int index)
{
    /* get node at index */
    memberNode_t* target_p = get_member_at_index(*head_node_p_p, index);

    /* return error case if target does not exist */
    if (target_p == NULL) 
        return NULL;

    del_member(head_node_p_p, target_p);
    return *head_node_p_p;
}

/******************************************************************************
* clear_all_members:
* - clears all members from program memory and empties the list
* inputs:
* - memberNode_t** head_node_p_p: head node of linked list
* output:
* - (int): indicator for valid clear of list
******************************************************************************/
int clear_all_members(memberNode_t** head_node_p_p)
{
    memberNode_t* cur_node_p = *head_node_p_p;

    if (cur_node_p == NULL) return 1;

    /* Goto last node */
    while(cur_node_p->next_p != NULL)
    {
        cur_node_p = cur_node_p->next_p;
    }


    while(cur_node_p->previous_p != NULL)
    {
        cur_node_p = cur_node_p->previous_p;
        free(cur_node_p->next_p);
    }

    free(cur_node_p);
    *head_node_p_p = NULL;
    return 0;
}


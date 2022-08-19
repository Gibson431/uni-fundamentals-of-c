/******************************************************************************
 * Header file for the linked list 
 * Contains memberNode struct and linked list prototypes
******************************************************************************/

#ifndef LIST_H
#define LIST_H 1

#include "member.h" /* member_t */

typedef struct memberNode {
    struct memberNode* head_p;
    struct memberNode* previous_p;
    struct memberNode* next_p;
    member_t data;
} memberNode_t;


/* Linked list prototypes */
memberNode_t* get_member_at_index(memberNode_t* head_node_p, int index);

memberNode_t* add_member(memberNode_t** head_node_p_p, member_t data);
memberNode_t* add_member_at_index(memberNode_t** head_node_p_p, member_t data, int index);

memberNode_t* del_member(memberNode_t** head_node_p_p, memberNode_t* target_p); 
memberNode_t* del_member_at_index(memberNode_t** head_node_p_p, int index); 
int clear_all_members(memberNode_t** head_node_p_p);

#endif

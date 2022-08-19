/******************************************************************************
 * Header file for the member struct
 * Contains a character array for first name, last name, phone number and
 * subscription
******************************************************************************/
#ifndef MEMBER_H
#define MEMBER_H 1

#include "date.h" /* date_t */

#define MAX_NAME_LEN 10
#define MAX_PHONE_LEN 11
#define MAX_SUB_LEN 4

typedef struct member{
    int id;
    char first_name[MAX_NAME_LEN];
    char last_name[MAX_NAME_LEN];
    char phonenumber[MAX_PHONE_LEN];
    date_t dob;
    char subscription[MAX_SUB_LEN];
} member_t;

#endif

/******************************************************************************
 * Header file for the date struct 
 * Contains a character array for day, month, and year of date
******************************************************************************/

#ifndef DATE_H
#define DATE_H 1

#define MAX_BDAY_LEN 3
#define MAX_BMON_LEN 3
#define MAX_BYEAR_LEN 5

typedef struct date{
    char day[MAX_BDAY_LEN];
    char month[MAX_BMON_LEN];
    char year[MAX_BYEAR_LEN];
} date_t;

#endif

#ifndef ABK_H
#define ABK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// contact structure
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

// function declarations
void menu();

void add_contact();
void view_contacts();
void search_contact();
void edit_contact();
void delete_contact();

int contact_exists(const char *name);
void log_event(const char *msg);

#endif

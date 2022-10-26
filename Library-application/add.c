// Copyright Spinochi Andreea, 312CA
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "structs.h"
#include "die.h"
#include "hashmap_functions.h"
#include "get.h"

// adding a book to the library
void
add_book(hashtable_t *ht, char *p, char *aux)
{
    char book_name[45];
    int book_def_no = 0;

    // taking out the name of the book from the entire command
    p = strtok(NULL, "\"");
    strcpy(book_name, p);

    // if the book already exists, then we first free the memory
    if (ht_has_key(ht, book_name) == 1) {
        book_t *book = (book_t *)ht_get(ht, book_name);
        ht_free(book->ht);
        ht_remove_entry(ht, book_name);
    }

    book_t *book_info = book_create(hash_function, compare_function);

    // taking out the number of definitions we will place in the book
    char *p2 = strtok(aux, " ");
    while (p2 != NULL) {
        if (atoi(p2) != 0) {
            book_def_no = atoi(p2);
        }
        p2 = strtok(NULL, " ");
    }

    int i = 0;
    // taking out the definitions and actually placing them in the book
    while (i < book_def_no) {
        char book_name_put[20];
        scanf("%s", book_name_put);

        char book_def[20];
        scanf("%s", book_def);

        ht_put(book_info->ht, book_name_put, 20, book_def, 20);

        i++;
    }

    // putting the book in the library
    ht_put(ht, book_name, 45, book_info, sizeof(book_t));
    free(book_info);
}

// adding definitions to a book
void
add_def(hashtable_t *ht, char *p, char *aux)
{
    char book_name[45];
    char key[21], value[21];

    // taking out the name of the book from the entire command
    p = strtok(NULL, "\"");
    strcpy(book_name, p);

    book_t *book = (book_t *)ht_get(ht, book_name);

    // checking if the book exists in the library or not
    if (ht_has_key(ht, book_name) != 1 || book->lost == 1) {
        printf("The book is not in the library.\n");
        return;
    }

    // taking out the definitions
    char *p2 = strtok(aux, " ");
    while (p2 != NULL) {
        if (p2[strlen(p2) - 1] == '\"') {
            p2 = strtok(NULL, " ");
            strcpy(key, p2);
            p2 = strtok(NULL, " ");
            strcpy(value, p2);
            value[strlen(value) - 1] = '\0';
            p2 = strtok(NULL, " ");
        } else {
            p2 = strtok(NULL, " ");
        }
    }

    // putting the definitions in the book
    ht_put(book->ht, key, 20, value, 20);
}

// adding users
void add_user(hashtable_t *user, char *p)
{
    users_t *user_info = users_create();
    char username[21];

    // taking out the name of the users from the entire command
    p = strtok(NULL, " ");
    strcpy(username, p);

    if (username[strlen(username) - 1] == '\n') {
        username[strlen(username) - 1] = '\0';
    } else {
        username[strlen(username)]= '\0';
    }

    // checking if the user is already registred
    if (ht_has_key(user, username) == 1) {
        printf("User is already registered.\n");
        free(user_info);
        return;
    }

    // actually putting the users in the hashtable
    ht_put(user, username, 21, user_info, sizeof(users_t));

    // deallocating the memory for the user information
    free(user_info);
}

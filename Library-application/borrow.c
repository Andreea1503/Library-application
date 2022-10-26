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
#include "add.h"

// borrowing a book from the library
void borrow_book(hashtable_t *ht, hashtable_t *user, char *p, char *aux)
{
    char username[21];
    unsigned int days_available = 0;

    // cutting the newline character which exists after the username
    strcpy(username, p);
    username[strlen(username) - 1] = '\0';

    char copy[100];

    strcpy(copy, aux);
    char *ptr = strtok(aux, "\"");
    ptr = strtok(NULL, "\"");

    // taking out the name of the book from the entire command
    char book_name[45];
    strcpy(book_name, ptr);

    char *ptr2 = strtok(copy, " ");
    while (ptr2) {
        if (atoi(ptr2) != 0) {
            days_available = atoi(ptr2);
            ptr2 = strtok(NULL, " ");
        } else {
            ptr2 = strtok(NULL, " ");
        }
    }

    // checking if the user is exists
    if (ht_has_key(user, username) != 1) {
        printf("You are not registered yet.\n");
        return;
    }

    users_t *user_info = (users_t *)ht_get(user, username);

    // checking if the user is banned
    if (user_info->banned == 1) {
        printf("You are banned from this library.\n");
        return;
    }

    book_t *book = (book_t *)ht_get(ht, book_name);

    // checking if the user has already borrowed a book
    if (user_info->borrowed == 1) {
        printf("You have already borrowed a book.\n");
        return;
    }

    // checking is the book exists
    if (ht_has_key(ht, book_name) != 1 || book->lost == 1) {
        printf("The book is not in the library.\n");
        return;
    }

    // checking if the book is borrowed
    if (book->reachable == 1) {
        printf("The book is borrowed.\n");
        return;
    }

    // keeping the name of the book in order to know who borrowed what
    strcpy(user_info->book, book_name);
    user_info->borrowed = 1;
    user_info->days_available = days_available;

    book->reachable = 1;
}

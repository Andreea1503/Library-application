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
#include "borrow.h"
#include "return.h"

#define LOST_BOOK 50

void lost_book(hashtable_t *ht, hashtable_t *user, char *p, char *aux)
{
    char username[21];

    // cutting the newline character after the username
    strcpy(username, p);
    username[strlen(username) - 1] = '\0';

    char copy[100];

    strcpy(copy, aux);
    char *ptr = strtok(aux, "\"");
    ptr = strtok(NULL, "\"");

    // taking out the name of the book from the entire command
    char book_name[45];
    strcpy(book_name, ptr);

    users_t *user_info = (users_t *)ht_get(user, username);
    book_t *book = (book_t *)ht_get(ht, book_name);

    // checking if the user exists
    if (ht_has_key(user, username) != 1) {
        printf("You are not registered yet.\n");
        return;
    }

    // checking if the user is banned
    if (user_info->banned == 1) {
        printf("You are banned from this library.\n");
        return;
    }

    // decreasing the user's score
    user_info->users_rating -= LOST_BOOK;

    // if the score is under 0, then the user is banned
    if (user_info->users_rating < 0) {
        user_info->banned = 1;
        printf("The user %s has been banned from this library.\n", username);
        book->lost = 1;
        return;
    }

    book->lost = 1;
    user_info->borrowed = 0;
}

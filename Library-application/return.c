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

void return_book(hashtable_t *ht, hashtable_t *user, char *p, char *aux)
{
    char username[21];
    unsigned int days_since_borrow = 0;
    unsigned int rating;

    // taking out the username from the command and removing the newline
    // character after the string
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
        if (atoi(ptr2) != 0 || strncmp(ptr2, "0", 1) == 0) {
            days_since_borrow = atoi(ptr2);
            ptr2 = strtok(NULL, " ");
            rating = atoi(ptr2);
            ptr2 = strtok(NULL, " ");
        } else {
            ptr2 = strtok(NULL, " ");
        }
    }


    book_t *book = (book_t *)ht_get(ht, book_name);

    // checking if the book is in the library
    if (ht_has_key(ht, book_name) != 1 || book->lost == 1) {
        printf("The book is not in the library.\n");
        return;
    }

    users_t *user_info = (users_t *)ht_get(user, username);

    // checking if the user is banned
    if (user_info->banned == 1) {
        printf("You are banned from this library.\n");
        return;
    }

    // checking if the user has any book borrowed
    if (user_info->borrowed == 0) {
        printf("You didn't borrow this book.\n");
        return;
    }

    // checking if the book the user wants to return is the one they borrowed
    if (strcmp(user_info->book, book_name) != 0) {
        printf("You didn't borrow this book.\n");
        return;
    }

    user_info->days_since_borrow = days_since_borrow;

    // calculating the user's score
    if (user_info->days_available < user_info->days_since_borrow) {
        user_info->users_rating -= ((user_info->days_since_borrow -
        user_info->days_available) * 2);
    } else if (user_info->days_available > user_info->days_since_borrow) {
        user_info->users_rating += (double)user_info->days_available -
        (double)user_info->days_since_borrow;
    }

    // if the user's score goes below 0, then the user is banned
    if (user_info->users_rating < 0) {
        user_info->banned = 1;
        printf("The user %s has been banned from this library.\n", username);
        book->reachable = 0;
        book->points += rating;
        book->borrow++;
        book->purchases++;
        return;
    }

    book->reachable = 0;
    book->points += rating;
    book->borrow++;
    book->purchases++;
    book->lost = 0;

    user_info->borrowed = 0;
    strcpy(user_info->book, "");
}

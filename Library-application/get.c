// Copyright Spinochi Andreea, 312CA
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "structs.h"
#include "die.h"
#include "hashmap_functions.h"

#define LOST_BOOK 50

// getting and printing a book
void get_book(hashtable_t *ht, void *key)
{
    // checking if the book exists in the library
    if (ht_has_key(ht, key) != 1) {
        printf("The book is not in the library.\n");
    } else {
        book_t *book = (book_t *)ht_get(ht, key);
        // only displaying the information if the book isn't lost
        if (book->lost == 0) {
            if (book->borrow != 0) {
                book->book_rating = book->points / book->borrow;
            }
            printf("Name:%s Rating:%.3f Purchases:%d\n", (char *)key,
                    book->book_rating, book->purchases);
        } else {
            printf("The book is not in the library.\n");
        }
    }
}

void get_def(hashtable_t *ht, char *p, char *aux)
{
    char book_name[45];
    char key[21];

    // taking out the name of the book from the entire command
    p = strtok(NULL, "\"");
    strcpy(book_name, p);

    // taking out the definitions of the book
    char *p2 = strtok(aux, " ");
    while (p2 != NULL) {
        if (p2[strlen(p2) - 1] == '\"') {
            p2 = strtok(NULL, " ");
            strcpy(key, p2);
            key[strlen(key) - 1] = '\0';
        } else {
            p2 = strtok(NULL, " ");
        }
    }

    book_t *book = (book_t *)ht_get(ht, book_name);

    // checking if the book is in the library
    if (ht_has_key(ht, book_name) != 1 || book->lost == 1) {
        printf("The book is not in the library.\n");
        return;
    }

    // checking if the definition we want to print is in the book
    if (ht_has_key(book->ht, key) != 1) {
        printf("The definition is not in the book.\n");
        return;
    }

    char *value = (char *)ht_get(book->ht, key);
    printf("%s\n", value);
}

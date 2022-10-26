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

// removing the definitions of a book
void remove_def(hashtable_t *ht, char *p, char *aux)
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
    if (ht_has_key(ht, book_name) == 0 || book->lost == 1) {
        printf("The book is not in the library.\n");
        return;
    }

    // checking if the definition is in the book
    if (ht_has_key(book->ht, key) == 0) {
        printf("The definition is not in the book.\n");
        return;
    }

    // actually removing the definition from the book
    ht_remove_entry(book->ht, key);
}

// removing a book from the library
void remove_book(hashtable_t *ht, char *p)
{
    char book_name[45];

    // taking out the name of the book
    p = strtok(NULL, "\"");
    strcpy(book_name, p);

    book_t *book = (book_t *)ht_get(ht, book_name);

    // actually removing the book from the library
    ht_free(book->ht);
    ht_remove_entry(ht, book_name);
}

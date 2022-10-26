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
#include "remove.h"
#include "borrow.h"
#include "return.h"
#include "lost.h"
#include "exit.h"

#define LOST_BOOK 50
#define MAX_NAME 40
#define MAX 100

int main(void)
{
    hashtable_t *user = ht_create(10, hash_function, compare_function);
    hashtable_t *hashmap = ht_create(10, hash_function, compare_function);
    char book_name[MAX_NAME];

    while (1) {
        char command[MAX];
        fgets(command, MAX, stdin);

        char aux[MAX];
        strcpy(aux, command);
        char *p;

        if (strncmp(command, "EXIT", 4) == 0) {
            exit_program(hashmap, user);
        }

        if (strstr(command, "\"") == NULL) {
            p = strtok(command, " ");
        } else {
            p = strtok(command, "\"");
        }

        if (strcmp("ADD_BOOK ", p) == 0) {
            add_book(hashmap, p, aux);

        } else if (strcmp("GET_BOOK ", p) == 0) {
            p = strtok(NULL, "\"");
            strcpy(book_name, p);

            get_book(hashmap, book_name);
        } else if (strcmp("RMV_BOOK ", p) == 0) {
            remove_book(hashmap, p);

        } else if (strcmp("ADD_DEF ", p) == 0) {
            add_def(hashmap, p, aux);

        } else if (strcmp("GET_DEF ", p) == 0) {
            get_def(hashmap, p, aux);

        } else if (strcmp("RMV_DEF ", p) == 0) {
            remove_def(hashmap, p, aux);

        } else if (strcmp("ADD_USER", p) == 0) {
            add_user(user, p);

        } else if (strncmp("BORROW", p, 6) == 0) {
            char copy[MAX];
            strcpy(copy, p + 7);

            borrow_book(hashmap, user, copy, aux);
        } else if (strncmp("RETURN", p, 6) == 0) {
            char copy[MAX];
            strcpy(copy, p + 7);

            return_book(hashmap, user, copy, aux);
        } else if (strncmp("LOST", p, 4) == 0) {
            char copy[MAX];
            strcpy(copy, p + 5);

            lost_book(hashmap, user, copy, aux);
        }
    }

    return 0;
}

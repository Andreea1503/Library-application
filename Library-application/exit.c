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

// printing the book information in a precise order
void book_ranking(hashtable_t *ht)
{
    linked_list_t *sorting_list = ll_create(sizeof(info));

    // copying the elements inside a list, so we can easily sort them
    for (unsigned int i = 0; i < ht->hmax; i++) {
        ll_node_t *curr = ht->buckets[i]->head;
        while (curr != NULL) {
            book_t *book = (book_t *)curr->data;
            info *aux = (info *)book;
            ll_add_nth_node(sorting_list, sorting_list->size, aux);
            curr = curr->next;
        }
    }

    ll_node_t *current = sorting_list->head, *index = NULL;
    info *temp;

    while (current != NULL) {
        index = current->next;

        while (index != NULL) {
            // swaping the nodes according to some criteria
            info *book1 = (info *)current->data;
            info *book2 = (info *)index->data;

            book_t *data1 = (book_t *)book1->value;
            book_t *data2 = (book_t *)book2->value;

            if (data1->borrow != 0) {
                data1->book_rating = data1->points / data1->borrow;
            }

            if (data2->borrow != 0) {
                data2->book_rating = data2->points / data2->borrow;
            }

            if (data1->book_rating < data2->book_rating) {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            } else if (data1->book_rating == data2->book_rating &&
                data1->points < data2->points) {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            } else if (data1->book_rating == data2->book_rating &&
                data1->points == data2->points &&
                strcmp(book1->key, book2->key) > 0) {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }

            index = index->next;
            }
            current = current->next;
            }

    int cnt = 1;
    current = sorting_list->head;
    printf("Books ranking:\n");

    // printing the book information in the new order
    while (current != NULL) {
        info* book_info = (info *)current->data;
        book_t *data = (book_t *)book_info->value;
        if (data->borrow != 0) {
            data->book_rating = data->points / data->borrow;
        }
        if (data->lost == 0) {
            printf("%d. Name:%s Rating:%.3f Purchases:%d\n", cnt,
                    (char *)book_info->key, data->book_rating,
                    data->purchases);
            cnt++;
            }
        current = current->next;
    }

    // deallocating the memory used for sorting the books
    ll_free(&sorting_list);
}

// displaying the user information in a precise order
void user_ranking(hashtable_t *user)
{
    linked_list_t *sorting_list = ll_create(sizeof(info));

    // copying the elements inside a list so we can easily sort them
    for (unsigned int i = 0; i < user->hmax; i++) {
        ll_node_t *curr = user->buckets[i]->head;
        while (curr != NULL) {
            ll_add_nth_node(sorting_list, sorting_list->size,
                            (info *)curr->data);
            curr = curr->next;
        }
    }
    ll_node_t *current = sorting_list->head, *index = NULL;
    info *temp;

        while (current != NULL) {
            index = current->next;

            while (index != NULL) {
                // swapping the nodes according to some criteria
                info *user1 = (info *)current->data;
                info *user2 = (info *)index->data;

                users_t *user_data1 = (users_t *)user1->value;
                users_t *user_data2 = (users_t *)user2->value;

                if (user_data1->users_rating < user_data2->users_rating) {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                } else if (user_data1->users_rating == user_data2->users_rating
                           && strcmp(user1->key, user2->key) > 0) {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }

                index = index->next;
            }
            current = current->next;
        }

    int cnt = 1;
    current = sorting_list->head;
    printf("Users ranking:\n");
    // displaying the user information in the new order
    while (current != NULL) {
        info *user = (info *)current->data;
        users_t *user_data = (users_t *)user->value;
        if (user_data->banned == 0) {
            printf("%d. Name:%s Points:%d\n", cnt, (char *)user->key,
                    (int)user_data->users_rating);
            cnt++;
        }
        current = current->next;
    }

    // deallocationg the memory used for sorting the users
    ll_free(&sorting_list);
}

void exit_program(hashtable_t *ht, hashtable_t *user)
{
    // displaying the information about the users and books
    book_ranking(ht);
    user_ranking(user);

    // deallocating all the memory used for the entire program
    ht_free(user);

    for (unsigned int i = 0; i < ht->hmax; i++) {
        ll_node_t *curr = ht->buckets[i]->head;
        while (curr != NULL) {
            info *book_name = (info *)curr->data;
            book_t *book = (book_t *)ht_get(ht, book_name->key);
            ht_free(book->ht);
            curr = curr->next;
        }
    }

    ht_free(ht);
    exit(0);
}

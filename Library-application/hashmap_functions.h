// Copyright Spinochi Andreea, 312CA

#ifndef HASHMAP_FUNCTIONS_H_
#define HASHMAP_FUNCTIONS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "structs.h"
#include "die.h"

linked_list_t*
ll_create(unsigned int data_size);
ll_node_t*
create_node(const void* new_data, unsigned int data_size);
void
ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data);
ll_node_t*
ll_remove_nth_node(linked_list_t* list, unsigned int n);
ll_node_t*
get_nth_node(linked_list_t* list, unsigned int n);
int
compare_function(void *a, void *b);
unsigned int
hash_function(void *a);
hashtable_t *
ht_create(unsigned int hmax, unsigned int (*hash_function)(void*),
		int (*compare_function)(void*, void*));
book_t *
book_create(unsigned int (*hash_function)(void*),
		int (*compare_function)(void*, void*));
users_t *
users_create();
int
ht_has_key(hashtable_t *ht, void *key);
void*
ht_get(hashtable_t *ht, void *key);
void ht_redim(hashtable_t *ht, unsigned int old_size);
void
ht_resize(hashtable_t *hashmap);
void
ht_put(hashtable_t *ht, void *key, unsigned int key_size,
	void *value, unsigned int value_size);
void
ht_remove_entry(hashtable_t *ht, void *key);
void
ht_free(hashtable_t *ht);
void
ll_free(linked_list_t** pp_list);

#endif  // HASHMAP_FUNCTIONS_H_

// Copyright Spinochi Andreea, 312CA
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <stdint.h>
#include "structs.h"
#include "die.h"
#define MIN(x, y) ((x) < (y) ? (x) : (y))

ll_node_t*
get_nth_node(linked_list_t* list, unsigned int n)
{
	unsigned int len = list->size - 1;
	unsigned int i;
	ll_node_t* node = list->head;

	n = MIN(n, len);

	for (i = 0; i < n; ++i)
		node = node->next;

	return node;
}

linked_list_t*
ll_create(unsigned int data_size)
{
	linked_list_t* ll = calloc(1, sizeof(*ll));
    DIE(!ll, "Calloc failed\n");

	ll->data_size = data_size;

	return ll;
}

ll_node_t*
create_node(const void* new_data, unsigned int data_size)
{
	ll_node_t* node = calloc(1, sizeof(*node));
    DIE(!node, "Calloc failed\n");

	node->data = malloc(data_size);
    DIE(!node->data, "Malloc failed\n");

	memcpy(node->data, new_data, data_size);

	return node;
}

void
ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data)
{
	ll_node_t *new_node, *prev_node;

	if (!list)
		return;

	new_node = create_node(new_data, list->data_size);

	if (!n || !list->size) {
		new_node->next = list->head;
		list->head = new_node;
	} else {
		prev_node = get_nth_node(list, n - 1);
		new_node->next = prev_node->next;
		prev_node->next = new_node;
	}

	++list->size;
}

ll_node_t*
ll_remove_nth_node(linked_list_t* list, unsigned int n)
{
	ll_node_t *prev_node, *removed_node;

	if (!list || !list->size)
		return NULL;

	if (!n) {
		removed_node = list->head;
		list->head = removed_node->next;
		removed_node->next = NULL;
	} else {
		prev_node = get_nth_node(list, n - 1);
		removed_node = prev_node->next;
		prev_node->next = removed_node->next;
		removed_node->next = NULL;
	}

	--list->size;

	return removed_node;
}

int
compare_function(void *a, void *b)
{
	char *str_a = (char *)a;
	char *str_b = (char *)b;

	return strcmp(str_a, str_b);
}

unsigned int
hash_function(void *a)
{
	unsigned char *puchar_a = (unsigned char*) a;
	uint64_t hash = 5381;
	int c;

	while ((c = *puchar_a++))
		hash = ((hash << 5u) + hash) + c;

	return hash;
}

hashtable_t *
ht_create(unsigned int hmax, unsigned int (*hash_function)(void*),
		int (*compare_function)(void*, void*))
{
	if (!hash_function || !compare_function) {
        return NULL;
    }

    hashtable_t* map = malloc(sizeof(hashtable_t));
    DIE(!map, "Malloc failed\n");

    map->size = 0;
    map->hmax = hmax;
    map->hash_function = hash_function;
    map->compare_function = compare_function;

    map->buckets = malloc(map->hmax * sizeof(linked_list_t *));
    DIE(!map->buckets, "Malloc failed\n");

    for (unsigned int i = 0; i < map->hmax; ++i) {
        map->buckets[i] = ll_create(sizeof(info));
    }

    return map;
}

book_t *
book_create(unsigned int (*hash_function)(void*),
		int (*compare_function)(void*, void*))
{
	if (!hash_function || !compare_function) {
        return NULL;
    }

    book_t* book = malloc(sizeof(book_t));
    DIE(!book, "Malloc failed\n");

    book->ht = ht_create(10, hash_function, compare_function);

    book->reachable = 0;
    book->book_rating = 0;
    book->points = 0;
    book->borrow = 0;
    book->purchases = 0;
    book->lost = 0;

    return book;
}


users_t *
users_create()
{
    users_t *user_info = malloc(sizeof(users_t));
    DIE(!user_info, "Malloc failed\n");

    user_info->users_rating = 100;
    user_info->banned = 0;
    user_info->days_available = 0;
    user_info->days_since_borrow = 0;
    user_info->borrowed = 0;

    return user_info;
}

int
ht_has_key(hashtable_t *ht, void *key)
{
	if (!ht || !key) {
        return -1;
    }

    int hash_index = ht->hash_function(key) % ht->hmax;
    ll_node_t* node = ht->buckets[hash_index]->head;

    while (node != NULL) {
        info* data_info = (info *)node->data;
        if (!ht->compare_function(data_info->key, key)) {
            return 1;
        }
        node = node->next;
    }

	return 0;
}

void*
ht_get(hashtable_t *ht, void *key)
{
	if (!ht || !key || ht_has_key(ht, key) != 1) {
        return NULL;
    }

    int hash_index = ht->hash_function(key) % ht->hmax;
    ll_node_t* node = ht->buckets[hash_index]->head;

    while (node != NULL) {
        info* data_info = (info *)node->data;
        if (!ht->compare_function(data_info->key, key)) {
            return data_info->value;
        }
        node = node->next;
    }

	return NULL;
}

void ht_redim(hashtable_t *ht, unsigned int old_size)
{
    unsigned int i;
	linked_list_t **aux = (linked_list_t **)realloc(ht->buckets,
						ht->hmax * sizeof(linked_list_t *));
	DIE(!aux, "Realloc failed\n");

	ht->buckets = aux;
	for (i = old_size; i < ht->hmax; i++)
		ht->buckets[i] = ll_create(sizeof(struct info));

	for (i = 0; i < old_size; i++) {
        int count = 0;
		ll_node_t *it = ht->buckets[i]->head, *curr;
		while (it != NULL) {
			void *key = ((struct info *)(it->data))->key;
			unsigned int index = (unsigned int)ht->hash_function(key) % (ht->hmax);
            count++;
			it = it->next;
			if (index == i)
				continue;
			curr = ll_remove_nth_node(ht->buckets[i], count - 1);
			if (!ht->buckets[i]->size)
				ht->size--;
			if (!ht->buckets[old_size + i]->size)
				ht->size++;
			ll_add_nth_node(ht->buckets[old_size + i],
							ht->buckets[old_size + i]->size, curr->data);
			free(curr->data);
			free(curr);
		}
	}
}

void
ht_resize(hashtable_t *hashmap)
{
    unsigned int old_size = hashmap->hmax;
    hashmap->hmax *= 2;
    ht_redim(hashmap, old_size);
}

void
ht_put(hashtable_t *ht, void *key, unsigned int key_size,
	void *value, unsigned int value_size)
{
	if (!ht || !key || !value) {
        return;
    }

    int hash_index = ht->hash_function(key) % ht->hmax;

    if (ht_has_key(ht, key) == 1) {
        ll_node_t* node = ht->buckets[hash_index]->head;
        while (node != NULL) {
            info* data_info = node->data;

            if (!ht->compare_function(data_info->key, key)) {
                free(data_info->value);

                data_info->value = malloc(value_size);

                memcpy(data_info->value, value, value_size);
                return;
            }

            node = node->next;
        }
    }

    info* data_info = malloc(sizeof(info));
    DIE(!data_info, "Malloc failed\n");

    data_info->key = malloc(key_size);
    DIE(!data_info->key, "Malloc failed\n");

    data_info->value = malloc(value_size);
    DIE(!data_info->value, "Malloc failed\n");

    memcpy(data_info->key, key, key_size);
    memcpy(data_info->value, value, value_size);

    ll_add_nth_node(ht->buckets[hash_index], 0, data_info);
    ht->size++;

    int resizable = 0;

    for (unsigned int i = 0; i < ht->hmax; i++) {
        resizable += ht->buckets[i]->size;
    }

    if (ht->size != 0) {
        if (resizable / ht->size > 1) {
            ht_resize(ht);
        }
    }

    free(data_info);
}

void
ht_remove_entry(hashtable_t *ht, void *key)
{
	if (!ht || !key || ht_has_key(ht, key) != 1) {
        return;
    }

    int hash_index = ht->hash_function(key) % ht->hmax;
    ll_node_t* node = ht->buckets[hash_index]->head;

    unsigned int node_nr = 0;

    while (node != NULL) {
        info* data_info = (info *) node->data;

        if (!ht->compare_function(data_info->key, key)) {
            free(data_info->key);
            free(data_info->value);
            free(data_info);

            ll_node_t* deleted_node =
            ll_remove_nth_node(ht->buckets[hash_index], node_nr);
            free(deleted_node);

            ht->size--;
            return;
        }

        node = node->next;
        node_nr++;
    }
}

void
ll_free(linked_list_t** pp_list)
{
	ll_node_t* node;

	if (!pp_list || !*pp_list)
		return;

	while ((*pp_list)->size) {
		node = ll_remove_nth_node(*pp_list, 0);
		free(node->data);
		free(node);
	}

	free(*pp_list);
	*pp_list = NULL;
}

void
ht_free(hashtable_t *ht)
{
	if (!ht) {
        return;
    }

    for (unsigned int i = 0; i < ht->hmax; ++i) {
        ll_node_t* node = ht->buckets[i]->head;

        while (node != NULL) {
            info* data_info = (info *)node->data;
            free(data_info->key);
            free(data_info->value);
            node = node->next;
        }

        ll_free(&ht->buckets[i]);
    }

    free(ht->buckets);
    free(ht);
}

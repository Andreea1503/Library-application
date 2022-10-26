// Copyright Spinochi Andreea, 312CA

#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct ll_node_t ll_node_t;
struct ll_node_t
{
	void* data;
	ll_node_t* next;
};

typedef struct linked_list_t linked_list_t;
struct linked_list_t
{
	ll_node_t* head;
	unsigned int data_size;
	unsigned int size;
};

typedef struct info info;
struct info {
	void *key;
	void *value;
};

typedef struct hashtable_t hashtable_t;
struct hashtable_t {
	linked_list_t **buckets;
	unsigned int size;
	unsigned int hmax;
	unsigned int (*hash_function)(void*);
	int (*compare_function)(void*, void*);
};

typedef struct book_t book_t;
struct book_t {
	hashtable_t *ht;
    unsigned int reachable;
    double book_rating;
    double points;
    double borrow;
    unsigned int lost;
    unsigned int purchases;
};

typedef struct users_t users_t;
struct users_t {
    char book[45];
    unsigned int borrowed;
    double users_rating;
    unsigned int banned;
    unsigned int days_available;
    unsigned int days_since_borrow;
};

#endif  // STRUCTS_H_

// Copyright Spinochi Andreea, 312CA

#ifndef ADD_H_
#define ADD_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "structs.h"
#include "die.h"
#include "hashmap_functions.h"
#include "get.h"

void
add_book(hashtable_t *ht, char *p, char *aux);
void
add_def(hashtable_t *ht, char *p, char *aux);
void add_user(hashtable_t *user, char *p);

#endif  // ADD_H_

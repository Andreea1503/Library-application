// Copyright Spinochi Andreea, 312CA

#ifndef GET_H_
#define GET_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "structs.h"
#include "die.h"
#include "hashmap_functions.h"

void get_book(hashtable_t *ht, void *key);
void get_def(hashtable_t *ht, char *p, char *aux);

#endif  // GET_H_

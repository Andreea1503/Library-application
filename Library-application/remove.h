// Copyright Spinochi Andreea, 312CA

#ifndef REMOVE_H_
#define REMOVE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "structs.h"
#include "die.h"
#include "hashmap_functions.h"
#include "get.h"

void remove_def(hashtable_t *ht, char *p, char *aux);
void remove_book(hashtable_t *ht, char *p);

#endif  // REMOVE_H_

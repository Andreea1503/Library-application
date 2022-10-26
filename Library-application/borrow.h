// Copyright Spinochi Andreea, 312CA

#ifndef BORROW_H_
#define BORROW_H_

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

void borrow_book(hashtable_t *ht, hashtable_t *user, char *p, char *aux);

#endif  // BORROW_H_

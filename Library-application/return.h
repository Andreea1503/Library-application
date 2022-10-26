// Copyright Spinochi Andreea, 312CA

#ifndef RETURN_H_
#define RETURN_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "structs.h"
#include "die.h"
#include "hashmap_functions.h"
#include "remove.h"
#include "get.h"
#include "add.h"
#include "borrow.h"

void return_book(hashtable_t *ht, hashtable_t *user, char *p, char *aux);

#endif  // RETURN_H_

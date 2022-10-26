// Copyright Spinochi Andreea, 312CA

#ifndef LOST_H_
#define LOST_H_

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
#include "borrow.h"
#include "return.h"

void lost_book(hashtable_t *ht, hashtable_t *user, char *p, char *aux);

#endif  // LOST_H_

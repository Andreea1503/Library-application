// Copyright Spinochi Andreea, 312CA

#ifndef EXIT_H_
#define EXIT_H_

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
#include "lost.h"

void book_ranking(hashtable_t *ht);
void user_ranking(hashtable_t *user);
void exit_program(hashtable_t *ht, hashtable_t *user);

#endif  // EXIT_H_

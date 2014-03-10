/*
 * Copyright (c) 2014 Jerry Lundström <lundstrom.jerry@gmail.com>
 * Copyright (c) 2014 .SE (The Internet Infrastructure Foundation).
 * Copyright (c) 2014 OpenDNSSEC AB (svb)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __db_result_h
#define __db_result_h

struct db_result;
struct db_result_list;
typedef struct db_result db_result_t;
typedef struct db_result_list db_result_list_t;

#include "db_value.h"

struct db_result {
	db_result_t* next;
	db_value_set_t* value_set;
};

db_result_t* db_result_new(void);
void db_result_free(db_result_t*);
const db_value_set_t* db_result_value_set(const db_result_t*);
int db_result_set_value_set(db_result_t*, db_value_set_t*);
int db_result_not_empty(const db_result_t*);
const db_result_t* db_result_next(const db_result_t*);

struct db_result_list {
	db_result_t* begin;
	db_result_t* end;
};

db_result_list_t* db_result_list_new(void);
void db_result_list_free(db_result_list_t*);
int db_result_list_add(db_result_list_t*, db_result_t*);
const db_result_t* db_result_list_begin(const db_result_list_t*);

#endif
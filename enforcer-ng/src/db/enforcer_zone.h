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

#ifndef __enforcer_zone_h
#define __enforcer_zone_h

struct enforcer_zone;
struct enforcer_zone_list;
typedef struct enforcer_zone enforcer_zone_t;
typedef struct enforcer_zone_list enforcer_zone_list_t;

#include "db_object.h"
#include "key_data.h"
#include "adapter.h"
#include "key_dependency.h"

struct enforcer_zone {
	db_object_t* dbo;
	char* name;
	char* policy;
	int signconf_needs_writing;
    char* signconf_path;
    int next_change;
    int ttl_end_ds;
    int ttl_end_dk;
    int ttl_end_rs;
    int roll_ksk_now;
    int roll_zsk_now;
    int roll_csk_now;
	int next_ksk_roll;
	int next_zsk_roll;
	int next_csk_roll;
};

enforcer_zone_t* enforcer_zone_new(const db_connection_t*);
void enforcer_zone_free(enforcer_zone_t*);
key_data_list_t* enforcer_zone_get_keys(const enforcer_zone_t*);
adapter_list_t* enforcer_zone_get_adapters(const enforcer_zone_t*);
key_dependency_list_t* enforcer_zone_get_key_dependencies(const enforcer_zone_t*);

struct enforcer_zone_list {
	db_object_t* dbo;
	db_result_list_t* result_list;
	db_result_t* result;
};

enforcer_zone_list_t* enforcer_zone_list_new(const db_connection_t*);
void enforcer_zone_list_free(enforcer_zone_list_t*);
int enforcer_zone_list_get(void);
const enforcer_zone_t* enforcer_zone_list_begin(enforcer_zone_list_t*);
const enforcer_zone_t* enforcer_zone_list_next(const enforcer_zone_list_t*);

#endif
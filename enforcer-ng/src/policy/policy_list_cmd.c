/*
 * Copyright (c) 2011 Surfnet 
 * Copyright (c) 2011 .SE (The Internet Infrastructure Foundation).
 * Copyright (c) 2011 OpenDNSSEC AB (svb)
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

#include "config.h"

#include "daemon/cmdhandler.h"
#include "shared/log.h"
#include "shared/str.h"
#include "daemon/engine.h"
#include "daemon/clientpipe.h"
#include "db/policy.h"

#include "policy/policy_list_cmd.h"

/* static const char *module_str = "policy_list_cmd"; */

static void
usage(int sockfd)
{
	client_printf(sockfd,
		"policy list            List policies.\n");
}

static void
help(int sockfd)
{
	client_printf(sockfd,
		"List all policies in the database\n"
	);
}

static int
handles(const char *cmd, ssize_t n)
{
	return ods_check_command(cmd, n, policy_list_funcblock()->cmdname)?1:0;
}

static int
run(int sockfd, engine_type* engine, const char *cmd, ssize_t n,
	db_connection_t *dbconn)
{
	const char *fmt = "%-31s %-48s\n";
	policy_list_t *pol_list;
	const policy_t *policy;
	(void)cmd; (void)n; (void)engine;

	if (!(pol_list = policy_list_new(dbconn)))
		return 1;
	if (policy_list_get(pol_list)) {
		policy_list_free(pol_list);
		return 1;
	}

	/* May want to keep this for compatibility?
	 * client_printf(sockfd, "Database set to: %s\nPolicies:\n",
		engine->config->datastore);*/
	client_printf(sockfd, fmt, "Policy:", "Description:");

	policy = policy_list_begin(pol_list);
	while (policy) {
		client_printf(sockfd, fmt, policy_name(policy),
			policy_description(policy));
		policy = policy_list_next(pol_list);
	}
	policy_list_free(pol_list);
	return 0;
}

static struct cmd_func_block funcblock = {
	"policy list", &usage, &help, &handles, &run
};

struct cmd_func_block*
policy_list_funcblock(void)
{
	return &funcblock;
}
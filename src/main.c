/* 
# Copyright (c) 2016, Anis Elleuch / vadmeste at gmail dot com
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <keyutils.h>
#include <assert.h>

#include "config.h"
#include "str-replace.h"
#include "sm_opts.h"

#define SM_MAGIC 0x534d5f4d

#define KEY_PAYLOAD_MAXLEN 512
#define SESSION_NAME_MAXLEN 512


void
print_usage()
{
	fprintf(stderr, "USAGE:\n");
	fprintf(stderr, "  secret-manager  [FLAGS] [CMD [ARGS...]] \n");
	fprintf(stderr, "\n");
	fprintf(stderr, "FLAGS:\n");
	fprintf(stderr, "    -h   Show this help. \n");
	fprintf(stderr, "    -v   Show version information. \n");
	fprintf(stderr, "    -s   Show current key id. \n");
	fprintf(stderr, "    -t   Set the key id timeout. \n");
	fprintf(stderr, "    -q   Quit the keyring session. \n");
	fprintf(stderr, "    -r   Specify the replace string. \n");
	fprintf(stderr, "\n");
	fprintf(stderr, "VERSION: " PACKAGE_VERSION "\n");
}

int
main(int argc, char *argv[])
{
	int ret = 1;
	char *secret_cmd = NULL;
	char *subprocess_argv[4];

	struct sm_opts *opts = NULL;

	key_serial_t key_id; 
	char key_payload[KEY_PAYLOAD_MAXLEN];
	char session_name[SESSION_NAME_MAXLEN];

	// parse_opts gives use default values if not provided
	opts = sm_opts_parse(argc, argv);
	if (opts == NULL) {
		ret = 1;
		goto exit;
	}

	if (opts->flags & OPT_HELP || opts->flags & OPT_UNRECOGNIZED) {
		print_usage();
		ret = 0;
		goto exit;
	}

	if (opts->flags & OPT_VERSION) {
		fprintf(stderr, PACKAGE_NAME " " PACKAGE_VERSION "\n");
		ret = 0;
		goto exit;
	}

	// We deal with only one session name for the moment
	sprintf(session_name, "sm-session-%u", SM_MAGIC);

	// Start to request a key in the current session if present
	key_id = request_key("user", session_name, NULL, KEY_SPEC_SESSION_KEYRING);

	if (opts->flags & OPT_QUIT ) {
		if (key_id > 0)
			keyctl_revoke(key_id);
		else
			fprintf(stderr, "No keyring session could be found.\n");
		ret = 0;
		goto exit;
	}

	if (opts->flags & OPT_SHOW_KEYID) {
		if (key_id > 0) {
			printf("%d\n", key_id);
			ret = 0;
			goto exit;
		} else {
			fprintf(stderr, "No key is attached to the current session.\n");
			ret = 1;
			goto exit;
		}
	}

	if (key_id <= 0) {
		// Ask the user to enter his secret phrase and
		memset(key_payload, 0, KEY_PAYLOAD_MAXLEN);
		sprintf(key_payload, "%s", getpass("Secret: "));
		if (strlen(key_payload) == 0) {
			fprintf(stderr, "An empty secret phrase is not supported.\n");
			ret = 1;
			goto exit;
		}
		key_id = add_key("user", session_name, key_payload, 
				strlen(key_payload), KEY_SPEC_SESSION_KEYRING); 
		if (key_id < 0) {
			fprintf(stderr, "FATAL: Cannot add a passphrase, is CONFIG_KEYS enabled in your kernel?\n");
			ret = 1;
			goto exit;
		}
		// To be able to find again the passphrase in the next execution of sm,
		// we have to attach the current keyring session to the shell
		// interpreter which executed this cmd
		keyctl_session_to_parent();
	} else {
		// Read the passphrase
		memset(key_payload, 0, KEY_PAYLOAD_MAXLEN);
		if (keyctl_read(key_id, key_payload, KEY_PAYLOAD_MAXLEN) < 0) {
			ret = 1;
			goto exit;
		}
	}

	// We should have here a valid key id, so trigger the timeout again
	keyctl_set_timeout(key_id, (unsigned int) opts->timeout_sec);

	// Replace all {} occurrences by the secret phrase
	secret_cmd = replace_str(opts->cmd, opts->repl_str, key_payload);

	// Execute the secret cmd
	if (secret_cmd) {
		// Replacing the current executable image will at least return the exit
		// code of the executed command
		subprocess_argv[0] = "sh";
		subprocess_argv[1] = "-c";
		subprocess_argv[2] = secret_cmd;
		subprocess_argv[3] = NULL;
		execvp("/bin/sh", subprocess_argv);

		assert(0);
	}

exit:
	if (opts)
		sm_opts_free(opts);

	return ret;
}


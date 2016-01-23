
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "opts.h"

void
sm_opts_free(struct sm_opts *opts) 
{
	if (opts == NULL)
		return;
	if (opts->cmd != NULL)
		free(opts->cmd);
	if (opts->repl_str != NULL)
		free(opts->repl_str);
	free(opts);
}

struct sm_opts*
sm_opts_parse(int argc, char *argv[])
{
	int ch;

	struct sm_opts *opts = malloc(sizeof(struct sm_opts));
	opts->flags = 0;
	opts->repl_str == NULL;
	opts->cmd == NULL;

	// Disable printing getopt errors
	opterr = 0;

	// Parse passed options
	while (1) {
		int option_index = 0;
		static struct option long_options[] = {
			{"replace", required_argument, 0, 'r' },
			{"help", no_argument, 0, 'h' },
			{"quit", required_argument, 0, 'q' },
			{0, 0, 0, 0 }
		};
		// + will stop parsing when getopt encouters a non flag arg
		ch = getopt_long(argc, argv, "+hqr:", long_options, &option_index);
		if (ch == -1)
			break;
		switch (ch) {
			case 'h':
				opts->flags |= OPT_HELP;
				break;
			case 'r':
				opts->repl_str = strdup(optarg);
				break;
			case 'q':
				opts->flags |= OPT_QUIT;
				break;
			default:
				opts->flags |= OPT_UNRECOGNIZED;
		}
	}

	// Set opts default values
	if (opts->repl_str == NULL)
		opts->repl_str = strdup("{}");
	opts->cmd = strdup("");

	// Construct the cmd string
	if (optind < argc) {
		while (optind < argc) {
			// printf("debug -- [%s]\n", argv[optind]);
			opts->cmd = (char *) realloc(opts->cmd, 
					strlen(opts->cmd) + strlen(" ") + strlen(argv[optind]) + 1);
			strcat(opts->cmd, argv[optind]);
			strcat(opts->cmd, " ");
			optind++;
		}
	}

	return opts;
}


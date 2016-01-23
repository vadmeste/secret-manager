
#ifndef _OPTS_H
#define _OPTS_H

#define OPT_HELP 0x0001
#define OPT_QUIT 0x0002
#define OPT_REPLACE_STR 0x0004
#define OPT_UNRECOGNIZED 0x0008

// opts structure holds sm global data
struct sm_opts {
	int flags;
	char *cmd;
	char *repl_str;
};

struct sm_opts *sm_opts_parse(int argc, char *argv[]);
void sm_opts_free(struct sm_opts *opts);

#endif

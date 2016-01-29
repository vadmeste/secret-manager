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

#ifndef _OPTS_H
#define _OPTS_H

#define OPT_HELP 0x0001
#define OPT_VERSION 0x0002
#define OPT_QUIT 0x0004
#define OPT_REPLACE_STR 0x0008
#define OPT_SHOW_KEYID 0x00010
#define OPT_UNRECOGNIZED 0x0020

// opts structure holds sm global data
struct sm_opts {
	int flags;
	char **argv;
	char *repl_str;
	int timeout_sec;
};

struct sm_opts *sm_opts_parse(int argc, char *argv[]);
void sm_opts_free(struct sm_opts *opts);

#endif

/* 
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* replace_str(char* buffer, char* old_str, char* new_str)
{
	char *new_p = NULL, *pos;
	char *cur_p = buffer;

	if (buffer == NULL)
		return NULL;

	if (old_str == NULL || new_str == NULL)
		return strdup(buffer);

	new_p = malloc(1);
	memset(new_p, 0, 1);

	while (pos = strstr(cur_p, old_str)) {
		new_p = (char*) realloc(new_p, pos - cur_p + strlen(new_str) + 1);
		strncat(new_p, cur_p, pos - cur_p );
		strcat(new_p, new_str);
		cur_p = pos + strlen(old_str);
	}

	if (*new_p != '\0') {
		strcat(new_p, cur_p);
		return new_p;
	} else {
		return strdup(buffer);
	}
}


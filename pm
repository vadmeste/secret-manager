#!/bin/bash
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
# AUTHOR: vadmeste at gmail dot com (Anis Elleuch)
# README: https://github.com/vadmeste/pm/blob/master/README.md
#
# STILL BETA version. Use it at your own risk.
#

[ -z "$(which keyctl 2>/dev/null)" ] &&
    echo "Please install keyutils tool with your package manager" \
	    "or from https://people.redhat.com/dhowells/keyutils/" && exit 1

while getopts ":sh" opt; do
  case ${opt} in
    s)
      keyctl session ; echo "Quitting keyring session.." && exit 0
      ;;
    h)
      echo "USAGE: pm [-h | -s] [cmd [args..]]"
      echo "    -h   show this help."
      echo "    -s   start a new keyring session."
      exit 1
      ;;
    \?)
      echo "${OPTARG} : invalid option"
      exit 1
      ;;
  esac
done

# Retrieve the key belonging to the current keyring session, 
# ask for password otherwise
_pwd_keyid=$(keyctl request user pm_key 2>/dev/null || ( \
		read -s -p "Password: " pm_pwd && \
		keyctl add user pm_key "${pm_pwd}" @s \
	    ))

_pwd_payload=$(keyctl print "${_pwd_keyid}" 2>/dev/null)

[ -z "${_pwd_keyid}" -o -z "${_pwd_payload}" ] && \
	echo "Cannot find your password payload. Quitting.." && exit 1

# Replace {} by the actual password and execute the cmd
$(echo $@ | sed "s/{}/$(keyctl print "${_pwd_keyid}")/g")


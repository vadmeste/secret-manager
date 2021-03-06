# secret-manager [![Join the chat at https://gitter.im/vadmeste/secret-manager](https://badges.gitter.im/vadmeste/secret-manager.svg)](https://gitter.im/vadmeste/secret-manager?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge) [![Build Status](https://travis-ci.org/vadmeste/secret-manager.svg?branch=master)](https://travis-ci.org/vadmeste/secret-manager)
A simple secret manager for CLI. Only GNU/Linux is supported.  
(under heavy development, use it at your own risk !!)

## Demo
[![demo](https://asciinema.org/a/1j03c37d83jlkh6t53st85h8n.png)](https://asciinema.org/a/1j03c37d83jlkh6t53st85h8n?autoplay=1)

## Building

Before compiling, you should ensure that keyutils library is installed and CONFIG_KEYS is enabled in your kernel, then:

```
$ bash autogen.sh
$ ./configure
$ make
```

## User story

To see the help message:
```
$ sm -h
```

To execute an arbitrary command:
```
$ sm curl http://your_username:{}@hostname/path
Secret:
```

sm will ask for a password which will replace {} in your entered command. The password is asked only once and it will be lost when you quit your session.
```
$ sm curl http://your_username:{}@hostname/another_path
...
```

To quit your sm session
```
$ sm -q
```

## Bash prompt customization

Add the following line in your .bashrc,
```
PROMPT_COMMAND="sm -s &>/dev/null && echo -ne '\e[1;31m[session open] \e[0m'"
```


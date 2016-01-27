# secret-manager [![Join the chat at https://gitter.im/vadmeste/secret-manager](https://badges.gitter.im/vadmeste/secret-manager.svg)](https://gitter.im/vadmeste/secret-manager?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge) 
A simple secret manager for CLI.
(under heavy development, use it at your own risk !!)

## Building

Before compiling, you should ensure that keyutils library is installed and CONFIG_KEYS is enabled in your kernel, then:

```
$ bash autogen.sh
$ ./configure
$ make
```

## User story

* To see the help message:
  ```
  $ sm -h
  ```

* To execute an arbitrary command:
  ```
  $ sm curl http://your_username:{}@hostname/path
  Secret:
  ```
  sm will ask for a password which will replace {} in your entered command. The password is asked only once and it will be lost when you quit your session.
  ```
  $ sm curl http://your_username:{}@hostname/another_path
  ...
	```

* To quit your sm session
  ```
  $ sm -q
  ```

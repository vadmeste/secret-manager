# secret-manager
A simple secret manager for CLI.

## Building

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

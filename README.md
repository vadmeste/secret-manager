# pm
A simple password manager for CLI.

## Installation
No installation script for the moment because pm is still under heavy development.

## Manual installation

```
$ wget "https://raw.githubusercontent.com/vadmeste/pm/master/pm"
$ chmod +x pm
```

Then, add the pm directory in your PATH environment variable in ~/.bashrc. Then you have to install keyutils and be sure that CONFIG_KEYS is enabled in your Linux kernel.

## User story

* To see the help message:
```
$ pm -h
```

* To start a new pm session:
```
$ pm -s
```

* To execute an arbitrary command:
```
$ pm curl http://your_username:{}@hostname/path
Password: 
```

pm will ask for a password which will replace {} in your entered command. The password is asked only once and it will be lost when you quit your session.

```
$ pm curl http://your_username:{}@hostname/another_path
...
```

* To quit your pm session
```
$ exit
```

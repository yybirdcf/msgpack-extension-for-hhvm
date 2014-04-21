msgpack-extension-for-hhvm
==========================

A simple msgpack extension implement for hhvm, a simple try

###Environment

The extension is developed at ubuntu12.04 and gcc version 4.8.1

###Installing

* First, you need install hhvm : [HHVM](https://github.com/facebook/hhvm)

* Second, you need install msgpack-c : 

```
$ wget https://github.com/msgpack/msgpack-c/releases/download/cpp-0.5.8/msgpack-0.5.8.tar.gz
$ tar zxvf msgpack-0.5.8.tar.gz
$ cd msgpack-0.5.8
$ ./configure
$ make
$ sudo make install
```

* Then, sh build.sh or chmod +x build.sh and ./build.sh

* If everything is ok, you can see msgpack.so in the folder, now add below to your hhvm config.hdf:

```
DynamicExtensions {
  msgpack = /path/to/msgpack.so
}
```

###Testing

* Simple test: hhvm test/test.php

###Report Errors
First, I am sorry about anything unexpected! If you get any trouble when installing and running the extension , please tell me (haipengchencf@gmail.com); 
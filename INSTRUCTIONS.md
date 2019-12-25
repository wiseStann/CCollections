## Build and Run
### - Build

First of all, you need to clone this repository on your local PC:
</br>
```
$ git clone https://github.com/StarKerrr/CCollections.git
```
When you clone this repository on your local machine, change your current directory to this Project folder:
</br>
```
$ cd CCollections
```
To build a pipeline Cmake needs to know where is the source folder and where is binary folder. The source folder is where your CMakeLists.txt is located. Binary folder you have to create manually and usually it is named 'build'. Using an empty "build" directory is a technique called "out-of-source build", in which all your generated files are generated in the separate "build" directory and not mixed with source files. So, make a 'build' folder and go into it:
```
$ mkdir build
$ cd build
```
The next what you have to do is to execute 'cmake' command with specifying directory with source files, in order to generate Makefile following the instructions in CMakeLists.txt in root directory. In our case directory with source files is the parent directory so you just type in dot 2 times:
```
$ cmake ..
```
The next step is to execute 'make' command which builds executable programs and libraries from source code:
```
$ make
```
When all files are generated, you should install the public headers, in order to use it in your programs. By default, all libraries will be installed in usr/local/include directory:
```
$ sudo make install
```

### - Running

&nbsp; &nbsp; &nbsp; Well, now we have built the project and we want to use the library in our code. Let's assume that we have a file 'test.c':

```c
#include <stdio.h>
#include <stdlib.h>
#include <Collections/array.h>

int main(int argc, char** argv)
{
    Array* arr = arrayNew();
    arrayToEnd(arr, (void*)10);
    arrayToEnd(arr, (void*)20);
    arrayToEnd(arr, "Something");
    arrayReverseMut(arr);
    
    void* end = arrayGetEnd(arr);
    printf("The end of array = %d\n", toInteger(end));
}
```

You want to compile this code and run the binary. You can do it with Static and Dynamic Linking:

* Static. To link your code statically, you have to add flag -static to the command and directly tell compiler what the lib should be used: </br>

(GCC compiler)
```
$ gcc test.c -static -lCollections -o test
``` 
(CLANG compiler)
```
$ clang test.c -static -lCollections -o test
```

* Dynamic. To link your code dynamically, you can just remove -static flag from your command. You just have to tell compiler what the library should be used addind -l flag: </br>

(GCC compiler)
```
$ gcc test.c -lCollections -o test
```
(CLANG)
```
$ clang test.c -lCollections -o test
```
</br>
Now you can easily execute your binary from the current directory:
```
./test
```
And your console should show you `The end of array = 10`

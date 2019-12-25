## Build and Run

</br>
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
To build a pipeline Cmake needs to know where is the source folder and where is binary folder. The source folder is where your CMakeLists.txt is located. Binary folder you have to create and usually it is named 'build'. Using an empty "build" directory is a technique called "out-of-source build", in which all your generated files are generated in the separate "build" directory and not mixed with source files. So, make a 'build' folder and go into it:
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

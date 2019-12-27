<p align="center">
  <img src="https://github.com/StarKerrr/CCollections/blob/master/res/c-and-data-structures.png?raw=true" width="600px">
</p>

## - About this project
&nbsp; &nbsp; &nbsp; &nbsp; I am a big fan of C, that's why I want to make work with this language more comfortable and easier. So I've decided to write a library of generic data structures. Working on this project, I had a great experience in C programming and data structures. As we know, C doesn't have special collections like linked lists or stacks and this is rather terrible because embedded arrays often can't satisfy all our needs. First of all, they have a fixed size, i.e. they can't be dynamically expanded. Secondly, we can put the data only of the same type into array that also isn't convenient. So, I present to you the library of generic data structures! But first thing's first.
</br>

> Contents
- [What is a Data Structure](#--about-this-project)
- [Why learn data structure](#--what-is-a-data-structure)
- [Popular data structures and library implementations](#--about-popular-data-structures)
- [Build and Run](#--how-to-build-and-run-the-library-linux)

## - What is a Data Structure?
> Data structure is a way in which data are stored for efficient search and retrieval.

&nbsp; &nbsp; &nbsp; &nbsp; Different data structures are suited for different problems. Some data structures are useful for simple general problems, such as retrieving data that has been stored with a specific identifier. For example, an online dictionary can be structured so that it can retrieve the definition of a word. On the other hand, specialized data structures have been devised to solve complex specific search problems.                                               

## - Why should we learn data structures?
&nbsp; &nbsp; &nbsp; &nbsp; Computer software is all about handling data. Data covers all types of information and the more basic forms are `numbers` and `strings`. Data structures explain how data is organized. This structure dictates how fast and efficient your code will run, that's why, depending on what type of data structure you have chosen, your program can be executed in a millisecond or in a minute. Once you deeply understand how data structures work, your code will run better and be prettier. On the data scientist side, we all write code, but writing good code also opens you up to software engineering opportunities. Surely, learning something that allows you to be good in your own craft while expanding into other lucrative fields can’t be that bad. Data structures play crucial role for programmers.     

## - About popular data structures

<h3>Array</h3>

<img src="https://github.com/StarKerrr/CCollections/blob/master/res/array-diargam.png" width="650px">
&nbsp; &nbsp; &nbsp; &nbsp; An array is a collection of items stored at contiguous memory locations. The idea is to store multiple items of the same type together. This makes it easier to calculate the position of each element by simply adding an offset to a base value, i.e., the memory location of the first element of the array (generally denoted by the name of the array). Each element can be uniquely identified by their index in the array. This data structure is the base of majority of data structures and it isn't surprising.
</br></br>

&nbsp; &nbsp; &nbsp; &nbsp; As it was said above, this library is the library of generic data structures and array is not an exception. The usage of Array data structure is truly simple:
</br>

![](https://github.com/StarKerrr/CCollections/blob/master/res/ArrayUsage.png)
</br></br>

<h3>Linked List</h3>

<img src="https://github.com/StarKerrr/CCollections/blob/master/res/linked-list.svg" width="650px">
&nbsp; &nbsp; &nbsp; &nbsp; One disadvantage of using arrays to store data is that arrays are static structures and therefore can't be easily extended or reduced to fit the data set. Unlike arrays, the elements in linked lists are not stored at contiguous memory locations. They are linked using pointers as shown in the image above. Each element of a list is comprising of two items - the data and a reference to the next node. The last node has a reference to null. A linked list is a dynamic data structure, therefore number of nodes in a list is not fixed and can grow and shrink on demand. Any application which has to deal with an unknown number of objects will need to use a linked list.
</br></br>

&nbsp; &nbsp; &nbsp; &nbsp; Let's see what features the library provides to use a linked list data structure.
</br>

![](https://github.com/StarKerrr/CCollections/blob/master/res/SListUsage.png)
</br></br>

<h3>Stack</h3>

</br>

<img src="https://github.com/StarKerrr/CCollections/blob/master/res/stackImg.png" width="650px">
&nbsp; &nbsp; &nbsp; &nbsp; A stack is a basic data structure that can be logically thought of as a linear structure represented by a real physical stack or pile, a structure where insertion and deletion of items takes place at one end called top of the stack. The basic concept can be illustrated by thinking of your data set as a stack of books or cards where you can only take the top item off the stack in order not to destroy all the stack of things. The basic implementation of a stack is also called a LIFO (Last In First Out) to demonstrate the way it accesses data.
</br></br>

&nbsp; &nbsp; &nbsp; &nbsp; In my library you can find two implementations of Stack, viz. dynamic array-based and singly linked list-based. Well, that's how you can use Stack in your code.
</br>

![](https://github.com/StarKerrr/CCollections/blob/master/res/StackUsage.png)
</br></br></br>

## - How to build and run the library (LINUX)
### - Building

&nbsp; &nbsp; &nbsp; The most important part of this README is the build and run instructions which you can also find in INSTRUCTIONS.md 
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

### - Running

&nbsp; &nbsp; &nbsp; Well, now we have built the project and we want to use the library in our code. Let's assume that we have a file 'test.c':

```c
#include <stdio.h>
#include <stdlib.h>
#include <Collections/array.h>
#include <Collections/array_sortings.h>

int main(int argc, char** argv)
{
    Array* arr = arrayNew();
    arrayToEnd(arr, (void*)30);
    arrayToEnd(arr, (void*)20);
    arrayToEnd(arr, (void*)10);
    Array* sorted_array = arraySortNew(arr, bubbleSort);
    
    void* begin = arrayGetBegin(sorted_array);
    printf("First element of array: %d", toInteger(begin));
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

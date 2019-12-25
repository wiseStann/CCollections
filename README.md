<p align="center">
  <img src="https://github.com/StarKerrr/CCollections/blob/master/res/c-and-data-structures.png?raw=true" width="600px">
</p>

## - About this project
&nbsp; &nbsp; &nbsp; &nbsp; I am a big fan of C, that's why I want to make work with this language more comfortable and easier. So I've decided to write a library of generic data structures. Working on this project, I had a great experience in C programming and data structures. As we know, C doesn't have special collections like linked lists or stacks and this is rather terrible because embedded arrays often can't satisfy all our needs. First of all, they have a fixed size, i.e. they can't be dynamically expanded. Secondly, we can put the data only of the same type into array that also isn't convenient. So, I present to you the library of generic data structures! But first thing's first.

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

![](https://github.com/StarKerrr/CCollections/blob/master/res/StackNew.png)
</br></br></br>

## - How to build and run the library

&nbsp; &nbsp; The most important part of this README is the build and run instructions which you can also find in INSTRUCTIONS.md
</br>
First of all, you need to clone this repository on your local PC:
</br>

```
git clone https://github.com/StarKerrr/CCollections.git
```

When you clone this repository on your local machine, change your current directory to this Project folder:
</br>

```
cd CCollections
```

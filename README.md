# tinylinkedlist
**TinyLinkedList** is a C++ library to containerize data of unknown length following the single linked list pattern. [Further read on linked lists.](https://en.wikipedia.org/wiki/Linked_list)

This implementation is designed to iterate forward and has therefore a simple iteration protocol included. It is not design to pop and get things frequently on the the high side of the container.

It cannot be used for types which disallow copy constructor as elements are passed by value. However, pointer can be passed. Memory management than will be with the user.

## Features
* Template class to use arbitrary types.
* Minimalistic interface with only five methods.
* Iter protocol `while(list.iter()) el = list.iter.next()`
* No over-allocating. Full memory management.
* Pass-by-Value design. This means the list will take over ownership. 
* Destructor will destroy every value.

## Disclaimer
Uses C++11. Was developed on a ESP8266. May run on any other machine as well. 

## Usage / Example
```c++
#include "linkedlist.h"

void main(){
    LinkedList<int> list{};
    list.append(1);
    list.append(2);
    list.append(3);

    while(list.iter()){
        int i = list.iter.next();
        /* do stuff */
    }

    int el = list.get(0);
    el = list.pop();
    int idx = list.index(2);
    el = list.remove(idx);

    while(1){
        el = list.iter.loopNext();
        /* do stuff forever */
    }

}

```
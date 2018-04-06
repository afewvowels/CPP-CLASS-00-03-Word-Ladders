#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
#include "exceptions.h"

using namespace std;

const unsigned int
  QUEUE_SIZE = 16;

template <class QueueType>
class Queue {
public:
  Queue(void) {
    head = QUEUE_SIZE - 1;
    tail = 0;
    count = 0;
    cap = QUEUE_SIZE;

    data = new QueueType[cap];
  }

  ~Queue(void) {
    delete[] data;
  }

  bool isEmpty(void) { return count == 0; }

  int size(void) { return count; }

  int arrSize(void) { return cap; }

  void clear(void) {
    head = cap - 1;
    tail = 0;
    count = 0;
  }

  void enqueue(QueueType v) {
    // Only works if duplication happens
    // before array is entirely full
    // if (count == cap-1) {
    if(head==tail) {
      // Create temporary array twice the size
      // of the existing array
      QueueType *tmpData = nullptr;
      tmpData = new QueueType[2*cap];

      for(int i=0;i<count;i++) {
        tmpData[i]=data[i];
      }

      // If tail!=cap, that is, tail is between
      // 0 and size of array,
      // 1. Loop through tail to array size - 1
      // and copy starting at j - tail (==0)
      // 2. Loop through 0 to tail and copy
      // starting at j + tail
      // if(tail!=count) {
      //   for(int j=tail;j<=cap;j++)
      //     tmpData[j-tail]=data[j];
      //   for(int j=0;j<=tail;j++)
      //     tmpData[j+tail]=data[j];
      // }
      // If tail==cap, then everything is linear
      // and there is no loopback in the Queue.
      // Simply loop through from 0 to array size
      // and copy tmpData[i] to data[i].
      // else if(tail==count-1) {
      //   for(int i=0;i<cap;i++) {
      //     tmpData[i]=data[i];
      //   }
      // }

      delete[] data;

      data=tmpData;

      // I get an error "Pointer being freed
      // was not allocated" when I try to delete
      // the temporary array?!
      // delete[] tmpData;

      // Set the new tail to == the total number of
      // items in the array since the queue begins
      // at index 0.
      tail=count;

      cap*=2;

      // Reset head to end of array so that
      // (head+1)%cap == 0.
      head=cap-1;

//      cout << "Array Doubled" << endl;
    }

//    cout << "Head: " << head << endl;
//    cout << "Tail: " << tail << endl;
//    cout << "Count: " << count << endl;
//    cout << endl;

    data[tail] = v;
    tail = (tail + 1) % cap;

    count++;
  }

  QueueType dequeue(void) {

    head = (head + 1) % cap;

    count--;

    return data[head];
  }
    
    QueueType peek(void) {
        return data[(head + 1) % cap];
    }

private:
  unsigned int
    head,tail,count,cap;
  QueueType
    *data;
};

#endif

//#ifndef _LINEARLIST_H
//#define _LINEARLIST_H
//
//#include "exceptions.h"
//
//template<class ListType>
//// Forward declaration
//class LinearList;
//
//template<class ListType>
//class ListNode {
//private:
//  // Value held in the pointer
//  ListType val;
//
//  // Pointer to a list node that holds list types
//  // (Next node in the list)
//  ListNode<ListType> *next;
//public:
//  friend class LinearList<ListType>;
//};
//
//template<class ListType>
//class LinearList {
//public:
//  LinearList(void) {
//    head=NULL;
//    count=0;
//  }
//
//  ~LinearList(void) { clear(); }
//
//  void clear(void) {
//    ListNode<ListType> *tmp;
//
//    for(int i=0;i<count;i++) {
//      // head->next is an idiom,
//      // Appears a lot with pointers and list
//      // structures
//      tmp=head->next;
//      delete head;
//      head=tmp;
//    }
//
//    head=NULL;
//    count=0;
//  }
//
//  int size(void) { return count; }
//
//  bool isEmpty(void) { return count==0; }
//
//  // List specific actions
//
//  // Search has to be sequential search, can't walk to
//  // end fast enough for sentinal search.
//  int search(ListType &key) throw (KeyNotFoundException) {
//    int i;
//
//    ListNode<ListType> *tmp;
//
//    for(tmp=head,i=0;i<count;i++,tmp=tmp->next) {
//      if(tmp->val==key) {
//        return i;
//      }
//    }
//
//    throw KeyNotFoundException(key);
//  }
//
//  // Operator add.
//  // Start at beginning of list.
//  // Take parameter.
//  // Walk number of positions equal to parameter.
//  // Should be at node with parameter at end of process.
//  //
//  // Start at head of the list.
//  // Validate that position is legal.
//  ListType &operator[](int pos) throw (InvalidIndexException) {
//    int i;
//
//    ListNode<ListType> *tmp;
//
//    if(pos<0||pos>=count) {
//      throw InvalidIndexException(pos);
//    }
//
//    // Rare for loop that nerminates in a semicolon (null body).
//    for(tmp=head,i=0;i<pos;i++,tmp=tmp->next);
//
//    // Temp points to node once loop terminates.
//    return tmp->val;
//  }
//
//  // fp is a pointer to a function
//  // function takes one param: ListType
//  // function returns void
//  // name of function no parentheses is
//  // the memory location (pointer) of a function
//  // Function();
//  // vs.
//  // Function;
//  void traverse(void (*fp)(ListType &)) {
//    int i;
//
//    ListNode<ListType> *tmp;
//
//    for(tmp=head,i=0;i<count;i++,tmp=tmp->next) {
//      // Parentheses forces precedence.
//      (*fp)(tmp->val);
//    }
//  }
//
//  // ** is pointer to a pointer
//  void insert(int pos,const ListType &v) throw (InvalidIndexException) {
//    int i;
//
//    ListNode<ListType> *tmp;
//    ListNode<ListType> **pred;
//
//    // Step 0: Validate position
//    if(pos<0||pos>count) {
//      throw InvalidIndexException(pos);
//    }
//
//    // Step 1: Create new node and fill in the value
//    tmp=new ListNode<ListType>;
//    tmp->val=v; // Passed by reference, could be a lot of data.
//
//    // Step 2: Find the predecessor
//    pred=&head; // Points to header pointer.
//    for(i=0;i<pos;i++) {
//      pred=&((*pred)->next); // Pointing to pointers
//    }
//
//    //  Step 3: New node gets copy of predecessor pointer
//    // tmp->next=*pred->next;
//    tmp->next=*pred;
//
//
//    // Step 4: Predecessor points to new node
//    *pred=tmp;
//
//    // Step 5: Update count
//    count++;
//  }
//
//  void remove(int pos) throw (InvalidIndexException) {
//    int i;
//
//    ListNode<ListType> *tmp;
//    ListNode<ListType> **pred;
//
//    // Step 0: Validate position
//    if(pos<0||pos>=count) {
//      throw InvalidIndexException(pos);
//    }
//
//    // Step 1: Find the predecessor
//    pred=&head; // Points to header pointer.
//    for(i=0;i<pos;i++) {
//      pred=&((*pred)->next); // Pointing to pointers
//    }
//
//    //  Step 2: Remember node to be deleted
//    tmp=(*pred)->next;
//
//    // Step 3: Point around node to be deleted
//    (*pred)=tmp->next;
//
//    // Step 4: Delete node to be deleted
//    delete tmp;
//
//    // Step 5: Update count
//    count--;
//  }
//
//private:
//  // Head object pointer
//  ListNode<ListType> *head;
//
//  // Int counter
//  int count;
//};
//
//#endif

#ifndef _LINEARLIST_H
#define _LINEARLIST_H

#include "exceptions.h"

template <class ListType>
class LinearList;

template <class ListType>
class ListNode {
public:
    friend class LinearList<ListType>;
private:
    ListType
    val;
    ListNode<ListType>
    *next;
};

template <class ListType>
class LinearList {
public:
    LinearList(void) {
        
        head = NULL;
        count = 0;
    }
    
    ~LinearList(void) { clear(); }
    
    void clear(void) throw (KeyNotFoundException){
        ListNode<ListType>
        *tmp;
        
        for (int i=0;i<count;i++) {
            tmp = head->next;
            delete head;
            head = tmp;
        }
        
        head = NULL;
        count = 0;
    }
    
    int size(void) { return count; }
    
    bool isEmpty(void) { return count == 0; }
    
    //----
    
    int search(ListType &key) throw (KeyNotFoundException) {
        int
        i;
        ListNode<ListType>
        *tmp;
        
        for (tmp=head,i=0;i<count;i++,tmp=tmp->next)
            if (tmp->val == key)
                return i;
        
        throw KeyNotFoundException(key);
    }
    
    ListType &operator[](int pos) throw (InvalidIndexException) {
        int
        i;
        ListNode<ListType>
        *tmp;
        
        if (pos < 0 || pos >= count)
            throw InvalidIndexException(pos);
            
            for (tmp=head,i=0;i<pos;i++,tmp=tmp->next);
        
        return tmp->val;
    }
    
    void traverse(void (*fp)(ListType &)) {
        int
        i;
        ListNode<ListType>
        *tmp;
        
        for (tmp=head,i=0;i<count;i++,tmp=tmp->next)
            (*fp)(tmp->val);
    }
    
    void insert(int pos,const ListType &v) throw (InvalidIndexException) {
        int
        i;
        ListNode<ListType>
        *tmp,**pred;
        
        // step 0: make sure pos is valid
        if (pos < 0 || pos > count)
            throw InvalidIndexException(pos);
            
            // step 1: create new node and fill in value
            tmp = new ListNode<ListType>;
        tmp->val = v;
        
        // step 2: find the predecessor
        pred = &head;
        for (i=0;i<pos;i++)
            pred = &((*pred)->next);
        
        // step 3: new node gets copy of pred's pointer
        tmp->next = *pred;
        
        // step 4: pred points to new node
        *pred = tmp;
        
        // step 5: update count
        count++;
    }
    
    void remove(int pos) throw (InvalidIndexException) {
        int
        i;
        ListNode<ListType>
        *tmp,**pred;
        
        // step 0: make sure pos is valid
        if (pos < 0 || pos >= count)
            throw InvalidIndexException(pos);
            
            // step 1: find the predecessor
            pred = &head;
        for (i=0;i<pos;i++)
            pred = &((*pred)->next);
        
        // step 2: remember node to be deleted (ntbd)
        tmp = *pred;
        
        // step 3: point around ntbd
        (*pred) = tmp->next;
        
        // step 4: delete ntbd
        delete tmp;
        
        // step 5: update count
        count--;
    }
    
private:
    ListNode<ListType> *head;
    int count;
};

#endif


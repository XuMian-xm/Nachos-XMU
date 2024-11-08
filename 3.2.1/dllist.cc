#include "dllist.h"
#include <iostream>

DLLElement::DLLElement(void *itemPtr,int sortKey)
{
    this->key=sortKey;
    this->next=NULL;
    this->prev=NULL;
    this->item=itemPtr;
}

DLList::DLList() : first(NULL), last(NULL) {}

DLList::~DLList() {
    int key;
    while (!IsEmpty()) {
        Remove(&key);
    }
}

void DLList::Prepend(void *item) {
    int sortkey=100;
    if(first)sortkey=first->key-1;
    DLLElement *element = new DLLElement(item, sortkey);
    if (first == NULL) {
        first = last = element;
    } else {
        element->next = first;
        first->prev = element;
        first = element;
    }
}

void DLList::Append(void *item) {
    int sortkey=100;
    if(last)sortkey=last->key+1;
    DLLElement *element = new DLLElement(item, sortkey);
    if (last == NULL) {
        first = last = element;
    } else {
        element->prev = last;
        last->next = element;
        last = element;
    }
}

void *DLList::Remove(int *keyPtr) {
    if (IsEmpty()) return NULL;
    DLLElement *element = first;
    *keyPtr = element->key;
    first = first->next;
    if (first == NULL) last = NULL;
    else first->prev = NULL;
    void *item = element->item;
    delete element;
    return item;
}

bool DLList::IsEmpty() {
    return first == NULL;
}

void DLList::SortedInsert(void *item, int sortKey) {
    DLLElement *newElement = new DLLElement(item, sortKey);
    DLLElement *current = first;
    if(first==NULL){//¿Õ±í
        first=last=newElement;
        return;
    }
    while (current != NULL && current->key < sortKey) {
        current = current->next;
    }
    if (current == NULL) {
        last->next = newElement;
        newElement->prev = last;
        last = newElement;
    } else if (current->prev == NULL) {
        first = newElement;
        newElement->next = current;
        current->prev = newElement;
    } else {
        newElement->next = current;
        newElement->prev = current->prev;
        current->prev->next = newElement;
        current->prev = newElement;
    }
}

void *DLList::SortedRemove(int sortKey) {
    DLLElement *current = first;
    while (current != NULL && current->key < sortKey) {
        current = current->next;
    }
    if (current == NULL) return NULL;
    if (current->key!=sortKey)return NULL;
    void *item = current->item;
    if(current==first){
        first = first->next;
        if(first==NULL)last=NULL;
        else first->prev=NULL;
    }
    else if(current==last){
        last = last->prev;
        if(last==NULL)first=NULL;
        else last->prev=NULL;
    }
    else
    {
        DLLElement *element2 = current->next;
        DLLElement *element1 = current->prev;
        element1->next=element2;
        element2->prev=element1;
    }
    delete current;
    return item;
}

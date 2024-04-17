#pragma once
#include "priNode.h"


//This class impelements the priority queue as a sorted list (Linked List)
//The item with highest priority is at the front of the queue
template <typename T>
class priQueue
{
    priNode<T>* head;
    int counter = 0;
public:
    priQueue() : head(nullptr) {}

    ~priQueue() {
        T tmp;
        int p;
        while (dequeue( p));
    }
    int getCounter() {return counter;};
    //insert the new node in its correct position according to its priority
    void enqueue(const T& data, int priority) {
        priNode<T>* newNode = new priNode<T>(data, priority);
        this->counter++;

        if (head == nullptr || priority > head->getPri()) {

            newNode->setNext(head);
            head = newNode;
            return;
        }

        priNode<T>* current = head;
        while (current->getNext() && priority <= current->getNext()->getPri()) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
    }

    T* dequeue(int& pri) {
        if (isEmpty())
            return NULL;

        T* item = new T(head->getItem(pri));
        priNode<T>* temp = head;
        head = head->getNext();
        delete temp;
        this->counter--;
        return item;
    }

    bool peek(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem();
        pri = head->getPri();
        return true;
    }

    bool isEmpty() const {
        return head == nullptr;
    }
    bool print(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        //priNode<T>* temp = head;
        topEntry = head->getItem(pri);
        head = head->getNext();
        return true;
    }
    
};



#include <iostream>
using namespace std;
#include "Node.h"

template <typename T>
class LinkedStack
{
private:
	Node<T>* frontPtr;
	int counter = 0;
public:
	LinkedStack();
	bool isEmpty() const;
	bool Push(const T& newEntry);
	bool Pop(T& frntEntry);
	bool peek(T& frntEntry)  const;
	void PrintStack();
	bool Print(T& frntEntry);
	~LinkedStack();
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Satck()
The constructor of the Stack class.

*/

template <typename T>
LinkedStack<T>::LinkedStack()
{
	frontPtr = nullptr;
}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this Stack is empty.

Input: None.
Output: True if the Stack is empty; otherwise false.
*/
template <typename T>
bool LinkedStack<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:Push
Adds newEntry at the back of this Stack.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedStack<T>::Push(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The Stack is empty
	else {
		newNodePtr->setNext(frontPtr) ; // The Stack was not empty
		frontPtr = newNodePtr;
	}
	this->counter++;
	return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: Pop
Removes the Last of this Stack. That is, removes the item that was added
Last.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedStack<T>::Pop(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Stack is not empty; remove front


	// Free memory reserved for the deleted node
	delete nodeToDeletePtr;
	this->counter--;
	return true;
}



/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peek
copies the front of this Stack to the passed param. The operation does not modify the Stack.

Input: None.
Output: The front of the Stack.
*/

template <typename T>
bool LinkedStack<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
template <typename T>
bool LinkedStack<T>::Print(T& frntEntry)
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();

	return true;
}
template<typename T>
void LinkedStack<T>::PrintStack()
{
	T K;
	cout << "\n Stack contents: ";
	while (this->Pop(K))
		cout << K << " ";
	cout << endl;
}
///////////////////////////////////////////////////////////////////////////////////


template <typename T>
LinkedStack<T>::~LinkedStack()
{

	T temp;
	while (Pop(temp));

}


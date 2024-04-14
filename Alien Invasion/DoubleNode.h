#pragma once

template <typename T>
class DoubleNode
{
private:
	T item; // A data item
	DoubleNode<T>* next; // Pointer to next node
	DoubleNode<T>* prev; // Pointer to prev node
public:
	DoubleNode();
	DoubleNode(const T& r_Item);
	DoubleNode(const T& r_Item, DoubleNode<T>* nextNodePtr, DoubleNode<T>* prevNodePtr);
	void setItem(const T& r_Item);
	void setNext(DoubleNode<T>* nextNodePtr);
	DoubleNode<T>* getNext() const;
	void setprev(DoubleNode<T>* prevNodePtr);
	DoubleNode<T>* getprev() const;
	T getItem() const;
}; // end Node


template < typename T>
DoubleNode<T>::DoubleNode()
{
	next = nullptr;
	prev = nullptr;
}

template < typename T>
DoubleNode<T>::DoubleNode(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
	prev = nullptr;
}

template < typename T>
DoubleNode<T>::DoubleNode(const T& r_Item, DoubleNode<T>* nextNodePtr, DoubleNode<T>* prevNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
	prev = prevNodePtr;
}
template < typename T>
void DoubleNode<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void DoubleNode<T>::setNext(DoubleNode<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
T DoubleNode<T>::getItem() const
{
	return item;
}

template < typename T>
DoubleNode<T>* DoubleNode<T>::getNext() const
{
	return next;
}

template<typename T>
void DoubleNode<T>::setprev(DoubleNode<T>* prevNodePtr)
{
	prev = prevNodePtr;
}

template<typename T>
DoubleNode<T>* DoubleNode<T>::getprev() const
{
	return prev;
}

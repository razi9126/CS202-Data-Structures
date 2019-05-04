#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

template <class T>
Stack<T>::Stack()
{
}

template <class T>
Stack<T>::Stack(const Stack<T>& otherStack)
{
    LinkedList<T> l=otherStack.list;
    ListItem<T> *temp= l.getTail();
    while(temp!=NULL)
    {
        this->push(temp->value);
        temp=temp->prev;

    }
}

template <class T>
Stack<T>::~Stack()
{

}

template <class T>
void Stack<T>::push(T item)
{
    list.insertAtHead(item);
}

template <class T>
T Stack<T>::top()
{
    return (list.getHead()->value);
}

template <class T>
T Stack<T>::pop()
{
    ListItem<T> *v =list.getHead();
    T val= v->value;
    list.deleteHead();
    return (val);


}

template <class T>
int Stack<T>::length()
{
    return list.length();
}

template <class T>
bool Stack<T>::isEmpty()
{
    if (list.length()==0)
        return true;
    else
        return false;
}

#endif

#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue()
{

}

template <class T>
Queue<T>::Queue(const Queue<T>& otherQueue)
{
    LinkedList<T> l=otherQueue.list;
    ListItem<T> *temp= l.getTail();
    while(temp!=NULL)
    {
        this->enqueue(temp->value);
        temp=temp->prev;

    }
}

template <class T>
Queue<T>::~Queue()
{

}

template <class T>
void Queue<T>::enqueue(T item)
{
    list.insertAtHead(item);
}

template <class T>
T Queue<T>::front()
{
    if(list.getTail()!=NULL)
    {
        return (list.getTail()->value);
    }
}

template <class T>
T Queue<T>::dequeue()
{
    ListItem<T> *v =list.getTail();
    T val= v->value;
    list.deleteTail();
    return (val);

}

template <class T>
int Queue<T>::length()
{
    return list.length();
}

template <class T>
bool Queue<T>::isEmpty()
{
    if (list.length()==0)
        return true;
    else
        return false;
}


#endif

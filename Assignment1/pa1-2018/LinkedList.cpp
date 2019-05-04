#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include "LinkedList.h"

template <class T>
LinkedList<T>::LinkedList()
{
	head = NULL;

}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{

}

template <class T>
LinkedList<T>::~LinkedList()
{
	ListItem<T> *temp;
    while(head->next!=NULL)
    {
        temp=head;
        head=head->next;
        delete temp;
    }
    delete head;
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
	ListItem<T> *temp_Head = new ListItem<T>(item);
	head->prev = temp_Head;
	temp_Head->next = head;
	temp_Head->prev = NULL;
	head = temp_Head;
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
	ListItem<T> *temp;
    ListItem<T> *newdata;
    temp=get_tail();
    newdata=new ListItem<T>(item);
    temp->next=newdata;
    newdata->prev =temp;
    newdata->next=NULL;
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{


}

template <class T>
void LinkedList<T>::insertSorted(T item)
{

}

template <class T>
ListItem<T>* LinkedList<T>::getHead()
{
	return head;
}

template <class T>
ListItem<T>* LinkedList<T>::getTail()
{
	ListItem<T> *temp=head;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    return temp;
}

template <class T>
ListItem<T> *LinkedList<T>::searchFor(T item)
{

}

template <class T>
void LinkedList<T>::deleteElement(T item)
{

}

template <class T>
void LinkedList<T>::deleteHead()
{

}

template <class T>
void LinkedList<T>::deleteTail()
{

}

template <class T>
int LinkedList<T>::length()
{

}

template <class T>
void LinkedList<T>::reverse()
{
	
}

template <class T>
void LinkedList<T>::parityArrangement()
{
	
}

#endif

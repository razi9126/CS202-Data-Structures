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
    if (otherLinkedList.head == NULL)
    {
        head=NULL;
    }
    else
    {

        ListItem<T> *otherList= otherLinkedList.head;
        head = new ListItem<T>(otherList->value);
        ListItem<T> *temp=head;
        head->prev = NULL;
        head->next = NULL;

        while(otherList->next!=NULL)
        {
            otherList=otherList->next;
            ListItem<T> *newdata = new ListItem<T>(otherList->value);
            newdata->prev = temp;
            newdata->next = NULL;
            temp->next=newdata;
            temp=temp->next;
        }
        temp->next=NULL;
    }

}

template <class T>
LinkedList<T>::~LinkedList()
{
	ListItem<T> *temp;
    while(head!=NULL)
    {
        temp=head->next;
        delete head;
        head=temp;
    }
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
    if (head==NULL)
    {
        head = new ListItem<T>(item);
        head->prev = NULL;
        head->next=NULL;
    }
    else
    {
        ListItem<T> *temp_Head = new ListItem<T>(item);
        head->prev = temp_Head;
        temp_Head->next = head;
        temp_Head->prev = NULL;
        head = temp_Head;
    }
}

template <class T>
ListItem<T>* LinkedList<T>::getHead()
{
    return head;
}

template <class T>
ListItem<T>* LinkedList<T>::getTail()
{
    if (head==NULL)
        return NULL;
    else
    {
        ListItem<T> *temp=head;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        return temp;
    }

}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
    if (head==NULL)
    {
        this->insertAtHead(item);
    }
    else
    {
        ListItem<T> *temp;
        ListItem<T> *newdata;
        temp=this->getTail();
        newdata=new ListItem<T>(item);
        temp->next=newdata;
        newdata->prev =temp;
        newdata->next=NULL;
    }

}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
    if (head==NULL)
    {

    }
    else
    {
        bool found=false;
        ListItem<T> *temp=head;
        while ((found==false) && (temp!=NULL))
        {
            if (temp->value == afterWhat)
            {
                if (temp==head)
                {
                    ListItem<T> *new_node=new ListItem<T>(toInsert);
                    new_node->next = NULL;
                    temp->next = new_node;
                    new_node->prev = temp;
                    found=true;
                }
                else if (temp==getTail())
                {
                    this->insertAtTail(toInsert);
                    found=true;
                }
                else
                {
                    ListItem<T> *new_node=new ListItem<T>(toInsert);
                    ListItem<T> *next_item=temp->next;
                    new_node->next = next_item;
                    next_item->prev= new_node;
                    temp->next = new_node;
                    new_node->prev = temp;
                    found=true;
                }
            }
            else
            {
                temp=temp->next;
            }
        }
    }
}

template <class T>
void LinkedList<T>::insertSorted(T item)
{
    if (head==NULL)     //0 element list
    {
        this->insertAtHead(item);
    }

    else if (head->next == NULL) //1 element list
    {
        if(item >= head->value)
        {
            this->insertAtTail(item);
        }
        else
        {
            this->insertAtHead(item);
        }
    }
    else
    {
        ListItem<T> *current=head;
        ListItem<T> *temp=current->next;
        bool done=false;
        while ((done==false) && (temp!=NULL))
        {
            if((current->value <= item) && (temp->value > item))
            {
                ListItem<T> *new_node=new ListItem<T>(item);
                new_node->next = temp;
                new_node->prev = current;
                current->next=new_node;
                temp->prev=new_node;
                done=true;
            }
            else
            {
                current=current->next;
                temp=current->next;
            }
        }
        if (done==false)
            if (current->value < item)
            {
                this->insertAtTail(item);
                done=true;
            }
            else
            {
                ListItem<T> *temp=current->prev;
                ListItem<T> *new_node=new ListItem<T>(item);
                new_node->next = current;
                new_node->prev = temp;
                current->prev=new_node;
                temp->next=new_node;
                done=true;
            }
        }

}



template <class T>
ListItem<T> *LinkedList<T>::searchFor(T item)
{
    if (head==NULL)
    {
        return NULL; //changed this line
    }
    else
    {
        bool found=false;
        ListItem<T> *temp=head;
        while ((found==false) && (temp!=NULL))
        {

            if (temp->value == item)
            {
                found=true;
                return temp;
            }
            else
            {
                temp=temp->next;
            }
        }
        return NULL;

    }
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
    if (head==NULL)
    {

    }
    else
    {
        bool found=false;
        ListItem<T> *temp=head;
        while ((found==false) && (temp!=NULL))
        {
            if (temp->value == item)
            {
                if (temp==head)
                    {deleteHead();
                    found=true;}
                else if (temp==getTail())
                    {deleteTail();
                    found=true;}
                else
                {
                    ListItem<T> *previous=temp->prev;
                    ListItem<T> *next_item=temp->next;
                    previous->next = next_item;
                    next_item->prev= previous;
                    found=true;
                }
            }
            else
            {
                temp=temp->next;
            }
        }

    }

}

template <class T>
void LinkedList<T>::deleteHead()
{
    if (head->next==NULL)
    {
        //delete head;
        head=NULL;
    }
    else
    {

        ListItem<T> *temp= head;
        head=head->next;
        head->prev=NULL;
        delete temp;
    }
}

template <class T>
void LinkedList<T>::deleteTail()
{
    ListItem<T> *old_tail=this->getTail();
    if(old_tail!=head)
    {
        ListItem<T> *prev = old_tail->prev;
        prev->next=NULL;
        delete old_tail;
    }
    else
    {
        deleteHead();
    }
}

template <class T>
int LinkedList<T>::length()
{
    int counter=0;
    if (head==NULL)
    {
        return 0;
    }
    else
    {
        ListItem<T> *temp=head;
        while (temp!=NULL)
        {
            counter++;
            temp=temp->next;
        }
        return counter;
    }
}

template <class T>
void LinkedList<T>::reverse()
{
    if (head==NULL)
    {

    }
    else if (head==getTail())
    {

    }
    else
    {
        head=getTail();
        ListItem<T> *new_head=head;
        ListItem<T> *temp;
        while(new_head!=NULL)
        {
            temp=new_head->prev;
            new_head->prev=new_head->next;
            new_head->next=temp;
            new_head=new_head->next;
        }
    }
}

template <class T>
void LinkedList<T>::parityArrangement()
{
    if (head == NULL)
    {

    }


    ListItem<T> *odd = head;
    ListItem<T> *even = head->next;

    ListItem<T> *evenFirst = even;

    while (true)
    {
        if (!odd || !even || !(even->next))
        {
            odd->next = evenFirst;
            evenFirst->prev=odd;
            break;
        }


        odd->next = even->next;
        ListItem<T> *temp=odd;
        odd = even->next;
        odd->prev=temp;

        if (odd->next == NULL)
        {
            even->next = NULL;
            odd->next = evenFirst;
            evenFirst->prev=odd;
            break;
        }


        even->next = odd->next;
        temp=even;
        even = odd->next;
        even->prev=temp;
    }
}

template <class T>
bool LinkedList<T>::isPalindrome()
{
    if (head==NULL)
    {
        return false;
    }
    else
    {
        int len=this->length()/2;
        bool isPal=true;
        int i=0;
        ListItem<T> *current=head;
        ListItem<T> *previous=this->getTail();

        while (i<len){
            if(current->value != previous->value)
            {
                isPal=false;
            }
            else
            {
                current=current->next;
                previous=previous->prev;
            }
            i++;
        }
        return isPal;
    }

}



#endif

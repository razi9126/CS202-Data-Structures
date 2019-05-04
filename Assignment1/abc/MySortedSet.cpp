#include "MySortedSet.h"

template <class T>
MySortedSet<T>::MySortedSet()
{
    //container = new LinkedList<T>;
}

template <class T>
MySortedSet<T>::~MySortedSet()
{
    ~container;
    delete container;
}

template <class T>
ListItem<T>* MySortedSet<T>::getListHead()
{
    return (container.getHead());
}

template <class T>
int MySortedSet<T>::insert(T ele)
{
    if (container.searchFor(ele) == NULL)
    {
        container.insertSorted(ele);
        return 1;
    }
    else
    {
        return 0;
    }
}

template <class T>
int MySortedSet<T>::deleteEle(T ele)
{
    if (container.searchFor(ele) == NULL)
    {
        return 0;
    }
    else
    {
        container.deleteElement(ele);
        return 1;
    }

}

template <class T>
int MySortedSet<T>::isEmpty()
{
    if (container.length()==0)
        return 1;
    else
        return 0;
}

template <class T>
int MySortedSet<T>::isMember(T ele)
{
    if (container.searchFor(ele) == NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

template <class T>
int MySortedSet<T>::isEqual(MySortedSet<T>* anotherset)
{
    if(this->container.length() == (anotherset->container).length())
    {

        ListItem<T> *temp=(this->container).getHead();
        while(temp!=NULL)
        {
            if (!(anotherset->isMember(temp->value)))
                return 0;
            else
            {
                temp=temp->next;
            }
        }
        return 1;
    }
    else
        return 0;
}

template <class T>
int MySortedSet<T>::isSubset(MySortedSet<T>* anotherset)
{
    ListItem<T> *temp=(anotherset->container).getHead();
    while(temp!=NULL)
    {
        if (!(this->isMember(temp->value)))
            return 0;
        else
        {
            temp=temp->next;
        }
    }
    return 1;

}

template <class T>
MySortedSet<T>* MySortedSet<T>::setUnion(MySortedSet<T>* anotherset)
{
    MySortedSet<T>* Ans = new MySortedSet<T>();
    ListItem<T> *temp=(anotherset->container).getHead();
    while(temp!=NULL)
    {
        Ans->insert(temp->value);
        temp=temp->next;
    }
    temp=(this->container).getHead();
    while(temp!=NULL)
    {
        Ans->insert(temp->value);
        temp=temp->next;
    }
    return Ans;


}

template <class T>
MySortedSet<T>* MySortedSet<T>::setIntersection(MySortedSet<T>* anotherset)
{
    MySortedSet<T>* Ans = new MySortedSet<T>();
    ListItem<T> *temp=(anotherset->container).getHead();
    while(temp!=NULL)
    {
        if (this->isMember(temp->value))
        {
            Ans->insert(temp->value);
        }
        else{}
        temp=temp->next;
    }
    return Ans;


}

template <class T>
MySortedSet<T>* MySortedSet<T>::setDifference(MySortedSet<T>* anotherset)
{
    MySortedSet<T>* res = new MySortedSet<T>();
    ListItem<T> *temp=(this->container).getHead();
    while(temp!=NULL)
    {
        if (anotherset->isMember(temp->value))
        {
        }
        else{
             res->insert(temp->value);
        }
        temp=temp->next;
    }
    return res;
}

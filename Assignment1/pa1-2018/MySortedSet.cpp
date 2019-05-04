#include "MySortedSet.h"

template <class T>
MySortedSet<T>::MySortedSet()
{}

template <class T>
MySortedSet<T>::~MySortedSet()
{}

template <class T>
ListItem<T>* MySortedSet<T>::getListHead()
{}

template <class T>
int MySortedSet<T>::insert(T ele)
{}

template <class T>
int MySortedSet<T>::deleteEle(T ele)
{}

template <class T>
int MySortedSet<T>::isEmpty()
{}

template <class T>
int MySortedSet<T>::isMember(T ele)
{}

template <class T>
int MySortedSet<T>::isEqual(MySortedSet<T>* anotherset)
{}

template <class T>
int MySortedSet<T>::isSubset(MySortedSet<T>* anotherset)
{}

template <class T>
MySortedSet<T>* MySortedSet<T>::setUnion(MySortedSet<T>* anotherset)
{}

template <class T>
MySortedSet<T>* MySortedSet<T>::setIntersection(MySortedSet<T>* anotherset)
{}

template <class T>
MySortedSet<T>* MySortedSet<T>::setDifference(MySortedSet<T>* anotherset)
{}
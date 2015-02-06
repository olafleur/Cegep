#include "StdAfx.h"
#include "SimpleList.h"

template <class T>
SimpleList<T>::SimpleList(void)
{
	m_List = new T[0];
}

template <class T>
SimpleList<T>::~SimpleList(void)
{

}

template <class T>
void Add(T item)
{
	T* OldList = m_List;
	m_List = new T[OldList->length + 1];

	for (int i = 0; i < OldList->length; i++)
		m_List[i] = OldList[i];

	m_List[OldList->length] = item;
}

template <class T>
void Remove(int Index)
{
	int Plus = 0;
	T* OldList = m_List;
	m_List = new T[OldList->length + 1];

	for (int i = 0; i < OldList->length; i++)
	{
		if (i == Index)
			Plus = 1;

		m_List[i] = OldList[i + Plus];
	}
}

template <class T>
void SimpleList<T>::Modify(T item, int Index)
{
	m_List[Index] = item;
}

template <class T>
T SimpleList<T>::Get(int Index)
{
	return List[Index];
}

template <class T>
T* SimpleList<T>::GetList()
{
	return List;
}
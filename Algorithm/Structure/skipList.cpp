//
//  skipList.cpp
//  List
//
//  Created by Mingkai Chen on 2016-02-02.
//
//

#ifdef __SKIP_LIST__H

#include <cstdlib>
#include <ctime>
#include <vector>
#include <stdexcept>

template <class T>
skipNode<T>::skipNode(T data, size_t height) : height(height)
	{
	this->dataInit(data);
	nexts = new skipNode<T>*[height];
	memset(nexts, NULL, sizeof(skipNode<T>*)*height);
	}
	
template <class T>
void skipNode<T>::seriesConnection(skipNode<T>* series)
	{
	skipNode<T>* buffer = NULL;
	for (size_t i = 0; i < height && NULL != buffer; i++)
		{
		for (buffer = series; NULL != buffer && buffer->height < i; buffer = buffer->next[0])
			{
			}
		nexts[i] = buffer;
		}
	}
	
template <class T>
skipNode<T>::skipNode(T data)
	{
	this->dataInit(data);
	height = 1;
	while (0 == rand()%2)
		{
		height++;
		}
	nexts = new skipNode<T>*[height];
	memset(nexts, NULL, sizeof(skipNode<T>*)*height);
	}
	
template <class T>
skipNode<T>::skipNode(T data, skipNode<T>* series)
	{
	this->dataInit(data);
	height = 1;
	while (0 == rand()%2)
		{
		height++;
		}
	nexts = new skipNode<T>*[height];
	memset(nexts, NULL, sizeof(skipNode<T>*)*height);
	seriesConnection(series);
	}
	
template <class T>
skipNode<T>::~skipNode()
	{
	delete[] nexts;
	}
	
template <class T>
void skipNode<T>::cascadeDelete()
	{
	if (NULL != nexts[0])
		{
		nexts[0]->cascadeDelete();
		}
	delete this;
	}
	
template <class T>
skipNode<T>* skipNode<T>::cascadeCopy()
	{
	skipNode<T>* copy = new skipNode<T>(this->data, height);
	copy->seriesConnection(nexts[0]->cascadeCopy());
	return copy;
	}
	
template <class T>
skipList<T>::skipList() : head(NULL)
	{
	}
	
template <class T>
skipList<T>::skipList(const skipList<T>& src)
	{
	if (NULL != src.head)
		{	
		head = src.head->cascadeCopy();
		}
	}
	
template <class T>
skipList<T>::~skipList()
	{
	if (NULL != head)
		{
		head->cascadeDelete();
		}
	}

template <class T>
skipList<T>& skipList<T>::operator = (const skipList<T>& src)
	{
	if (this != &src)
		{
		if (NULL != head)
			{
			head->cascadeDelete();
			}
		if (NULL != src.head)
			{	
			head = src.head->cascadeCopy();
			}
		}
	return *this;
	}
	
template <class T>
bool skipList<T>::insert(T data)
	{
	bool unique = true;
	
	if (NULL == head || data < head->getData())
		{
		head = new skipNode<T>(data, head);
		}
	else if (data == head->getData())
		{
		unique = false;
		}
	else
		{
		skipNode<T>* buffer = head;
		size_t curHeight;
		std::vector<skipNode<T>*> last;
		while (NULL != buffer->nexts[0] && data > buffer->nexts[0]->getData())
			{
			curHeight = buffer->height-1;
			for (signed i = last->size()-curHeight; i > -1; i--)
				{
				last->push_back(NULL);
				}
			while (curHeight > 0 && 
				(NULL == buffer->nexts[curHeight] || data < buffer->nexts[curHeight]->getData()))
				{
				last[curHeight] = buffer;
				curHeight--;
				}
			buffer = buffer->nexts[curHeight];
			}
		if (data == buffer->getData())
			{
			unique = false;
			}
		else
			{
			buffer->nexts[0] = new skipNode<T>(data, buffer->nexts[0]);
			for (size_t i = buffer->nexts[0]->height-1; i > 0; i--)
				{
				if (last->size() >= i)
					{
					last[i]->nexts[i] = buffer->nexts[0];
					}
				}
			}
		}
	return unique;
	}

template <class T>
bool skipList<T>::remove(T data)
	{
	bool found = true;
	skipNode<T>* buffer = head;
	
	if (NULL == head || data < head->getData())
		{
		found = false;
		}
	else if (data == head->getData())
		{
		head = head->nexts[0];
		delete buffer;
		}
	else
		{
		skipNode<T>* parent;
		size_t curHeight;
		std::vector<skipNode<T>*> last;
		while (NULL != buffer->nexts[0] && data > buffer->nexts[0]->getData())
			{
			parent = buffer;
			curHeight = buffer->height-1;
			for (signed i = last->size()-curHeight; i > -1; i--)
				{
				last->push_back(NULL);
				}
			while (curHeight > 0 && 
				(NULL == buffer->nexts[curHeight] || data < buffer->nexts[curHeight]->getData()))
				{
				last[curHeight] = buffer;
				curHeight--;
				}
			buffer = buffer->nexts[curHeight];
			}
		if (data == buffer->getData())
			{
			parent->nexts[0] = buffer->nexts[0];
			delete buffer;
			curHeight = 1;
			for (skipNode<T>* buffer = parent->nexts[0]; NULL != buffer && curHeight < last->size(); buffer = buffer->nexts[0])
				{
				while (curHeight < last->size() && curHeight < buffer->height)
					{
					last[curHeight]->nexts[curHeight] = buffer;
					curHeight++;
					}
				}
			while (curHeight < last->size())
				{
				last[curHeight]->nexts[curHeight] = NULL;
				curHeight++;
				}
			for (size_t i = buffer->nexts[0]->height-1; i > 0; i--)
				{
				if (last->size() >= i)
					{
					last[i]->nexts[i] = buffer->nexts[0];
					}
				}
			}
		else
			{
			found = false;
			}
		}
	return found;
	}

template <class T>
bool skipList<T>::search(T data)
	{
	bool found = true;
	
	if (NULL == head || data < head->getData())
		{
		found = false;
		}
	else if (data != head->getData())
		{
		skipNode<T>* buffer = head;
		size_t curHeight;
		while (NULL != buffer->nexts[0] && data > buffer->nexts[0]->getData())
			{
			curHeight = buffer->height-1;
			while (curHeight > 0 && 
				(NULL == buffer->nexts[curHeight] || data < buffer->nexts[curHeight]->getData()))
				{
				curHeight--;
				}
			buffer = buffer->nexts[curHeight];
			}
		if (data != buffer->getData())
			{
			found = false;
			}
		}
	return found;
	}

template <class T>
T skipList<T>::operator [] (size_t index)
	{
	skipNode<T>* buffer = head;
    size_t i = 0;
	for (i = 0; NULL != buffer && i < index; i++)
		{
		buffer = buffer->nexts[0];
		}
	if (i < index)
		{
		throw std::out_of_range("index out of bounds");
		}
	return buffer->getData();
	}

#endif /* __SKIP_LIST__H */
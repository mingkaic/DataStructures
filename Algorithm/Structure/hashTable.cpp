//
//  hashTable.cpp
//  List
//
//  Created by Ming Kai Chen on 2014-07-15.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __HASH_TABLE__H

#include <string>

static const size_t ASCII_SIZE = 256;

template <class T>
hashTable<T>::hashTable() : numBuckets(101), curSize(0)
    {
    dictionary = new searchList<pair<std::string, T> >[numBuckets];
    }

template <class T>
hashTable<T>::hashTable(size_t intendedSize) : curSize(0)
    {
    numBuckets = nearestPrime((int)2*intendedSize);
    dictionary = new searchList<pair<std::string, T> >[numBuckets];
    }

template <class T>
hashTable<T>::hashTable(const hashTable& src) : numBuckets(src.numBuckets), curSize(src.curSize)
    {
    dictionary = new searchList<pair<std::string, T> >[numBuckets];
    for (size_t i = 0; i < src.numBuckets; i++)
        {
        dictionary[i] = src.dictionary[i];
        }
    }

template <class T>
hashTable<T>::~hashTable()
    {
    delete[] dictionary;
    }

template <class T>
hashTable<T>& hashTable<T>::operator = (const hashTable<T>& src)
    {
    if (this != &src)
        {
        curSize = src.curSize;
        numBuckets = src.numBuckets;

        delete[] dictionary;
            
        dictionary = new searchList<pair<std::string, T> >[numBuckets];
        for (size_t i = 0; i < src.numBuckets; i++)
            {
            dictionary[i] = src.dictionary[i];
            }
        }
    
    return *this;
    }

template <class T>
T& hashTable<T>::operator [] (std::string key)
    {
    T data;
    size_t hashIndex = hashFunction(key);
    pair<std::string, T> p(key, data);
    signed existingIndex = dictionary[hashIndex].search(p);
    if (existingIndex > -1)
        {
        return dictionary[hashIndex].nPeek(existingIndex).getDataRef();
        }
    dictionary[hashIndex].push(p);
    return p.getDataRef();
    }

template <class T>
bool hashTable<T>::insert(std::string key, T data)
    {
    bool replaced = false;
    pair<std::string, T> p(key, data);
    size_t hashIndex = hashFunction(key);
    signed existingIndex = dictionary[hashIndex].search(p);
    if (existingIndex > -1)
        {
        replaced = true;
        dictionary[hashIndex].nReplace(p, existingIndex);
        }
    else
        {
        dictionary[hashIndex].push(p);
        }
    curSize++;
    return replaced;
    }

template <class T>
bool hashTable<T>::remove(std::string key)
    {
    bool removed = false;
    pair<std::string, T> p(key, data);
    size_t hashIndex = hashFunction(key);
    signed existingIndex = dictionary[hashIndex].search(key);
    if (existingIndex > -1)
        {
        dictionary[hashIndex].nRemove(existingIndex);
        curSize--;
        removed = true;
        }
    return removed;
    }

template <class T>
bool hashTable<T>::search(std::string key, T& data) const
    {
    size_t hashIndex = hashFunction(key);
    pair<std::string, T> p(key, data);
    signed existingIndex = dictionary[hashIndex].search(p);
    bool found = existingIndex > -1;
    if (true == found)
        {
        data = dictionary[hashIndex].nPeek(existingIndex).getData();
        }
    return found;
    }

template <class T>
size_t hashTable<T>::numInserted() const
    {
    return curSize;
    }

template <class T>
size_t hashTable<T>::numSlot() const
    {
    return numBuckets;
    }

template <class T>
double hashTable<T>::loadFactor() const
    {
    return (double)curSize/(double)numBuckets;
    }

template <class T>
std::vector<std::string> hashTable<T>::hashIntersect(const hashTable<T>& src) const
    {
    std::vector<std::string> joined;
    hashTable<T> copy = src;
    pair<std::string, T> buffer;

    for (size_t i = 0; i < copy.numBuckets; i++)
        {
        while (false == copy.dictionary[i].isEmpty())
            {
            buffer = copy.dictionary[i].pop();
            if (-1 < dictionary[hashFunction(buffer->getKey())].search(buffer))
                {
                joined.push_back(buffer.getKey());
                }
            }
        }
    
    return joined;
    }

template <class T>
std::vector<std::string> hashTable<T>::hashUnion(const hashTable& src) const
    {
    std::vector<std::string> joined;
    hashTable<T> copyThis = *this;
    hashTable<T> copyThat = src;
    pair<std::string, T> buffer;
    size_t hashIndex = 0;
    signed bufferIndex = 0;

    for (size_t i = 0; i < copyThat.numBuckets; i++)
        {
        while (false == copyThat.dictionary[i].isEmpty())
            {
            buffer = copyThat.dictionary[i].pop();
            hashIndex = hashFunction(buffer->getKey());
            bufferIndex = dictionary[hashIndex].search(buffer);
            if (-1 < bufferIndex)
                {
                copyThis.dictionary[hashIndex].nRemove(bufferIndex);
                }
            joined.push_back(buffer->getKey());
            }
        }
        
    for (size_t i = 0; i < copyThis.numBuckets; i++)
        {
        while (false == copyThis.dictionary[i].isEmpty())
            {
            buffer = copyThis.dictionary[i].pop();
            joined.push_back(buffer->getKey());
            }
        }
    
    return joined;
    }

template <class T>
std::vector<std::string> hashTable<T>::hashDifference(const hashTable& src) const
    {
    std::vector<std::string> diff;
    hashTable<T> copyThis = *this;
    hashTable<T> copyThat = src;
    pair<std::string, T> buffer;
    size_t hashIndex = 0;
    signed bufferIndex = 0;

    for (size_t i = 0; i < copyThat.numBuckets; i++)
        {
        while (false == copyThat.dictionary[i].isEmpty())
            {
            buffer = copyThat.dictionary[i].pop();
            hashIndex = hashFunction(buffer->getKey());
            bufferIndex = dictionary[hashIndex].search(buffer);
            if (-1 < bufferIndex)
                {
                copyThis.dictionary[hashIndex].nRemove(bufferIndex);
                }
            else
                {
                diff.push_back(buffer->getKey());
                }
            }
        }
        
    for (size_t i = 0; i < copyThis.numBuckets; i++)
        {
        while (false == copyThis.dictionary[i].isEmpty())
            {
            buffer = copyThis.dictionary[i].pop();
            diff.push_back(buffer->getKey());
            }
        }
    
    return diff;
    }

template <class T>
size_t hashTable<T>::nearestPrime(size_t optimus)
    {
    if (optimus == 2)
        return 2;
    else if (0 == optimus % 2)
        optimus++;
    while (!isPrime(optimus++))
        {
        optimus++;
        }
    return optimus;
    }

template <class T>
bool hashTable<T>::isPrime(size_t n)
    {
    for (size_t i = 3; i < n/2; i += 2)
        {
        if (0 == n % i)
            {
            return false;
            }
        }
    return true;
    }

template <class T>
size_t hashTable<T>::hashFunction(std::string key) const
    {
    // string to index conversion
	size_t index = 0;
    size_t keyValue = 0;
    
    for (size_t i = 0; i <= key.size(); i++)
        {
        keyValue = (size_t)key[i];
        
	    index = (index*ASCII_SIZE+keyValue)%numBuckets;
        }
    
    return index;
    }

#endif /* __HASH_TABLE__H */
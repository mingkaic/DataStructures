//
//  hashTable.cpp
//  List
//
//  Created by Ming Kai Chen on 2014-07-15.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __HASH_TABLE__H

template <class T>
hashTable<T>::hashTable() : maxSize(101), curSize(0)
    {
    dictionary = new listNode<tuple<std::string, T>>*[maxSize];
    }

template <class T>
hashTable<T>::hashTable(size_t n) : curSize(0)
    {
    maxSize = nearestPrime((int)2*n);
    dictionary = new listNode<tuple<std::string, T>>*[maxSize];
    }

template <class T>
hashTable<T>::hashTable(const hashTable& src):
maxSize(obj.maxSize), curSize(obj.curSize)
    {
    dictionary = new listNode<tuple<std::string, T>>*[maxSize];
    copy(obj.dictionary);
    }

template <class T>
hashTable<T>::~hashTable()
    {
    for (size_t i = 0; i < maxSize; i++)
        {
        if (NULL != dictionary[i])
            {
            dictionary[i]->cascadeDelete();
            }
        }
    
    delete[] dictionary;
    }

template <class T>
hashTable<T>& hashTable<T>::operator = (const hashTable<T>& obj)
    {
    if (this != &obj)
        {
        curSize = obj.curSize;
        maxSize = obj.maxSize;
            
        for (size_t i = 0; i < maxSize; i++)
            {
            if (NULL != dictionary[i])
                {
                dictionary[i]->cascadeDelete();
                }
            }
        delete[] dictionary;
            
        dictionary = new listNode<tuple<std::string, T>>[maxSize];
        copy(obj.dictionary);
        }
    
    return *this;
    }

template <class T>
bool hashTable<T>::insert(std::string str)
    {
    if (dictionary[hashFunction(str)].insert(str))
        {
        curSize++;
        return true;
        }
    else
        {
        return false;
        }
    }

template <class T>
bool hashTable<T>::remove(std::string str)
{
    if (dictionary[hashFunction(str)].remove(str)) {
        curSize--;
        return true;
    } else
        return false;
}

template <class T>
bool hashTable<T>::search(std::string str) const
{
    return dictionary[hashFunction(str)].search(str);
}

template <class T>
int hashTable<T>::size() const
{
    return curSize;
}

template <class T>
int hashTable<T>::maxSize() const
{
    return maxSize;
}

template <class T>
double hashTable<T>::loadFactor() const
{
    return (double)curSize/(double)maxSize;
}

template <class T>
std::vector<std::string> hashTable<T>::intersection(const hashTable& obj) const
{
    std::vector<std::string> perm;
    std::vector<std::string> temp; // constructed a local vector for holding every dictionary entry's get()

    for (int i = 0; i < maxSize; i++) {
        temp = dictionary[i].get();
        for (int j = 0; j < (int)temp.size(); j++) {
            if (obj.search(temp[j])) // goes through temp to decide whether temp[j] element belongs in the intersection
                perm.push_back(temp[j]);
        }
    }
    
    return perm;
}

template <class T>
std::vector<std::string> hashTable<T>::unions(const hashTable& obj) const
{
    std::vector<std::string> perm = obj.difference(*this); // access obj’s strings
    std::vector<std::string> temp; // constructed a local vector for holding every dictionary entry's get()

    for (int i = 0; i < maxSize; i++) {
        temp = dictionary[i].get();
        perm.insert(perm.end(), temp.begin(), temp.end());
    }
    
    return perm;
}

template <class T>
std::vector<std::string> hashTable<T>::difference(const hashTable& obj) const
{
    std::vector<std::string> perm;
    std::vector<std::string> temp;
    
    for (int i = 0; i < maxSize; i++) {
        temp = dictionary[i].get();
        for (int j = 0; j < (int)temp.size(); j++) {
            if (!obj.search(temp[j])) // goes through temp to decide whether temp[j] element belongs in the difference
                perm.push_back(temp[j]);
        }
    }
    
    return perm;
}

template <class T>
int hashTable<T>::nearestPrime(int n)
{
    if (n == 2)
        return 2;
    // if n is even, make it odd
    if (!(n % 2))
        n++;
    // guarantees n is odd
    for (; !isPrime(n); n += 2) {}
    return n;
}

template <class T>
bool hashTable<T>::isPrime(int n)
{
    for (int i = 3; i < n/2; i += 2) { // only checks odd numbers
        if (!(n % i))
            return false;
    }
    return true;
}

template <class T>
void hashTable<T>::copy(listNode<tuple<std::string, T>>* arr)
{
    for (int i = 0; i < maxSize; i++) {
        // dictionary[i] and arr[i] are objects
        // uses listNode<tuple<std::string, T>> assignment operator
        dictionary[i] = arr[i];
    }
}

template <class T>
int hashTable<T>::hashFunction(std::string str) const
{
    // string to index conversion
	int rawIndex = 0;
    int key = 0;
    
    for (int i = 0; i < (int)str.size(); i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            key = (int)(str[i] - 'a')+1;
        else if (str[i] >= 'A' && str[i] <= 'Z')
            key = (int)(str[i] - 'A')+1;
        else
            key = 0;
        
	rawIndex = (rawIndex*32+key)%maxSize;
    }
    
    return rawIndex;
}

#endif /* __HASH_TABLE__H */
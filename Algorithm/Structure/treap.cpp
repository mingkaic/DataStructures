//
//  treap.cpp
//  Tree
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#ifdef __TREAP__H

#include <cstdlib>
#include <ctime>

template <class T>
p_treeNode<T>::p_treeNode(T data) :
left(NULL), right(NULL), parent(NULL)
    {
    this->dataInit(data);
    priority = rand();
    }

template <class T>
p_treeNode<T>::p_treeNode(p_treeNode<T>* left, T data, p_treeNode<T>* right) :
left(left), right(right), parent(NULL)
    {
    this->dataInit(data);
    priority = rand();
    }
        
template <class T>
p_treeNode<T>* p_treeNode<T>::cascadeCopy()
    {
    p_treeNode<T>* copy = new p_treeNode<T>(this->data);
    if (NULL != left)
        {
        copy->left = left->cascadeCopy();
        copy->left->parent = copy;
        }
    if (NULL != right)
        {
        copy->right = right->cascadeCopy();
        copy->right->parent = copy;
        }
    return copy;
    }

template <class T>
bool operator < (const p_treeNode<T>* left, const p_treeNode<T>* right)
    {
    bool smallLeft = true;
    if (NULL == right)
        {
        smallLeft = false;
        }
    else if (NULL != left)
        {
        smallLeft = left->priority < right->priority;
        }
    return smallLeft;
    }

template <class T>
bool operator > (const p_treeNode<T>* left, const p_treeNode<T>* right)
    {
    bool bigLeft = false;
    if (NULL == right)
        {
        bigLeft = true;
        }
    else if (NULL != left)
        {
        bigLeft = left->priority > right->priority;
        }
    return bigLeft;
    }

template <class T>
p_treeNode<T>* treap<T>::BinSearch(T key, p_treeNode<T>* i_root) const
    {
    p_treeNode<T>* parent;
    p_treeNode<T>* child;
    parent = child = i_root;

    while(NULL != child)
        {
        if (child->getData() == key)
            {
            child = NULL;
            }
        else 
            {
            parent = child;
            if (child->getData() > key)
                {
                child = child->left;
                }
            else
                {
                child = child->right;
                }
            }
        }
    return parent;
    }

template <class T>
void treap<T>::rotate(p_treeNode<T>* parent, bool rotLeft)
    {
    p_treeNode<T>* child;
    if (true == rotLeft)
        {
        child = parent->right;
        // parent's right adopts child's left
        parent->right = child->left;
        if (child->left)
            child->left->parent = parent;
        // child's left adopts parent
        child->left = parent;
        }
    else
        {
        child = parent->left;
        // parent's left adopts child's right
        parent->left = child->right;
        if (child->right)
            child->right->parent = parent;
        // child's right adopts parent
        child->right = parent;
        }
    // child's new parent is his previous grandparent
    child->parent = parent->parent;
    // parent's new parent was its previous child
    // if root, no parent
    if (parent->parent)
        {
        if (parent->parent->left == parent)
            {
            parent->parent->left = child;
            }
        else
            {
            parent->parent->right = child;
            }
        }
    parent->parent = child;
    // rotation fixup
    if (root == parent)
        {
        root = child;
        }
    }

template <class T>
treap<T>* treap<T>::split()
    {
    }

template <class T>
void treap<T>::merge(treap<T>* other)
    {
    }

template <class T>
treap<T>::treap() : root (NULL)
    {
    }

template <class T>
treap<T>::~treap()
    {
    root->cascadeDelete();
    }

template <class T>
bool treap<T>::insert(T data)
    {
    bool unique = true;
    p_treeNode<T>* parent = BinSearch(data, root);
    if (NULL == parent)
        {
        root = new p_treeNode<T>(data);
        }
    else
        {
        bool isLeft = parent->getData() > data;
        p_treeNode<T>* child = isLeft ? parent->left : parent->right;
        if (NULL != child || parent->getData() == data)
            {
            unique = false;
            }
        else
            {
            if (isLeft)
                {
                child = parent->left = new p_treeNode<T>(data);
                }
            else
                {
                child = parent->right = new p_treeNode<T>(data);
                }
            while (child < parent)
                {
                rotate(parent, !isLeft);
                parent = child->parent;
                if (NULL != parent)
                    {
                    isLeft = parent->left == child;
                    }
                }
            }
        }
    return unique;
    }

template <class T>
bool treap<T>::remove(T data)
    {
    bool found = true;
    
    p_treeNode<T>* target = BinSearch(data, root);
    if (target->getData() != data)
        {
        found = false;
        }
    else
        {
        bool isLeft = target->left > target->right;
        p_treeNode<T>* child = isLeft ? target->left : target->right;
        p_treeNode<T>* buffer = isLeft ? target->right : target->left;
        if (root == target)
            {
            root = child;
            }
        while (NULL != child || NULL != buffer)
            {
            target->left = child->left;
            target->right = child->right;
            child->left = isLeft ? target : buffer;
            isLeft = target->left > target->right;
            child = isLeft ? target->left : target->right;
            buffer = isLeft ? target->right : target->left;
            }
        if (isLeft)
            {
            target->parent->left = NULL;
            }
        else
            {
            target->parent->right = NULL;
            }
        delete target;
        }
    
    return found;
    }

template <class T>
T treap<T>::removeTop()
    {
    T data = root->getData();
    return data;
    }

template <class T>
bool treap<T>::exists(T data)
    {
    p_treeNode<T>* buffer = root;
    while (NULL != buffer && buffer->getData() != data)
        {
        if (buffer->getData() < data)
            {
            buffer = buffer->left;
            }
        else
            {
            buffer = buffer->right;
            }
        }
    
    return NULL != buffer;
    }

template <class T>
void treap<T>::tr_union()
    {
    }

template <class T>
void treap<T>::tr_intersection()
    {
    }

template <class T>
void treap<T>::tr_difference()
    {
    }
        
#endif /* __TREAP__H */
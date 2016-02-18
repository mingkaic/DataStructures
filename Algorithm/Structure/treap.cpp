//
//  treap.cpp
//  Tree
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#ifdef __TREAP__H

#include <cstdlib>
#include "pTreeNode.hpp"
#include "priorityContainer.hpp"

template <class T>
bool operator < (const pTreeNode<priorityContainer<T> >* left, const pTreeNode<priorityContainer<T> >* right)
    {
    bool smallLeft = true;
    if (NULL == right)
        {
        smallLeft = false;
        }
    else if (NULL != left)
        {
        smallLeft = left->getData() < right->getData();
        }
    return smallLeft;
    }

template <class T>
bool operator > (const pTreeNode<priorityContainer<T> >* left, const pTreeNode<priorityContainer<T> >* right)
    {
    bool bigLeft = false;
    if (NULL == right)
        {
        bigLeft = true;
        }
    else if (NULL != left)
        {
        bigLeft = left->getData() > right->getData();
        }
    return bigLeft;
    }

template <class T>
void treap<T>::rotate(pTreeNode<priorityContainer<T> >* parent, bool rotLeft)
    {
    pTreeNode<priorityContainer<T> >* child;
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
    if (this->root == parent)
        {
        this->root = child;
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
treap<T>::treap(const treap<T>& src) : pBSTree<priorityContainer<T> >(src)
    {
    }

template <class T>
treap<T>& treap<T>::operator = (const treap<T>& src)
    {
    pBSTree<priorityContainer<T> >::operator = (src);
    return *this;
    }

template <class T>
bool treap<T>::insert(T data)
    {
    bool unique = true;
    pTreeNode<priorityContainer<T> >* parent = BinSearch(data, this->root);
    if (NULL == parent)
        {
        this->root = new pTreeNode<priorityContainer<T> >(data);
        }
    else
        {
        bool isLeft = parent->getData() > data;
        pTreeNode<priorityContainer<T> >* child = isLeft ? parent->left : parent->right;
        if (NULL != child || parent->getData() == data)
            {
            unique = false;
            }
        else
            {
            if (isLeft)
                {
                child = parent->left = new pTreeNode<priorityContainer<T> >(data);
                }
            else
                {
                child = parent->right = new pTreeNode<priorityContainer<T> >(data);
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
    
    pTreeNode<priorityContainer<T> >* target = BinSearch(data, this->root);
    if (target->getData() != data)
        {
        found = false;
        }
    else
        {
        bool isLeft = target->left > target->right;
        pTreeNode<priorityContainer<T> >* child = isLeft ? target->left : target->right;
        pTreeNode<priorityContainer<T> >* buffer = isLeft ? target->right : target->left;
        if (this->root == target)
            {
            this->root = child;
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
    T data = this->root->getData();
    return data;
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
//
//  BSTree.cpp
//  Tree
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#ifdef __BSTREE__H

#include <cstdlib>
#include "treeNode.hpp"

template <class T>
treeNode<T>* BSTree<T>::BinSearch(T key, treeNode<T>* i_root) const
    {
    treeNode<T>* parent;
    treeNode<T>* child;
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
treeNode<T>* BSTree<T>::successorParent(treeNode<T>* i_root)
    {
    treeNode<T>* success = i_root;
    treeNode<T>* parent = NULL;
    
    if (NULL != i_root->right)
        {
        parent = success;
        success = i_root->right;
        while (NULL != success->left)
            {
            parent = success;
            success = success->left;
            }
        }

    return parent;
    }

template <class T>
BSTree<T>::BSTree() : root(NULL)
    {
    }

template <class T>
BSTree<T>::BSTree(const BSTree<T>& src) : root(NULL)
    {
    if (NULL != src.root)
        {
        root = src.root->cascadeCopy();
        }
    }

template <class T>
BSTree<T>::~BSTree()
    {
    if (NULL != root)
        {
        root->cascadeDelete();
        }
    }

template <class T>
BSTree<T>& BSTree<T>::operator = (const BSTree<T>& src)
    {
    if (this != &src)
        {
        if (NULL != root)
            {
            root->cascadeDelete();
            }
        if (NULL != src.root)
            {
            root = src.root->cascadeCopy();
            }
        }
    }

template <class T>
bool BSTree<T>::insert(T key)
    {
    bool replaced = false;
    treeNode<T>* parent = BinSearch(key, root);
    if (NULL == parent) // the root is NULL
        {
        root = new treeNode<T>(key);
        }
    else if (parent->getData() > key)
        {
        if (NULL != parent->left)
            {
            replaced = true;
            parent->left->injectData(key);
            }
        else
            {
            parent->left = new treeNode<T>(key);
            }
        }
    else if (parent->getData() < key)
        {
        if (NULL != parent->right)
            {
            replaced = true;
            parent->right->injectData(key);
            }
        else
            {
            parent->right = new treeNode<T>(key);
            }
        }
    else // parent is root
        {
        replaced = true;
        root->injectData(key);
        }
    return replaced;
    }

template <class T>
bool BSTree<T>::remove(T key)
    {
    bool found = false;
    treeNode<T>* parent = BinSearch(key, root);
    if (NULL != parent)
        {
        T p_data = parent->getData();
        bool isRoot = root == parent && p_data == key;
        bool isLeft = p_data > key;
        treeNode<T>* heir = NULL;
        treeNode<T>* keyComparer;
        
        if (isRoot)
            {
            keyComparer = parent;
            }
        else if (true == isLeft)
            {
            keyComparer = parent->left;
            }
        else
            {
            keyComparer = parent->right;
            }

        if (NULL != keyComparer && key == keyComparer->getData())
            {
            treeNode<T>* heirParent = successorParent(keyComparer);
            if (NULL == heirParent)
                {
                if (NULL != keyComparer->left)
                    {
                    heir = keyComparer->left;
                    }
                }
            else if (heirParent == keyComparer)
                {
                heir = keyComparer->right;
                heir->left = keyComparer->left;
                }
            else
                {
                heir = heirParent->left;
                heirParent->left = heir->right;
                heir->left = keyComparer->left;
                heir->right = keyComparer->right;
                }
            delete keyComparer;
            found = true;
                
            if (isRoot)
                {
                root = heir;
                }
            else if (isLeft)
                {
                parent->left = heir;
                }
            else
                {
                parent->right = heir;
                }
            }
        }

    return found;
    }

template <class T>
bool BSTree<T>::exists(T key)
    {
    treeNode<T>* parent = BinSearch(key, root);
    bool found = false;
    if (NULL != parent)
        {
        treeNode<T>* keyComparer = parent;
        if (key < parent->getData())
            {
            keyComparer = parent->left;
            }
        else if (key > parent->getData())
            {
            keyComparer = parent->right;
            }
        if (NULL != keyComparer)
            {
            found = key == keyComparer->getData();
            }
        }
    return found;
    }

#endif /* __BSTREE__H */
//
//  BSTree.cpp
//  Tree
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#ifdef __BSTREE__H

template <class T>
void BSTree<T>::draw()
    {
    }

template <class T>
treeNode<T>* BSTree<T>::BinSearch(T key, treeNode<T>* i_root)
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
treeNode<T>* BSTree<T>::successor(treeNode<T>* i_root)
    {
    treeNode<T>* success = i_root;

    if (NULL != i_root->right)
        {
        success = i_root->right;
        }
    while (NULL != success->left)
        {
        success = success->left;
        }

    return success;
    }

template <class T>
BSTree<T>::BSTree() : root(NULL)
    {
    }

template <class T>
BSTree<T>::~BSTree()
    {
    root->cascadeDelete();
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
    if (NULL == parent)
        {
        bool isLeft = parent->getData() > key;
        treeNode<T>* keyComparer = isLeft ? parent->left : parent->right;
        treeNode<T>* heir = successor(keyComparer);
        BinSearch(heir->getData(), keyComparer)->left = heir->right;
        heir->left = keyComparer->left;
        heir->right = keyComparer->right;
        if (isLeft)
            {
            parent->left = heir;
            }
        else
            {
            parent->right = heir;
            }
        delete keyComparer;
        found = true;
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
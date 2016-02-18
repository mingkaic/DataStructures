//
//  pBSTree.cpp
//  Tree
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#ifdef __P_BSTREE__H

#include <cstdlib>
#include "pTreeNode.hpp"

template <class T>
pTreeNode<T>* pBSTree<T>::BinSearch(T key, pTreeNode<T>* i_root) const
    {
    pTreeNode<T>* match;
    pTreeNode<T>* child = match = i_root;

    while(NULL != child && match->getData() != key)
        {
        match = child;
        if (child->getData() > key)
            {
            child = child->left;
            }
        else
            {
            child = child->right;
            }
        }
    return match;
    }

template <class T>
pTreeNode<T>* pBSTree<T>::successor(pTreeNode<T>* i_root)
    {
    pTreeNode<T>* success = i_root;
    
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
pBSTree<T>::pBSTree() : root(NULL)
    {
    }

template <class T>
pBSTree<T>::pBSTree(const pBSTree<T>& src) : root(NULL)
    {
    if (NULL != src.root)
        {
        root = src.root->cascadeCopy();
        }
    }

template <class T>
pBSTree<T>::~pBSTree()
    {
    if (NULL != root)
        {
        root->cascadeDelete();
        }
    }

template <class T>
pBSTree<T>& pBSTree<T>::operator = (const pBSTree<T>& src)
    {
    if (this != &src)
        {
        if (NULL != src.root)
            {
            root = src.root->cascadeCopy();
            }
        if (NULL != root)
            {
            root->cascadeDelete();
            }
        root = src.root->cascadeCopy();
        }
    return *this;
    }

template <class T>
bool pBSTree<T>::insert(T key)
    {
    bool unique = true;
    pTreeNode<T>* candidate = BinSearch(key, root);
    
    if (NULL == candidate)
        {
        root = new pTreeNode<T>(key);
        }
    else if (candidate->getData() == key)
        {
        unique = false;
        candidate->injectData(key);
        }
    else
        {
        pTreeNode<T>* child = new pTreeNode<T>(key);
        child->parent = candidate;
        
        if (candidate->getData() > key)
            {
            candidate->left = child;
            }
        else
            {
            candidate->right = child;
            }
        }
    return unique;
    }

template <class T>
bool pBSTree<T>::remove(T key)
    {
    bool found = true;
    pTreeNode<T>* foundNode = BinSearch(key, root);

	// if the tree is empty or the data is not found
    if (NULL == foundNode && foundNode->getData() != key)
        {
        found = false;
        }
    else // remove by successor
        {
        pTreeNode<T>* heir = successor(foundNode);
        pTreeNode<T>* child = NULL == heir->right ? heir->left : heir->right;
        pTreeNode<T>* parent = heir->parent;
        
        foundNode->injectData(heir->getData());
        
        // detach child from heir (if child exists)
        if (NULL != child) // at least 1 child
            {
            child->parent = parent;
            }
            
        if (NULL == parent) // if heir is the root
            {
            root = child;
            }
        else if (heir == parent->left)
            {
            parent->left = child;
            }
        else
            {
            parent->right = child;
            }
            
        delete heir;
        }
        
    return found;
    }

template <class T>
bool pBSTree<T>::exists(T key)
    {
    pTreeNode<T>* match = BinSearch(key, root);
    
    return NULL != match && match->getData() == key;
    }

#endif /* __P_BSTREE__H */
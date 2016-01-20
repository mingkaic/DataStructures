//
//  RBTree.cpp
//  Tree
//
//  Created by Ming Kai Chen on 2014-06-26.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __RB_TREE__H

template <class T>
RBNode<T>::RBNode(T data) :
isBlack(true), left(NULL), right(NULL), parent(NULL)
    {
    dataInit(data);
    }
        
template <class T>
RBNode<T>::RBNode(T data, bool isBlack) :
isBlack(isBlack), left(NULL), right(NULL), parent(NULL)
    {
    dataInit(data);
    }

template <class T>
RBNode<T>::RBNode(RBNode<T>* left, T data, RBNode<T>* right) :
isBlack(true), left(left), right(right), parent(NULL)
    {
    dataInit(data);
    }

template <class T>
RBNode<T>* RBNode<T>::cascadeCopy()
    {
    RBNode<T>* cpyLeft = NULL;
    RBNode<T>* cpyRight = NULL;
    RBNode<T>* cpy = new RBNode<T>(this->data);
    if (NULL != left)
        {
        cpyLeft = left->cascadeCopy();
        cpyLeft->parent = cpy;
        }
    if (NULL != right)
        {
        cpyRight = right->cascadeCopy();
        cpyRight->parent = cpy;
        }
    cpy->left = cpyLeft;
    cpy->right = cpyRight;
    return cpy;
    }

template <class T>
RBTree<T>::RBTree() : root(NULL)
    {
    }

template <class T>
RBTree<T>::RBTree(const RBTree& src)
    {
    root = src.root->cascadeCopy();
    }

template <class T>
RBTree<T>::~RBTree()
    {
    root->cascadeDelete();
    }

template <class T>
RBTree<T>& RBTree<T>::operator = (const RBTree<T>& src)
    {
    if (this != &src)
        {
        root->cascadeDelete();
        root = src.root->cascadeCopy();
        }
    return this;
    }

template <class T>
bool RBTree<T>::insert(T key)
    {
    bool childIsLeft = false;
    bool parentIsLeft = false;
    RBNode<T>* secondGen = NULL;
    // found insertion place
    RBNode<T>* firstGen = closestNode(root, key);
    
    // Insert to empty tree
    if (NULL == firstGen)
        {
        root = new RBNode<T>(key);
        return true;
        }
    
    // if a duplicate of data is found, don't insert
    if (firstGen->data == key)
        {
        root->injectData(key);
        return false;
        }
    
    // this Node is red and has parent set to insertAfter
    secondGen = new RBNode<T>(key, false);
    secondGen->parent = firstGen;
    
    // connect parent to a child,
    // determine if inserted Node is left or right child of parent
    if (firstGen->data < key) {
        firstGen->right = secondGen;
        childIsLeft = false;
    } else {
        firstGen->left = secondGen;
        childIsLeft = true;
    }
    
    // maintain RedBlack properties
    // firstGen previously represented secondGen's parent, but now
    // firstGen represents secondGen's uncle
    while (secondGen->parent && !secondGen->parent->isBlack) {
        // find the uncle (use firstGen pointer)
        if (secondGen->parent == secondGen->parent->parent->left ) {
            parentIsLeft = true;
            firstGen = secondGen->parent->parent->right;
        } else {
            parentIsLeft = false;
            firstGen = secondGen->parent->parent->left;
        }
        // case 1: uncle is red
        if (firstGen && !firstGen->isBlack) {
            // swap the colours
            secondGen->parent->isBlack = firstGen->isBlack = true;
            secondGen->parent->parent->isBlack = false;
            // Move up the tree to grandparent
            secondGen = secondGen->parent->parent;
            if (secondGen->parent && secondGen->parent->left == secondGen)
				childIsLeft = true;
			else
				childIsLeft = false;
        } else {
            // uncle is a black Node
            // childIsLeft XOR parentIsLeft
            if (childIsLeft ^ parentIsLeft) {
                // case 2 - move up and rotate
                secondGen = secondGen->parent;
                rotate(secondGen, parentIsLeft);
            }
            // case 3
            secondGen->parent->isBlack = true;
            secondGen->parent->parent->isBlack = false;
            rotate(secondGen->parent->parent, !parentIsLeft);
        }
    }
    // Colour the root black
    root->isBlack = true;
    
    return true;
    }

template <class T>
bool RBTree<T>::remove(T key)
    {
    }

template <class T>
RBNode<T>* RBTree<T>::closestNode(RBNode<T>*& root, T data) const
    {
    RBNode<T>* foundN = NULL;
    if (NULL == root)
        {
        foundN = root; 
        }
    else if (root->left && root->getData() > data) // go closer
        {
        foundN = closestNode(root->left, data);
        }
    else if (root->right && root->getData() < data)
        {
        foundN = closestNode(root->right, data);
        }
    return root;
}

#endif /* __RB_TREE__H */
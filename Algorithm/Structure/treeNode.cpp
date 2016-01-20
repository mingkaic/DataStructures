//
//  treeNode.cpp
//  Tree
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#ifdef __TREE_NODE__H

template <class T>
void treeNode<T>::injectData(T data)
    {
    this->data = data; // simple shallow copy
    }

template <class T>
treeNode<T>::treeNode(T data)
    {
    this->dataInit(data);
    this->left = this->right = NULL;
    }

template <class T>
treeNode<T>::treeNode(treeNode<T>* left, T data, treeNode<T>* right)
    {
    this->dataInit(data);
    this->left = this->right = NULL;
    }

template <class T>
void treeNode<T>::cascadeDelete()
    {
    if (NULL != this->left)
        {
        this->left->cascadeDelete();
        }
    if (NULL != this->right)
        {
        this->right->cascadeDelete();
        }
    }

#endif /* __TREE_NODE__H */
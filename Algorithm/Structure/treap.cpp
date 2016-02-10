//
//  treap.cpp
//  Tree
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#ifdef __TREAP__H

template <class T>
p_treeNode::p_treeNode(T data) :
left(NULL), right(NULL), parent(NULL)
    {
    this->dataInit(data);
    priority = rand();
    }

template <class T>
p_treeNode::p_treeNode(p_treeNode<T>* left, T data, p_treeNode<T>* right) :
left(NULL), right(NULL), parent(NULL)
    {
    this->dataInit(data);
    }
        
template <class T>
p_treeNode<T>* p_treeNode::cascadeCopy()
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
treap<T>* treap<T>::split();

template <class T>
void treap<T>::merge(treap* other);

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
void treap<T>::insert(T data)
    {
    
    }

template <class T>
T treap<T>::remove()
    {
    return root->getData();
    }

template <class T>
signed treap<T>::search(signed key)
    {
    return -1;
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
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
    this->dataInit(data);
    }
        
template <class T>
RBNode<T>::RBNode(T data, bool isBlack) :
isBlack(isBlack), left(NULL), right(NULL), parent(NULL)
    {
    this->dataInit(data);
    }

template <class T>
RBNode<T>::RBNode(RBNode<T>* left, T data, RBNode<T>* right) :
isBlack(true), left(left), right(right), parent(NULL)
    {
    dataInit(data);
    }

template <class T>
void RBNode<T>::cascadeDelete()
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

template <class T>
RBNode<T>* RBNode<T>::cascadeCopy()
    {
    RBNode<T>* cpy = new RBNode<T>(this->data);
    if (NULL != left)
        {
        cpy->left = left->cascadeCopy();
        cpy->left->parent = cpy;
        }
    if (NULL != right)
        {
        cpy->right = right->cascadeCopy();
        cpy->right->parent = cpy;
        }
    return cpy;
    }

template <class T>
RBTree<T>::RBTree() : root(NULL)
    {
    }

template <class T>
RBTree<T>::RBTree(const RBTree& src)
    {
    if (NULL != src.root)
        {
        root = src.root->cascadeCopy();
        }
    }

template <class T>
RBTree<T>::~RBTree()
    {
    if (NULL != root)
        {
        root->cascadeDelete();
        }
    }

template <class T>
RBTree<T>& RBTree<T>::operator = (const RBTree<T>& src)
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
    return this;
    }

// return true if inserted key is unique
// if existing key is found, key content will overwrite the data
template <class T>
bool RBTree<T>::insert(T key)
    {
    bool unique = true;
    bool childIsLeft = false;
    
    // find primary insertion place:
    //      NULL -> empty tree,
    //      data = key -> duplicate,
    //      data > key -> left is NULL -> child is left,
    //      data < key -> right is NULL -> child is right,
    RBNode<T>* topNode = BinSearch(key, root);
    
    // Insert to empty tree
    if (NULL == topNode)
        {
        root = new RBNode<T>(key);
        }
    else if (topNode->getData() == key)
        {
        topNode->injectData(key);
        unique = false;
        }
    else
        {
        // this Node is red and has parent set to insertAfter
        RBNode<T>* child = new RBNode<T>(key, false);
        bool parentIsLeft = false;
        child->parent = topNode;
        
        childIsLeft = topNode->getData() > key;
        if (true == childIsLeft)
            {
            topNode->left = child;
            }
        else
            {
            topNode->right = child;
            }
        
        // maintain RedBlack properties
        // note: grandparent is black in loop, since parent is red
        while (NULL != child->parent && false == child->parent->isBlack)
            {
            // due to iteration, topNode is not yet
            // guaranteed to be child's parent
            parentIsLeft = child->parent == child->parent->parent->left;
            // make topNode the uncle of the child
            topNode = parentIsLeft ? child->parent->parent->right : child->parent->parent->left;
            
            // case 1: uncle is red
            if (NULL != topNode && false == topNode->isBlack)
                {
                child->parent->isBlack = topNode->isBlack = true;
                topNode->parent->isBlack = false;
                // Move up to the grandparent
                child = topNode->parent;
                childIsLeft = (root != child && child->parent->left == child);
                }
            else // uncle is a black Node or nil
                {
                // case 2: parent and child orientation are not aligned
                // rotate parent, stay at the same level (the parent becometh the child)
                if (childIsLeft != parentIsLeft)
                    {
                    child = child->parent;
                    rotate(child, parentIsLeft);
                    }
                // case 3: orientations are aligned
                // parent must be black (in order to take over grandparent's position)
                // grandparent change to red
                child->parent->isBlack = true;
                child->parent->parent->isBlack = false;
                rotate(child->parent->parent, !parentIsLeft); // parent moves up
                }
            }
        // property 1: root is black
        root->isBlack = true;
        }
    
    return unique;
    }

template <class T>
bool RBTree<T>::remove(T key)
    {
    bool found = true;
    RBNode<T>* foundNode = BinSearch(key, root);

	// if the tree is empty or the data is not found
    if (!(foundNode && foundNode->getData() == key))
        {
        found = false;
        }
    else // remove by successor
        {
        RBNode<T>* heir = successor(foundNode);
        RBNode<T>* child = NULL == heir->right ? heir->left : heir->right;
        RBNode<T>* parent = heir->parent;
        bool childIsLeft = true;
        
        foundNode->injectData(heir->getData());
        
        // detach child from heir (if child exists)
        if (NULL != child) // at least 1 child
            {
            child->parent = parent;
            }
        if (NULL == parent) // if heir is the root
            {
            root = child;
            if (NULL != root)
                {
                root->isBlack = true;
                }
            }
        else
            {
            childIsLeft = heir == parent->left;
            if (true == childIsLeft)
                {
                parent->left = child;
                }
            else
                {
                parent->right = child;
                }
            if (true == heir->isBlack)
                {
                // child could be null, so parent is passed in
                deleteFixUp(parent, childIsLeft);
                }
            }
            
        delete heir;
        }
        
    return found;
    }

template <class T>
RBNode<T>* RBTree<T>::BinSearch(T key, RBNode<T>* i_root) const
    {
    RBNode<T>* match;
    RBNode<T>* child = match = i_root;

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
void RBTree<T>::deleteFixUp(RBNode<T>* parent, bool childIsLeft)
    {
    RBNode<T>* child;
    RBNode<T>* sibling;
    
    child = childIsLeft ? parent->left : parent->right;
    while (child != root && (NULL == child || child->isBlack))
        {
        sibling = childIsLeft ? parent->right : parent->left;
        // sibling cannot be NULL, parent cannot be NULL
        if (false == sibling->isBlack)
            {
            sibling->isBlack = true;
            parent->isBlack = false;
            // rotate in the child's direction
            rotate(parent, childIsLeft);
            sibling = childIsLeft ? parent->right : parent->left;
            }
        // sibling can be childless which are treated as black
        if ((NULL == sibling->left || sibling->left->isBlack) &&
            (NULL == sibling->right || sibling->right->isBlack))
            {
            sibling->isBlack = false;
            // moving up in the tree
            child = parent;
            parent = child->parent;
            if (parent && parent->left == child)
                childIsLeft = true;
            else
                childIsLeft = false;
            }
        else
            {
            if (true == childIsLeft &&
                (NULL == sibling->right || sibling->right->isBlack))
                {
                if (NULL != sibling->left)
                    {
                    sibling->left->isBlack = true;
                    }
                
                sibling->isBlack = false;
                rotate(sibling, false); // right rotate
                sibling = parent->right;
                }
            if (false == childIsLeft &&
                (NULL == sibling->left || sibling->left->isBlack))
                {
                if (NULL != sibling->right)
                    {
                    sibling->right->isBlack = true;
                    }
                
                sibling->isBlack = false;
                rotate(sibling, true); // left rotate
                sibling = parent->left;
                }
            if (true == childIsLeft && NULL != sibling->right)
                {
                sibling->right->isBlack = true;
                }
            if (false == childIsLeft && NULL != sibling->left)
                {
                sibling->left->isBlack = true;
                }
            sibling->isBlack = parent->isBlack;
            parent->isBlack = true;
            rotate(parent, childIsLeft); // rotate in child's direction
            child = root;
            }
        }
    child->isBlack = true;
    }

template <class T>
void RBTree<T>::rotate(RBNode<T>* parent, bool rotateLeft)
    {
    RBNode<T>* child;
    if (true == rotateLeft)
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
RBNode<T>* RBTree<T>::successor(RBNode<T>* i_root)
    {
    RBNode<T>* success = i_root;
    
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
bool RBTree<T>::exists(T key)
    {
    RBNode<T>* match = BinSearch(key, root);
    
    return NULL != match && match->getData() == key;
    }

#endif /* __RB_TREE__H */
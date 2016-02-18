//
//  RBTree.cpp
//  Tree
//
//  Created by Ming Kai Chen on 2014-06-26.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __RB_TREE__H

template <class T>
void RBTree<T>::deleteFixUp(pTreeNode<pair<bool, T> >* parent, bool childIsLeft)
    {
    pTreeNode<pair<bool, T> >* child;
    pTreeNode<pair<bool, T> >* sibling;
    
    child = childIsLeft ? parent->left : parent->right;
    while (child != this->root && (NULL == child || isBlack(child)))
        {
        sibling = childIsLeft ? parent->right : parent->left;
        // sibling cannot be NULL, parent cannot be NULL
        if (false == isBlack(sibling))
            {
            isBlack(sibling) = true;
            isBlack(parent) = false;
            // rotate in the child's direction
            rotate(parent, childIsLeft);
            sibling = childIsLeft ? parent->right : parent->left;
            }
        // sibling can be childless which are treated as black
        if ((NULL == sibling->left || isBlack(sibling->left)) &&
            (NULL == sibling->right || isBlack(sibling->right)))
            {
            isBlack(sibling) = false;
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
                (NULL == sibling->right || isBlack(sibling->right)))
                {
                if (NULL != sibling->left)
                    {
                    isBlack(sibling->left) = true;
                    }
                
                isBlack(sibling) = false;
                rotate(sibling, false); // right rotate
                sibling = parent->right;
                }
            if (false == childIsLeft &&
                (NULL == sibling->left || isBlack(sibling->left)))
                {
                if (NULL != sibling->right)
                    {
                    isBlack(sibling->right) = true;
                    }
                
                isBlack(sibling) = false;
                rotate(sibling, true); // left rotate
                sibling = parent->left;
                }
            if (true == childIsLeft && NULL != sibling->right)
                {
                isBlack(sibling->right) = true;
                }
            if (false == childIsLeft && NULL != sibling->left)
                {
                isBlack(sibling->left) = true;
                }
            isBlack(sibling) = isBlack(parent);
            isBlack(parent) = true;
            rotate(parent, childIsLeft); // rotate in child's direction
            child = this->root;
            }
        }
    isBlack(child) = true;
    }

template <class T>
void RBTree<T>::rotate(pTreeNode<pair<bool, T> >* parent, bool rotateLeft)
    {
    pTreeNode<pair<bool, T> >* child;
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
    if (this->root == parent)
        {
        this->root = child;
        }
    }

template <class T>
RBTree<T>::RBTree(const RBTree& src) : pBSTree<pair<bool, T> >(src)
    {
    }

template <class T>
RBTree<T>& RBTree<T>::operator = (const RBTree<T>& src)
    {
    pBSTree<pair<bool, T> >::operator = (src);
    return *this;
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
    pTreeNode<pair<bool, T> >* topNode = BinSearch(key, this->root);
    
    // Insert to empty tree
    if (NULL == topNode)
        {
        this->root = new pTreeNode<pair<bool, T> >(pair<bool, T>(true, key));
        }
    else if (topNode->getData() == key)
        {
        topNode->injectData(key);
        unique = false;
        }
    else
        {
        // this Node is red and has parent set to insertAfter
        pTreeNode<pair<bool, T> >* child = new pTreeNode<pair<bool, T> >(pair<bool, T>(false, key));
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
        while (NULL != child->parent && false == isBlack(child->parent))
            {
            // due to iteration, topNode is not yet
            // guaranteed to be child's parent
            parentIsLeft = child->parent == child->parent->parent->left;
            // make topNode the uncle of the child
            topNode = parentIsLeft ? child->parent->parent->right : child->parent->parent->left;
            
            // case 1: uncle is red
            if (NULL != topNode && false == isBlack(topNode))
                {
                isBlack(child->parent) = isBlack(topNode) = true;
                isBlack(topNode->parent) = false;
                // Move up to the grandparent
                child = topNode->parent;
                childIsLeft = (this->root != child && child->parent->left == child);
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
                isBlack(child->parent) = true;
                isBlack(child->parent->parent) = false;
                rotate(child->parent->parent, !parentIsLeft); // parent moves up
                }
            }
        // property 1: root is black
        isBlack(this->root) = true;
        }
    
    return unique;
    }

template <class T>
bool RBTree<T>::remove(T key)
    {
    bool found = true;
    pTreeNode<pair<bool, T> >* foundNode = BinSearch(key, this->root);

	// if the tree is empty or the data is not found
    if (!(foundNode && foundNode->getData() == key))
        {
        found = false;
        }
    else // remove by successor
        {
        pTreeNode<pair<bool, T> >* heir = successor(foundNode);
        pTreeNode<pair<bool, T> >* child = NULL == heir->right ? heir->left : heir->right;
        pTreeNode<pair<bool, T> >* parent = heir->parent;
        bool childIsLeft = true;
        
        foundNode->injectData(heir->getData());
        
        // detach child from heir (if child exists)
        if (NULL != child) // at least 1 child
            {
            child->parent = parent;
            }
        if (NULL == parent) // if heir is the root
            {
            this->root = child;
            if (NULL != this->root)
                {
                isBlack(this->root) = true;
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
            if (true == isBlack(heir))
                {
                // child could be null, so parent is passed in
                deleteFixUp(parent, childIsLeft);
                }
            }
            
        delete heir;
        }
        
    return found;
    }

#endif /* __RB_TREE__H */
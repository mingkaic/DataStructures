//
//  BSTree.h
//  Tree
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __BSTREE__H
#define __BSTREE__H

#include "TreeNode.hpp"

template <class T>
class BSTree
    {
    private:
        treeNode<T>* root;
    protected:
        // return   NULL if root is NULL
        //          pointer to root (if root contains key)
        //          pointer to the parent to node containing key
        treeNode<T>* BinSearch(T key, treeNode<T>* i_root);
        treeNode<T>* successor(treeNode<T>* i_root);
    public:
        BSTree();
        virtual ~BSTree();

        virtual bool insert(T key); // true if key is existed
        virtual bool remove(T key); // true if removed
        bool exists(T key);
        //child search(key);
        
        void draw();
    };

#include "BSTree.cpp"

#endif /* __BSTREE__H */
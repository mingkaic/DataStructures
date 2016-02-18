//
//  BSTree.hpp
//  Tree
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __BSTREE__H
#define __BSTREE__H

#include "treeNode.hpp"

template <class T>
class BSTree
    {
    private:
        treeNode<T>* root;
        // return   NULL if root is NULL
        //          pointer to root (if root contains key)
        //          pointer to the parent to node containing key
        treeNode<T>* BinSearch(T key, treeNode<T>* i_root) const;
        virtual treeNode<T>* successorParent(treeNode<T>* i_root);
    public:
        BSTree();
        BSTree(const BSTree<T>& src);
        virtual ~BSTree();
        BSTree<T>& operator = (const BSTree<T>& src);

        bool insert(T key); // true if key is existed
        bool remove(T key); // true if removed
        bool exists(T key);
        //child search(key);
        treeNode<T>* getRoot() {return root;}
    };

#include "BSTree.cpp"

#endif /* __BSTREE__H */
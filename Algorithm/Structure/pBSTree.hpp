//
//  pBSTree.hpp
//  Tree
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __P_BSTREE__H
#define __P_BSTREE__H

#include "pTreeNode.hpp"

template <class T>
class pBSTree
    {
    private:
        pTreeNode<T>* root;
        // gets exact match if key found, closest match otherwise
        pTreeNode<T>* BinSearch(T key, pTreeNode<T>* i_root) const;
        pTreeNode<T>* successor(pTreeNode<T>* i_root);
    public:
        pBSTree();
        pBSTree(const pBSTree<T>& src);
        virtual ~pBSTree();
        pBSTree<T>& operator = (const pBSTree<T>& src);

        virtual bool insert(T key); // true if key is existed
        virtual bool remove(T key); // true if removed
        bool exists(T key);
        //child search(key);
        
        pTreeNode<T>* getRoot() {return root;}
    };

#include "pBSTree.cpp"

#endif /* __P_BSTREE__H */
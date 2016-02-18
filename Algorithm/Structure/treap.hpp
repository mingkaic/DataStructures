//
//  treap.h
//  Tree
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __TREAP__H
#define __TREAP__H

#include "pBSTree.hpp"
#include "priorityContainer.hpp"

template <class T>
class treap : pBSTree<priorityContainer<T> >
    {
    private:
        void rotate(pTreeNode<priorityContainer<T> >* parent, bool rotLeft);
        treap* split();
        void merge(treap* other);
    public:
        treap(const treap<T>& src);
        virtual ~treap() {} // parent's got it handled
        treap<T>& operator = (const treap<T>& src);

        // basic self-balancing tree operations
        bool insert(T data);
        bool remove(T data);
        T removeTop();

        // bulk ops
        void tr_union();
        void tr_intersection();
        void tr_difference();
    };

#include "treap.cpp"

#endif /* __TREAP__H */
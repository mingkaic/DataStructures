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

#include "treeNode.hpp"

class treap
    {
    private:
        treeNode<signed>* head;

        treap* split();
        void merge(treap* other);
    public:
        treap();
        ~treap();

        // basic self-balancing tree operations
        void insert();
        void remove();
        signed search(signed key);

        // bulk ops
        void tr_union();
        void tr_intersection();
        void tr_difference();
    };

#include "treap.cpp"

#endif /* __TREAP__H */
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

#include <cstdlib>
#include <ctime>
#include "treeNode.hpp"

srand(time(NULL));

template <class T>
class p_treeNode : public treeNode
    {
    private:
        size_t priority;

    public:
        p_treeNode<T>* left;
        p_treeNode<T>* right;
        p_treeNode<T>* parent;
        
        p_treeNode(T data);
        p_treeNode(p_treeNode<T>* left, T data, p_treeNode<T>* right);
        virtual ~p_treeNode() {}
        
        virtual p_treeNode<T>* cascadeCopy();
        bool operator < (const p_treeNode& left);
    };

template <class T>
class treap
    {
    private:
        p_treeNode<T>* root;
        
        void rotate(p_treeNode<T>* parent, bool rotLeft);
        treap* split();
        void merge(treap* other);
    public:
        treap();
        ~treap();

        // basic self-balancing tree operations
        void insert(T data);
        T remove();
        signed search(signed key);

        // bulk ops
        void tr_union();
        void tr_intersection();
        void tr_difference();
    };

#include "treap.cpp"

#endif /* __TREAP__H */
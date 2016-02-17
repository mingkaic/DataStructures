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

template <class T>
class p_treeNode : public treeNode<T>
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
    };

template <class T>
class treap
    {
    private:
        p_treeNode<T>* root;
        
        p_treeNode<T>* BinSearch(T key, p_treeNode<T>* i_root) const;
        void rotate(p_treeNode<T>* parent, bool rotLeft);
        treap* split();
        void merge(treap* other);
    public:
        treap();
        ~treap();

        // basic self-balancing tree operations
        bool insert(T data);
        bool remove(T data);
        T removeTop();
        bool exists(T data);

        // bulk ops
        void tr_union();
        void tr_intersection();
        void tr_difference();
        
        p_treeNode<T>* getRoot() {return root;}
    };

#include "treap.cpp"

#endif /* __TREAP__H */
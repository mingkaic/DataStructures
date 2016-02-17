//
//  NDStructTest.cpp
//  NDStructTest
//
//  Created by Mingkai Chen on 2016-02-05.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#include <cstring>
#include <iostream>
#include "Structure/treap.hpp"
#include "Structure/skipList.hpp"

using namespace std;

size_t maxHeight(p_treeNode<size_t>* root)
    {
    if (NULL == root->left && NULL == root->right)
        return 1;
    size_t l = 0, r = 0;
    if (NULL != root->left)
        l = maxHeight(root->left);
    if (NULL != root->right)
        r = maxHeight(root->right);
    return (l > r ? l : r)+1;
    }

void treePositionSeeker(p_treeNode<size_t>* root, size_t level, size_t width, string** dataField)
    {
    dataField[level][width] = to_string(root->getData());
    if (NULL != root->left)
        {
        treePositionSeeker(root->left, level+1, 2*width, dataField);
        }
    if (NULL != root->right)
        {
        treePositionSeeker(root->right, level+1, 2*width+1, dataField);
        }
    }

void drawTree(p_treeNode<size_t>* n)
    {
    size_t maxH = maxHeight(n);
    size_t w = 1;
    string** levels = new string* [maxH];
    size_t currLevel = 0;
    for (currLevel = 0;
        currLevel < maxH;
        currLevel++)
        {
        levels[currLevel] = new string[w];
        for (size_t i = 0; i < w; i++)
            {
            levels[currLevel][i] = "nil";
            }
        w *= 2;
        }
        
    if (NULL != n)
        {
        treePositionSeeker(n, 0, 0, levels);
        }

    for (w = 1, currLevel = 0; currLevel < maxH; currLevel++)
        {
        cout << currLevel << ": ";
        for (size_t i = 0; i < w; i++)
            {
            cout << levels[currLevel][i] << " ";
            }
        cout << endl;
        w *= 2;
        }
         
    for (currLevel = 0; currLevel < maxH; currLevel++)
        {
        delete [] levels[currLevel];
        }
         
    delete [] levels;
    }

bool BSTVerify(p_treeNode<size_t>* root) {
    if (NULL == root)
        return true;
    bool verify = BSTVerify(root->left) && BSTVerify(root->right);
    if (NULL != root->left)
        {
        verify = verify && root->left->getData() < root->getData();
        }
    if (NULL != root->right)
        {
        verify = verify && root->getData() < root->right->getData();
        }
    return verify;
}

bool heapVerify(p_treeNode<size_t>* root) {
    if (NULL == root)
        return true;
    bool verify = heapVerify(root->left) && heapVerify(root->right);
    if (NULL != root->left)
        {
        verify = verify && root->left > root;
        }
    if (NULL != root->right)
        {
        verify = verify && root->right > root;
        }
    return verify;
}

int main(int argc, const char * argv[]) {
    size_t i;
    size_t limit = 3000;
    bool* inserted;
    char structure[64] = "treap";
    size_t* testValues;
    size_t spec = 1;
    if (argc > 1)
        {
        memcpy(structure, argv[1], 64);
        }
    if (argc > 2)
        spec = atoi(argv[1]);
    if (argc > 3)
        {
        limit = atoi(argv[2]);
        }
    
    treap<size_t> t;
        
    inserted = new bool [limit];
    memset(inserted, false, limit*sizeof(bool));
    size_t N, testVal;
    cin >> N;
    testValues = new size_t [N];
    cout << N << endl;
    vector<size_t> remover;
    
    cout << structure << " " << spec << endl;
        
    switch (structure[0])
        {
        case 'T':
        case 't':
            for (i = 0; i < N; i++)
                {
                cin >> testVal;
                cout << testVal << endl;
                testValues[i] = testVal;
                inserted[testVal] = true;
                t.insert(testVal);
                if (false == BSTVerify(t.getRoot()))
                    {
                    cout << "error: BST failed\n";
                    }
                if (false == heapVerify(t.getRoot()))
                    {
                    cout << "error: heap failed\n";
                    }
                }
            
            drawTree(t.getRoot());
            break;
                
            for (i= 0; i < limit; i++)
                {
                if (inserted[i] != t.exists(i))
                    {
                    cout << "error: unsuccessful existential check " << i << endl;
                    }
                if (true == inserted[i])
                    {
                    remover.push_back(i);
                    }
                }
        }
        
    cout << ">>>SUCCESS<<<" << endl;

    delete[] inserted;
    delete[] testValues;

    return 0;
}

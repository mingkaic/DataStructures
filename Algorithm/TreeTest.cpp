// TreeTest.cpp : Defines the entry point for the console application.
//

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include "Structure/Treap.hpp"
#include "Structure/BSTree.hpp"
#include "Structure/RBTree.hpp"
#include "Structure/Queue.hpp"
using namespace std;

size_t maxHeight(RBNode<size_t>* root)
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

size_t minHeight(RBNode<size_t>* root)
    {
    if (NULL == root->left && NULL == root->right)
        return 1;
    size_t l = 0, r = 0;
    if (NULL != root->left)
        l = minHeight(root->left);
    if (NULL != root->right)
        r = minHeight(root->right);
    return (l < r ? l : r)+1;
    }

void treePositionSeeker(treeNode<size_t>* root, size_t level, size_t width, string** dataField)
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

void treePositionSeeker(RBNode<size_t>* root, size_t level, size_t width, string** dataField)
    {
    dataField[level][width] = to_string(root->getData());
    if (false == root->isBlack)
        {
        dataField[level][width].push_back('R');
        }
    if (NULL != root->left)
        {
        treePositionSeeker(root->left, level+1, 2*width, dataField);
        }
    if (NULL != root->right)
        {
        treePositionSeeker(root->right, level+1, 2*width+1, dataField);
        }
    }

void drawTree(RBNode<size_t>* n)
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

bool RBProperty(RBNode<size_t>* r)
    {
    bool holds = true;
    if (NULL != r && false == r->isBlack)
        {
        if (NULL != r->left)
            {
            holds = holds && r->left->isBlack;
            if (holds)
                {
                holds = holds && RBProperty(r->left);
                }
            }
        if (NULL != r->right)
            {
            holds = holds && r->right->isBlack;
            if (holds)
                {
                holds = holds && RBProperty(r->right);
                }
            }
        }
    return holds;
    }

int main(int argc, char* argv[])
    {
    size_t i;
    size_t limit = 3000;
    bool* inserted;
    char structure[64] = "RBTree";
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
        
    inserted = new bool [limit];
    memset(inserted, false, limit*sizeof(bool));
    size_t N, testVal;
    cin >> N;
    testValues = new size_t [N];
    cout << N << endl;
    BSTree<size_t> b;
    RBTree<size_t> r;
    vector<size_t> remover;
    
    srand(time(NULL)+spec);
    
    cout << structure << " " << spec << endl;
        
    switch (structure[0])
        {
        case 'B':
        case 'b':
            for (i = 0; i < N; i++)
                {
                cin >> testVal;
                cout << testVal << endl;
                testValues[i] = testVal;
                inserted[testVal] = true;
                b.insert(testVal);
                }

            for (i= 0; i < limit; i++)
                {
                if (inserted[i] != b.exists(i))
                    {
                    cout << "error: unsuccessful existential check " << i << endl;
                    }
                if (true == inserted[i])
                    {
                    remover.push_back(i);
                    }
                }
            while (remover.size() > 0)
                {
                i = rand() % remover.size();
                cout << "removing index: " << i << endl;
                if (false == b.remove(remover[i]))
                    {
                    cout << "error: unsuccessful removal of " << remover[i] << endl;
                    }
                
            /*cout << "---------\n";
            drawTree(b.getRoot());
            cout << "---------\n";*/
                remover.erase(remover.begin()+i);
                cout << remover.size() << "remaining\n";
                }
                
            if (b.getRoot() != NULL)
                {
                cout << "error: incomplete removal\n";
                cout << b.getRoot()->getData() << endl;
                }
            
            break;
        case 'R':
        case 'r':
            for (i= 0; i < N; i++)
                {
                cin >> testVal;
                cout << testVal << endl;
                testValues[i] = testVal;
                inserted[testVal] = true;
                r.insert(testVal);
                
            cout << "---------\n";
            drawTree(r.getRoot());
            cout << "---------\n";
                    
                size_t max = maxHeight(r.getRoot());
                size_t min = minHeight(r.getRoot());
                if (max > 2*min)
                    cout << "error: invalid balance\n";
                }
                
            for (i= 0; i < limit; i++)
                {
                if (inserted[i] != r.exists(i))
                    {
                    cout << "error: unsuccessful existential check " << i << endl;
                    }
                if (true == inserted[i])
                    {
                    remover.push_back(i);
                    }
                }
            cout << "---------\n";
            drawTree(r.getRoot());
            cout << "---------\n";
            
            while (remover.size() > 0)
                {
                //cin >> i;
                i = rand() % remover.size();
                cout << "removing index: " << i << " " << remover[i] << endl;
                if (false == r.remove(remover[i]))
                    {
                    cout << "error: unsuccessful removal of " << remover[i] << endl;
                    }
                if (false == RBProperty(r.getRoot()))
                    cout << "error: RB property doesn't hold\n";
                remover.erase(remover.begin()+i);
                if (r.getRoot())
                    {
                    size_t max = maxHeight(r.getRoot());
                    size_t min = minHeight(r.getRoot());
                    if (max > 2*min)
                        cout << "error: invalid balance\n";
                        
                    cout << "---------\n";
                    drawTree(r.getRoot());
                    cout << "---------\n";
                    }
                }
                
            if (b.getRoot() != NULL)
                cout << "error: incomplete removal\n";
            
            break;
        }
        
    cout << ">>>SUCCESS<<<" << endl;

    delete[] inserted;
    delete[] testValues;

    return 0;
    }


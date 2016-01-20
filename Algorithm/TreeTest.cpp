// TreeTest.cpp : Defines the entry point for the console application.
//

#include <cstdlib>
#include <iostream>
#include "Structure/TreeNode.hpp"
#include "Structure/Treap.hpp"
#include "Structure/BSTree.hpp"
#include "Structure/RBTree.hpp"
using namespace std;

int main(int argc, char* argv[])
    {
    size_t limit = 3000;
    bool* inserted;
    size_t* testValues;
    if (argc > 2)
        limit = atoi(argv[1]);
    inserted = new bool [limit];
    memset(inserted, false, limit*sizeof(bool));
    BSTree<size_t> b;
    size_t N, testVal;
    cin >> N;
    cout << N << endl;
    testValues = new size_t [N];
    for (size_t i = 0; i < N; i++)
        {
        cin >> testVal;
        cout << testVal << endl;
        testValues[i] = testVal;
        inserted[testVal] = true;
        b.insert(testVal);
        }

    for (size_t i = 0; i < limit; i++)
        {
        if (inserted[i] != b.exists(i))
            {
            cout << "error: unsuccessful existential check " << i << endl;
            }
        }

    delete[] inserted;
    delete[] testValues;

    return 0;
    }


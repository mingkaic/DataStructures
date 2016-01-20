// List.cpp : Defines the entry point for the console application.
//

#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cstddef>

#include "Deque.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
using namespace std;

int main(int argc, char* argv[])
    {
    size_t N, testVal;
    char* structure = new char[256];
    cout << "enter structure: ";
    cin >> structure;
    cin >> N;
    size_t* testPlate = new size_t[N];
    Stack<size_t> s;
    Queue<size_t> q;

    switch (structure[0])
        {
        case 's':
        case 'S':
            if (false == s.isEmpty())
                {
                cout << "bad stack initialization\n";
                }
            for (size_t i = 0; i < N; i++)
                {
                cin >> testVal;
                testPlate[i] = testVal;
                s.push(testVal);
                }
            for (size_t comparer = 0; false == s.isEmpty(); N--)
                {
                comparer = s.pop();
                cout << comparer << endl;
                if (comparer != testPlate[N-1])
                    {
                    cout << "error: wrong stack value\n";
                    }
                }
            break;
        case 'q':
        case 'Q':
            if (false == q.isEmpty())
                {
                cout << "bad queue initialization\n";
                }
            for (size_t i = 0; i < N; i++)
                {
                cin >> testVal;
                testPlate[i] = testVal;
                q.enqueue(testVal);
                }
            size_t i = 0;
            for (size_t comparer = 0; false == q.isEmpty(); i++)
                {
                comparer = q.dequeue();
                cout << comparer << endl;
                if (comparer != testPlate[i])
                    {
                    cout << "error: wrong queue value\n";
                    }
                }
            break;
        }
    delete[] testPlate;
    return 0;
    }

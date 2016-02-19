// List.cpp : Defines the entry point for the console application.
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cstddef>

#include "Structure/deque.hpp"
#include "Structure/queue.hpp"
#include "Structure/stack.hpp"
using namespace std;

const size_t INSTREAM_MAX = 20000;
    
void elog(string msg)
    {
    cout << "ERROR: " << msg << endl;
    }

/* objects with the same method signature */
// tests for initialization, insertion, deletion, and deallocation
template <template <class T> class dataStructure>
bool basic_test(void (dataStructure<size_t>::*input_func)(size_t), 
                size_t (dataStructure<size_t>::*output_func)(), 
                bool orderFrontToBack)
    {
    dataStructure<size_t> coreSubject;
    dataStructure<size_t> fullRemoveTest;
    dataStructure<size_t> copyAssignmentSubject;
    bool success = true, caseSuccess;
    signed N, elem;
    signed entered[INSTREAM_MAX] = {-1};
    
    cin >> N;
    N %= INSTREAM_MAX;
    for (signed i = 0; i < N; i++)
        {
        cin >> elem;
        cout << "inserting element " << i << endl;
        elem %= INSTREAM_MAX;
        (coreSubject.*input_func)(elem);
        (fullRemoveTest.*input_func)(elem); // investigate issues with deallocating non-empty structures
        entered[elem] = i;
        }
        
    dataStructure<size_t> copySubject(coreSubject);
    copyAssignmentSubject = coreSubject;
    signed copyCElem, copyAElem;
    
    for (signed i = 0; i < N; i++)
        {
        elem = (coreSubject.*output_func)();
        copyCElem = (copySubject.*output_func)();
        copyAElem = (copyAssignmentSubject.*output_func)();
        cout << "removing element " << i << endl;

        caseSuccess = false;
        if ((entered[elem] == i && orderFrontToBack) || (entered[elem] == N-i-1 && !orderFrontToBack))
            {
            caseSuccess = true;
            entered[elem] = -1;
            }
        else
            {
            elog("retrieval order failed");
            }
            
        if (copyCElem != elem)
            {
            cout << "copy constructer elem: " << copyCElem << endl;
            elog("copy constructer removal not matching");
            }
        if (copyAElem != elem)
            {
            cout << "copy assignment elem: " << copyCElem << endl;
            elog("copy assignment removal not matching");
            }
        success = success && caseSuccess;
        }
        
    try
        {
        (coreSubject.*output_func)();
        success = false;
        elog("no error on empty removal");
        }
    catch(std::exception)
        {
        cout << "good throw" << endl;
        }
        
    return success;
    }
    
// test for copy constructer, assignment, state checker
template <template <class T> class dataStructure, class resultType>
bool advance_test(resultType (dataStructure<size_t>::*get_func)() const, 
                void (dataStructure<size_t>::*input_func)(size_t), 
                size_t nInput, size_t input[], resultType expectedResult)
    {
    bool success = true;
    dataStructure<size_t> obj;
    
    for (size_t i = 0; i < nInput; i++)
        {
        (obj.*input_func)(input[i]);
        }
    if (expectedResult != (obj.*get_func)())
        {
        elog("incorrect result");
        success = false;
        }
    
    return success;
    }

int main(int argc, char* argv[])
    {
    size_t staticPeekTest[6] = {20, 1, 23, 22, 42, 134};
    size_t singles[1] = {0};
    // STACK
    // begin basic test
    cout << "STACK TEST" << endl;
    if (true == basic_test<stack>(&stack<size_t>::push, &stack<size_t>::pop, false))
        {
        // proceed to advance test
        if (false == (advance_test<stack, bool>(&stack<size_t>::isEmpty, &stack<size_t>::push, 1, singles, false) ||
                    advance_test<stack, bool>(&stack<size_t>::isEmpty, &stack<size_t>::push, 0, singles, true)))
            {
            cout << "^^^ isEmpty() problem\n";
            }
        if (false == advance_test<stack, size_t>(&stack<size_t>::peek, &stack<size_t>::push, 6, staticPeekTest, 134))
            {
            cout << "^^^ peek() problem\n";
            }
        }
    // QUEUE
    // begin basic test
    cout << "QUEUE TEST" << endl;
    if (true == basic_test<queue>(&queue<size_t>::enqueue, &queue<size_t>::dequeue, true))
        {
        // proceed to advance test
        if (false == (advance_test<queue, bool>(&queue<size_t>::isEmpty, &queue<size_t>::enqueue, 1, singles, false) ||
                    advance_test<queue, bool>(&queue<size_t>::isEmpty, &queue<size_t>::enqueue, 0, singles, true)))
            {
            cout << "^^^ isEmpty() problem\n";
            }
        if (false == (advance_test<queue, size_t>(&queue<size_t>::peek_front, &queue<size_t>::enqueue, 6, staticPeekTest, 20) ||
                    advance_test<queue, size_t>(&queue<size_t>::peek_back, &queue<size_t>::enqueue, 6, staticPeekTest, 134)))
            {
            cout << "^^^ peek() problem\n";
            }
        }
    // DEQUE
    // begin basic test
    cout << "DEQUE TEST" << endl;
    if (true == basic_test<deque>(&deque<size_t>::enqueue, &deque<size_t>::dequeue, true) &&
        true == basic_test<deque>(&deque<size_t>::push_back, &deque<size_t>::pop_front, true))
        {
        // proceed to advance test
        if (false == (advance_test<deque, bool>(&deque<size_t>::isEmpty, &deque<size_t>::enqueue, 1, singles, false) ||
                    advance_test<deque, bool>(&deque<size_t>::isEmpty, &deque<size_t>::enqueue, 0, singles, true)))
            {
            cout << "^^^ isEmpty() problem\n";
            }
        if (false == (advance_test<deque, size_t>(&deque<size_t>::peek_front, &deque<size_t>::enqueue, 6, staticPeekTest, 20) ||
                    advance_test<deque, size_t>(&deque<size_t>::peek_back, &deque<size_t>::enqueue, 6, staticPeekTest, 134)))
            {
            cout << "^^^ peek() problem\n";
            }
        }
    
    return 0;
    }

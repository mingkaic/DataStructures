// TestGenerate.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstdlib>     /* srand, rand */
#include <time.h>    
using namespace std;

static size_t bigLimit = 3000;

static void generateTestCase(size_t n, size_t spec)
    {
    srand(time(NULL)+spec);
    cout << n << endl;
    while (n--)
        {
        cout << rand() % bigLimit << endl;
        }
    }

int main(int argc, char* argv[])
    {
    size_t testCase = 0;
    size_t spec = 0;
    if (argc >= 2)
        spec = atoi(argv[1]);
    if (argc >= 3)
        testCase = atoi((char*) argv[2]);
    if (argc >= 4)
        bigLimit = atoi((char*) argv[3]);

    if (!testCase)
        testCase = 10;

    generateTestCase(testCase, spec);

	return 0;
    }


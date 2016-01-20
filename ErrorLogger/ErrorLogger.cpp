//
//  main.cpp
//  MacErrorLogger
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>
using namespace std;

int main(int argc, const char * argv[])
    {
    vector<string> lines;
    string input;
    bool warningPlus = false;
    while (getline(cin, input))
        {
        if (0 == input.find_first_of("error:") ||
            0 == input.find_first_of("warning:"))
            {
            warningPlus = true;
            }
        lines.push_back(input);
        }
    
    if (warningPlus)
        {
        stringstream sbuff;
        srand(time(NULL));
        size_t spec;
        if (argc >= 2)
            spec = atoi(argv[1]);
        else
            spec = rand();
            
        string dir = "";
        if (argc >= 3)
            dir = argv[2];
            
        sbuff << dir << "/e_log" << time(NULL) << spec << ".txt";
        string fileName = sbuff.str();
        
        cout << "printing to file " << fileName << endl;
            
        ofstream myfile;
        myfile.open(fileName);

        for (vector<string>::iterator it = lines.begin();
             it != lines.end();
             it++)
            {
            myfile << *it << endl;
            }
            
        myfile.close();
        }
    
    return 0;
    }

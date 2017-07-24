#include <iostream>
#include <vector>
#include <iomanip>

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;


// printes the hex (in ascii) of an ascii message

int main(int argc, char* argv[])
{
    if(argc < 1 || (argc>=2 && strcmp(argv[1],"-h")==0)) {
        cerr << "Usage: " << argv[0] << " [-h] [m], where m is a string." <<  endl;
        cerr << "If no argument is given, string is read from stdin" << endl;
        return -1;
    }

    std::string m;
    if(argc >= 2)
    {
        m = argv[1];
    }
    else
    {
        getline(cin, m);
    }

    if(m.length() < 1)
    {
        cerr << "m must have length > 0" << endl;
        return -1;
    }

    for(int i = 0; i < m.size(); ++i)
    {
        unsigned char ch = m[i];

        cout << hex << setw(2) << setfill('0') << (unsigned int)ch;
    }

    cout << dec << endl;
    
        
    return 0;
}

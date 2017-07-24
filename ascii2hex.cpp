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
    if(argc < 2) {
        cerr << "Usage: " << argv[0] << " m, where m is a string " <<  endl;
        return -1;
    }

    std::string m(argv[1]);
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

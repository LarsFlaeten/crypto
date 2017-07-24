#include <iostream>
#include <vector>
#include <iomanip>
#include <bitset>

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

// Converts binary representation to ascii hex

void printUsage(const std::string& p)
{
        cout << "Usage: " << p << " [-h] [binstring] " << endl;
        cout << "If no argument is given, binstring is read from stdin" << endl;
}

int main(int argc, char* argv[])
{
    if(argc < 1) {
        printUsage(argv[0]);
        return -1;
    }

    std::string m;
    if(argc > 1)
    {
        m = argv[1];
        if(strcmp(m.c_str(), "-h")==0)
        {
            printUsage(argv[0]);
            return 0;
        }
    } else
    {
        getline(cin, m);
    }


    if(m.length() % 8 != 0)
    {
        cerr << "m must have length in multiple of 8s, m length was " << m.length() << ", text was [" << m << "]" << endl;
        return -1;
    }
    char *p;

    std::vector<unsigned char> mArray;
    for(int i = 0; i < m.size(); i = i+8)
    {
        bitset<8> bs(m.substr(i*8,8));
        unsigned n = bs.to_ulong();

        if(n>255)
        {
            cerr << "Error, number in m at position " << i*2 << " was not an HEX" << endl;
            return -1;
        }

        cout << hex << setw(2) << setfill('0') << n;
    }

    cout << dec << endl;
 
        
    return 0;
}

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

// Prints binary representation of ascii hex

void printUsage(const std::string& p)
{
        cout << "Usage: " << p << " [-h] [hexstring] " << endl;
        cout << "If no argument is given, hexstring is read from stdin" << endl;
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

    if(m.length() < 2)
    {
        cerr << "m must have length >= 2" << endl;
        return -1;
    }
    char *p;

    std::vector<unsigned char> mArray;
    for(int i = 0; i < m.size(); i = i+2)
    {
        char cstr[2];
        cstr[0] = m[i];
        cstr[1] = m[i+1];
        uint32_t ui=0;
        ui=strtoul(cstr, &p, 16);
        if(ui>255)
        {
            cerr << "Error, number in m at position " << i*2 << " was not an HEX" << endl;
            return -1;
        }

        cout << std::bitset<8>((unsigned char)ui) << " ";
    }

    cout << endl;
 
        
    return 0;
}

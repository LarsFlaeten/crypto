#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <random>

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

// Implementation of the One-Time Pad key generation

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Usage: " << argv[0] << " len (key lenght in bytes)" << endl;
        return -1;
    }

    int len = atoi(argv[1]);
    if(len < 1)
    {
        cout << "Error in key size specification, must be > 1" << endl;
        return -1;
    }


    // Open random device:
    std::random_device rd2("/dev/random");    
    std::uniform_int_distribution<> dis(0,255);
    for(unsigned int i = 0; i < len; ++i)
    {
        std::cout << hex << setw(2) << setfill('0') << dis(rd2);
    }
    std::cout << dec << endl;


    return 0;
}

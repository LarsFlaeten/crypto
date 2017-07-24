#include <iostream>
#include <vector>
#include <iomanip>

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

// prints the XOR of two bytes strings c = m XOR k

int main(int argc, char* argv[])
{
    if(argc < 3) {
        cout << "Usage: " << argv[0] << " m k, where m and k are hex strings of same lenght " << endl;
        return -1;
    }

    std::string m(argv[1]);
    std::string k(argv[2]);
    if(m.length() != k.length() || m.length() < 2)
    {
        cerr << "m and k must be same length and >= 2" << endl;
        return -1;
    }
    char *p;

    std::vector<unsigned char> mArray;
    std::vector<unsigned char> kArray;
    std::vector<unsigned char> cArray; 
    for(int i = 0; i < m.size(); i = i+2)
    {
        char cstr[2];
        cstr[0] = m[i];
        cstr[1] = m[i+1];
        uint32_t ui=0;
        ui=strtoul(cstr, &p, 16);
        mArray.push_back((unsigned char)ui);
        if(ui>255)
        {
            cout << "Error, number in m at position " << i*2 << " was not an HEX" << endl;
            return -1;
        }

        cstr[0] = k[i];
        cstr[1] = k[i+1];
        ui=strtoul(cstr, &p, 16);
        kArray.push_back((unsigned char)ui);
    
        if(ui>255)
        {
            cout << "Error, number in k at position " << i*2 << " was not an HEX" << endl;
            return -1;
        }
    }

    std::vector<unsigned char>::iterator mit, kit;
    for(mit = mArray.begin(), kit= kArray.begin(); mit != mArray.end(); ++mit, ++kit)
    {
        //cout << hex << (unsigned int)*mit << " XOR " << (unsigned int)*kit << " = " << (*mit ^ *kit) << endl;
        unsigned char c = *mit ^ *kit;
        cArray.push_back(c);
        cout << hex << setw(2) << setfill('0') << (unsigned int)c;
    }
    cout << dec << endl;
    // convert from an unsigned long int to a 4-byte array
    //byteArray[0] = (int)((uv >> 24) & 0xFF) ;
    //byteArray[1] = (int)((uv >> 16) & 0xFF) ;
    //byteArray[2] = (int)((uv >> 8) & 0XFF);
    //byteArray[3] = (int)((uv & 0XFF));


   /* int size = 4;
    if(byteArray[0]==0)
    {
        --size;
        if(byteArray[1]==0)
        {
            --size;
            if(byteArray[2]==0)
                --size;
        }
    }
    */





    std::vector<unsigned char> c;
 
        
    return 0;
}

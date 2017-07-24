#include <iostream>
#include <vector>
#include <iomanip>

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

// modification to standard Viginere, works on hex values instaed of a-z

int main(int argc, char* argv[])
{
    if(argc < 3) {
        cout << "Usage: " << argv[0] << " key enc/dec [message]" << endl;
        return -1;
    }

    std::string key(argv[1]);

    char *p;

    std::vector<unsigned char> byteArray;
    
    for(int i = 0; i < key.size(); i = i+2)
    {
        char cstr[2];
        cstr[0] = key[i];
        cstr[1] = key[i+1];
        uint32_t ui=0;
        ui=strtoul(cstr, &p, 16);
        byteArray.push_back((unsigned char)ui);

    }


    int size = byteArray.size();
    int offset = 0;

    bool encrypt = true;

    if(strcmp(argv[2],"dec")==0)
    {
        encrypt = false;
    } 


    // get message from cmdline or stdin:
    std::string message;  
    if(argc < 4)
    {
        //cin >> message;
        getline(cin, message);
    }
    else
        message = argv[3];


    std::vector<unsigned char> c;
    int keylen = key.size();
 
    if(encrypt)
    {
        
        
        for(int i = 0; i < message.size(); ++i)
        {
            c.push_back(message[i] ^ byteArray[i%size + offset]);
        }

    } else
    {
        // the message should be recast to the cipher:
        // Take each two letters in the message and make a number from them
        for(int i = 0; i < message.size();)
        {
            char cstr[2];
            cstr[0] = message[i];
            cstr[1] = message[i+1];
            uint32_t ui=0;
            ui=strtoul(cstr, &p, 16);
            c.push_back((unsigned char)ui);
            i = i + 2;
        }

        // Now do reverse cipher:
        message.clear();
        for(int j = 0; j < c.size(); ++j)
        {
            message.push_back(byteArray[j%size + offset] ^ c[j]);
        }
    } 

    if(encrypt)
    {
        for(int i = 0; i < c.size(); ++i)
            cout << hex << setw(2) << setfill('0') << (unsigned int)c[i];
        cout << dec << endl;
    } else
        cout << message << endl;

    return 0;
}

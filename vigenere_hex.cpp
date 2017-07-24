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

    int size = byteArray.size();
    int offset = 0;

    //cout << "key size: " << size << ", offset " << offset << endl;

    //for(int k = 0; k < size; ++k)
    //    cout << hex << (int)byteArray[k + offset];
    //cout << dec << endl;

    bool encrypt = true;

    if(strcmp(argv[2],"dec")==0)
    {
        encrypt = false;
        //cout << "Decrypting" << endl;
    } else
    {
        //cout << "Encrypting" << endl;
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
    //cout << "Using key: " << key << endl;
    //cout << "Message:   " << message << endl;
 
    if(encrypt)
    {
        
        
        for(int i = 0; i < message.size(); ++i)
        {
            //cout << hex << (int)message[i];
            // Carry the newline
            c.push_back(message[i] ^ byteArray[i%size + offset]);
        }
        //cout << dec << endl;

        //for(int i = 0; i < message.size(); ++i)
        //{
        //    cout << i%size + offset << " ";
        //}
        //cout << dec << endl;



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
            //cout << hex << (int)c[c.size()-1] << dec << endl;
            i = i + 2;
        }

        // Now do reverse cipher:
        message.clear();
        for(int j = 0; j < c.size(); ++j)
        {
            message.push_back(byteArray[j%size + offset] ^ c[j]);
        }
    } 

    //if(argc > 3 && (strcmp(argv[3],"--verbose") || strcmp(argv[3],"-v")))
    //{
    //   cout << "Cipher:    " << c << endl;
    //} else
    if(encrypt)
    {
        for(int i = 0; i < c.size(); ++i)
            cout << hex << setw(2) << setfill('0') << (unsigned int)c[i];
        cout << dec << endl;
    } else
        cout << message << endl;

    return 0;
}

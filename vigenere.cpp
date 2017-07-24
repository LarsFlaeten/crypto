#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

int main(int argc, char* argv[])
{
    if(argc < 3) {
        cout << "Usage: " << argv[0] << " key enc/dec [message]" << endl;
        return -1;
    }

    std::string key(argv[1]);
    for(int i = 0; i < key.size(); ++i)
    {
        if(key[i] < 'a' || key[i] > 'z')
        {
            cout << "Error; key space must be [a-z] " << endl;
            return -1;
        }
    }

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
        getline(cin, message);
    else
        message = argv[3];


    // Check message space:
    
   
    
    for(int i = 0; i < message.size(); ++i)
    {
        if(message[i] < 'a' || message[i] > 'z')
        {
            cout << "Error; message space must be [a-z] " << endl;
            return -1;
        }
    }

    std::string c;
    int keylen = key.size();
    //cout << "Using key: " << key << endl;
    //cout << "Message:   " << message << endl;
 
    if(encrypt)
    {
        for(int i = 0; i < message.size(); ++i)
        {
            c.push_back(mod(int(message[i] - 'a' + key[i%keylen] - 'a'),26) + 'a');
        }
    } else
    {
        for(int i = 0; i < message.size(); ++i)
        {
            c.push_back(mod(int(message[i] - 'a' - (key[i%keylen] - 'a')),26) + 'a');
        }
    } 

    //if(argc > 3 && (strcmp(argv[3],"--verbose") || strcmp(argv[3],"-v")))
    //{
    //   cout << "Cipher:    " << c << endl;
    //} else
        cout << c << endl;


    return 0;
}

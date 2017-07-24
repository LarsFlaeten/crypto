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
    if(argc < 2) {
        cout << "Usage: " << argv[0] << " key [message]" << endl;
        return -1;
    }

    int key = atoi(argv[1]);
    if(key < -25 || key > 25)
    {
        cout << "Error, key must be [0,25]" << endl;
        return -1;
    }

    // get message from cmdline or stdin:
    std::string message;  
    if(argc < 3)
        getline(cin, message);
    else
        message = argv[2];


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
    for(int i = 0; i < message.size(); ++i)
    {
        c.push_back(mod(int(message[i] - 'a' + key),26) + 'a');
    }
        



    if(argc > 3 && (strcmp(argv[3],"--verbose") || strcmp(argv[3],"-v")))
    {
        cout << "Using key: " << key << endl;
        cout << "Message:   " << message << endl;
        cout << "Cipher:    " << c << endl;
    } else
        cout << c << endl;


    return 0;
}

#include <iostream>
#include <vector>
#include <iomanip>

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;


// Tries to find the key lenght used on a vigenere hex ciphertext

int main(int argc, char* argv[])
{
    if(argc < 3) {
        cout << "Usage: " << argv[0] << " minkeysize maxkeysize [message]" << endl;
        return -1;
    }

    int minKeySize = atoi(argv[1]);
    int maxKeySize = atoi(argv[2]);
    if(minKeySize < 1 || maxKeySize <= minKeySize)
    {
        cout << "Error in key size specification, min must be > 1 and max must be > min" << endl;
        return -1;
    }

    // get message from cmdline or stdin:
    std::string message;  
    if(argc < 4)
        getline(cin, message);
    else
        message = argv[3];


    if(message.size() % 2 != 0 || message.size() < 2)
    {
        cout << "Error, message size must be a multiple of 2 and larger than 2" << endl;
        return -1;
    }

    cout << "Message size: " << message.size() << endl;

    int keySize;
    for(int i = minKeySize; i <= maxKeySize; i++)
    {
        keySize = i;

        char hexbyte[2];
        char *p;
        // Take the byte frequency of every Nth character, where N is the proposed key size:
        vector<double> frequencies(256,0.0);
        double sum = 0.0;
        for(int j = 0; j < message.size();)
        {
            hexbyte[0] = message[j];
            hexbyte[1] = message[j+1];
            uint32_t ul = strtoul(hexbyte, &p, 16);
            j += 2*keySize;

            if(ul < 0 || ul > 255)
            {
                cout << "Error, ciphertext should be bytes [0,255], caught " << ul;
                cout << " at char index " << j << ", " << j+1 << endl;
                return -1;
            }
            frequencies[ul] += 1.0;
            sum += 1.0;
        }

        
        // Compute Sum of qi²
        double sum_q_i_sqrd = 0.0;
        double q_i;
        for(int j = 0; j < 256; j++)
        {
            q_i = frequencies[j];
            q_i /= sum;
            sum_q_i_sqrd += q_i * q_i;
        }
        cout << "Key length: " << keySize << ", Sum q_i squared: " << sum_q_i_sqrd << endl; 

    }

    cout << "The correct key lenght should have a value in the proximity of 0.065, while ";
    cout << "non-correct key lenghts wil have values closer to " << 1.0 / 256.0 << endl;
    cout << "(Last value applies for infinite length texts, shorter text may have higher values)" << endl;
    cout << "Anyway, the largest value above is a good hint of the key length used" << endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

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



// Frequency of english letters a-z, from 
// https://en.wikipedia.org/wiki/Letter_frequency
double p_i[26] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
    0.00978, 0.0236, 0.0015, 0.01974, 0.00074};


// Tries to break the vigenere cipher when the key lenght is known
// Use Vigenere_key_lenght to try to establish key length used in a cipher text

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Usage: " << argv[0] << " keysizeguess [message]" << endl;
        return -1;
    }

    int keySize = atoi(argv[1]);
    if(keySize < 1)
    {
        cout << "Error in key size specification, must be > 1" << endl;
        return -1;
    }

    // get message from cmdline or stdin:
    std::string message;  
    if(argc < 3)
        cin >> message;
    else
        message = argv[2];


    if(message.size() % 2 != 0 || message.size() < 2)
    {
        cout << "Error, message size must be a multiple of 2 and larger than 2" << endl;
        return -1;
    }

    cout << "Message size: " << message.size() << endl;
    cout << "Key size to try: " << keySize << endl;

    std::vector<unsigned char> finalKey;


    for(int offset = 0; offset < keySize; offset++)
    {
        cout << "*** Offset " << offset << endl;
        double min_qipi_delta = 1.0;
        unsigned char qipi_index = 0;
        
        
        for(int i = 0; i <= 255; i++)
        {
            char hexbyte[2];
            char *p;
   
            unsigned char key = (unsigned char)i;

            std::vector<double> qi(256,0.0);
            double sum = 0.0;

            unsigned char minc = 255;
            unsigned char maxc = 0;
            for(int j = offset*2; j < message.size(); j += 2*keySize )
            {
                hexbyte[0] = message[j];
                hexbyte[1] = message[j+1];
                uint32_t ul = strtoul(hexbyte, &p, 16);
            

                if(ul < 0 || ul > 255)
                {
                    cout << "Error, ciphertext should be bytes [0,255], caught " << ul;
                    cout << " at char index " << j << ", " << j+1 << endl;
                    return -1;
                }
        
                unsigned char c = (unsigned char)ul;
           
                unsigned char m;
                m =  key ^ c;


                // Do tests on M with the current used key:
                if(m < minc) 
                    minc = m;
                if(m > maxc) 
                    maxc = m;

                qi[m] += 1.0;
                
                // Sum for a-z only
                if(m >= 97 && m <= 122)
                    sum += 1.0;
        
            }

            // Postprocess qi:
            // and multiply frequency with known frequencies of a-z
            double S_qipi = 0.0;
            double q = 0.0;
            // Only for 'a' thorugh 'z'
            // we must guard agains potential sum==0.0:
            if(sum>0.0)
            {
                
                for(unsigned int b = 97; b <= 122; b++)
                {
                    q = qi[b];
                    q = q/sum;
                    S_qipi += q*p_i[b-97];
                }
               
            } 


           
            if(minc >=32 && maxc <= 126)
            {
                cout << "Candidate key: " << hex << (int)key << dec << " min: ";
                cout << (int)minc << " max: " << (int)maxc << ", Sqipi: " << S_qipi;
                
                if(fabs(S_qipi-0.065) < min_qipi_delta)
                {
                    min_qipi_delta = fabs(S_qipi-0.065);
                    qipi_index = key;
                    cout << "R(" << S_qipi << ", d:" << fabs(S_qipi - 0.065);;
                }
                cout << endl;
            }
        }   
    
        // For this offset (key index), give the best candidate:
        cout << "Best Candidate for offset " << offset << " was key ";
        cout << hex << setw(2) << setfill('0') << (int)qipi_index << dec;
        cout << ", with QiPi=" << min_qipi_delta+0.065 << endl;

        finalKey.push_back(qipi_index);
    }
        
    cout << "Proposed key: " << endl;
    std::vector<unsigned char>::iterator it;
    cout << "0x" << hex << setw(2) << setfill('0');
    for(it = finalKey.begin(); it!=finalKey.end(); ++it)
        cout << (int)*it;
    cout << dec << endl;

    return 0;
}

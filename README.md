# Crypto

## Introduction
This repo contains various tools and apps from a cryptography course I have taken. Some further description and examples are given below.

## Building
All apps/tools should be built easily with CMake (in-tree build allowed)
```
$ cmake .
$ make
```

## Shift Cipher
The shift cipher, or Ceasar's Cipher, is one of the simplest and most widely known encryption techniques. It is a type of substitution cipher in which each letter in the plaintext is replaced by a letter some fixed number of positions down the alphabet. Use `shift_cipher` in the code repo to test it as shown below. `shift_cipher` shifts all letters by a fixed value (the key) with wrap around. Only accepts chracters a-z, and key 0-26. Accepts a message as argument or taken from `stdin`:
```
$ ./shift_cipher 1 helloworld
ifmmpxpsme    //all characters shifted by 1

$ echo "helloworld" | ./shift_cipher 1
ifmmpxpsme    //same as above

$ echo "helloworld" | ./shift_cipher 0
helloworld    //key=0 preserves the original "plaintext"
```
## Vigenere Cipher
The [Vigenere Cipher](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher) is implemented in its most basic form with `vigenere` (with key and message space {a-z}), and as a more generic HEX-variant in `vigenere_hex`. The Vigenère cipher consists of several Caesar ciphers in sequence with different shift values. The different shift values are taken successively from the "key", with wraparound if the key is shorter than the text. Example (from wikipedia):
- Plaintext:  ATTACKATDAWN
- Key:    LEMONLEMONLE
- Ciphertext: LXFOPVEFRNHR



Some examples below:

Basic Vigenere:
```
$ echo "attackatdawn" | ./vigenere lemon enc
lxfopvefrnhr    // The ciphertext of "attackatdawn" using the key "lemon"
$ echo "lxfopvefrnhr" | ./vigenere lemon dec
attackatdawn    // The recovered plaintext
```
HEX version of Vigenere, with a hex key from the ascii text "lemon":
```
$ ./ascii2hex lemon
6c656d6f6e    // Key in HEX
$ echo "attackatdawn" | ./vigenere_hex 6c656d6f6e  enc
0d11190e0d0704190b0f1b0b  // Ciphertext in HEX
$ echo "attackatdawn" | ./vigenere_hex `./ascii2hex lemon` enc
0d11190e0d0704190b0f1b0b  // Same ciphertext generated from a one-liner
$ echo "0d11190e0d0704190b0f1b0b" | ./vigenere_hex `./ascii2hex lemon` dec
attackatdawn   // plaintext recovered
```
With this Vigenere version, we can also use other characters than a-z:
```
$ echo "I see you!" | ./vigenere_hex `./ascii2hex spy` enc
3a500a1615590a1f0c52
$ echo "3a500a1615590a1f0c52" | ./vigenere_hex `./ascii2hex spy` dec
I see you!
```
## Breaking the Vigenere Cipher
Allthough considered for a long time to be very secure, the Vigenere Cipher can quite easily be broken. The method below relies on the key being considerably shorter than the plaintext.

A ciphertext is given in `ciphertext.txt`, which is encrypted with a random key with unkown lenght:
```
$ cat ciphertext.txt
F96DE8 ... [abbreviated] ... 4794
```
### Getting the key lenght
By taking into consideration that for a key lenght of N, the every Nth character will be shifted (XORed) with the same value. We can therefore examine frequencies of reccurring letters with varying N. When using N not the same as the key used, different characters will occur (almost) uniformly, while when using N equals the key length, we will see frequencies resembling that of normal letter frequencies in english text. If we sum the square of the frequencies, we tend to get a number equal to 0.065 when N is the same as the key lenght, while the sum is more equal to 1/256 when N is not equal to the key lenght used. The program `vigenere_key_length` uses this technique to try to establish the key lenght, here with a try in key lenghts form 1 to 10 bytes:
```
$ cat ciphertext.txt | vigenere_key_length 1 10
Message size: 940
Key length: 1, Sum q_i squared: 0.0135355
Key length: 2, Sum q_i squared: 0.0138524
Key length: 3, Sum q_i squared: 0.0191083
Key length: 4, Sum q_i squared: 0.0173801
Key length: 5, Sum q_i squared: 0.0244455
Key length: 6, Sum q_i squared: 0.0197084
Key length: 7, Sum q_i squared: 0.0860727
Key length: 8, Sum q_i squared: 0.0249928
Key length: 9, Sum q_i squared: 0.0295479
Key length: 10, Sum q_i squared: 0.0312359
The correct key lenght should have a value in the proximity of 0.065, whilenon-corrcet key lenghts wil have values closer to 0.00390625
(Last value applies for infinite length texts, shorter text may have higher values)
Anyway, the largest value above is a good hint of the key length used
```
From above, we see that the sum of q_i^2 is much higher for N=7, hence the key was probably 7 bytes long.

### Getting the individual bytes of the key
There are several techniques on how to do this, but knowing the key length, we can utilize frequency analysis (assuming we know the text is english) to try to guess the key. Letter frequencies for english text is used, as can be seen in `vigenere_break`, a program which tries to guess the key based on the key length from previous section.

```
$ cat ciphertext.txt | ./vigenere_break 7
Message size: 940
Key size to try: 7
*** Offset 0
Candidate key: a2 min: 52 max: 126, Sqipi: 0.022742 ............
.....[output truncated].....
Best Candidate for offset 6 was key 3e, with QiPi=0.0704661
Proposed key: 
0xba56c2b2539e3e
```
We can now try to decrypty the message with the proposed key:
```
$ cat ciphertext.txt | ./vigenere_hex ba56c2b2539e3e dec
C;*pt<gr(#hysisi'hespr(0ti0e (=d  tu-* o5 t,0hn:qu, [output truncated]
```
OK, so we are not there yet. One way of completing this is to look at the output of `viginere_break`, and for the different offsets try different key values that sums close to 0.065. Howevere antother approach can be used.

Looking at the text (and rememebering we have a recurring shift pattern of 7 characters due to the key length), it seems from the result that we are correct on at least the 1st, 4th, 5th and 7th characters. We can also start to guess some of the letters in the plaintext. I.e. if we guess that character 2 and 3 should be 'r' and 'y' in the plaintext (since it resembles somthing with "crypto"). We can get the key bytes for those positions by XORing(since m XOR c = k):
```
$ cat ciphertext.txt | cut -c3-4
6D
$ ./ascii2hex r
72
$ ./xor 6d 72
1f // We now know the second byte of the key should be 1f (This was also a good candicate for this offset in viginere_break
```
Similary with the third character which we believe is 'y'
```
$ cat ciphertext.txt | cut -c5-6
E8
$ ./ascii2hex y
79
$ ./xor
91
```
We can now try with our "improved" key, `0xba1f91b2539e3e`:
```
$ cat ciphertext | ./vigenere_hex ba1f91b2539e3e dec
Crypt<graphysis thespracti0e and  tudy o5 techn:ques f<r, amo=g othe! thing .....
```
OK, almost there. Key bits for the sixt offset can now easily be retrieved by e.g. looking at chaacter position 6 which we think is an 'o':
```
$ ./xor `cat ciphertext | cut -c11-12` `./ascii2hex o`
cd
```
Voila, the 6th byte is 0xCD, and we have recovered the complete key used to generated the ciphertext as 0xBA1F91B253CD3E.

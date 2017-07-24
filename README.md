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
The [Vigenere Cipher](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher) is implemented in its most basic form with `vigenere` (with key and message space {a-z}), and as a more generic HEX-variant in `vigenere_hex`. The Vigenère cipher consists of several Caesar ciphers in sequence with different shift values. The different shift values are taken successively from the "key". Example (from wikipedia):
Plaintext:  ATTACKATDAWN
Key:    LEMONLEMONLE
Ciphertext: LXFOPVEFRNHR



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


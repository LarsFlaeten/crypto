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
The [Vigenere Cipher](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher) is implemented in its most basic form with `vigenere` (with key and message space {a-z}), and as a more generic HEX-variant in `vigenere_hex`. Some examples below:
```
$ echo "attackatdawn" | ./vigenere lemon enc
lxfopvefrnhr    // The ciphertext of "attackatdawn" using the key "lemon"
$ echo "lxfopvefrnhr" | ./vigenere lemon dec
attackatdawn    // The recovered plaintext

```

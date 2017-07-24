# Crypto

## Introduction
This repo contains various tools and apps fro a cryptography course I have taken. Some further description and examples are given below.

## Shift Cipher
The simplest cryptographic construct, use `shift_cipher` to test it. `shift_cipher` shifts all letters by a fixed value (the key), with wrap around. Only accepts chracters a-z, and key 0-26. Accepts a message as argument or taken from `stdin`:
```
$ ./shift_cipher 1 helloworld
ifmmpxpsme    //all characters shifted by 1

$ echo "helloworld" | ./shift_cipher 1
ifmmpxpsme    //same as above

$ echo "helloworld" | ./shift_cipher 0
helloworld    //key=0 preserves the original "plaintext"
```


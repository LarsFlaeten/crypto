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
`$ cat ciphertext.txt
F96DE8C227A259C87EE1DA2AED57C93FE5DA36ED4EC87EF2C63AAE5B9A7EFFD673BE4ACF7BE8923CAB1ECE7AF2DA3DA44FCF7AE29235A24C963FF0DF3CA3599A70E5DA36BF1ECE77F8DC34BE129A6CF4D126BF5B9A7CFEDF3EB850D37CF0C63AA2509A76FF9227A55B9A6FE3D720A850D97AB1DD35ED5FCE6BF0D138A84CC931B1F121B44ECE70F6C032BD56C33FF9D320ED5CDF7AFF9226BE5BDE3FF7DD21ED56CF71F5C036A94D963FF8D473A351CE3FE5DA3CB84DDB71F5C17FED51DC3FE8D732BF4D963FF3C727ED4AC87EF5DB27A451D47EFD9230BF47CA6BFEC12ABE4ADF72E29224A84CDF3FF5D720A459D47AF59232A35A9A7AE7D33FB85FCE7AF5923AA31EDB3FF7D33ABF52C33FF0D673A551D93FFCD33DA35BC831B1F43CBF1EDF67F0DF23A15B963FE5DA36ED68D378F4DC36BF5B9A7AFFD121B44ECE76FEDC73BE5DD27AFCD773BA5FC93FE5DA3CB859D26BB1C63CED5CDF3FE2D730B84CDF3FF7DD21ED5ADF7CF0D636BE1EDB79E5D721ED57CE3FE6D320ED57D469F4DC27A85A963FF3C727ED49DF3FFFDD24ED55D470E69E73AC50DE3FE5DA3ABE1EDF67F4C030A44DDF3FF5D73EA250C96BE3D327A84D963FE5DA32B91ED36BB1D132A31ED87AB1D021A255DF71B1C436BF479A7AF0C13AA14794
`

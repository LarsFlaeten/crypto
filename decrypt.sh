#!/bin/bash
for (( i = 0; i > -26; i--))
do
    echo `./shift_cipher $i $1` key $i 
done

#!/usr/bin/python
from oracle import *
import sys

def strxor(a, b):     # xor two strings of same length
    return "".join([chr(ord(x)^ord(y)) for (x, y) in zip(a, b)])


data = "I, the server, hereby agree that I will pay $100 to this student"

Oracle_Connect()
# Create "normal" tag for 32 byte message data[0:32]:
tag1 = Mac(data[0:32],32)
# data[0:32] is m1 + m2
print "Tag for first part is ", str(tag1).encode("hex")

#  L       m1      m2          m3       m4
#  |       |       |           |        |
#  |   ---XOR  ---XOR      ---XOR  ----XOR
#  |   |   |   |   |       |   |   |    |
# [Fk] |  [FK] |  [Fk]     |  [Fk] |   [Fk]
#  |___|   |___|   |----->tag1 |----    |---->TAG

# we now know tag1 and m3, and can compute Fk_inp for third stage
m3 = data[32:48]
Fk_inp = strxor(str(tag1), m3)
TAG = Mac(Fk_inp + data[48:64], 32)
print "Final tag is ", str(TAG).encode("hex")

ret = Vrfy(data, 64, TAG)

if (ret==1):
    print "Message verified successfully!"
else:
    print "Message verification failed."

Oracle_Disconnect()

from oracle import *
import sys

L = 16  #block length

def xor(a, b):     # xor two arrays of same lengths
    return [x^y for (x, y) in zip(a, b)]

def usage():
    print "Usage: python dec.py <filename>"
    sys.exit(-1)

def decrypt(ctext):
    num_blocks = len(ctext)/L
    print "[*] Num blocks: %d" % num_blocks
    mn = []
    mn = decrypt_last(ctext, num_blocks)
    m1 = decrypt_remaining_blocks(ctext, num_blocks)
    message = m1 + mn
    #print m1
    a = ['']
    for i in range(0,len(message)):
        a += chr(message[i])
    print "Encrypted message was:"
    print "\"",
    print ''.join(a),
    print "\""

def decrypt_last(ctext, num_blocks):
    print "[*] Decrypting last block (no %d)" % num_blocks
    # Start from next last block (IV for last block):
    blocks = [ctext[i*16:(i+1)*16] for i in range(0, num_blocks)]
    IV = blocks[num_blocks-2]

    pad = 0xff
    for i in range(L):
        IV[i] += 1;
        data = []
        for j in range (0,num_blocks-2):
            data += blocks[j]
        data += IV + blocks[num_blocks-1]
        #print data
        ret = Oracle_Send(data,num_blocks)
        IV[i] -= 1;
        if not ret:
            pad = L-i
            print "[+] Padding is %d" % pad
            break

    # We now know IV has pad number of paddings from the end
    # Ensure pad is less than L
    if pad >= L:
        print "Error, pad %d expected to be less than L=%d" % (pad, L)
        sys.exit(-1)

    m = [None] * L;
    # print m
    for i in range(L-pad,L):
        m[i] = pad
    #print "m: ",m

    # Reset IV:
    IV = blocks[num_blocks-2]

    # Calc Finv:
    Finv = [None] * L
    #a = m[L-pad:L]
    #b = IV[L-pad:L]
    #print "a ", a
    #print "b ", b
    Finv[L-pad:L] = xor(m[L-pad:L], IV[L-pad:L])
    #print "Finv: ",Finv
    for i in range(L-pad-1,-1, -1):
        newpad = L-i
        #print newpad
        # Fill IV with new encoded pads:
        pdvec = [newpad]*(newpad-1)
        Finvvec = Finv[L-newpad+1:L]
        #print pdvec
        #print Finv[L-newpad+1:L]
        IV[L-newpad+1:16] = xor ([newpad]*(newpad-1),Finv[L-newpad+1:L])
        oldIV = IV[L-newpad]
        IV[L-newpad] = 0; # the value to calculate
        #print IV
        for j in range(256):
            IV[L-newpad] = j;
            data = []
            for k in range (0,num_blocks-2):
                data += blocks[k]
            data += IV + blocks[num_blocks-1]
            #print data
            ret = Oracle_Send(data,3)
            #print j, ret
            if ret == 1:
                #print "IV = %d gave correct return" % j
                break
        # assign newfound value to FINV:
        F = j^newpad
        Finv[L-newpad] = F
        #print "New Finv[]", Finv
        m[L-newpad] = F^oldIV
        #print "m[L-newpad] is ", m[L-newpad]
        #print m
        for l in range(0,L-pad):
            if m[l] == None:
                print "X",
            else:
                print chr(m[l]),
        print
    # end for
    return m[0:L-pad]

def decrypt_remaining_blocks(ctext, num_blocks):
    # Now do remaining blocks num_blocks-2
    # The oracle expects tha last block to be padded
    # So we iterate until we find IV that equals pad 01 in last position, etc
    # I.e same method as the last block
    message = []
    for i in range(num_blocks-2,0,-1):
        print "[*] Decoding block %d with IV in block %d" % (i+1, i)
        for l in range(0,L):
            print "X",
        print


        blocks = [ctext[i*16:(i+1)*16] for i in range(0, num_blocks-1)]
        IV = blocks[i-1]
        c = blocks[i]
        Finv = [None]*L
        m = [None]*L
        for j in range(L-1,-1,-1):
            F = None
            pad = L-j
            #print "Pad: %d, j=%d " % (pad,j)
            #print "Set IVs after %d to equal new pad %d" %(j,pad)
            IV[L-pad+1:16] = xor ([pad]*(pad-1),Finv[L-pad+1:L])
            #print IV

            # Set IV[j] to 00 and iterate:
            oldIV = IV[j]
            IV[j]= 0
            #print "Iterating with new IV:"
            #print IV
            for k in range(256):
                IV[j] = k
                data = IV + c
                ret = Oracle_Send(data,i+1)
                if ret==1:
                    #print "pad %d, j=%d, k=%d, ret=%d" %(pad, j, k, ret)
                    F = pad^k # Get value for Finv(c)
                    Finv[j] = F
                    m[j] = F^oldIV
                    IV[j] = oldIV
                    break
            #print "Found char %d, was value %d" % (j,m[j])
            for l in range(0,L):
                if m[l] == None:
                    print "X",
                else:
                    print chr(m[l]),
            print

        message = m +  message

    return message


if __name__ == "__main__":
    if len(sys.argv) < 2:
        usage()

    f = open(sys.argv[1])
    data = f.read()
    f.close()

    Oracle_Connect()

    #decrypt([ord(c) for c in data.decode('hex')])
    decrypt([(int(data[i:i+2],16)) for i in range(0, len(data),2)])
    Oracle_Disconnect()

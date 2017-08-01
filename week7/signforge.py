from helper import *
from oracle import *

# In an attempt to avoid the attacks on the "plain RSA" signature scheme, J. Random Hacker has designed her own RSA-based signature scheme. The scheme works as follows: the public key is a standard RSA public key (N, e), and the private key is the usual (N, d), where N is a 128-byte (1024-bit) integer. To sign a message m of length exactly 63 bytes, set

# M = 0x00 m 0x00 m

# (note that M is exactly 128 bytes long) and then compute the signature M^d mod N. (If m is shorter than 63 bytes, 0-bytes are first preprended to make its length exactly 63 bytes.

# J. Random Hacker is so sure this scheme is secure, she is offering a bounty of 1 point to anyone who can forge a signature on the 63-byte message

msg = "Crypto is hard --- even schemes that look complex can be broken"

# with respect to the public key
n = 119077393994976313358209514872004186781083638474007212865571534799455802984783764695504518716476645854434703350542987348935664430222174597252144205891641172082602942313168180100366024600206994820541840725743590501646516068078269875871068596540116450747659687492528762004294694507524718065820838211568885027869
e = 65537


m = ascii_to_int(msg)

# Solution:
# M = 0x00 m 0x00 m (128 bytes)
# i.e, M = m * (2^(8*64) + 1)

# We are not allowed to do sigma = Sign(m)
# So we can construct some other m1*m2 = m,
# and we can check Sign(m1) and Sign(m2). Eg:
m1 = 2
m2 = m/2

# Now M = m1*m2*(2^(8*64) + 1)
s1 = Sign(m1) # = [(m1(2^512+1))^d mod n]
s2 = Sign(m2) # = [(m2(2^512+1))^d mod n]
s0 = Sign(1)  # = [(2^512 + 1)^d mod n]

# We want (m*A)^d mod n, A = (2^512 + 1)
# (m*A)^2 mod n = m1^d * m2^d * A^d
# = m1^d * A^d * m2^d * A^d * A^-d mod n
# = s1 * s2 * s0^-1 mod n
sigma = (s1 * s2 * modinv(s0,n)) % n


if Verify(m, sigma):
    print "Forged correct signature on m"
else:
    print "Incorrect Signature"

Oracle_Disconnect()

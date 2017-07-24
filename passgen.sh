#!/bin/sh
# Make a 48-bit password (8 characters, 6 bits per char)
dd if=/dev/urandom count=1 2>/dev/null | base64 | head -1 | cut -c4-11 

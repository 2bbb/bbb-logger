#!/bin/bash

for source in simple customize;
do
    echo build start: example/$source
    g++ $1 -I./include -std=c++11 -stdlib=libc++ -o example/$source example/$source.cpp && echo build complete: example/$source || echo build failed: example/$source
done

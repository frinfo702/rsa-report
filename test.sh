#!/bin/bash

g++ -std=c++17 main.cpp -o a.out

assert() {
    input="$1"
    expected="$2"

    actual=$(./a.out "$input")

    if [ "$actual" = "$expected" ]; then
        echo "$input => $actual"
    else
        echo "$input => $expected expected, but got $actual"
        exit 1
    fi
}

assert 26002301791 "23
33"

echo OK

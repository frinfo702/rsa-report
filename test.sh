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

assert 60 60
assert 2 2
assert 30 30
assert 17 17
assert 91 91

echo OK

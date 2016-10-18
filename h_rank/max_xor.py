#!/usr/bin/python



v = input()^input()
v |= v >> 1
v |= v >> 2
v |= v >> 4
v |= v >> 8
v |= v >> 16
print v

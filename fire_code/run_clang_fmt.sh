#!/bin/bash

find . -name "*.java" | xargs grep clang-format -i 

#!/bin/bash

printf "File to test: $1\n"
printf "==================================================\n"
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         $1 
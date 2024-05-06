#!/bin/bash

rm -rf valgrind-out.txt
>> valgrind-out.txt

# ------------------------------------------------------------------------------
echo -e "\033[0;92m"
echo -e "test: 1"

echo -e "\033[0;31m"
echo -e "valgrind"
echo -e "\nTEST: 1\n--------------------------------------------------------------------------------\n" >> valgrind-out.txt
valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=9 9>>valgrind-out.txt ./pipex Makefile cat 'grep CC' outfile

echo -e "\033[0;93m"
echo -e "< Makefile cat | grep CC > outfile"
< Makefile cat | grep CC > outfile
echo -e "\033[0;35m"exit code - $?

echo -en "\033[0;93m"
echo -e "./pipex Makefile cat 'grep CC' outfile"
./pipex Makefile cat 'grep CC' outfile
echo -e "\033[0;35m"exit code - $?
sleep 0.1

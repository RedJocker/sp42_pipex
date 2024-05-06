#!/bin/bash

rm -rf valgrind-out.txt
>> valgrind-out.txt

# ------------------------------------------------------------------------------
echo -e "\033[0;92m"
echo -e "test: 1"

echo -e "\033[0;31m"
echo -e "valgrind"
echo -e "\nTEST: 1\n--------------------------------------------------------------------------------\n" >> valgrind-out.txt
valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=9 9>>valgrind-out.txt ./pipex Makefile /src/ 'grep CC' outfile

echo -e "\033[0;93m"
echo -e "< Makefile /src/ | grep CC > outfile"
< Makefile /src/ | grep CC > outfile
echo -e "\033[0;35m"exit code - $?

echo -en "\033[0;93m"
echo -e "./pipex Makefile /src/ 'grep CC' outfile"
./pipex Makefile /src/ 'grep CC' outfile
echo -e "\033[0;35m"exit code - $?
sleep 0.1

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

echo -e "\033[0;92m"
echo -e "test: 2"

echo -e "\033[0;31m"
echo -e "valgrind"
echo -e "\nTEST: 2\n--------------------------------------------------------------------------------\n" >> valgrind-out.txt
valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=9 9>>valgrind-out.txt ./pipex Makefile ./src/ 'grep CC' outfile

echo -e "\033[0;93m"
echo -e "< Makefile ./src/ | grep CC > outfile"
< Makefile ./src/ | grep CC > outfile
echo -e "\033[0;35m"exit code - $?

echo -en "\033[0;93m"
echo -e "./pipex Makefile ./src/ 'grep CC' outfile"
./pipex Makefile ./src/ 'grep CC' outfile
echo -e "\033[0;35m"exit code - $?
sleep 0.1

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

echo -e "\033[0;92m"
echo -e "test: 3"

echo -e "\033[0;31m"
echo -e "valgrind"
echo -e "\nTEST: 3\n--------------------------------------------------------------------------------\n" >> valgrind-out.txt
valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=9 9>>valgrind-out.txt ./pipex Makefile src/ 'grep CC' outfile
echo -e "\033[0;93m"

echo -e "< Makefile src/ | grep CC > outfile"
< Makefile src/ | grep CC > outfile
echo -e "\033[0;35m"exit code - $?

echo -en "\033[0;93m"
echo -e "./pipex Makefile src/ 'grep CC' outfile"
./pipex Makefile src/ 'grep CC' outfile
echo -e "\033[0;35m"exit code - $?
sleep 0.1

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

echo -e "\033[0;92m"
echo -e "test: 4"

echo -e "\033[0;31m"
echo -e "valgrind"
echo -e "\nTEST: 4\n--------------------------------------------------------------------------------\n" >> valgrind-out.txt
valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=9 9>>valgrind-out.txt ./pipex Makefile 'grep CC' /src/ outfile
echo -e "\033[0;93m"

echo -e "< Makefile grep CC | /src/ > outfile"
< Makefile grep CC | /src/ > outfile
echo -e "\033[0;35m"exit code - $?

echo -en "\033[0;93m"
echo -e "./pipex Makefile 'grep CC' /src/ outfile"
./pipex Makefile 'grep CC' /src/ outfile
echo -e "\033[0;35m"exit code - $?
sleep 0.1

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

echo -e "\033[0;92m"
echo -e "test: 5"

echo -e "\033[0;31m"
echo -e "valgrind"
echo -e "\nTEST: 5\n--------------------------------------------------------------------------------\n" >> valgrind-out.txt
valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=9 9>>valgrind-out.txt ./pipex Makefile 'grep CC' ./src/ outfile
echo -e "\033[0;93m"

echo -e "< Makefile grep CC | ./src/ > outfile"
< Makefile grep CC | ./src/ > outfile
echo -e "\033[0;35m"exit code - $?

echo -en "\033[0;93m"
echo -e "./pipex Makefile 'grep CC' ./src/ outfile"
./pipex Makefile 'grep CC' ./src/ outfile
echo -e "\033[0;35m"exit code - $?
sleep 0.1

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

echo -e "\033[0;92m"
echo -e "test: 6"

echo -e "\033[0;31m"
echo -e "valgrind"
echo -e "\nTEST: 6\n--------------------------------------------------------------------------------\n" >> valgrind-out.txt
valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=9 9>>valgrind-out.txt ./pipex Makefile 'grep CC' src/ outfile

echo -e "\033[0;93m"
echo -e "< Makefile grep CC | src/ > outfile"
< Makefile grep CC | src/ > outfile
echo -e "\033[0;35m"exit code - $?

echo -en "\033[0;93m"
echo -e "./pipex Makefile 'grep CC' src/ outfile"
./pipex Makefile 'grep CC' src/ outfile
echo -e "\033[0;35m"exit code - $?
sleep 0.1

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

echo -e "\033[0;92m"
echo -e "test: 7"

echo -e "\033[0;31m"
echo -e "valgrind"
echo -e "\nTEST: 7\n--------------------------------------------------------------------------------\n" >> valgrind-out.txt
valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=9 9>>valgrind-out.txt ./pipex /src/ cat 'grep CC' outfile

echo -e "\033[0;93m"
echo -e "< /src/ cat | grep CC > outfile"
< /src/ cat | grep CC > outfile
echo -e "\033[0;35m"exit code - $?

echo -en "\033[0;93m"
echo -e "./pipex /src/ cat 'grep CC' outfile"
./pipex /src/ cat 'grep CC' outfile
echo -e "\033[0;35m"exit code - $?
sleep 0.1

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

echo -e "\033[0;92m"
echo -e "test: 8"

echo -e "\033[0;31m"
echo -e "valgrind"
echo -e "\nTEST: 8\n--------------------------------------------------------------------------------\n" >> valgrind-out.txt
valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=9 9>>valgrind-out.txt ./pipex ./src/ cat 'grep CC' outfile

echo -e "\033[0;93m"
echo -e "< ./src/ cat | grep CC > outfile"
< ./src/ cat | grep CC > outfile
echo -e "\033[0;35m"exit code - $?

echo -en "\033[0;93m"
echo -e "./pipex ./src/ cat 'grep CC' outfile"
./pipex ./src/ cat 'grep CC' outfile
echo -e "\033[0;35m"exit code - $?
sleep 0.1

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

echo -e "\033[0;92m"
echo -e "test: 9"

echo -e "\033[0;31m"
echo -e "valgrind"
echo -e "\nTEST: 9\n--------------------------------------------------------------------------------\n" >> valgrind-out.txt
valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=9 9>>valgrind-out.txt ./pipex src/ cat 'grep CC' outfile

echo -e "\033[0;93m"
echo -e "< src/ cat | grep CC > outfile"
< src/ cat | grep CC > outfile
echo -e "\033[0;35m"exit code - $?

echo -en "\033[0;93m"
echo -e "./pipex src/ cat 'grep CC' outfile"
./pipex src/ cat 'grep CC' outfile
echo -e "\033[0;35m"exit code - $?
sleep 0.1

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

echo -e "\033[0;92m"
echo -e "test: 10"

echo -e "\033[0;31m"
echo -e "valgrind"
echo -e "\nTEST: 10\n--------------------------------------------------------------------------------\n" >> valgrind-out.txt
valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=9 9>>valgrind-out.txt ./pipex Makefile cat 'grep CC' /src/

echo -e "\033[0;93m"
echo -e "< Makefile cat | grep CC > /src/"
< Makefile cat | grep CC > /src/
echo -e "\033[0;35m"exit code - $?

echo -en "\033[0;93m"
echo -e "./pipex Makefile cat 'grep CC' /src/"
./pipex Makefile cat 'grep CC' /src/
echo -e "\033[0;35m"exit code - $?
sleep 0.1

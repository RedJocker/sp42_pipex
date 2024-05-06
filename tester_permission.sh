#!/bin/bash

rm -rf valgrind-out.txt
>> valgrind-out.txt

# ------------------------------------------------------------------------------
echo -e "\033[0;92m"
echo -e "test: 1"

echo -e "\033[0;31m"
echo -e "valgrind"
echo -e "\nTEST: 1\n--------------------------------------------------------------------------------\n" >> valgrind-out.txt
valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=9 9>>valgrind-out.txt ./pipex /osquery.flags cat 'grep CC' outfile

echo -e "\033[0;93m"
echo -e "< /osquery.flags cat | grep CC > outfile"
< /osquery.flags cat | grep CC > outfile
echo -e "\033[0;35m"exit code - $?

echo -en "\033[0;93m"
echo -e "./pipex /osquery.flags cat 'grep CC' outfile"
./pipex /osquery.flags cat 'grep CC' outfile
echo -e "\033[0;35m"exit code - $?
sleep 0.1

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

echo -e "\033[0;92m"
echo -e "test: 2"

echo -e "\033[0;31m"
echo -e "valgrind"
echo -e "\nTEST: 2\n--------------------------------------------------------------------------------\n" >> valgrind-out.txt
valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=9 9>>valgrind-out.txt ./pipex Makefile /osquery.flags 'grep CC' outfile

echo -e "\033[0;93m"
echo -e "< Makefile /osquery.flags | grep CC > outfile"
< Makefile /osquery.flags | grep CC > outfile
echo -e "\033[0;35m"exit code - $?

echo -en "\033[0;93m"
echo -e "./pipex Makefile /osquery.flags 'grep CC' outfile"
./pipex Makefile /osquery.flags 'grep CC' outfile
echo -e "\033[0;35m"exit code - $?
sleep 0.1

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

echo -e "\033[0;92m"
echo -e "test: 3"

echo -e "\033[0;31m"
echo -e "valgrind"
echo -e "\nTEST: 3\n--------------------------------------------------------------------------------\n" >> valgrind-out.txt
valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=9 9>>valgrind-out.txt ./pipex Makefile cat /osquery.flags outfile

echo -e "\033[0;93m"
echo -e "< Makefile cat | /osquery.flags > outfile"
< Makefile cat | /osquery.flags > outfile
echo -e "\033[0;35m"exit code - $?

echo -en "\033[0;93m"
echo -e "./pipex Makefile cat '/osquery.flags' outfile"
./pipex Makefile cat '/osquery.flags' outfile
echo -e "\033[0;35m"exit code - $?
sleep 0.1

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

echo -e "\033[0;92m"
echo -e "test: 4"

echo -e "\033[0;31m"
echo -e "valgrind"
echo -e "\nTEST: 4\n--------------------------------------------------------------------------------\n" >> valgrind-out.txt
valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=9 9>>valgrind-out.txt ./pipex Makefile cat 'grep CC' /osquery.flags

echo -e "\033[0;93m"
echo -e "< Makefile cat | grep CC > /osquery.flags"
< Makefile cat | grep CC > /osquery.flags
echo -e "\033[0;35m"exit code - $?

echo -en "\033[0;93m"
echo -e "./pipex Makefile cat 'grep CC' /osquery.flags"
./pipex Makefile cat 'grep CC' /osquery.flags
echo -e "\033[0;35m"exit code - $?
sleep 0.1

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

echo -e "\033[0;92m"
echo -e "test: 5"

echo -e "\033[0;31m"
echo -e "valgrind"
echo -e "\nTEST: 5\n--------------------------------------------------------------------------------\n" >> valgrind-out.txt
valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=9 9>>valgrind-out.txt ./pipex Makefile cat /osquery.flags /osquery.flags

echo -e "\033[0;93m"
echo -e "< Makefile cat | /osquery.flags > /osquery.flags"
< Makefile cat | /osquery.flags > /osquery.flags
echo -e "\033[0;35m"exit code - $?

echo -en "\033[0;93m"
echo -e "./pipex Makefile cat '/osquery.flags' /osquery.flags"
./pipex Makefile cat '/osquery.flags' /osquery.flags
echo -e "\033[0;35m"exit code - $?
sleep 0.1

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

echo -e "\033[0;92m"
echo -e "test: 6"

echo -e "\033[0;31m"
echo -e "valgrind"
echo -e "\nTEST: 6\n--------------------------------------------------------------------------------\n" >> valgrind-out.txt
valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=9 9>>valgrind-out.txt ./pipex Makefile /osquery.flags /osquery.flags /osquery.flags

echo -e "\033[0;93m"
echo -e "< Makefile /osquery.flags | /osquery.flags > /osquery.flags"
< Makefile /osquery.flags | /osquery.flags > /osquery.flags
echo -e "\033[0;35m"exit code - $?

echo -en "\033[0;93m"
echo -e "./pipex Makefile /osquery.flags '/osquery.flags' /osquery.flags"
./pipex Makefile /osquery.flags '/osquery.flags' /osquery.flags
echo -e "\033[0;35m"exit code - $?
sleep 0.1

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------

echo -e "\033[0;92m"
echo -e "test: 7"

echo -e "\033[0;31m"
echo -e "valgrind"
echo -e "\nTEST: 7\n--------------------------------------------------------------------------------\n" >> valgrind-out.txt
valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=9 9>>valgrind-out.txt ./pipex /osquery.flags /osquery.flags /osquery.flags /osquery.flags

echo -e "\033[0;93m"
echo -e "< /osquery.flags /osquery.flags | /osquery.flags > /osquery.flags"
< /osquery.flags /osquery.flags | /osquery.flags > /osquery.flags
echo -e "\033[0;35m"exit code - $?

echo -en "\033[0;93m"
echo -e "./pipex /osquery.flags /osquery.flags '/osquery.flags' /osquery.flags"
./pipex /osquery.flags /osquery.flags '/osquery.flags' /osquery.flags
echo -e "\033[0;35m"exit code - $?
sleep 0.1

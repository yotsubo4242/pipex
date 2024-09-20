#!/bin/sh

ESC=$(printf '\033')
#printf "${ESC}[31m%s${ESC}[m\n" 'RED'
#printf "\033[32m%s\033[m\n" 'GREEN'
#printf "\033[36m%s\033[m" 'CYAN'

printf "\033[32m%s\033[m\n" '~ Normal Test ~'
touch infile
touch outfile
echo "yeah\nthis\nis\nme." > infile
echo "" > outfile
echo "[infile]"
cat infile
echo "[outfile]"
cat outfile

# test 1
printf "\033[36m%s\033[m\n" '1. < infile cat | grep i > outfile'
echo "# bash #"
< infile cat | grep i > outfile
cat outfile
echo ""
echo "" > outfile
echo "# pipex #"
./pipex infile cat "grep i" outfile
cat outfile

echo ""

# test2
printf "\033[36m%s\033[m\n" '2. < infile ls | cat > outfile'
echo "# bash #"
< infile ls | cat > outfile
cat outfile
echo ""
echo "" > outfile
echo "# pipex #"
./pipex infile ls cat outfile
cat outfile
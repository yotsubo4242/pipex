#!/bin/sh

ESC=$(printf '\033')
#printf "${ESC}[31m%s${ESC}[m\n" 'RED'
#printf "\033[32m%s\033[m\n" 'GREEN'
#printf "\033[36m%s\033[m\n" 'CYAN'
#printf "\033[33m%s\033[m\n" 'YELLOW'

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
printf "\033[33m%s\033[m\n" '# bash #'
< infile cat | grep i > outfile
cat outfile
echo ""
echo "" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile cat "grep i" outfile
cat outfile

echo ""
echo ""

# test2
printf "\033[36m%s\033[m\n" '2. < infile ls | cat > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile ls | cat > outfile
cat outfile
echo ""
echo "" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile ls cat outfile
cat outfile

echo ""
echo ""



# Bad Commands
printf "\033[32m%s\033[m\n" '~ Bad Commands Test ~'

# test3 (second command's flag is invalid)
printf "\033[36m%s\033[m\n" '3. < infile ls | cat -wrongflag > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile ls | cat -wrongflag > outfile
cat outfile
echo ""
echo "" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile ls "cat -wrongflag" outfile
cat outfile

echo ""
echo ""

# test4 (first command's flag is invalid)
printf "\033[36m%s\033[m\n" '4. < infile ls -wrongflag | cat > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile ls -wrongflag | cat > outfile
cat outfile
echo ""
echo "" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile "ls -wrongflag" cat outfile
cat outfile

echo ""
echo ""

# test5 (both of two commands's flags are invalid)
printf "\033[36m%s\033[m\n" '5. < infile ls -wrongflag | cat -wrongflag > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile ls -wrongflag | cat -wrongflag > outfile
cat outfile
echo ""
echo "" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile "ls -wrongflag" "cat -wrongflag" outfile
cat outfile

echo ""
echo ""

# test6 (second command is invalid)
printf "\033[36m%s\033[m\n" '6. < infile cat | fake_command > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile cat | fake_command > outfile
cat outfile
echo ""
echo "" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile cat fake_command outfile
cat outfile

echo ""
echo ""

# test7 (first command is invaild)
printf "\033[36m%s\033[m\n" '7. < infile fake_command | ls > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile fake_command | ls > outfile
cat outfile
echo ""
echo "" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile fake_command ls outfile
cat outfile

echo ""
echo ""

# test8 (both of two commands are invalid)
printf "\033[36m%s\033[m\n" '8. < infile fake_command | fake_command > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile fake_command | fake_command > outfile
cat outfile
echo ""
echo "" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile fake_command fake_command outfile
cat outfile

echo ""
echo ""
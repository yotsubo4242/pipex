#!/usr/bin/bash

ESC=$(printf '\033')
#printf "${ESC}[31m%s${ESC}[m\n" 'RED'
#printf "\033[32m%s\033[m\n" 'GREEN'
#printf "\033[36m%s\033[m\n" 'CYAN'
#printf "\033[33m%s\033[m\n" 'YELLOW'

printf "\033[32m%s\033[m\n" '~ Normal Test ~'
touch infile
touch outfile
echo "yeah\nthis\nis\nme." > infile
echo "this\nshoud\nbe\noverrided" > outfile
echo "[infile]"
cat infile
echo "[outfile]"
cat outfile

# test 1
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '1. < infile cat | grep i > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile cat | grep i > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile cat "grep i" outfile
cat outfile

echo ""
echo ""

# test2
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '2. < infile ls | cat > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile ls | cat > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile ls cat outfile
cat outfile

echo ""
echo ""





# Bad Commands
printf "\033[32m%s\033[m\n" '~ Bad Commands Test ~'

# test3 (second command's flag is invalid)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '3. < infile ls | cat -wrongflag > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile ls | cat -wrongflag > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile ls "cat -wrongflag" outfile
cat outfile

echo ""
echo ""

# test4 (first command's flag is invalid)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '4. < infile ls -wrongflag | cat > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile ls -wrongflag | cat > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile "ls -wrongflag" cat outfile
cat outfile

echo ""
echo ""

# test5 (both commands's flags are invalid)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '5. < infile ls -wrongflag | cat -wrongflag > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile ls -wrongflag | cat -wrongflag > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile "ls -wrongflag" "cat -wrongflag" outfile
cat outfile

echo ""
echo ""

# test6 (second command is invalid)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '6. < infile cat | fake_command > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile cat | fake_command > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile cat fake_command outfile
cat outfile

echo ""
echo ""

# test7 (first command is invaild)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '7. < infile fake_command | ls > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile fake_command | ls > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile fake_command ls outfile
cat outfile

echo ""
echo ""

# test8 (both commands are invalid)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '8. < infile fake_command | fake_command > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile fake_command | fake_command > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile fake_command fake_command outfile
cat outfile

echo ""
echo ""




# command path test
printf "\033[32m%s\033[m\n" '~ Command Path Test ~'

# test9 (first command is absolute path)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '9. < infile /bin/ls | cat > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile /bin/ls | cat > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile /bin/ls cat outfile
cat outfile

echo ""
echo ""

# test10 (second command is absolute path)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '10. < infile ls | /usr/bin/cat > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile ls | /usr/bin/cat > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile ls /usr/bin/cat outfile
cat outfile

echo ""
echo ""

# test11 (both commands are absolute path)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '11. < infile /usr/bin/ls | /usr/bin/cat > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile /usr/bin/ls | /usr/bin/cat > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile /usr/bin/ls /usr/bin/cat outfile
cat outfile

echo ""
echo ""



# make test executabel file
cc tmp.c

# test12 (first command is relative path)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '12. < infile ./a.out | /usr/bin/cat > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile ./a.out | /usr/bin/cat > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile ./a.out /usr/bin/cat outfile
cat outfile

echo ""
echo ""

# test13 (second command is relative path)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '13. < infile ./a.out | /usr/bin/cat > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile ./a.out | /usr/bin/cat > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile /usr/bin/ls ./a.out outfile
cat outfile

echo ""
echo ""

# test14 (both commands are relative path)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '14. < infile ./a.out | ./a.out > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile ./a.out | ./a.out > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile ./a.out ./a.out outfile
cat outfile

echo ""
echo ""

# test15 (first command is bad path)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '15. < infile ../a.out | sleep 3 > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile ../a.out | sleep 3 > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile ../a.out "sleep 3" outfile

echo ""
echo ""

# test16 (second command is bad path)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '16. < infile sleep 3 | ../a.out > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile sleep 3 | ../a.out > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile "sleep 3" ../a.out outfile

echo ""
echo ""

# test17 (both commands are bad path)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '17. < infile ../a.out | ../a.out > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile ../a.out | ../a.out > outfile
cat outfile
echo ""echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '19. < infile sleep 3 | ../a.out -wrongflag > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile sleep 3 | ../a.out -wrongflag > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile "sleep 3" "../a.out -wrongflag" outfile

echo ""
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile ../a.out ../a.out outfile

echo ""
echo ""

# test18 (first command is relative path & bad option)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '18. < infile ../a.out -wrongflag | sleep 3 > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile ../a.out -wrongflag | sleep 3 > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile "../a.out -wrongflag" "sleep 3" outfile

echo ""
echo ""

# test19 (second command is relative path & bad option)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '19. < infile sleep 3 | ../a.out -wrongflag > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile sleep 3 | ../a.out -wrongflag > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile "sleep 3" "../a.out -wrongflag" outfile

echo ""
echo ""

# test20 (both command are relative path & bad option)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '20. < infile ../a.out -wrongflag | ../a.out -wrongflag > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile ../a.out -wrongflag | ../a.out -wrongflag > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile "../a.out -wrongflag" "../a.out -wrongflag" outfile

echo ""
echo ""

# test21 (first command is close relative path)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '21. < infile a.out | sleep 3 > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile a.out | sleep 3 > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile a.out "sleep 3" outfile

echo ""
echo ""

# test22 (second command is close relative path)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '22. < infile sleep 3 | a.out > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile sleep 3 | a.out > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile "sleep 3" a.out outfile

echo ""
echo ""

# test23 (both command are close relative path)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '23. < infile a.out | a.out > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile a.out | a.out > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile a.out a.out outfile

echo ""
echo ""

# test24 (first command is close relative path)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '24. < infile /a.out | sleep 3 > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile /a.out | sleep 3 > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile /a.out "sleep 3" outfile

echo ""
echo ""

# test25 (second command is close relative path)
echo "this\nshoud\nbe\noverrided" > outfile< infile a.out | a.out > outfile
printf "\033[36m%s\033[m\n" '25. < infile sleep 3 | /a.out > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile sleep 3 | /a.out > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile "sleep 3" /a.out outfile

echo ""
echo ""

# test26 (both command are close relative path)
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[36m%s\033[m\n" '26. < infile /a.out | /a.out > outfile'
printf "\033[33m%s\033[m\n" '# bash #'
< infile /a.out | /a.out > outfile
cat outfile
echo ""
echo "this\nshoud\nbe\noverrided" > outfile
printf "\033[33m%s\033[m\n" '# pipex #'
./pipex infile /a.out /a.out outfile

echo ""
echo ""




rm a.out
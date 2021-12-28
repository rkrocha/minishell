#!/bin/bash

MINISHELL=../minishell

source './assert.sh'
make -C ../ || exit 1

fail=0
extra=0
pass=0

test_ok() # $1: comando de teste	$2:
{
	# echo -e $@

	result=$(echo -e "$@" | $MINISHELL | tail -n +2)
	expected=$(echo -e "$@" | bash)

	# echo $result
	# echo $expected

	assert_eq "$result" "$expected" "[KO with cmd: $1]" && ((++pass)) && return
	((++fail))
}

test_ok 'echo' '123'
test_ok 'echo' '""$HOME'
test_ok 'echo' '$HOME'
test_ok 'echo' '$HOME$HOME'
test_ok 'echo' 'abc"123"'
test_ok 'echo' 'abc'123
test_ok 'echo' "abc"123

test_ok 'pwd'

test_ok 'cd not'
test_ok 'cd ../samples'
test_ok 'cd ~'
test_ok 'cd .. | pwd'

test_ok 'export abc=123\nenv | grep abc'



norminette ../ &>/dev/null && echo -e '\n'${GREEN}Norme: pass'\n' || echo -e '\n'${RED}Norme: fail'\n'

echo ${RED}KO: $fail
echo ${YELLOW}EX: $extra
echo ${GREEN}OK: $pass
echo ${NORMAL}
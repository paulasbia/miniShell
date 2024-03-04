<h1 align="center">
	42cursus' Minishell
</h1>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/paulasbia/miniShell?color=blueviolet" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/paulasbia/miniShell?color=blue" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/paulasbia/miniShell?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/paulasbia/miniShell?color=brightgreen" />
</p>

- Actual Status : Concluded
- Result        : 101 %
- Observations  : N.A

## About
Refer to the [**subject of this project**](https://github.com/paulasbia/miniShell/blob/main/subject_mini_shell.pdf)

Minishell is a 42 school team project to create a basic shell program in C. It implements redirections and pipes, as well as environment variable expansions and the cd, echo, env, exit, export, pwd and unset builtin commands.

## 📑 Index

`@root`

* [**📁 includes:**](includes/) contains the program's headers.
* [**📁 libft:**](libft/) contains the source code of the `libft` library, which is used in the program.
* [**📁 srcs:**](srcs/) contains the source code of the program.
* [**📁 executes:**](executes/) contains the executes code of the program.
* [**📁 parsing:**](parsing/) contains the parsing code of the program.
* [**📁 builtins:**](builtins/) contains the builtins code of the program.
* [**📁 utils:**](utils/) contains the utils code of the program.
* [**Makefile**](Makefile) - contains instructions for compiling the program and testing it.
* [**📁 tests e2e:**](e2e/) contains the e2e tests code of the program.
* [**📁 unit test:**](unit/) contains the unit tests code of the program.

### Requirements

The program is written in C language for **Linux** distributions and thus needs the **`clang` compiler** and some standard **C libraries** to run.

### Instructions

**Compiling the program**

To compile the program, run:

```shell
$ make
```
![image](https://github.com/paulasbia/miniShell/assets/112953928/0a03f3f4-a9e1-45e7-a731-5975869f35d2)

**Executing the program**

Run:

```shell
$ ./minishell
```
### Some commands to try:

As this project is made to mimic bash, you can try any commands you normally would try in bash.

If you really can't think of anything try some of the following.  You do have to enter each line separately as the program doesn't handle new lines.
```
ls -la | grep a | tr 'a-z' 'A-Z'
```

```
cat << EOF > file
cat file
rm file
```

```
ls | rev > file
cat file
rev file | cat
rm file
```

*to exit the program:*
```
exit
```

## Study references
[mini bash Medium](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)
[Precedence climbing](https://eli.thegreenplace.net/2012/08/02/parsing-expressions-by-precedence-climbing)
[42Docs](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
https://github.com/LucasKuhn/minishell_tester
[Sigaction](https://linuxhint.com/c-sigaction-function-usage/)
[Expansion](https://linuxcommand.org/lc3_lts0080.php)
[Dirent (readir)](https://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html)
[getcwd](https://www.ibm.com/docs/en/zos/2.3.0?topic=functions-getcwd-get-path-name-working-directory)
[getcwd_bytes](https://superuser.com/questions/142893/why-is-the-size-of-a-directory-always-4096-bytes-in-unix)
[exit](https://www.ibm.com/docs/en/zos/3.1.0?topic=descriptions-exit-return-shells-parent-process-tsoe)
[export](https://guialinux.uniriotec.br/export/)
[export_more](https://www.vivaolinux.com.br/dica/O-comando-export)
[fork before exec](https://stackoverflow.com/questions/15817627/what-is-the-use-of-fork-ing-before-exec)
[wait](https://stackoverflow.com/questions/3776859/how-can-i-get-the-return-value-of-a-program-executed-by-exec)
[redirect](https://www.digitalocean.com/community/tutorials/an-introduction-to-linux-i-o-redirection)

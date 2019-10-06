# Operating Systems Assignment 1
## Jake Epstein, Chinese University of Hong Kong & Dartmouth College

### Usage:

The following is a c-based linux shell emulator. When compiled and run, it takes bash commands from stdin, and sends in to stdout. It supports basic piped commands (tested rigorously up to 2 pipes (3 commands), built to support any number) but no other wildcards (redirections, &, etc.). Pipes must be preceeded by and proceeded by a space. Example `ls -l | wc`, not `ls -l| wc`

Run using `./SimpleShell`. When running, the user will be prompted with a command line. Type any bash command with the above specifications and click `ENTER`. Shell output is sent to stdout and the programs command line prompt repeats. To leave the emulator, type `EXIT`.

### Compilation

To compile: `make`

To run: `./SimpleShell`

### Testing

The following tests compare the terminal's output with the emulator's output for a few basic bash commands.

#### Command `ls`

Terminal:
```
jake@jake-MacBookPro:~/OS/Assign1$ ls
Makefile  README.md  simple-execute.c  simple-execute.o  simple-shell.c  simple-shell.o
```

Emulator:
```
jake@jake-MacBookPro:~/OS/Assign1$ ./SimpleShell
---------------------------------------------------------
|Simple Shell Program for CSCI 3150 (Zili Shao@CSE,CUHK)|
---------------------------------------------------------

Usage: Input a command for execution or EXIT for exit. 

$$$ ls 
Makefile  README.md  simple-execute.c  simple-execute.o  SimpleShell  simple-shell.c  simple-shell.o
$$$ 
```

#### Command 'ls -l | sort`

Terminal:
```
jake@jake-MacBookPro:~/OS/Assign1$ ls -l | sort
-rw-r--r-- 1 jake jake   270 Oct  4 12:55 Makefile
-rw-r--r-- 1 jake jake  2806 Oct  6 13:22 simple-execute.c
-rw-r--r-- 1 jake jake  3432 Oct  6 12:50 simple-shell.c
-rw-r--r-- 1 jake jake  3600 Oct  6 13:29 simple-shell.o
-rw-r--r-- 1 jake jake  3936 Oct  6 13:29 simple-execute.o
-rw-r--r-- 1 jake jake   881 Oct  6 13:46 README.md
-rwxr-xr-x 1 jake jake 17392 Oct  6 13:47 SimpleShell
total 44
```

Emulator:
```
$$$ ls -l | sort 
-rw-r--r-- 1 jake jake   270 Oct  4 12:55 Makefile
-rw-r--r-- 1 jake jake  2806 Oct  6 13:22 simple-execute.c
-rw-r--r-- 1 jake jake  3432 Oct  6 12:50 simple-shell.c
-rw-r--r-- 1 jake jake  3600 Oct  6 13:29 simple-shell.o
-rw-r--r-- 1 jake jake  3936 Oct  6 13:29 simple-execute.o
-rw-r--r-- 1 jake jake   881 Oct  6 13:46 README.md
-rwxr-xr-x 1 jake jake 17392 Oct  6 13:47 SimpleShell
total 44
```

#### Command 'ls -l | grep D | wc -l`

Terminal:
```
jake@jake-MacBookPro:~/OS/Assign1$ ls -l | grep D | wc -l
1
```

Emulator:
```
$$$ ls -l | grep D | wc -l
1
```

#### Command 'ls -l| wc -l`

Emulator:
```
$$$ ls -l| wc
ls: invalid option -- '|'
Try 'ls --help' for more information.
```

#### Command `EXIT`

Emulator:
```
$$$ EXIT
jake@jake-MacBookPro:~/OS/Assign1$
```


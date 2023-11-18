i# Simple Shell

## Description

The Simple Shell project is a basic implementation of a Unix shell. A shell is a command-line interpreter that allows users to interact with the operating system by entering commands. This simple shell project provides a command-line interface where users can execute commands, and it also includes basic features like command execution, path resolution, and simple command chaining.

## COPYRIGHT
Copyright (C) 2023 by [**Abdul-Hafiz Yussif**](https://github.com/IAmAbdulHafiz) and [**Florence Obiri Manu**](https://github.com/Flo20201994) <br> All rights reserved

## Features

- **Command Execution:** Execute commands entered by the user.
- **Path Resolution:** Search for executable files in the system's PATH.
- **Command Chaining:** Allow the user to chain multiple commands using operators like `;`, `&&`, and `||`.
- **Built-in Commands:** Include some built-in commands like `cd` for changing the current directory.

## Getting Started

### Prerequisites

- C compiler (e.g., GCC)
- Unix-like operating system

### Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

```
## Usage
```bash
./hsh
```
## Usage Examples

### Execute a command:
```bash
$ ls
file1.txt file2.txt file3.txt
```
1. Change directory:
```bash
$ cd /path/to/directory
```

2. Command chaining:
```bash
$ ls -l ; pwd
file1.txt
file2.txt
file3.txt
/current/directory
```
3. Built-in commands:
```bash
$ cd /new/directory
$ pwd
/new/directory
```

## Contributing

If you would like to contribute to the development of the Simple Shell project, please follow these steps:

1. Fork the repository on GitHub.
2. Clone your forked repository to your local machine.
3. Create a new branch for your feature or bug fix.
4. Make changes and commit them to your branch.
5. Push your changes to your fork on GitHub.
6. Open a pull request to the original repository.

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- The Simple Shell project was inspired by the Unix shell.
- Betty Holberton | Alx-Africa.


# msh - Simple Shell Implementation

msh is a basic shell (command-line interface) written in C. It provides a minimalistic interactive shell environment where users can enter commands, and the shell executes those commands. This project is intended for educational purposes to understand the fundamentals of shell programming and process management in a Unix-like environment.

## Features

- **Basic Shell Features:**
  - Provides a shell prompt (`msh>`).
  - Reads user commands from the command line.
  - Tokenizes the input command to extract individual arguments.

- **Command Execution:**
  - Forks a child process to execute the entered command.
  - Child process executes the command using `execvp()`.
  - Parent process waits for the child process to finish.

- **Built-In Commands:**
  - `cd`: Changes the current working directory.
  - `quit` or `exit`: Exits the shell.
  - `showpids`: Displays the process IDs (PIDs) of child processes.
  - `history`: Displays a list of previously entered commands.

- **Command History:**
  - Maintains a command history in a circular buffer, storing up to 15 recent commands.
  - Supports command retrieval and re-execution using `!n` syntax. [eg: `!3`]

- **Error Handling:**
  - Provides basic error handling, reporting a command not found if `execvp()` fails.

- **Changing Directories:**
  - The `cd` command allows users to change the current working directory.

- **Dynamic Memory Allocation:**
  - Uses dynamic memory allocation with `malloc` to manage memory for command strings.

## Getting Started

### Prerequisites

- GCC Compiler

### Compilation

```bash
gcc msh.c -o msh -std=c99
./msh
```
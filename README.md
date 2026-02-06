# custom_shell

Custom POSIX-compliant shell in C++ – parses commands, runs externals/builtins (cd, pwd, echo, type, exit).

[![Stage Progress](https://img.shields.io/badge/stages-5%2F12-green)](https://app.codecrafters.io/c/tobiaskocur/s/shell)

## Features
- REPL loop
- Builtins: `exit`, `echo`, `pwd`, `cd`, `type`
- PATH search + exec perms check [your fix!]
- Robust dir iteration (skips missing paths)

## Build & Run
```bash
mkdir build && cd build
cmake ..
make
./shell

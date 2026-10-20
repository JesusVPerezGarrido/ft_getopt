# ft_getopt

`ft_getopt` is a small C library for parsing short command-line options. It
supports single-character flags, clustered flags (such as `-abc`), and options
that take an argument, either attached (`-oresult`) or in the next argument
(`-o result`). Each parser has its own state, stored in a `t_getopt` structure.

## Build

Build the static library:

```sh
make
```

This creates `getopt.a` in the project directory. Run the test program with:

```sh
make test
```

## Use

Include `ft_getopt.h`, initialize a `t_getopt`, then call `ft_getopt` until it
returns `-1`. In the option string, list each supported option character. Add
one colon after an option that requires an argument.

```c
#include "ft_getopt.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    t_getopt parser;
    int option;

    ft_getoptinit(&parser, argc, argv, "vo:");
    while ((option = ft_getopt(&parser)) != -1)
    {
        if (option == 'v')
            puts("verbose mode enabled");
        else if (option == 'o')
            printf("output: %s\n", parser.optarg);
        else if (option == '?')
            fprintf(stderr, "unknown option\n");
        else if (option == ':')
            fprintf(stderr, "option requires an argument\n");
    }
    return 0;
}
```

Compile and link your program against the library:

```sh
cc -Wall -Wextra -Iinc main.c getopt.a -o my_program
```

For the example option string `"vo:"`, `-v` is a flag and `-o` requires a
value. Both `-oresult` and `-o result` set `parser.optarg` to the value.

## API

```c
void ft_getoptinit(t_getopt *info, int argc, char **argv, const char *optstr);
int  ft_getopt(t_getopt *info);
```

The parser state exposes these fields:

| Field | Description |
| --- | --- |
| `argc`, `argv` | The argument count and vector passed to `ft_getoptinit`. |
| `optstr` | A copy of the option string. The structure holds at most 31 characters plus the terminating null byte. |
| `optind` | Index in `argv` of the current or next argument. It starts at `1`, after the program name. |
| `nextchar` | Position within a clustered option argument, such as `-abc`. |
| `optarg` | Pointer to the current option's argument, or `NULL` when there is none. Reset on each call. |

`ft_getopt` returns the recognized option character when it finds an option,
`'?'` for an unknown option character, `':'` when a recognized option requiring
an argument has no argument, and `-1` when parsing stops. Parsing stops at the
first positional argument or at `--`; the stopping argument is not consumed, so
`optind` points to it.

Options are single-dash options. A single-dash token may contain clustered
flags, and an option requiring an argument uses the rest of its token as the
argument when present.

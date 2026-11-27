*This project has been created as part of the 42 curriculum by kmota.*

# get_next_line

![completed](https://img.shields.io/badge/completed-0a4518)

## Languages Used

- `C`

## Objective

Create a function that reads and returns a line from a file descriptor, one line at a time, while learning how static variables work in C and how to manage dynamically allocated memory.

## Description

**Get Next Line** is a 42 curriculum project that consists of implementing a function that reads from a file descriptor and returns one line at each call.

The function must preserve the remaining content between calls, allowing the next call to continue reading from where the previous one stopped.

The project is divided into two parts:

- **Mandatory:** Implements `get_next_line()` using a static variable to preserve the remaining content between calls.
- **Bonus:** Extends the implementation to handle multiple file descriptors simultaneously, using only one static variable.

The function prototype is:

```c
char *get_next_line(int fd);
```

It returns:
- A line read from the file descriptor, including the terminating `\n` when present.
- `NULL` when there is nothing else to read or when an error occurs.

The implementation also supports reading from standard input.

### Mandatory Part

The mandatory implementation uses a single static pointer:

```c
static char *stash;
```

The stash stores the content read from the file descriptor that has not yet been returned.

Each call to `get_next_line()` extracts one line from the stash and preserves the remaining content for the next call.

### Bonus Part

The bonus implementation extends the mandatory functionality to support multiple file descriptors at the same time.

It uses a single static array:

```c
static char *stash[FD_MAX];
```

Each position of the array stores the remaining content associated with a specific file descriptor.

For example, `stash[3]`, `stash[4]`, and `stash[5]` independently preserve the reading state of three different file descriptors.

This allows calls to `get_next_line()` to alternate between different files without mixing their contents or losing their reading positions.

### External Functions Used

The project uses the following external functions:

- `read()` — reads data from a file descriptor.
- `malloc()` — dynamically allocates memory for buffers, lines and strings.
- `free()` — releases dynamically allocated memory.

No external libraries or Libft functions are used.

### Concepts Learned

This project reinforces concepts such as:

- Static variables and persistent data.
- File descriptors and the `read()` system call.
- Dynamic memory allocation and memory management.
- String manipulation and concatenation.
- Buffer management.
- Handling multiple file descriptors.
- EOF and error handling.
- Understanding how to preserve data between function calls.

# Instructions

## Requirements

- `cc` compiler (GCC or Clang).
- Linux or another Unix-like environment.
- Valgrind (optional, for memory testing).

## Compilation

The project can be compiled using the following commands.

### Mandatory

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c
```

### Bonus

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line_bonus.c get_next_line_utils_bonus.c
```

The `BUFFER_SIZE` value determines how many bytes are read in each call to `read()`.

It can be adjusted during compilation:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 \
get_next_line.c get_next_line_utils.c
```

The project must also compile without explicitly defining `BUFFER_SIZE`, using the default value specified in the header.

## Usage

1. Include the appropriate header in your program.

For the mandatory part:

```c
#include "get_next_line.h"
```

For the bonus part:

```c
#include "get_next_line_bonus.h"
```

2. Call `get_next_line()` with a valid file descriptor.

### Quick Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);

    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }

    close(fd);
    return (0);
}
```

### Bonus Example: Multiple File Descriptors

The bonus implementation allows reading from multiple files alternately.

```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int     fd1;
    int     fd2;
    char    *line;

    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);

    line = get_next_line(fd1);
    printf("%s", line);
    free(line);

    line = get_next_line(fd2);
    printf("%s", line);
    free(line);

    line = get_next_line(fd1);
    printf("%s", line);
    free(line);

    close(fd1);
    close(fd2);
    return (0);
}
```

Each file descriptor maintains its own stash, allowing the function to continue reading independently.

## Testing

The implementation should be tested with different file contents and buffer sizes.

Important test cases include:

- Empty files.
- Files containing a single line.
- Files containing multiple lines.
- Files ending with a newline.
- Files without a newline at the end.
- Very long lines.
- Lines shorter and longer than `BUFFER_SIZE`.
- Different `BUFFER_SIZE` values, including `1` and large values.
- Standard input.
- Invalid file descriptors.
- Multiple file descriptors read alternately (Bonus).

The bonus implementation should also be tested by alternating calls between at least three different file descriptors to ensure that their contents are never mixed.

### Memory Testing with Valgrind

Memory leaks and memory-related errors can be checked using Valgrind.

Compile the mandatory implementation:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c main.c -o gnl
```

Run Valgrind:

```bash
valgrind --leak-check=full ./gnl
```

For more detailed memory checking:

```bash
valgrind --leak-check=full --show-leak-kinds=all \
--track-origins=yes ./gnl
```

The returned lines must be freed by the caller, and the internal stash must be properly managed to avoid memory leaks and invalid memory accesses.

# Algorithm and Data Structure

## Overall Approach

The implementation uses a static variable called `stash` to preserve the content read from the file descriptor between function calls.

The algorithm reads data in chunks using `read()`, with each chunk having a maximum size determined by `BUFFER_SIZE`.

Instead of reading the entire file at once, the function reads only until it finds a newline character or reaches the end of the file.

The algorithm is divided into three main operations:

1. **Read and Stash:** Reads data from the file descriptor and appends it to the stash.
2. **Extract Line:** Extracts the next line from the stash, including the newline character when present.
3. **Refresh Stash:** Removes the extracted line and preserves the remaining content for the next call.

## Mandatory Algorithm

The mandatory implementation uses:

```c
static char *stash;
```

The main function follows these steps:

1. Validate the file descriptor and `BUFFER_SIZE`.
2. Call `ft_read_file()` to read additional content into the stash.
3. Call `ft_start()` to extract the next line.
4. Call `ft_update()` to remove the extracted line from the stash.
5. Return the extracted line.

### Helper Functions

The helper functions are responsible for reading data from the file descriptor, extracting the next line and updating the stash.

- **`ft_read_file()`**: Reads data using `read()`, appends it to the stash using `ft_strjoin()` and stops when a newline is found or EOF is reached. Handles read errors and allocation failures.
- **`ft_start()`**: Extracts the next line from the stash using `ft_substr()`, including `\n` when present. Returns the remaining content if EOF is reached without a final newline.
- **`ft_update()`**: Removes the extracted line, preserves the remaining content in the stash and frees the previous allocation. Returns `NULL` when no content remains.

In the Bonus implementation, these functions operate on the stash associated with the current file descriptor, allowing multiple files to be read independently.

## Bonus Algorithm

The bonus implementation uses a single static array:

```c
static char *stash[FD_MAX];
```

Instead of having one stash for the entire function, each file descriptor has its own independent stash.

The main function follows the same algorithm as the mandatory implementation, but all stash operations use the current file descriptor as an index.

```c
stash[fd] = ft_read_and_stash(fd, stash[fd]);

line = ft_extract_line(stash[fd]);

stash[fd] = ft_refresh_stash(stash[fd]);
```

This allows multiple files to be read independently, even when calls to `get_next_line()` are alternated between different file descriptors.

## Why This Design

- **Static variable:** Preserves information between calls without using global variables.
- **Read only when necessary:** Avoids reading the entire file when only one line is requested.
- **Dynamic allocation:** Allows the implementation to handle lines larger than `BUFFER_SIZE`.
- **Separate helper functions:** Divides the algorithm into smaller operations, making the code easier to understand and maintain.
- **Independent stashes (Bonus):** Allows multiple file descriptors to be read simultaneously without mixing their contents.
- **Memory management:** Temporary buffers and previously used stashes are freed when no longer needed.

## Data Structures

The project does not require complex data structures.

It uses:

- A static character pointer (`stash`) in the mandatory implementation.
- A static array of character pointers (`stash[FD_MAX]`) in the bonus implementation.
- Temporary character buffers for reading data.
- Dynamically allocated strings for extracted lines and remaining content.
- Integer variables for tracking positions and the number of bytes read.

# Project Structure

| File | Description |
|---|---|
| `get_next_line.c` | Mandatory implementation of `get_next_line()` and its helper functions. |
| `get_next_line.h` | Mandatory header containing definitions and function prototypes. |
| `get_next_line_utils.c` | Mandatory string manipulation and utility functions. |
| `get_next_line_bonus.c` | Bonus implementation supporting multiple file descriptors. |
| `get_next_line_bonus.h` | Bonus header containing definitions and function prototypes. |
| `get_next_line_utils_bonus.c` | Bonus string manipulation and utility functions. |

# Resources

## Classic References

- [Linux Manual – read(2)](https://man7.org/linux/man-pages/man2/read.2.html) – documentation of the `read()` system call.
- [Linux Manual – open(2)](https://man7.org/linux/man-pages/man2/open.2.html) – opening files and obtaining file descriptors.
- [Linux Manual – close(2)](https://man7.org/linux/man-pages/man2/close.2.html) – closing file descriptors.
- [Linux Manual – malloc(3)](https://man7.org/linux/man-pages/man3/malloc.3.html) – dynamic memory allocation.
- [Linux Manual – free(3)](https://man7.org/linux/man-pages/man3/free.3.html) – releasing allocated memory.
- [GNU Make Manual](https://www.gnu.org/software/make/manual/) – Makefile documentation.
- [cppreference – C](https://en.cppreference.com/w/c) – reference for the C language and standard library.
- [Valgrind Documentation](https://valgrind.org/docs/manual/manual.html) – memory error and leak detection.
- 42 Norm (Norminette) – coding style rules required by the curriculum.

## AI Usage

AI was used occasionally as a learning aid:

- **Understanding Concepts:** Explanations of static variables, file descriptors, buffer management and dynamic memory allocation.
- **Code Review:** Suggestions for identifying potential memory leaks, NULL handling issues and edge cases.
- **Algorithm Understanding:** Help understanding the differences between the mandatory and bonus implementations.
- **Testing:** Suggestions for test cases involving different buffer sizes, EOF handling and multiple file descriptors.

The implementation and debugging process were carried out as part of the learning process of the 42 curriculum.

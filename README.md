*This project has been created as part of the 42 curriculum by tsimao-g.*

# get_next_line

## Description

**get_next_line** is a function that reads a line from a file descriptor, one line at a time. Each call to `get_next_line()` returns the next line from the file, including the terminating newline character (`\n`), except for the last line if it doesn't end with one.

### Goal

The main objective of this project is to learn about:
- **Static variables** in C and how they preserve state between function calls
- **File descriptors** and low-level file I/O operations using `read()`
- **Dynamic memory allocation** and proper memory management to avoid leaks
- Reading data in chunks using a configurable `BUFFER_SIZE`

### Overview

The implementation consists of three files:
| File | Purpose |
|------|---------|
| `get_next_line.c` | Main logic: reading, extracting lines, and managing the static buffer |
| `get_next_line_utils.c` | Helper functions (`ft_strlen`, `ft_strchr`, `ft_strjoin`, `ft_calloc`) |
| `get_next_line.h` | Header file with function prototypes and `BUFFER_SIZE` definition |

---

## Instructions

### Compilation

To use `get_next_line` in your project, compile it with your source files:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c your_program.c -o your_program
```

You can change `BUFFER_SIZE` to any positive value to adjust how many bytes are read at a time.

### Usage Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("example.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Return Values

| Return | Meaning |
|--------|---------|
| `char *` | The next line read from the file descriptor |
| `NULL` | End of file reached or an error occurred |

---

## Algorithm Explanation

### Why This Approach?

The algorithm uses a **static variable** to store leftover data between function calls. This is essential because `read()` operates on arbitrary byte chunks (defined by `BUFFER_SIZE`), not on logical lines.

### Step-by-Step Breakdown

#### 1. `read_line(fd, text)`
This function accumulates data from the file until a newline is found:

1. **Initialize buffer**: If `text` is `NULL` (first call), allocate an empty string
2. **Read loop**: Repeatedly call `read()` to fill a temporary buffer
3. **Accumulate**: Concatenate each chunk to `text` using `join_and_free()`
4. **Stop condition**: Break when a `\n` is found in `text` or EOF is reached

```
File content: "Hello\nWorld\n"
BUFFER_SIZE: 4

Read 1: "Hell" > text = "Hell"
Read 2: "o\nWo" > text = "Hello\nWo" > newline found, stop!
```

#### 2. `ft_get_line(text)`
Extracts the current line (up to and including `\n`) from the accumulated text:
- Counts characters until `\n` or end of string
- Allocates and copies exactly one line

#### 3. `clean_line(text)`
Removes the extracted line from `text`, keeping the remainder for the next call:
- Finds the position after `\n`
- Creates a new string with everything after the newline
- Frees the old `text`

### Justification

| Design Choice | Reason |
|---------------|--------|
| **Static variable** | Preserves leftover data between calls without global variables |
| **Dynamic buffer accumulation** | Handles lines of any length, regardless of `BUFFER_SIZE` |
| **Separate read/extract/clean functions** | Modular design improves readability and maintainability |
| **Configurable BUFFER_SIZE** | Allows performance tuning (larger = fewer syscalls, more memory) |


## Resources

### Documentation & References

- [read() - Linux man page](https://man7.org/linux/man-pages/man2/read.2.html)
- [Static Variables in C](https://www.geeksforgeeks.org/static-variables-in-c/)
- [File Descriptors](https://en.wikipedia.org/wiki/File_descriptor)
- [understanding get_next_line (english subtitles)](https://www.youtube.com/watch?v=-Mt2FdJjVno)

### AI Usage

AI assistance was used in the following ways during this project:

**Tasks Assisted by AI:**

- **Debugging Support**: Identifying edge cases and potential memory leaks (e.g., handling EOF, empty files, read errors)
- **Code Review**: Validating the logic of buffer management and static variable handling
- **Documentation**: Structuring this README and explaining the algorithm step-by-step

#### Parts Developed Without AI:

- **Core Implementation**: All source code was written manually
- **Logic Design**: The overall architecture, static variable approach, and function decomposition were designed independently
- **Testing**: Manual testing with various file types (empty files, single line, multiple lines, no newline at EOF)

The core algorithm and implementation were developed independently, with AI serving as a documentation and learning aid.
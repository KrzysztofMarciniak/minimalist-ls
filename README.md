# C-Posix-2008-Template

A template for C projects targeting the POSIX.1-2008 standard.  This template provides a basic project structure and a Makefile for easy building and management of your C projects.

## Features

*   **POSIX.1-2008 Compliance:**  Ensures your project adheres to the POSIX.1-2008 standard by defining `_POSIX_C_SOURCE=200809L`.
*   **Organized Structure:**  Includes a `src/` directory for source files and a `bin/` directory for compiled binaries.
*   **Makefile:**  Provides a Makefile for easy compilation and cleaning of the project.
*   **Multiple Source File Support:** Supports projects with multiple source files.
*   **Clean Build Process:**  Separates object files and binaries into a dedicated `bin/` directory.
*   **Warnings:** Enables `-Wall` and `-Wextra` compiler flags for more verbose warnings.
## Usage

1.  **Clone the repository:**

    ```bash
    git clone https://github.com/KrzysztofMarciniak/C-Posix-2008-Template.git
    cd C-Posix-2008-Template
    ```

2.  **Place your source files in the `src/` directory.**  Modify or add `.c` files as needed.

3.  **Build the project:**

    ```bash
    make
    ```

    This will compile your code and create an executable named `output` in the `bin/` directory.

4.  **Run the executable:**

    ```bash
    bin/output
    ```

5.  **Clean the project:**

    ```bash
    make clean
    ```

    This will remove the `bin/` directory and all compiled files.

## Makefile Options

*   `CC`:  The C compiler to use (default: `gcc`).  You can override this by setting the `CC` variable, e.g., `make CC=clang`.
*   `CFLAGS`:  Compiler flags (default: `-std=c99 -Wall -Wextra -D_POSIX_C_SOURCE=200809L`).  You can add or modify flags as needed.
*   `TARGET`: The name of the executable (default: `output`).


C CLI Toolkit

A beginner-friendly Unix-style command-line toolkit built in C.

This project explores computer science fundamentals through practical command-line utilities rather than isolated beginner exercises.

Features

The toolkit includes five commands:

Command	Description
stats	Calculate the count, minimum, maximum, and average of numbers in a file.
count	Count lines, words, and bytes in a file.
reverse	Reverse text supplied through the command line.
temperature	Convert Celsius to Fahrenheit.
bytes	Display the size of a file in bytes.

Example

./toolkit stats numbers.txt

Example output:

Count:   5
Minimum: 10
Maximum: 50
Average: 30.00

Requirements

* macOS or Linux
* Clang or GCC
* Terminal
* Git (optional, for cloning the repository)

On macOS, install the Apple Command Line Tools if necessary:

xcode-select --install

Check that Clang is available:

clang --version

Installation

Clone the repository:

git clone https://github.com/vsroshan/c-cli-toolkit.git

Enter the project directory:

cd c-cli-toolkit

Compile the program:

clang -std=c11 -Wall -Wextra -Wpedantic toolkit.c -o toolkit

If you are using GCC instead:

gcc -std=c11 -Wall -Wextra -Wpedantic toolkit.c -o toolkit

The compiler creates an executable named toolkit.

Usage

Display help

./toolkit help

Reverse text

./toolkit reverse hello

Example output:

Original: hello
Reversed: olleh

Convert temperature

./toolkit temperature 32

Example output:

32.00 Celsius = 89.60 Fahrenheit

Count lines, words, and bytes

Create a sample file:

printf 'C is fun\nLearning takes practice\n' > notes.txt

Run:

./toolkit count notes.txt

Inspect file size

./toolkit bytes notes.txt

Calculate statistics

Create a numeric data file:

printf '10 20 30 40 50\n' > numbers.txt

Run:

./toolkit stats numbers.txt

The statistics command supports decimal and negative numbers. It reports an error if a token is not a valid number or if the file contains no numbers.

Concepts Explored

This project reinforces several foundational C and computer science concepts:

* Variables and data types
* Arithmetic and floating-point precision
* Conditional statements
* Loops and iteration
* Functions and return values
* Command-line arguments using argc and argv
* Strings and string comparison
* File handling and standard input/output
* Error handling and exit status codes
* Compilation with Clang or GCC
* Integer counters and floating-point calculations
* Modular program design

C vs. Python

C requires explicit compilation and provides more direct control over types and memory management than Python.

Python generally handles many implementation details automatically, making it convenient for rapid development.

By implementing similar functionality in C, this project provides an opportunity to explore how compiled programs process arguments, read files, represent numeric values, and handle errors.

Limitations

* The reverse command is intended for basic ASCII text. It reverses bytes rather than complete Unicode characters.
* The count command uses whitespace to identify words and is not intended to reproduce every detail of Unix wc.
* The bytes command uses file seeking and is intended for regular, seekable files.
* The statistics command expects whitespace-separated numeric tokens.
* Floating-point arithmetic can introduce small representation errors.

Future Improvements

Potential extensions include:

* A wordfreq command to count word frequencies.
* A min or max command for numeric files.
* A fahrenheit command to convert temperatures in the opposite direction.
* CSV input support.
* Unit tests and automated builds.
* A Makefile to simplify compilation.
* Support for Unicode-aware text reversal.
* More detailed command-line options.

Learning Objective

The goal is to use a practical project to understand how C programs are compiled, how command-line utilities are structured, and how fundamental programming concepts translate into working software.

License

Released under the MIT License. See LICENSE.

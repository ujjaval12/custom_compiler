# Custom Code Format and Compiler

This project is a compiler built to parse and execute a custom programming language format designed from scratch. The compiler utilizes **Flex** and **Bison** for lexical analysis and parsing, enabling the execution of code written in the custom format.


## Introduction
The aim of this project is to create a compiler for a custom code format, demonstrating a deep understanding of lexical analysis and syntax parsing. The project uses **Flex** for tokenizing the source code and **Bison** for building the parser, transforming input into executable instructions.

This compiler project highlights the following:
- Designing a custom programming language syntax.
- Building a lexer and parser for the language.
- Translating custom language instructions into actions.

## Features
- **Custom Syntax**: A unique programming language designed for this project.
- **Lexer and Parser**: Implements tokenization and grammar parsing using Flex and Bison.
- **Error Handling**: Identifies and reports syntax and semantic errors.
- **Cross-Platform**: Runs on any system with Flex and Bison installed.
- **Modular Design**: Easy to extend and modify the language rules.

## Technologies Used
- **Flex**: A tool for generating lexical analyzers.
- **Bison**: A parser generator that converts grammar descriptions into a parser.
- **C/C++**: Used as the backend language for implementing actions.

## Setup
### Prerequisites
- Flex
- Bison
- GCC (or any compatible C/C++ compiler)

### Installation Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/compiler-project.git
   cd compiler-project
   ```
2. Build the lexer and parser:
   ```bash
   flex yourfile.l
   bison -d yourfile.y
   gcc lex.yy.c yourfile.tab.c -o compiler
   ```
3. Run the compiler executable:
   ```bash
   ./compiler
   ```

## Usage
1. Write code in the custom format and save it in a `.txt` or `.custom` file.
2. Pass the file to the compiler:
   ```bash
   ./compiler < yourfile.custom
   ```
3. View the output or error messages in the terminal.

## Examples
### Sample Code (Custom Format)
#### Basic Arithmetic
```custom
// Define variables
let a = 10;
let b = 20;

// Perform addition
let c = a + b;

// Print result
print(c);
```
**Execution**:
```bash
./compiler < sample.custom
Output: 30
```

#### Loop Statement
```custom
// Loop from 1 to 5
let i = 1;
while (i <= 5) {
    print(i);
    i = i + 1;
}
```
**Execution**:
```bash
./compiler < loop.custom
Output: 
1
2
3
4
5
```

#### Conditional Statement
```custom
// Check if a number is even or odd
let num = 4;
if (num % 2 == 0) {
    print("Even");
} else {
    print("Odd");
}
```
**Execution**:
```bash
./compiler < conditional.custom
Output: Even
```

#### Continue Statement
```custom
// Skip printing the number 3 in a loop
let i = 1;
while (i <= 5) {
    if (i == 3) {
        i = i + 1;
        continue;
    }
    print(i);
    i = i + 1;
}
```
**Execution**:
```bash
./compiler < continue.custom
Output: 
1
2
4
5
```

#### Nested Loops
```custom
// Print a multiplication table (1 to 3)
let i = 1;
while (i <= 3) {
    let j = 1;
    while (j <= 3) {
        print(i * j);
        j = j + 1;
    }
    i = i + 1;
}
```
**Execution**:
```bash
./compiler < nested_loops.custom
Output: 
1
2
3
2
4
6
3
6
9
```

## Contributing
Contributions are welcome! To contribute:
1. Fork the repository.
2. Create a feature branch.
3. Commit your changes.
4. Open a pull request.

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.

---

Feel free to raise issues or submit feature requests. Enjoy exploring the custom compiler!


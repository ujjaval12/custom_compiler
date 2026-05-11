# Custom Language Compiler - Usage Guide

## Overview
This is a compiler for a custom language with:
- **Lexical Analysis**: Token extraction with trace output
- **Syntax Analysis**: Grammar validation
- **Semantic Analysis**: Expression evaluation and variable management

## How to Use

### Option 1: File Input (Recommended)
Create a `.txt` file with your program and run:
```cmd
abc.exe < input.txt
```

### Option 2: Manual Input (Interactive)
Run the executable directly and type your program:
```cmd
abc.exe
[type your program]
[press Ctrl+Z then Enter to end input on Windows]
```

## Output
- **output.txt**: Contains the complete analysis:
  - Lexical trace (step, lexeme, token)
  - Syntax validation results
  - Semantic execution results
  - Compilation status

## Language Specification

### Data Types
- `T-Number` - Integer type
- `T-decimal` - Float type  
- `T-symbol` - Character type
- `Arr` - Array type

### Keywords
- `start` - Main program entry point
- `??` - If conditional
- `?:` - Elif conditional
- `!:` - Else conditional
- `'@-??` - Repeat loop (until do-while)
- `??-@'` - Until loop end
- `case` - Switch case label
- `switch` - Switch statement
- `switch_end` - Switch end
- `default` - Default case
- `op-stop` - Break statement
- `func` - Function declaration
- `sizeof` - Size of operator
- `call_` - Function call

### Operators
- Arithmetic: 
  - `|` - Addition
  - `~` - Subtraction
  - `#` - Multiplication
  - `%` - Division
  - `/` - Modulo
  - `^` - Power
- Comparison: 
  - `<` - Less than
  - `>` - Greater than
  - `<=` - Less than or equal
  - `>=` - Greater than or equal
  - `==` - Equal
  - `!=` - Not equal
- Logical: 
  - `AND` - Logical AND
  - `OR` - Logical OR
  - `XOR` - Logical XOR
  - `NOT` - Logical NOT
- Assignment: `=`
- Increment/Decrement: `++`, `--`

### Mathematical Functions
- `SIN`, `COS`, `TAN` - Trigonometric
- `SQRT` - Square root
- `log`, `log2`, `ln` - Logarithms
- `FACT` - Factorial

### Program Structure
```
start
(
)
{
    [declarations]
    [statements]
}
```

## Example Program
```
start
(
)
{
T-Number x;
T-Number y;
x = 10;
y = 20;
x | y;
}
```

## Output Example
```
Step# | Lexeme  | Token
1     | start   | MAIN
2     | (       | LP
3     | )       | RP
4     | {       | LB
5     | T-Number| INT
6     | x       | VAR
7     | ;       | SM

valid declaration
8     | x       | VAR
9     | =       | ASSIGN
10    | 10      | NUM
...
value of expression: 30
...
Successful compilation
```

## Notes
- All statements end with `;`
- Variables are automatically declared with type
- Expressions are evaluated during parsing
- Array operations use format: `varname[index]`
- Parentheses on separate lines for start() keyword

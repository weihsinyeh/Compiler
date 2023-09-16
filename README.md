# Compiler
## How to use
### Environment Setup
In Ubuntu 20.04 LTS
```
sudo apt install flex bison fit python3 python3-pip
```
### HW1 Scanner
Scanner for the μRust language with lex. 
```
cd HW1
```
write lexer.l

Define token and Notice the newline & comma & multi-Line-Comment 

Use Conditional compilation 
--> https://doc.rust-lang.org/reference/conditional-compilation.html
#### debug
Compile source code and feed the input to your program, then compare with the ground truth.
```
make clean && make
./myscanner < input/a01_arithmetic.rs >| tmp.out
diff -y tmp.out answer/a01_arithmetic.out
```
Check the output file char-by-char (Space and Tab are different)
```
od -c answer/a01_arithmetic.out
```
#### References

Flex: https://westes.github.io/flex/manual/

##### about Rust (not μRust)
Rust token document: https://doc.rust-lang.org/reference/tokens.html
Rust playground: https://play.rust-lang.org/?version=stable&mode=debug&edition=2021
### HW2 Parser
#### Goal : 
1. Yacc Definitions
In the HW1, the Lex code to split the input text stream into tokens that will be accepted by Yacc. In the HW2, build the code to analyze these
tokens and check the syntax validity based on the given grammar rules.
#### TODO :
1. De ne tokens and types
2. Design μGo grammar and implement the related actions 
3. Handle semantic errors 

compiler.l is somehow like HW1 lexer.l

In HW2 my work is mainly done in compiler.y file.

In this home
### HW3 Generate assembly code
[HOMEWORK DESCRIPTION](https://hackmd.io/@visitor-ckw/compiler_hw3)
#### Description
generate Java assembly code (for Java Virtual Machines) of the given μRust program. The generated code will then be translated to the Java bytecode by the Java assembler, Jasmin. The generated Java bytecode should be run by the Java Virtual Machine (JVM) successfully. 

#### Java Assembly Code Generation
In this assignment, you have to build a μRust compiler. The descriptions for the execution steps are as follows.

1. Build your μRust compiler by injecting the Java assembly code into your flex/bison code developed in the previous assignments.
2. Run the compiler with the given μRust program (e.g., test.rs le) to generate the corresponding Java assembly code (e.g., test.j le).
3. Run the Java assembler, Jasmin, to convert the Java assembly code into the Java bytecode (e.g., test.class le).
4. Run the generated Java bytecode (e.g., test.class le) with JVM and display the results.
#### Workflow Of The Assignment
Build a μRust compiler based on the previous two assignments. The execution steps are described as follows.
1. Build compiler by make command and get an executable named mycompiler .
2. Run compiler 
```
./mycompiler < input.rs 
``` 
this is built by lex and yacc, with the given μRust code ( .rs le) to generate the corresponding Java assembly code ( .j le).
3. The Java assembly code can be converted into the Java Bytecode ( .class le) through the Java assembler, Jasmin,
```
java -jar jasmin.jar hw3.j 
```
to generate Main.class .
4. Run the Java program ( .class le) with Java Virtual Machine (JVM); the program should generate the execution results required by this assignment, i.e., use 
```
java Main 
```

Install dependencies: 
```
sudo apt install flex bison
```
Java Virtual Machine (JVM)
```
sudo apt install default-jre
```
Java Assembler (Jasmin) is included in the Compiler hw3 le.

Judgmental tool: 
```
pip3 install local-judge
```
In this homework I work on compiler.y

Use CODEGEN to generate JSAMINE assembler language

TIP : USE CHATGPT to generate JASMINE code

## Homework Goal :



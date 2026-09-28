# Generated Calculator

A C++ program that generates a calculator's source code using metaprogramming. The calculator is produced by `generator.cpp` rather than written by hand. No AI is involved.

## Generate the calculator

Compile and run the generator:

```sh
g++ generator.cpp -o generator
./generator
```

The generated source file will be at `output/calculator.cpp`.

## Run the calculator

Compile and run the generated program:

```sh
g++ output/calculator.cpp -o calculator
./calculator
```

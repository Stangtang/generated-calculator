# Generated Calculator

An intentionally impractical calculator as a proof of concept.

`generator.cpp` precomputes addition, subtraction, multiplication, and division for every pair of integers from `0` to `1000`, generating a separate `if` statement for each case. The generated calculator simply navigates these `if` statements to print the result without doing any arithmetic at runtime.

## Customization

Change the `max_operand` constant in `generator.cpp` to adjust the range, then compile the calculator.

I recommend starting with `100`. At `1000`, the generated file is too large (almost 400 MB) to compile on my machine.

## Output

The generated calculator source is in the `output/` folder.

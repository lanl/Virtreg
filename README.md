# Virtreg (Virtual register)
**Virtreg** (LANL code number O4799) is a C++ code designed to perform
additions and subtractions of floating-point numbers over a wide dynamic
range without loss of precision.

# Example
In the `src/` directory compile and run the demo,
manually entering three numbers to be added.

(assumes `g++`; see `common/makefile` for other options)
```
make
./virtreg
Enter double 1: 5
Enter double 2: 1e-90
Enter double 3: -5
```
and note the final results:
```
Floating point sum: 0
Virtual register sum: 1e-90
```

# Testing
In the `src/` directory compile and run the tests.
```
make tests
./tests
```


[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/f_6PzPyj)

# ds-graphical-recursive

Let's get creative. On this lab, you will be creating a recursive program that generates the base for a graphical recursive algorithm. Since we haven't seen any graphics library, you don't need to worry about the visualization, the professor will provide the mechanism ro visualize your data.

From the _Essential Algorithms: A Practical Approach to Computer Algorithms_ book, in [Chapter 9: Recursion](https://learning.oreilly.com/library/view/essential-algorithms-a/9781118612101/17_chapter09.html#c09-5), implement one of the following 3 graphical recursive algorithms

- Koch Curves
- Hilbert Curve
- Sierpiński Curve

# Implementation Requirements

- Each algorithm has its own parameters, make sure you document them in the [following section](#how-to-compile--run-you-program)
- Parameters must be sent through the command line. Example below:

  ```
  ./your-program <param1> <param2> ...
  ```

- The output of your program will be a list of line segments in a file called `lines.txt`. The `lines.txt` file must follow the following format. Each pair represents a point in a 2D plane

  ```
  (1,2)(33,3)
  (3,5)(3,43)
  (2,1)(3,3)
  ```

- There's a 1024x1024 canvas, make sure that your generated points are inside that limited space.
- The progressor will provide the mechanism to visualize your data, just make sure you generate the proper `lines.txt` file

# Implemented algorithms 💡

This program implements two fractal geometry algorithms, both recursive, which generate complex figures from simple rules.

## Hilbert Curve 🌀

This algorithm generates a space-filling curve, which is a continuous curve that "fills" a two-dimensional plane. The recursion divides the space into subsections, and the algorithm calls itself to draw segments in a specific sequence to cover each subsection

### - Command line parameters

- `<depth>`: An integer that defines the recursion level. A higher depth will result in a more detailed and longer curve.

- `<dx>`: An integer representing the displacement on the X-axis for the first segment of the curve.

- `<dy>`: An integer representing the displacement on the Y-axis for the first segment of the curve.

## Koch Fractal ❄️

This algorithm generates the Koch fractal, built from a line segment. In each recursive step, the segment is divided into three equal parts, and the middle part is replaced by the two sides of an equilateral triangle pointing outwards.

### - Command line parameters

- `<depth>`: An integer that defines the recursion level. A higher depth results in a more complex shape. A depth of 0 is just a straight line.

- `<angle>`: A floating-point number that represents the initial angle of the baseline, measured in degrees.

- `<length>`: A floating-point number that defines the initial length of the baseline.

# How to compile & run you program

## Compilation ⚙️

To compile the program is required g++ compiler. The command below will compile the source file `main.cpp`.

```sh
g++ main.cpp -o main
```

- `g++`: The command for the GNU C++ compiler

- `-o`: The -o option specifies the name of the executable file

- `main`: The name of the executable file

## Execution 🪲

### To Generate a Hilbert Curve:

Use the following format, replacing the bracketed terms with your desired values.

```sh
./main --Hilbert <depth> <dx> <dy>
```

#### Example

`./main --Hilbert 5 0 2` would generate a Hilbert curve with a depth of 5, starting at coordinates (0,0) and an initial line segment of (0,0) to (0,2).

---

### To Generate a Koch Fractal

Use the following format, replacing the bracketed terms with your desired values.

```sh
./main --Koch <depth> <angle> <length>
```

#### Example

`./main --Koch 3 0 50` would generate a Koch Fractal with a depth of 3, starting from an angle of 0 degrees and a base length of 50 units.

# Grading Policy

| **Rubric**                            | **Points** |
| ------------------------------------- | ---------- |
| Successful Compilation                | 25%        |
| Coding Practices                      | 5%         |
| Well formed `lines.txt` file          | 35%        |
| Proper Algorithm's graphics rendering | 35%        |
| **Total**                             | 100%       |

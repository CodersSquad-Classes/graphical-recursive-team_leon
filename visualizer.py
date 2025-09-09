#!/usr/bin/env python3

# This script requires the matplotlib
# you can install it with pip
# pip install matplotlib

import ast
import matplotlib.pyplot as plt
import sys

def get_lines_from_file(filepath):
    lines = []
    try:
        with open(filepath, 'r') as file:
            for line in file.readlines():
                [p1, p2] = line.strip().split(')(')
                p1 = ast.literal_eval(p1 + ')')
                p2 = ast.literal_eval('(' + p2)
                lines.append((p1,p2))
    except FileNotFoundError:
        print(f"Error: The file '{filepath}' was not found.")
    except Exception as e:
        print(f"An error occurred: {e}")
    return lines

def plot_lines(lines):
    # Create the plot
    fig, ax = plt.subplots()
    ax.set_title("Lines drawer")
    ax.set_xlabel("X-axis")
    ax.set_ylabel("Y-axis")

    # Plot each line segment
    for line in lines:
        p1, p2 = line
        line_x = [p1[0], p2[0]]
        line_y = [p1[1], p2[1]]
        #ax.plot(p1[0], p1[1], 'o', color='blue')
        #ax.plot(p2[0], p2[1], 'o', color='blue')
        ax.plot(line_x, line_y, color='red', linestyle='-', linewidth=2)

    ax.grid(True)
    plt.show()

def main(file_name):
    # Get the lines from the file
    lines_from_file = get_lines_from_file(file_name)

    # Plot the points and lines
    plot_lines(lines_from_file)


if __name__ == "__main__":

    file_name = "lines.txt"
    if len(sys.argv) > 1:
        file_name = sys.argv[1]
    main(file_name)
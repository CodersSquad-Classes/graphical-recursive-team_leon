#!/usr/bin/env python3

# Este script requiere la biblioteca matplotlib
# Puedes instalarla con pip:
# pip install matplotlib

import ast
import matplotlib.pyplot as plt
import sys

def get_lines_from_file(filepath):
    """
    Lee un archivo de texto y extrae las coordenadas de las líneas.

    Se espera que el archivo tenga un par de coordenadas por línea en el formato:
    (x1, y1)(x2, y2)

    Args:
        filepath (str): La ruta del archivo de texto.

    Returns:
        list: Una lista de tuplas, donde cada tupla contiene los puntos
              de inicio y fin de una línea.
              Ejemplo: [((x1, y1), (x2, y2)), ...]
    """
    lines_list = []
    try:
        with open(filepath, 'r') as file:
            for i, line in enumerate(file.readlines()):
                line = line.strip()
                if not line:
                    continue  # Ignora las líneas vacías
                try:
                    # Buscamos el final de la primera tupla
                    split_index = line.find(')(')
                    if split_index == -1:
                        print(f"Advertencia: El formato de la línea {i+1} no es correcto.")
                        continue

                    # Separamos las dos tuplas y las evaluamos
                    p1 = ast.literal_eval(line[:split_index + 1])
                    p2 = ast.literal_eval(line[split_index + 1:])
                    lines_list.append((p1, p2))
                except (ValueError, SyntaxError) as e:
                    print(f"Error al procesar la línea {i+1}: {e}")
                    print(f"Línea con error: '{line}'")

    except FileNotFoundError:
        print(f"Error: El archivo '{filepath}' no fue encontrado.")
        sys.exit(1) # Salimos del programa si no se encuentra el archivo
    except Exception as e:
        print(f"Ocurrió un error inesperado: {e}")
        sys.exit(1)
        
    return lines_list

def plot_lines(lines):
    """
    Dibuja una lista de líneas en un gráfico 2D.

    Args:
        lines (list): Una lista de tuplas de puntos, como la que devuelve
                      la función get_lines_from_file.
    """
    # Crea el gráfico
    fig, ax = plt.subplots()
    ax.set_title("Dibujador de Líneas")
    ax.set_xlabel("Eje X")
    ax.set_ylabel("Eje Y")

    # Dibuja cada línea
    for p1, p2 in lines:
        line_x = [p1[0], p2[0]]
        line_y = [p1[1], p2[1]]
        ax.plot(line_x, line_y, color='red', linestyle='-', linewidth=2)

    ax.grid(True)
    plt.show()

def main(file_name):
    """
    Función principal que coordina la lectura y el trazado de las líneas.

    Args:
        file_name (str): El nombre del archivo que contiene las coordenadas.
    """
    lines_from_file = get_lines_from_file(file_name)
    
    if lines_from_file:
        plot_lines(lines_from_file)

if __name__ == "__main__":
    # Si se proporciona un argumento en la línea de comandos, úsalo como nombre de archivo
    file_name = "lines.txt"
    if len(sys.argv) > 1:
        file_name = sys.argv[1]
    
    main(file_name)
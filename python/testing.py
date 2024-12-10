import subprocess
import random
import sys

def generate_random_coordinates(coordinate_range):
    """Gera coordenadas aleatórias para x1, y1, x2, y2 com distância de Manhattan >= coordinate_range / 2."""
    
    x1 = random.randint(0, coordinate_range - 1)
    y1 = random.randint(0, coordinate_range - 1)
    x2 = random.randint(0, coordinate_range - 1)
    y2 = random.randint(0, coordinate_range - 1)
            
    return x1, y1, x2, y2

def execute_program(program_path, algorithm_name, map_dir, x1, y1, x2, y2):
    """Executa o programa com os parâmetros especificados e retorna a saída."""
    command = [
        program_path, 
        map_dir,
        algorithm_name, 
        str(x1), str(y1), 
        str(x2), str(y2), 
        "stats"
    ]
    try:
        result = subprocess.run(
            command, 
            capture_output=True, 
            text=True,
            check=True
        )
        return result.stdout.strip()  # Remove espaços extras
    except subprocess.CalledProcessError as e:
        return e.stdout.strip()  # Retorna a saída mesmo em caso de erro

def main():
    if len(sys.argv) != 8:
        print("Uso: python3 script.py <program_path> <map_dir> <algorithm_name> <results_count> <coordinate_max> <output_file> <seed>")
        print("Exemplo: python3 script.py ./pathfinder ./maps Astar 100 100 results.txt 3")
        sys.exit(1)

    # Lê os argumentos da linha de comando
    program_path = sys.argv[1]
    map_dir = sys.argv[2]
    algorithm_name = sys.argv[3]
    results_count = int(sys.argv[4])
    coordinate_range = int(sys.argv[5])
    output_file = sys.argv[6]
    seed = int(sys.argv[7])

    # Configura a seed para geração aleatória
    random.seed(seed)

    valid_count = 0

    with open(output_file, "w") as file:
        while valid_count < results_count:
            # Gera coordenadas aleatórias
            x1, y1, x2, y2 = generate_random_coordinates(coordinate_range)

            # Executa o programa e captura a saída
            output = execute_program(program_path, algorithm_name, map_dir, x1, y1, x2, y2)

            # Verifica se a saída é válida
            if output and "Coordinates invalid" not in output and "-1" not in output:
                # Escreve a saída válida no arquivo
                file.write(output + " " + str(abs(x1 - x2) + abs(y1 - y2)) + "\n")
                valid_count += 1
                print(f"Saída válida #{valid_count}: {output}")

if __name__ == "__main__":
    main()

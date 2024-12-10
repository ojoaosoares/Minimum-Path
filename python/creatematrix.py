import random
import sys

def create_matrix(seed, rows, cols, char_probs):
    """
    Cria uma matriz personalizada com base em uma seed e probabilidades.
    
    :param seed: Inteiro usado para inicializar o gerador de números aleatórios.
    :param rows: Número de linhas da matriz.
    :param cols: Número de colunas da matriz.
    :param char_probs: Lista de tuplas (caracter, probabilidade).
    :return: Matriz 2D contendo os caracteres gerados.
    """
    # Inicializa o gerador de números aleatórios com a seed fornecida
    random.seed(seed)
    
    # Constrói uma lista cumulativa de probabilidades
    chars, probs = zip(*char_probs)
    cumulative_probs = [sum(probs[:i+1]) for i in range(len(probs))]
    
    # Verifica se as probabilidades somam 1
    if not (0.99 <= cumulative_probs[-1] <= 1.01):
        raise ValueError("As probabilidades devem somar 1.")
    
    # Cria a matriz
    matrix = []
    for _ in range(rows):
        row = []
        for _ in range(cols):
            rand_val = random.random()
            for char, cum_prob in zip(chars, cumulative_probs):
                if rand_val <= cum_prob:
                    row.append(char)
                    break
        matrix.append(row)
    
    return matrix

def save_matrix_to_file(matrix, filename, rows, cols):
    """
    Salva uma matriz 2D em um arquivo, incluindo as dimensões na primeira linha.
    
    :param matrix: Matriz 2D a ser salva.
    :param filename: Nome do arquivo de destino.
    :param rows: Número de linhas da matriz.
    :param cols: Número de colunas da matriz.
    """
    with open(filename, "w") as file:
        # Escreve o número de linhas e colunas na primeira linha
        file.write(f"{rows} {cols}\n")
        # Escreve a matriz
        for row in matrix:
            file.write("".join(row) + "\n")

if __name__ == "__main__":
    # Lê os parâmetros da linha de comando
    if len(sys.argv) < 6:
        print("Uso: python script.py <colunas> <linhas> <seed> <nome_arquivo> <caractere1 probabilidade1> ...")
        sys.exit(1)

    # Parâmetros principais
    cols = int(sys.argv[1])
    rows = int(sys.argv[2])
    seed = int(sys.argv[3])
    filename = sys.argv[4]  # Nome do arquivo para salvar
    
    # Lê os pares (caractere, probabilidade) da linha de comando
    char_probs = []
    args = sys.argv[5:]
    if len(args) % 2 != 0:
        print("Erro: Os pares (caractere probabilidade) devem ser fornecidos corretamente.")
        sys.exit(1)
    
    for i in range(0, len(args), 2):
        char = args[i]
        prob = float(args[i+1])
        char_probs.append((char, prob))
    
    # Cria a matriz
    matrix = create_matrix(seed, rows, cols, char_probs)
    
    # Salva a matriz em um arquivo com o nome fornecido
    save_matrix_to_file(matrix, filename, rows, cols)
    
    print(f"Matriz criada e salva em '{filename}'")

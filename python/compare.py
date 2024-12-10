import pandas as pd
import matplotlib.pyplot as plt
import glob
import os
import numpy as np

def read_and_process_files(file_paths, ucs_file):
    """
    Lê todos os arquivos .results, adiciona a coluna 'quantidade de nós no caminho' a partir do ucs.results,
    e ordena os DataFrames pela ordem dos nós do caminho.
    """
    # Lê o arquivo ucs.results e armazena a primeira coluna (tamanho do caminho), tratando como ponto flutuante
    ucs_df = pd.read_csv(ucs_file, sep=r'\s+', header=None, names=["Path_Size", "Path_Nodes", "Expanded_Nodes", "Execution_Time", "manhattan"])
    
    # Reinicia o índice de ucs_df para evitar problemas com o índice não único
    ucs_df = ucs_df.reset_index(drop=True)

    # Lê todos os arquivos .results e processa cada um
    data = {}
    for file in file_paths:
        algo_name = os.path.basename(file).split('.')[0]  # Usa o nome do arquivo como chave
        df = pd.read_csv(file, sep=r'\s+', header=None, names=["Path_Size", "Path_Nodes", "Expanded_Nodes", "Execution_Time", "manhattan"])
        
        # Reinicia o índice do DataFrame atual
        df = df.reset_index(drop=True)

        # Adiciona a coluna 'Distância mínima' a partir da ordem de ucs.results
        df["Distância mínima"] = ucs_df["Path_Size"]
        
        # Ordena o DataFrame pela coluna 'Distância mínima'
        df_sorted = df.sort_values(by="Distância mínima").reset_index(drop=True)
        
        # Armazena o DataFrame ordenado
        data[algo_name] = df_sorted
    
    return data


def plot_combined_graphs(data, output_dir="graph", group_size=50):
    """
    Gera dois gráficos combinados para comparação entre algoritmos com médias em grupos de pontos.
    """
    # Cria o diretório de saída, se não existir
    os.makedirs(output_dir, exist_ok=True)

    # Gráfico para "Nós Expandidos"
    plt.figure(figsize=(10, 6))
    for algo_name, df in data.items():
        # Divide os dados em grupos e calcula a média para cada grupo
        grouped_means = df.groupby(df.index // group_size).mean()
        
        # Pega os valores médios das distâncias mínimas e nós expandidos
        avg_distances = grouped_means["Distância mínima"]
        avg_expanded_nodes = grouped_means["Expanded_Nodes"]
        
        # Plota as médias
        plt.plot(avg_distances, avg_expanded_nodes, marker="o", linestyle="-", label=algo_name)
    
    plt.xscale("linear")
    plt.yscale("log")
    plt.title("Comparação de Nós Expandidos", fontsize=16)  # Aumenta o tamanho da fonte do título
    plt.xlabel("Distância", fontsize=14)  # Aumenta o tamanho da fonte do rótulo do eixo X
    plt.ylabel("Nós Expandidos", fontsize=14)  # Aumenta o tamanho da fonte do rótulo do eixo Y
    plt.legend(fontsize=12)  # Aumenta o tamanho da fonte da legenda
    plt.xticks(fontsize=12)  # Aumenta o tamanho da fonte dos ticks no eixo X
    plt.yticks(fontsize=12)  # Aumenta o tamanho da fonte dos ticks no eixo Y
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f"{output_dir}/comparison_expanded_nodes_groups.png")
    plt.close()

    # Gráfico para "Tempo de Execução"
    plt.figure(figsize=(10, 6))
    for algo_name, df in data.items():
        # Divide os dados em grupos e calcula a média para cada grupo
        grouped_means = df.groupby(df.index // group_size).mean()
        
        # Pega os valores médios das distâncias mínimas e tempos de execução
        avg_distances = grouped_means["Distância mínima"]
        avg_execution_time = grouped_means["Execution_Time"]
        
        # Plota as médias
        plt.plot(avg_distances, avg_execution_time, marker="o", linestyle="-", label=algo_name)
    
    plt.xscale("linear")
    plt.yscale("log")
    plt.title("Comparação de Tempo de Execução", fontsize=16)  # Aumenta o tamanho da fonte do título
    plt.xlabel("Distância", fontsize=14)  # Aumenta o tamanho da fonte do rótulo do eixo X
    plt.ylabel("Tempo de Execução (s)", fontsize=14)  # Aumenta o tamanho da fonte do rótulo do eixo Y
    plt.legend(fontsize=12)  # Aumenta o tamanho da fonte da legenda
    plt.xticks(fontsize=12)  # Aumenta o tamanho da fonte dos ticks no eixo X
    plt.yticks(fontsize=12)  # Aumenta o tamanho da fonte dos ticks no eixo Y
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f"{output_dir}/comparison_execution_time_groups.png")
    plt.close()


if __name__ == "__main__":
    # Caminhos dos arquivos
    ucs_file = "1000results/ucs.results"  # Substitua pelo caminho correto do arquivo ucs.results
    file_paths = glob.glob("1000results/*.results")
    
    if not file_paths or not os.path.exists(ucs_file):
        print("Nenhum arquivo .results ou arquivo ucs.results encontrado.")
    else:
        # Ler e processar arquivos
        data = read_and_process_files(file_paths, ucs_file)
        
        # Gerar gráficos combinados com médias em grupos
        plot_combined_graphs(data)
        print("Gráficos gerados na pasta 'graph'.")

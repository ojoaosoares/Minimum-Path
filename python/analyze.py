import pandas as pd
import matplotlib.pyplot as plt
import glob

def read_files(file_paths):
    """
    Lê os arquivos fornecidos e retorna um dicionário com DataFrames.
    """
    data = {}
    for file in file_paths:
        algo_name = file.split('/')[-1].split('.')[0]  # Usa o nome do arquivo como chave
        data[algo_name] = pd.read_csv(file, sep=r'\s+', header=None, names=[
            "Path_Size", "Path_Nodes", "Expanded_Nodes", "Execution_Time"])
    return data

def calculate_means(data):
    """
    Calcula as médias de cada métrica para cada algoritmo.
    """
    means = {}
    for algo_name, df in data.items():
        means[algo_name] = {
            "Média do tamanho do caminho": df["Path_Size"].mean(),
            "Média da quantidade de nós no caminho": df["Path_Nodes"].mean(),
            "Média de nós expandidos": df["Expanded_Nodes"].mean(),
            "Média de tempo de execução (ms)": df["Execution_Time"].mean()
        }
    return pd.DataFrame.from_dict(means, orient="index")

def plot_means(mean_df):
    """
    Gera gráficos comparativos das médias de cada métrica, utilizando escala logarítmica e eixos Y descritivos.
    """
    # Configurar estilo
    plt.style.use("ggplot")

    # Define rótulos descritivos para o eixo Y
    y_labels = {
        "Média do tamanho do caminho": "Tamanho do Caminho",
        "Média da quantidade de nós no caminho": "Quantidade de Nós no Caminho",
        "Média de nós expandidos": "Nós Expandidos",
        "Média de tempo de execução (ms)": "Tempo de Execução (ms)"
    }
    
    colors = ["blue", "green", "red", "purple"]

    for metric, color in zip(mean_df.columns, colors):
        plt.figure(figsize=(8, 5))
        plt.bar(mean_df.index, mean_df[metric], color=color, alpha=0.7)
        
        # Definir a escala logarítmica no eixo y
        plt.yscale('log')
        
        # Configuração de título e rótulos
        plt.title(metric, fontsize=12)  # Título mais curto para evitar cortes
        plt.xlabel("Algoritmos")
        plt.ylabel(y_labels.get(metric, metric))
        plt.xticks(rotation=45)

        # Ajustar layout e margem superior
        plt.tight_layout()
        plt.subplots_adjust(top=0.9)  # Ajusta margem superior para o título
        
        # Salvar o gráfico
        plt.savefig(f"graph/{metric.replace(' ', '_')}_comparison_log.png")
        plt.show()

if __name__ == "__main__":
    # Obter arquivos do diretório "results"
    file_paths = glob.glob("results/*.results")  # Ajuste o padrão conforme necessário
    
    if len(file_paths) < 2:
        print("Por favor, forneça pelo menos dois arquivos para comparar.")
    else:
        # Ler arquivos
        data = read_files(file_paths)
        
        # Calcular as médias
        mean_df = calculate_means(data)
        print("Médias calculadas:")
        print(mean_df)
        
        # Gerar gráficos comparativos
        plot_means(mean_df)

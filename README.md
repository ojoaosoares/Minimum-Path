# Algoritmos de Busca em Grafos

## Introdução

Este programa implementa diversos algoritmos de busca em grafos para encontrar o menor caminho entre dois pontos em um mapa. Ele suporta os seguintes algoritmos:

- **BFS**: Busca em Largura
- **IDS**: Busca em Profundidade Iterativa
- **UCS**: Busca de Custo Uniforme (Dijkstra)
- **Greedy**: Busca Gulosa
- **A***: Busca A*
- **DFS**: Busca em Profundidade
- **BSIDS**: Busca Binária com IDS

O programa oferece diferentes saídas dependendo das opções fornecidas na execução.

---

## Pré-requisitos

### Compilador necessário
- **g++** 

### Instalando o g++ no Ubuntu

Use o seguinte comando para instalar o g++ no Ubuntu:

```bash
sudo apt update && sudo apt install -y g++
```
## Como compilar

O projeto já inclui um arquivo Makefile para facilitar a compilação. Para compilar o programa, basta executar o seguinte comando na raiz do projeto:

```bash
make
```

Isso irá compilar o código e gerar o executável chamado `pathfinder` na pasta `bin`.

## Como Executar

O programa requer no mínimo 6 parâmetros de entrada:

1. **Diretório do Mapa**: O arquivo de mapa a ser utilizado.
2. **Algoritmo**: O algoritmo de busca a ser utilizado. Os algoritmos disponíveis são:
    - **BFS** (Busca em Largura)
    - **IDS** (Busca Iterativa em Profundidade)
    - **UCS** (Busca de Custo Uniforme)
    - **Greedy** (Busca Gulosa)
    - **Astar** (Busca A*)
    - **DFS** (Busca em Profundidade)
    - **BSIDS** (Busca Binária em IDS)

3. **Coordenada Inicial**: As coordenadas X e Y do ponto inicial.
4. **Coordenada Final**: As coordenadas X e Y do ponto final.
5. **stats(parametro opcional)**: Esse parametro indica que queremos as métricas do algoritimo

### Comportamento da Saída

1. **Sem o parâmetro `stats`:**  
   A saída será:
   - **Custo do Caminho:** O custo total do caminho encontrado. Se nenhum caminho for encontrado, o valor será `-1`.
   - **Coordenadas do Caminho:** Uma lista de coordenadas no formato `(x, y)` representando o caminho encontrado.

2. **Com o parâmetro `stats`:**  
   A saída será composta de:
   - **Custo do Caminho:** O custo total do caminho encontrado.
   - **Número de Nós do Caminho:** A quantidade de nós que compõem o caminho.
   - **Nós Expandidos:** A quantidade total de nós expandidos durante a busca.
   - **Tempo de Execução:** O tempo total de execução (em segundos, como um número flutuante).

### Exemplo de Execução

```bash
./pathfinder mapa.txt BFS 0 0 5 5
```
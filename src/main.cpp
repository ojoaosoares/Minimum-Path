#include "map.hpp"
#include "bfs.hpp"
#include "dijkstra.hpp"
#include "astar.hpp"
#include "greedy.hpp"
#include "dfs.hpp"
#include "ids.hpp"
#include <iostream>
#include <map>
#include <chrono> // Para medir o tempo

using namespace std;

typedef long long ll;

#define BFS_ID 1
#define IDS_ID 2
#define UCS_ID 3
#define Greedy_ID 4
#define Astar_ID 5
#define DFS 6

map<string, int> methodMap = {
    {"BFS", BFS_ID},
    {"IDS", IDS_ID},
    {"UCS", UCS_ID},
    {"Greedy", Greedy_ID},
    {"Astar", Astar_ID},
    {"DFS", DFS}
};

vector<pair<ll, ll>> readCoordinates(const string& filename) {
    vector<pair<ll, ll>> coordinates;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return coordinates;
    }

    string line;
    while (getline(file, line)) { // Lê linha por linha
        istringstream ss(line); // Cria um stream para processar a linha
        string token;

        while (getline(ss, token, ' ')) { // Divide a linha nos espaços
            if (token.empty()) continue; // Ignora tokens vazios

            if (token.front() == '(' && token.back() == ')') { // Verifica se o token é um par de coordenadas
                token = token.substr(1, token.size() - 2); // Remove os parênteses
                istringstream pairStream(token);
                string xStr, yStr;

                if (getline(pairStream, xStr, ',') && getline(pairStream, yStr)) {
                    int x = stoi(xStr); // Converte x para inteiro
                    int y = stoi(yStr); // Converte y para inteiro
                    coordinates.emplace_back(x, y); // Adiciona o par ao vetor
                }
            }
        }
    }

    file.close();
    return coordinates;
}

int main(int argc, char const *argv[])
{
    if (argc >= 7)
    {

        string mapFilename = argv[1];
        string algId = argv[2];    

        vector<vector<char>> map = readMap(mapFilename);

        ll x1 = (ll) atoi(argv[3]);
        ll y1 = (ll) atoi(argv[4]);

        ll x2 = (ll) atoi(argv[5]);
        ll y2 = (ll) atoi(argv[6]);

        try
        {
            ll rows = map.size(), cols = map[0].size();

            if (y1 < 0 || y1 >= rows || y2 < 0 || y2 >= rows || x1 < 0 || x1 >= cols || x1 < 0 || x2 >= cols)
                throw out_of_range("Coordinates out of range");

            if (map[y1][x1] == WALL || map[y2][x2] == WALL)
                throw invalid_argument("Coordinates invalid");

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return 0;
        }
        
        auto methodMapIt = methodMap.find(algId);

        pair<results, vector<pair<ull, ull>>> resultAndPath;

        std::chrono::high_resolution_clock::time_point start, end;

        if (methodMapIt != methodMap.end())
            switch (methodMapIt->second)
            {
            case BFS_ID:
                start = std::chrono::high_resolution_clock::now();
                resultAndPath = bfs(map, x1, y1, x2, y2);
                end = std::chrono::high_resolution_clock::now();
                break;
            case IDS_ID:
                start = std::chrono::high_resolution_clock::now();
                resultAndPath = ids(map, x1, y1, x2, y2);
                end = std::chrono::high_resolution_clock::now();
                break;
            case UCS_ID:
                start = std::chrono::high_resolution_clock::now();
                resultAndPath = dijkstra(map, x1, y1, x2, y2);
                end = std::chrono::high_resolution_clock::now();
                break;
            case Greedy_ID:
                start = std::chrono::high_resolution_clock::now();
                resultAndPath = greedy(map, x1, y1, x2, y2);
                end = std::chrono::high_resolution_clock::now();
                break;
            case Astar_ID:
                start = std::chrono::high_resolution_clock::now();
                resultAndPath = astar(map, x1, y1, x2, y2);
                end = std::chrono::high_resolution_clock::now();
                break;
            case DFS:
                start = std::chrono::high_resolution_clock::now();
                resultAndPath = dfs(map, x1, y1, x2, y2);
                end = std::chrono::high_resolution_clock::now();
                break;
            default:
                cout << "Unknown method\n";
                return 1;
            }   

        else
        {
            cout << "Unknown method\n";
            return 1;
        }

        cout << resultAndPath.first.distance << ' ';

        if (argc == 8 && string(argv[7]) == "stats")
        {
            cout << "Size of the path: " << resultAndPath.second.size() << '\n' << "Nodes reached: " << resultAndPath.first.nodesReached << '\n'
            << "Nodes analyzed: " <<  resultAndPath.first.nodesAnalyzed << '\n' << "Nodes explored: " << resultAndPath.first.nodesExplored << '\n';
            std::chrono::duration<double> duracao = end - start;
            cout << "Tempo de execução: " << duracao.count() << " segundos\n";

            return 0;
        }

        for (pair<ull, ull> coor : resultAndPath.second)
        cout << '(' << coor.first << ',' << coor.second << ") ";
    
        cout << '\n';
        
        return 0;
    }

    if (argc == 3)
    {
        string mapFilename = argv[1];
        string pathFilename = argv[2];

        vector<vector<char>> map = readMap(mapFilename);        
        vector<pair<ll, ll>> path = readCoordinates(pathFilename);

        double total = 0;

        for (auto it = path.begin() + 1; it != path.end(); it++)
            total += terrain_types[map[it->second][it->first]];   
        
        cout << total << '\n';

        return 0;
        
    }


    return 1;
}

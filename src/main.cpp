#include "map.hpp"
#include "bfs.hpp"
#include "dijkstra.hpp"
#include "astar.hpp"
#include <iostream>
#include <map>

using namespace std;

typedef long long ll;

#define BFS_ID 1
#define IDS_ID 2
#define UCS_ID 3
#define Greedy_ID 4
#define Astar_ID 5

map<string, int> methodMap = {
    {"BFS", BFS_ID},
    {"IDS", IDS_ID},
    {"UCS", UCS_ID},
    {"Greedy", Greedy_ID},
    {"Astar", Astar_ID}
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
    if (argc == 7)
    {

        string mapFilename = argv[1];
        string algId = argv[2];

        ll startX = (ll) atoi(argv[3]);
        ll startY = (ll) atoi(argv[4]);

        ll endX = (ll) atoi(argv[5]);
        ll endY = (ll) atoi(argv[6]);    

        vector<vector<char>> map = readMap(mapFilename);
        
        auto methodMapIt = methodMap.find(algId);

        pair<double, vector<pair<ull, ull>>> sizeAndPath;

        if (methodMapIt != methodMap.end())
            switch (methodMapIt->second)
            {
            case BFS_ID:
                sizeAndPath = bfs(map, startX, startY, endX, endY);
                break;
            case IDS_ID:
                /* code */
                break;
            case UCS_ID:
                sizeAndPath = dijkstra(map, startX, startY, endX, endY);
                break;
            case Greedy_ID:
                /* code */
                break;
            case Astar_ID:
                sizeAndPath = astar(map, startX, startY, endX, endY);
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

        cout << sizeAndPath.first << ' ';

        for (pair<ull, ull> coor : sizeAndPath.second)
            cout << '(' << coor.first << ',' << coor.second << ") ";
        
        cout << '\n';
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
        
    }


    return 1;
}

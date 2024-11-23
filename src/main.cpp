#include "map.hpp"
#include "bfs.hpp"
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

int main(int argc, char const *argv[])
{
    if (argc != 7)
        return 1;

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
            /* code */
            break;
        case Greedy_ID:
            /* code */
            break;
        case Astar_ID:
            /* code */
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
        cout << '(' << coor.first << ", " << coor.second << ") ";
    
    cout << '\n';
    


    return 0;
}

#include <string>

using namespace std;

typedef long long ll;

int main(int argc, char const *argv[])
{
    if (argc != 7)
        return 1;

    string mapfilepath = argv[1];
    string algId = argv[2];

    ll startX = atoi(argv[3]);
    ll startY = atoi(argv[4]);

    ll endX = atoi(argv[5]);
    ll endY = atoi(argv[6]);    

    return 0;
}

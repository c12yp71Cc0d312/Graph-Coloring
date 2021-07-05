#include <bits/stdc++.h>
#include <vector>
#include <unordered_set>
using namespace std;

bool rainbowNeighborhood(vector<vector<int>> adj, int x, vector<int> colors, int c) {

    if(adj[x].size() < c-1)
        return false;

    bool colorPresent[c];

    colorPresent[colors[x] - 1] = 1;

    for(int i = 0; i < adj[x].size(); i++) {

        colorPresent[colors[adj[x][i]] - 1] = 1;

    }

    for(int i = 0; i < c; i++) {
        if(colorPresent[i] == 0)
            return false;
    }

    return true;

}

// int main() {
// 	int n;
// 	vector<node> vert(n);
// 	vector<node> vv(5);
// 	vv = { {1, {2, 3}}, {2, {1, 3}}, {3, {1,2,4,5}}, {1, {3}}, {1, {3}} };
// 	unordered_set<int> :: iterator itrr;
// 	for(int i = 0; i< n; i++)
// 	{
// 	    vert[i].clr = -1;
// 	}
//     rainbowNeighbor(vv, 5, 3);

//     cout<<"\n\n";
//     system("pause");
//     return 0;
// }
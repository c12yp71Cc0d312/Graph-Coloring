#include<bits/stdc++.h>
using namespace std;
//hello mohan
// #define V 4
 
void printSolution(vector<int> color, int V);


bool isSafe(vector<vector<bool>> graph, vector<int> color, int V)
{
    for (int i = 0; i < V; i++)
        for (int j = i + 1; j < V; j++)
            if (graph[i][j] && color[j] == color[i])
                return false;
    return true;
}

bool graphColoring(vector<vector<bool>> graph, int m, int i, vector<int> color, int V)
{
    if (i == V) {
       
        if (isSafe(graph, color, V)) {
            printSolution(color, V);
            return true;
        }
        return false;

    }
 
    for (int j = 1; j <= m; j++) {
        color[i] = j;
 
        if (graphColoring(graph, m, i + 1, color, V))
            return true;
 
        color[i] = 0;
    }
 
    return false;
}
 
void printSolution(vector<int> color, int V)
{
    cout << "Solution Exists:" " Following are the assigned colors \n";
    for (int i = 0; i < V; i++)
        cout << "  " << color[i];
    cout << "\n";
}

void kChromaticValidation(vector<vector<int>> adj, int v, int k) {

    vector<bool> zeroVec(v, 0);
    vector<vector<bool>> adjMat(v, zeroVec);

    for(int i = 0; i < v; i++) {

        for(int j = 0; j < adj[i].size(); j++) {

            adjMat[i][adj[i][j]] = 1;

        }

    }

    vector<int> color(v, 0);
    
    if (!graphColoring(adjMat, k, 0, color, v))
        cout << "Solution does not exist";


}
 
// int main()
// {
//     bool graph[V][V] = {
//         { 0, 1, 1, 1 },
//         { 1, 0, 1, 0 },
//         { 1, 1, 0, 1 },
//         { 1, 0, 1, 0 },
//     };
//     int m = 3; 
 
//     int color[V];
//     for (int i = 0; i < V; i++)
//         color[i] = 0;
 
//     if (!graphColoring(graph, m, 0, color))
//         cout << "Solution does not exist";
 
//     return 0;
// }
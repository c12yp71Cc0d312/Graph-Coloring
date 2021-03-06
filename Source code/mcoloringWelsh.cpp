#include <stdbool.h>
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;
 
// #define V 4
 
void printSolution(int color[], int V);
 
bool isSafe(int v, vector<vector<int>> graph, int color[], int c, int V)
{
    for (int i = 0; i < V; i++)
        if (
            graph[v][i] && c == color[i])
            return false;
    return true;
}
 
bool graphColoringUtil(vector<vector<int>> graph, int m, int color[], int v, int V)
{
    if (v == V)
        return true;
 
    for (int c = 1; c <= m; c++) {

        if (isSafe(v, graph, color, c, V)) {
            color[v] = c;
 
            if (graphColoringUtil(graph, m, color, v + 1, V) == true)
                return true;
 
            color[v] = 0;
        }
    }
 
    return false;
}
 
bool kChromaticValidation(vector<vector<int>> graph, int V, int m)
{
    int color[V];
    for (int i = 0; i < V; i++)
        color[i] = 0;
 
    if (graphColoringUtil(graph, m, color, 0, V) == false) {
        printf("Solution does not exist");
        return false;
    }
 
    printSolution(color, V);
    return true;
}
 
void printSolution(int color[], int V)
{
    printf(
        "Solution Exists:"
        " Following are the assigned colors \n");
    for (int i = 0; i < V; i++)
        printf(" %d ", color[i]);
    printf("\n");
}
 
// int main()
// {
//     /* Create following graph and test
//        whether it is 3 colorable
//       (3)---(2)
//        |   / |
//        |  /  |
//        | /   |
//       (0)---(1)
//     */
//    vector< vector<int>> g;
//     bool graph[V][V] = {
//         { 0, 1, 1, 1 },
//         { 1, 0, 1, 0 },
//         { 1, 1, 0, 1 },
//         { 1, 0, 1, 0 },
//     };
//     int m = 3; // Number of colors
//     graphColoring(graph, m);
//     return 0;
// }
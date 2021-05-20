#include <bits/stdc++.h>
#include <vector>
#include <unordered_set>
using namespace std;

int countEdges(vector< vector<int> > adj, int v) {
    int sum = 0;
    for (int i = 0 ; i < v ; i++)
        sum += adj[i].size();
  
    return sum/2;
}

void mergeVertices(vector< vector<int> > &adj, int u, int v) {

    for(int i = 0; i < adj.size(); i++) {

        bool uNeighbor = false;
        int vIndex = -1;

        for(int j = 0; j < adj[i].size(); j++) {

            if(adj[i][j] == u) {
                uNeighbor = true;
            }

            if(adj[i][j] == v) {
                adj[i][j] = u;
                vIndex = j;
            }

            if(adj[i][j] > v) {
                adj[i][j]--;
            }

        }

        if(uNeighbor && (vIndex != -1)) {
            adj[i].erase(adj[i].begin() + vIndex);
        }

    }

    for(int i = 0; i < adj[v].size(); i++) {

        if(!(find(adj[u].begin(), adj[u].end(), adj[v][i]) != adj[u].end())) {
            adj[u].push_back(adj[v][i]);
        }

    }

    adj.erase(adj.begin() + v);

}

void add_edge(vector< vector<int> > &adj, int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}
 
void print_graph(vector< vector<int> > adj, int V)
{
    for (int v = 0; v < V; ++v)
    {
        cout << "\n Adjacency list of vertex " << v << "\n head ";
        for (int i = 0; i < adj[v].size(); i++)
           cout << " -> " << adj[v][i];
        cout<<endl;
    }
}

void chromaticPolynomial(vector< vector<int> > adj, int v, int e, vector<int> &k) {

    if(e == (v*(v-1))/2) {
        k[v]++;
        return;
    }

    vector< vector<int> > a = adj;
    vector< vector<int> > b = adj;

    bool abModified = false;

    for(int i = 0; i < v; i++) {

        if(adj[i].size() != v-1) {

            for(int j = 0; j < v; j++) {

                if(j == i)
                    continue;

                if(!(find(adj[i].begin(), adj[i].end(), j) != adj[i].end())) {

                    add_edge(a, i, j);

                    mergeVertices(b, i, j);

                    abModified = true;

                    break;

                }

            }

        }

        if(abModified)
            break;

    }

    chromaticPolynomial(a, v, e+1, k);
    chromaticPolynomial(b, v-1, countEdges(b, v-1), k);

    return;

    //return ( chromaticPolynomial(a, v, e+1, k) + " + " + chromaticPolynomial(b, v-1, countEdges(b, v-1), k) );

}

string generatePoly(int V, vector<int> k) {

    string polynomial;

    bool first = true;
    
    for(int i = 1; i <= V; i++) {

        if(k[i] == 0)
            continue;

        string poly;

        if(k[i] == 1)
            poly = "x";

        if(k[i] > 1)
            poly = to_string(k[i]) + "x";

        for(int j = 1; j < i; j++) {
            poly += "(x - " + to_string(j) + ")";
        }

        if(first) {
            first = false;
            polynomial = poly;
        }
            

        else {
            polynomial += " + " + poly;
        }

    }

    return polynomial;

}

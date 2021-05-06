#include <bits/stdc++.h>
#include <vector>
#include <unordered_set>
using namespace std;

int countEdges(vector< vector<int> > adj, int v)
{
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

// A utility function to add an edge in an
// undirected graph.
void addEdge(vector< vector<int> > &adj, int u, int v)
{
    adj[u].push_back({v});
    adj[v].push_back({u});
}
 
// A utility function to print the adjacency list
// representation of graph
void printGraph(vector< vector<int> > adj, int V)
{
    for (int v = 0; v < V; ++v)
    {
        cout << "\n Adjacency list of vertex " << v << "\n head ";
        for (int i = 0; i < adj[v].size(); i++)
           cout << " -> " << adj[v][i];
        printf("\n");
    }
}

void chromaticPolynomial(vector< vector<int> > adj, int v, int e, vector<int> &k) {

    if(e == (v*(v-1))/2) {

        // string poly = "x";
        // for(int i = 1; i < v; i++) {
        //     poly += "(x - " + to_string(i) + ")";
        // }
        //return poly;

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

                    addEdge(a, i, j);

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

int main() {

    int V = 5;
    int E = 7;
    vector< vector<int> > adj(V);
    vector<int> k(V+1, 0);
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 4);
    addEdge(adj, 1, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 1, 4);
    addEdge(adj, 2, 3);
    addEdge(adj, 3, 4);
    //printGraph(adj, V);

    //cout<<chromaticPolynomial(adj,V,E,k);
    chromaticPolynomial(adj,V,E,k);

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

    cout<<polynomial;

    cout<<"\n\n0 to exit";
    int t;
    cin>>t;
    return 0;

// 	int n;
// 	cout<<"enter the no of vertices in the graph: ";
// 	cin>>n;
// 	vector< vector<int> > f(n);
//     vector<int> colors(n,-1);
//     for(int i =0;i<n;i++){
//         cout<<"\nEnter the no of nieghbours of "<<i+1<<"\n";
//         int t;
//         cin>>t;
//         cout <<"Enter the nieghbours\n";     
//         for(int k=0;k<t;k++){
//             int r;
//             cin>>r;
//             f[i].push_back(r);
//         }
        
//     }
//     cout<<"\n\n";
//     //unordered_set<int> :: iterator itr;
//    /* for(int i=0;i<n;i++){
//        for (itr = f[i].begin(); itr != f[i].end(); itr++)
//         cout << *itr << " ";
//        cout<<"\n";
//     }
//     */
// 	//okk now we need to implement neighbor coloring....as mentioned in line 16
//     Wigderson(f,n,colors);
//     for(int i=0;i<colors.size();i++)
//     cout<<"vertex"<<i+1<<"\t"<<colors[i]<<"\n";

//     return 0;
}
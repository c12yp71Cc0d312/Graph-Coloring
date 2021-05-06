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

        }

        if(uNeighbor && (vIndex != -1)) {
            adj[i].erase(adj[i].begin() + vIndex);
        }

    }

}

// A utility function to add an edge in an
// undirected graph.
void addEdge(vector< vector<int> > &adj, int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
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

/*return type*/ chromaticPolynomial(vector< vector<int> > adj, int v, int e) {

    if(e = (v*(v-1))/2 ) {

        //return chromatic polynomial of complete graph with v vertices

    }

    vector< vector<int> > a = adj;
    vector< vector<int> > b = adj;

    for(int i = 0; i < v; i++) {

        if(adj[i].size() != v-1) {

            for(int j = 0; j < v; j++) {

                if(j == i)
                    continue;

                addEdge(a, i, j);

                mergeVertices(adj, i, j);

            }

        }

    }

    return chromaticPolynomial(a, v, e+1) + chromaticPolynomial(b, v-1, countEdges(b, v-1));

}

int main() {

    int V = 5;
    int E = 7;
    vector< vector<int> > adj(V);
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 4);
    addEdge(adj, 1, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 1, 4);
    addEdge(adj, 2, 3);
    addEdge(adj, 3, 4);
    printGraph(adj, V);

    cout<<"\n0 to exit";
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
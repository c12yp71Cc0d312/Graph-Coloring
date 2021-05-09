#include <bits/stdc++.h>
#include <vector>
#include <unordered_set>
#include "chromaticpoly.cpp"
#include "rainbow.cpp"
#include "mcoloring.cpp"
using namespace std;

// struct node {
//     int clr;
//     unordered_set<int> neigh;
// };

// void rainbowNeighbor(vector<node> vert, int n, int k) {
//     for(int i =0; i<n; i++)
//     {
//         cout << "vertex " << i+1 <<endl;
//         unordered_set<int> :: iterator itr;
//         unordered_set<int> tempClr;
//         for(itr = vert[i].neigh.begin(); itr != vert[i].neigh.end(); itr++)
//         {
//             tempClr.insert(vert[*itr-1].clr);
//             cout << vert[*itr-1].clr << endl;
//         }
//         if(tempClr.size() == k-1)
//             cout << "size is k-1 hence this vertex is a rainbow Neighbor" << endl;
//     }
// }


void greedyColor(vector< vector<int> > g, vector<int> &colors, int &maxC, bool addVertex) {

	int n = g.size();
	
	int c;
	
	if(addVertex) {

		int i = g.size() - 1;

		for(int j = 1; j <= maxC; j++) {

			c = j;
			
			bool canColor = true;
			
			for(int k = 0; k < g[i].size(); k++) {
				
				if(colors[g[i][k]] == c) {
					canColor = false;
					break;
				}
				
			}
			
			if(canColor) {
				colors[i] = c;
				break;
			}
				
		}
		
		if(colors[i] == -1) {
			maxC++;
			colors[i] = maxC;
		}

		return;
	}


	for(int i = 0; i < n; i++) {
		
		for(int j = 1; j <= maxC; j++) {
			
			c = j;
			
			bool canColor = true;
			
			for(int k = 0; k < g[i].size(); k++) {
				
				if(colors[g[i][k]] == c) {
					canColor = false;
					break;
				}
				
			}
			
			if(canColor) {
				colors[i] = c;
				break;
			}
				
			
		}
		
		if(colors[i] == -1) {
			maxC++;
			colors[i] = maxC;
		}
		
	}
	
	for(int i = 0; i < n; i++) {
		
		cout<<"\ncolor of vertex "<<i+1<<" is: "<<colors[i];
		
	}
	
}

void addEdge(vector< vector<int> > &adj, int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void printGraph(vector< vector<int> > adj, int V)
{
    for (int v = 0; v < V; ++v)
    {
        cout << "\n Adjacency list of vertex " << v+1 << "\n head ";
        for (int i = 0; i < adj[v].size(); i++)
           cout << " -> " << adj[v][i]+1;
        cout<<endl;
    }
}

void add_vertex(vector< vector<int> > &adj, int &maxC, vector<int> &colors, int &v, int &e) {

	int t;
	cout<<"\n\nenter no of neighbors of new vertex: ";
	cin>>t;

	int x = adj.size();

	adj.resize(x+1);
	//adjMat[x] = new int[x+1];
	colors.push_back(-1);

	// vector<int> zeroVec(n, 0);
	// adjMat.push_back(zeroVec);

	// for(int i = 0; i < x+1; i++) {
	// 	adjMat[x][i] = 0;
	// }

	cout<<"enter the neighbors: ";
	for(int i = 0; i < t; i++) {

		int n;
		cin>>n;

		adj[n-1].push_back(x);
		adj[x].push_back(n-1);

		// adjMat[x][n-1] = 1;

	}

	greedyColor(adj, colors, maxC, true);

	v++;
	e += t;

}

void delete_vertex(vector< vector<int> > &adj, vector<int> &colors, int &v, int &e) {

	int x;
	cout<<"\n\nenter vertex to be deleted: ";
	cin>>x;
	x--;

	int t = adj[x].size();

	adj.erase(adj.begin() + x);
	colors.erase(colors.begin() + x);

	for(int i = 0; i < adj.size(); i++) {

		vector<int> neighbors;

		for(int j = 0; j < adj[i].size(); j++) {

			if(adj[i][j] == x)
				continue;

			if(adj[i][j] > x)
				neighbors.push_back(adj[i][j] - 1);
			
			else
				neighbors.push_back(adj[i][j]);

		}

		adj.erase(adj.begin() + i);
		adj.emplace(adj.begin() + i, neighbors);

	}

	cout<<"\nadj updated";

	v--;
	e -= t;

}

int main() {

	int V, E;

    cout<<"enter the no of vertices: ";
    cin>>V;
    vector< vector<int> > adj(V);

    cout<<"enter the no of edges: ";
    cin>>E;

    cout<<"\nenter the edges (start vertex   end vertex):\n";
    for(int i = 0; i < E; i++) {

        int u, v;
        cin>>u>>v;

        addEdge(adj, u-1, v-1);

    }

	vector<int> colors(V, -1);
	int maxC = 1;

	greedyColor(adj, colors, maxC, false);

	/*  Call insert funcion */
	add_vertex(adj, maxC, colors, V, E);

	cout<<"\n";
	printGraph(adj, V);
	cout<<"\n";

	/*  Call delete funcion */
	delete_vertex(adj, colors, V, E);

	cout<<"\n";
	printGraph(adj, V);
	cout<<"\n";	
	
	/*  Call chromatic validator funcion */
	int y;
	cout<<"\n\nenter no of colors to check whether graph can be colored with: ";
	cin>>y;
	kChromaticValidation(adj, V, y);


	/*  Call rainbow funcion */
	int x;
    cout<<"\nenter the vertex to check for rainbow neighborhood: ";
    cin>>x;
	bool rainbow = rainbowNeighborhood(adj, x-1, colors, maxC);
	if(rainbow)
		cout<<"\nvertex "<<x<<" is in a rainbow neighborhood";
	else
		cout<<"\nvertex "<<x<<" is not in a rainbow neighborhood";

	/*  Call chromatic polynomial funcion */
	vector<int> k(V+1, 0);
	chromaticPolynomial(adj,V,E,k);
    string polynomial = generatePoly(V, k);
    cout<<"\n\nthe chromatic polynomial is:\n";
    cout<<polynomial;


	cout<<"\n\n";
    system("pause");
	return 0;
}
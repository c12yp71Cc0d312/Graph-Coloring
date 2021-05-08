#include <bits/stdc++.h>
#include <vector>
using namespace std;

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

void add_vertex(vector< vector<int> > &adj, int &maxC, vector<int> &colors, int &n) {

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

	n++;

}

void delete_vertex(vector< vector<int> > &adj, vector<int> &colors, int &n) {

	int x;
	cout<<"\n\nenter vertex to be deleted: ";
	cin>>x;
	x--;

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

	n--;

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

	add_vertex(adj, maxC, colors, V);

	cout<<"\n";
	printGraph(adj, V);
	cout<<"\n";

	delete_vertex(adj, colors, V);

	cout<<"\n";
	printGraph(adj, V);
	cout<<"\n";

	
	cout<<"\n\n";
    system("pause");
	return 0;
}
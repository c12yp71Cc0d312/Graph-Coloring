//add now
#include <bits/stdc++.h>
#include <vector>
#include <queue>
using namespace std;

struct NodeDegree {
	
	int nodeNum;
	int deg;
	
	//comparator
	bool operator<(const NodeDegree& rhs) const
    {
        return deg < rhs.deg;
    }
	
};

int** createAdjMat(vector< vector<int> > adj, int n) {

	int** adjMat = 0;
	adjMat = new int*[n];

	for(int i = 0; i < n; i++) {

		adjMat[i] = new int[n];

		for(int j = 0; j < n; j++) {

			adjMat[i][j] = 0;

		}

	}

	for(int i = 0; i < n; i++) {

		for(int j = 0; j < adj[i].size(); j++) {

			adjMat[i][adj[i][j]] = 1;

		}

	}

	return adjMat;
}

void WPALGO(int** adjMat, int n, int &c, vector<int> &nodeColor) {
	
	priority_queue<NodeDegree> nodes;
	
	//init
	//vector<int> nodeColor(n, -1);
	
	for(int i = 0; i < n; i++) {
		
		NodeDegree node;
		int deg = 0;
		
		for(int j = 0; j < n; j++) {
			
			if(adjMat[i][j] == 1) {
				deg++;
			}
			
		}
		
		node = {i, deg};
		nodes.push(node);
		
	}
	
	//int c = 1;
	
	while(nodes.size() > 0) {
		
		int highestDegVertex = nodes.top().nodeNum;
		
		if(nodeColor[highestDegVertex] != -1) {
			nodes.pop();
			continue;
		}

		
		for(int i = 0; i < n; i++) {
			
			if(adjMat[highestDegVertex][i] == 0 && nodeColor[i] == -1) {
				
				nodeColor[i] = c;
				
			}
			
		}
		
		c++;
		nodes.pop();
		
	}
	
	for(int i = 0; i < n; i++) {
		
		cout<<"\ncolor of node "<<i+1<<" is "<<nodeColor[i];
		
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
        cout << "\n Adjacency list of vertex " << v << "\n head ";
        for (int i = 0; i < adj[v].size(); i++)
           cout << " -> " << adj[v][i];
        cout<<endl;
    }
}

void colorVertex(vector<vector <int> > adj, int x, int &c, vector<int> &nodeColor) {

	for(int col = 1; col < c; col++) {

		bool colorChosen = true;

		for(int i = 0; i < adj[x].size(); i++) {
		
			if(nodeColor[adj[x][i]] == col) {
				colorChosen = false;
				break;
			}

		}

		if(colorChosen) {
			nodeColor[x] = col;
			break;
		}

	}

	if(nodeColor[x] == -1) {
		nodeColor[x] = c;
		c++;
	}

	cout<<"\ncolor of new vertex is "<<nodeColor[x];
	

}

void add_vertex(vector< vector<int> > &adj, int** &adjMat, int &c, vector<int> &nodeColor) {

	int t;
	cout<<"\n\nenter no of neighbors of new vertex: ";
	cin>>t;

	int x = adj.size();

	adj.resize(x+1);
	adjMat[x] = new int[x+1];
	nodeColor.push_back(-1);

	for(int i = 0; i < x+1; i++) {
		adjMat[x][i] = 0;
	}

	cout<<"enter the neighbors: ";
	for(int i = 0; i < t; i++) {

		int n;
		cin>>n;

		adj[n-1].push_back(x);
		adj[x].push_back(n-1);

		adjMat[x][n-1] = 1;

	}

	colorVertex(adj, x, c, nodeColor);

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


	int** adjMat = createAdjMat(adj, V);

	cout<<"\n";
	printGraph(adj, V);
	cout<<"\n";

	int c = 1;
	vector<int> nodeColor(V, -1);

	WPALGO(adjMat, V, c, nodeColor);

	add_vertex(adj, adjMat, c, nodeColor);

	cout<<"\n\n";
    system("pause");
	return 0;
}


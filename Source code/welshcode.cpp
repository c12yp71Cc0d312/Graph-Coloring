//add now
#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include "chromaticpoly.cpp"
#include "rainbow.cpp"
#include "mcoloring.cpp"
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


vector<vector<int>> createAdjMat(vector< vector<int> > adj, int n) {

	// int** adjMat = 0;
	// adjMat = new int*[n];

	vector<int> zeroRow(n, 0);
	vector< vector<int> > adjMat(n, zeroRow);

	// for(int i = 0; i < n; i++) {

	// 	adjMat[i] = new int[n];

	// 	for(int j = 0; j < n; j++) {

	// 		adjMat[i][j] = 0;

	// 	}

	// }

	for(int i = 0; i < n; i++) {

		for(int j = 0; j < adj[i].size(); j++) {

			adjMat[i][adj[i][j]] = 1;

		}

	}

	return adjMat;
}

void WPALGO(vector< vector<int> > adjMat, int n, int &c, vector<int> &nodeColor) {
	
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
        cout << "\n Adjacency list of vertex " << v+1 << "\n head ";
        for (int i = 0; i < adj[v].size(); i++)
           cout << " -> " << adj[v][i]+1;
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

void add_vertex(vector< vector<int> > &adj, vector< vector<int> > &adjMat, int &c, vector<int> &nodeColor, int &v, int &e) {

	int t;
	cout<<"\n\nenter no of neighbors of new vertex: ";
	cin>>t;

	int x = adj.size();

	adj.resize(x+1);
	//adjMat[x] = new int[x+1];
	nodeColor.push_back(-1);

	vector<int> zeroVec(v, 0);
	adjMat.push_back(zeroVec);

	// for(int i = 0; i < x+1; i++) {
	// 	adjMat[x][i] = 0;
	// }

	cout<<"enter the neighbors: ";
	for(int i = 0; i < t; i++) {

		int n;
		cin>>n;

		adj[n-1].push_back(x);
		adj[x].push_back(n-1);

		adjMat[x][n-1] = 1;

	}

	colorVertex(adj, x, c, nodeColor);

	v++;
	e += t;

}

void delete_vertex(vector< vector<int> > &adj, vector< vector<int> > &adjMat, vector<int> &nodeColor, int &v, int &e) {

	int x;
	cout<<"\n\nenter vertex to be deleted: ";
	cin>>x;
	x--;

	int t = adj[x].size();

	adj.erase(adj.begin() + x);
	nodeColor.erase(nodeColor.begin() + x);

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

	//delete [] adjMat[x];
	adjMat.erase(adjMat.begin() + x);

	// cout<<"\nrow x deleted";

	// cout<<"\nn - 1 value"<<v-1;

	for(int i = 0; i < v - 1; i++) {

		cout<<"\ninside row "<<i;

		for(int j = x; j < v - 1; j++) {

			cout<<"\n\tchecking "<<j<<"th ele of the row";

			adjMat[i][j] = adjMat[i][j+1];

		}

		cout<<"\n\tmaking last ele null";

		//adjMat[i][n-1] = -1;
		adjMat[i].pop_back();

		cout<<"\n\tmade last ele null";

	}

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


	vector< vector<int> > adjMat = createAdjMat(adj, V);

	cout<<"\n";
	printGraph(adj, V);
	cout<<"\n";

	int c = 1;
	vector<int> nodeColor(V, -1);

	WPALGO(adjMat, V, c, nodeColor);

	cout<<"\n\nc value is"<<c;

	/*  Call insert funcion */
	add_vertex(adj, adjMat, c, nodeColor, V, E);

	// cout<<"\n";
	// printGraph(adj, V);
	// cout<<"\n";

	/*  Call delete funcion */
	delete_vertex(adj, adjMat, nodeColor, V, E);

	cout<<"\n";
	printGraph(adj, V);
	cout<<"\n";
	
	/*  Call chromatic validator funcion */
	int y;
	cout<<"\n\nenter no of colors to check whether graph can be colored with at max: ";
	cin>>y;
	kChromaticValidation(adj, V, y);

	/*  Call rainbow funcion */
	int x;
    cout<<"\n enter the vertex to check for rainbow neighborhood: ";
    cin>>x;
	bool rainbow = rainbowNeighborhood(adj, x-1, nodeColor, c-1);
	if(rainbow)
		cout<<"\nvertex "<<x<<" is in a rainbow neighborhood";
	else
		cout<<"\nvertex "<<x<<" is not in a rainbow neighborhood";
	
	/*  Call chromatic polynomial funcion */
	vector<int> k(V+1, 0);
	chromaticPolynomial(adj,V,E,k);
    string polynomial = generatePoly(V, k);
    cout<<"\nthe chromatic polynomial is:\n";
    cout<<polynomial;

	cout<<"\n\n";
    system("pause");
	return 0;
}


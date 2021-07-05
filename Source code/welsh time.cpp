//add now
#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include "chromaticpoly.cpp"
#include "rainbow.cpp"
#include "mcoloring.cpp"
using namespace std;
using namespace std::chrono;

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

	vector<int> zeroRow(n, 0);
	vector< vector<int> > adjMat(n, zeroRow);

	for(int i = 0; i < n; i++) {

		for(int j = 0; j < adj[i].size(); j++) {

			adjMat[i][adj[i][j]] = 1;

		}

	}

	return adjMat;
}

void WPALGO(vector< vector<int> > adjMat, int n, int &c, vector<int> &nodeColor) {
	
	priority_queue<NodeDegree> nodes;
	
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

	
}

void addEdge(vector< vector<int> > &adj, int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void printGraph(vector< vector<int> > adj, int V)
{
	cout<<endl;

    for (int v = 0; v < V; ++v)
    {
        cout << "\n Adjacency list of vertex " << v+1 << "\n head ";
        for (int i = 0; i < adj[v].size(); i++)
           cout << " -> " << adj[v][i]+1;
        cout<<endl;
    }

	cout<<endl;
}

void displayColors(vector<int> colors) {

	cout<<endl;

	for(int i = 0; i < colors.size(); i++) {
		
		cout<<"\ncolor of vertex "<<i+1<<" is: "<<colors[i];
		
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

}

void add_vertex(vector< vector<int> > &adj, vector< vector<int> > &adjMat, int &c, vector<int> &nodeColor, int &v, int &e, int cv) {

	int t = 3;
	// cout<<"\n\nenter no of neighbors of new vertex: ";
	// cin>>t;

	int x = adj.size();

	adj.resize(x+1);
	nodeColor.push_back(-1);

	vector<int> zeroVec(v, 0);
	adjMat.push_back(zeroVec);

	// cout<<"enter the neighbors: ";
	// for(int i = 0; i < t; i++) {

	// 	int n;
	// 	cin>>n;

	// 	adj[n-1].push_back(x);
	// 	adj[x].push_back(n-1);

	// 	adjMat[x][n-1] = 1;

	// }

    adj[0].push_back(x);
		adj[x].push_back(0);

		adjMat[x][0] = 1;

    adj[cv].push_back(x);
		adj[x].push_back(cv);

		adjMat[x][cv] = 1;

    adj[cv+1].push_back(x);
		adj[x].push_back(cv+1);

		adjMat[x][cv+1] = 1;

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

	adjMat.erase(adjMat.begin() + x);

	for(int i = 0; i < v - 1; i++) {

		for(int j = x; j < v - 1; j++) {

			adjMat[i][j] = adjMat[i][j+1];

		}

		adjMat[i].pop_back();

	}

	v--;
	e -= t;

}

int main() {

	// int V, E;

    // cout<<"enter the no of vertices: ";
    // cin>>V;
    // vector< vector<int> > adj(V);

    // cout<<"enter the no of edges: ";
    // cin>>E;

    // cout<<"\nenter the edges (start vertex   end vertex):\n";
    // for(int i = 0; i < E; i++) {

    //     int u, v;
    //     cin>>u>>v;

    //     addEdge(adj, u-1, v-1);

    // }

    vector<int> vs;
    vector<long> ts;

    for(int i = 3; i < 50; i++) {

        cout<<"\ni: "<<i;

        int V = i*i;
        int E = 2*i + V - i - 1 - 1;

        vector<vector<int>> adj(V);
        //cout<<"\nvector created";
        int j = 0;

        for(j; j < i - 1; j++) {

            adj[j].push_back(j+1);
            adj[j+1].push_back(j);

        }

        adj[j].push_back(0);
        adj[0].push_back(j);
        //cout<<"\ncircular graph done";
        for(int k = 0; k < i; k++) {

            adj[i].push_back(k);
            adj[k].push_back(i);

        }
        //cout<<"\nstar graph done";
        adj[0].push_back(i+1);
        adj[i+1].push_back(0);
        //cout<<"\nlinear first node added";
        int remNumOfNodes = V - i - 1 - 1;

        for(int m = i + 1; m < i + 1 + remNumOfNodes; m++) {

            adj[m].push_back(m+1);
            adj[m+1].push_back(m);

        }
        //cout<<"\nlinear graph done";

        vector< vector<int> > adjMat = createAdjMat(adj, V);

	    int c = 1;
	    vector<int> nodeColor(V, -1);

        // auto start = high_resolution_clock::now();
	    WPALGO(adjMat, V, c, nodeColor);
        // auto stop = high_resolution_clock::now();

        // auto start = high_resolution_clock::now();
        // add_vertex(adj, adjMat, c, nodeColor, V, E, i);
        // auto stop = high_resolution_clock::now();

        //auto duration = duration_cast<microseconds>(stop - start);

        auto start = high_resolution_clock::now();
        //kChromaticValidation(adj, V, 4);
        int x = rand()%(V-1 + 1);
        bool rainbow = rainbowNeighborhood(adj, x - 1, colors, c);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);

        vs.push_back(V);
        ts.push_back(duration.count());

        // vector<int> colors(V, -1);
	    // int maxC = 1;

        // auto start = high_resolution_clock::now();
	    // greedyColor(adj, colors, maxC, false);
        // auto stop = high_resolution_clock::now();

        // auto duration = duration_cast<microseconds>(stop - start);

        //cout<<"("<<V<<", "<<duration.count() << ")\n";
	    //printGraph(adj, V);
	    //displayColors(colors);



    }

    for(int i = 0; i < vs.size(); i++)
        cout<<vs[i]<<endl;

    for(int i = 0; i < vs.size(); i++)
        cout<<ts[i]<<endl;

	// vector< vector<int> > adjMat = createAdjMat(adj, V);

	// int c = 1;
	// vector<int> nodeColor(V, -1);

	// WPALGO(adjMat, V, c, nodeColor);
	// printGraph(adj, V);
	// displayColors(nodeColor);

	// int ch;
	// do
	// {
	// 	int op;
	// 	cout << "\n\nenter operation to perform\n1.add vertex\n2.delete vertex\n3.check if graph can be colored with atmost k colors\n4.rainbow neighborhood\n5.chromatic polynomial\nenter choice: ";
	// 	cin >> op;

	// 	switch (op)
	// 	{

	// 	case 1:
	// 	{
	// 		add_vertex(adj, adjMat, c, nodeColor, V, E);
	// 		printGraph(adj, V);
	// 		displayColors(nodeColor);
	// 		break;
	// 	}

	// 	case 2:
	// 	{
	// 		delete_vertex(adj, adjMat, nodeColor, V, E);
	// 		printGraph(adj, V);
	// 		displayColors(nodeColor);
	// 		break;
	// 	}

	// 	case 3:
	// 	{
	// 		int y;
	// 		cout<<"\n\nenter no of colors to check whether graph can be colored with at max: ";
	// 		cin>>y;
	// 		kChromaticValidation(adj, V, y);
	// 		break;
	// 	}

	// 	case 4:
	// 	{
	// 		int x;
	// 		cout<<"\n\nenter the vertex to check for rainbow neighborhood: ";
	// 		cin>>x;
	// 		bool rainbow = rainbowNeighborhood(adj, x-1, nodeColor, c-1);
	// 		if(rainbow)
	// 			cout<<"\nvertex "<<x<<" is in a rainbow neighborhood";
	// 		else
	// 			cout<<"\nvertex "<<x<<" is not in a rainbow neighborhood";
	// 		break;
	// 	}

	// 	case 5:
	// 	{
	// 		vector<int> k(V+1, 0);
	// 		chromaticPolynomial(adj,V,E,k);
	// 		string polynomial = generatePoly(V, k);
	// 		cout<<"\n\nthe chromatic polynomial is:\n";
	// 		cout<<polynomial;
	// 		break;
	// 	}

	// 	default:
	// 	{
	// 		cout << "\ninvalid choice";
	// 		break;
	// 	}
	// 	}

	// 	cout << "\n\nperform another operation?(1-yes): ";
	// 	cin >> ch;

	// } while (ch == 1);	

	cout<<"\n\n";
    system("pause");
	return 0;
}
#include <bits/stdc++.h>
#include <vector>
#include <unordered_set>
#include "chromaticpoly.cpp"
#include "rainbow.cpp"
#include "mcoloring.cpp"
using namespace std;
using namespace std::chrono;

void ColorNeighbourhood(vector<unordered_set<int>> f, int i, int &c, vector<int> &colors, vector<bool> &present)
{

    int cIncrement = 1;

    unordered_set<int>::iterator itr;
    unordered_set<int>::iterator itr2;
    //itr indicates value of neighbor of i
    //itr2 indicates value of neighbor of neighbor of i

    for (itr = f[i].begin(); itr != f[i].end(); itr++)
    {

        if (present[*itr - 1] == false)
            continue;

        if (colors[*itr - 1] != -1)
            continue;

        for (itr2 = f[*itr - 1].begin(); itr2 != f[*itr - 1].end(); itr2++)
        {

            if (f[i].count(*itr2))
            {

                cIncrement = 2;
                //2-colorable case

                if (colors[*itr - 1] == -1 && colors[*itr2 - 1] == -1)
                {
                    colors[*itr - 1] = c;
                    colors[*itr2 - 1] = c + 1;
                }

                else if (colors[*itr - 1] == c && colors[*itr2 - 1] == -1)
                {
                    colors[*itr2 - 1] = c + 1;
                }

                else if (colors[*itr - 1] == c + 1 && colors[*itr2 - 1] == -1)
                {
                    colors[*itr2 - 1] = c;
                }

                else if (colors[*itr2 - 1] == c && colors[*itr - 1] == -1)
                {
                    colors[*itr - 1] = c + 1;
                }

                else if (colors[*itr2 - 1] == c + 1 && colors[*itr - 1] == -1)
                {
                    colors[*itr - 1] = c;
                }
            }
        }

        if (colors[*itr - 1] == -1)
            colors[*itr - 1] = c;

    }

    c += cIncrement;

    for (itr = f[i].begin(); itr != f[i].end(); itr++)
    {
        present[*itr - 1] = false;
    }
}

void colorRemainingVertices(vector< unordered_set<int> > arrNei, int &c, vector<int> &colors, vector<bool> &present) {

    int n = arrNei.size();
	
	int maxC = c;
	
	for(int i = 0; i < n; i++) {

        if(colors[i] != -1)
            continue;
		
		for(int col = c; col <= maxC; col++) {
			
			bool canColor = true;

            unordered_set<int> :: iterator itr;
			
			for(itr = arrNei[i].begin(); itr != arrNei[i].end(); itr++) {
				
				if(colors[*itr - 1] == col) {
					canColor = false;
					break;
				}
				
			}
			
			if(canColor) {
				colors[i] = col;
				break;
			}
			
		}
		
		if(colors[i] == -1) {
			maxC++;
			colors[i] = maxC;
		}
		
	}

    c = maxC;

}

void Wigderson(vector< unordered_set<int> > arrNei, int n, vector<int> &colors, int &c, vector<bool> present) {

	for(int i = 0; i < n; i++) {

        int noOfNeighboursPresent = 0;

        unordered_set<int> :: iterator itr;        

        if(present[i]) {

            for(itr = arrNei[i].begin(); itr != arrNei[i].end(); itr++) {

                if(present[*itr - 1] == true) {
                    noOfNeighboursPresent++;
                }

            }    

            if(noOfNeighboursPresent >= ceil(sqrt(n))) {

                ColorNeighbourhood(arrNei, i, c, colors, present);

            }

        }
        
    }

    colorRemainingVertices(arrNei, c, colors, present);
	
}

void addEdge(vector< unordered_set<int> > &adj, vector< vector<int> > &adjVec, int u, int v)
{
    adj[u - 1].insert(v);
    adj[v - 1].insert(u);

    adjVec[u-1].push_back(v-1);
    adjVec[v-1].push_back(u-1);
}

void add_node(vector< unordered_set<int> > &f, vector< vector<int> > &adjVec, vector<int> &colors, vector<bool> &present, int &c, int &v, int &e, int cv) {

    int t = 3;
    unordered_set<int> neighbors;

	// cout<<"\n\nEnter the no of nieghbours of new node: ";
    // cin>>t;
	
    int x = f.size() + 1;

    adjVec.resize(x);

    // cout <<"Enter the nieghbours:";     
    // for(int i = 0; i < t; i++) {
    //     int r;
    //     cin>>r;

    //     neighbors.insert(r);
    //     f[r-1].insert(x);

    //     adjVec[r-1].push_back(x-1);
    //     adjVec[x-1].push_back(r-1);
    // }

    // r = 1, cv

    neighbors.insert(1);
    f[0].insert(x);

    adjVec[0].push_back(x-1);
    adjVec[x-1].push_back(0);



   neighbors.insert(cv);
        f[cv-1].insert(x);

        adjVec[cv-1].push_back(x-1);
        adjVec[x-1].push_back(cv-1);

    neighbors.insert(cv+1);
        f[cv+1].insert(x);

        adjVec[cv].push_back(x-1);
        adjVec[x-1].push_back(cv);





	f.push_back(neighbors);
	colors.push_back(-1);
	present.push_back(true);

    int tempC = 1;
	colorRemainingVertices(f, tempC, colors, present);

    if(tempC > c)
        c = tempC;

    v++;
    e += t;

}

void delete_node(vector<unordered_set<int>> &f, vector< vector<int> > &adjVec, vector<int> &colors, vector<bool> &present, int &v, int &e)
{
    cout << "\nEnter the node to be deleted\n";
    int x;
    cin >> x;

    int t = adjVec[x-1].size();

    unordered_set<int> temp = f[x];
    f.erase(f.begin() + x - 1);
    colors.erase(colors.begin() + x - 1);
    present.erase(present.begin() + x - 1);

    adjVec.erase(adjVec.begin() + x - 1);

    cout << "\n\n";
    for (int i = 0; i < f.size(); i++)
    {
        unordered_set<int>::iterator itr;
        unordered_set<int> temp;
        for (itr = f[i].begin(); itr != f[i].end(); itr++) {

            int t = *itr;

            if(t>x){
                t--;
                temp.insert(t);
            }
            else if(t<x){
                temp.insert(t);
            }

        }

        f.erase(f.begin()+i);
        f.insert(f.begin() + i,temp);
        temp.erase(temp.begin(), temp.end());

    }


    //updating adjVec
    for(int i = 0; i < adjVec.size(); i++) {

		vector<int> neighbors;

		for(int j = 0; j < adjVec[i].size(); j++) {

			if(adjVec[i][j] == x-1)
				continue;

			if(adjVec[i][j] > x-1)
				neighbors.push_back(adjVec[i][j] - 1);
			
			else
				neighbors.push_back(adjVec[i][j]);

		}

		adjVec.erase(adjVec.begin() + i);
		adjVec.emplace(adjVec.begin() + i, neighbors);

	}

    v--;
    e -= t;

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

int main() {

    // int V, E;

    // cout<<"enter the no of vertices: ";
    // cin>>V;
    // vector< unordered_set<int> > adj(V);
    // vector< vector<int> > adjVec(V);

    // cout<<"enter the no of edges: ";
    // cin>>E;

    // cout<<"\nenter the edges (start vertex   end vertex):\n";
    // for(int i = 0; i < E; i++) {

    //     int u, v;
    //     cin>>u>>v;

    //     addEdge(adj, adjVec, u, v);

    // }



    // adj[u - 1].insert(v);
    // adj[v - 1].insert(u);

    // adjVec[u-1].push_back(v-1);
    // adjVec[v-1].push_back(u-1);


    vector<int> vs;
    vector<long> ts;

    for(int i = 3; i < 50; i++) {

        cout<<"\ni: "<<i;

        int V = i*i;
        int E = 2*i + V - i - 1 - 1;

        vector< unordered_set<int> > adj(V);
        vector< vector<int> > adjVec(V);
        //cout<<"\nvector created";
        int j = 0;

        for(j; j < i-1; j++) {

            // adj[j].push_back(j+1);
            // adj[j+1].push_back(j);

            addEdge(adj, adjVec, j+1, j+2);

        }

        // adj[j].push_back(0);
        // adj[0].push_back(j);

        addEdge(adj, adjVec, 1, j+1);

        //cout<<"\ncircular graph done";
        for(int k = 0; k < i; k++) {

            addEdge(adj, adjVec, i+1, k+1);

        }
        //cout<<"\nstar graph done";
        // adj[0].push_back(i+1);
        // adj[i+1].push_back(0);

        addEdge(adj, adjVec, 1, i+2);

        //cout<<"\nlinear first node added";
        int remNumOfNodes = V - i - 1 - 1;

        for(int m = i + 1; m < i + 1 + remNumOfNodes; m++) {

            // adj[m].push_back(m+1);
            // adj[m+1].push_back(m);
            addEdge(adj, adjVec, m+1, m+2);

        }
        //cout<<"\nlinear graph done";
        // vector<int> colors(V, -1);
	    // int maxC = 1;

        // auto start = high_resolution_clock::now();
	    // greedyColor(adj, colors, maxC, false);
        // auto stop = high_resolution_clock::now();

        // auto duration = duration_cast<microseconds>(stop - start);

        // cout<<V<<" vertices: "<<duration.count() << " microseconds\n";
	    //printGraph(adj, V);
	    //displayColors(colors);

        vector<int> colors(V,-1);
        int c = 1;
        vector<bool> present(V, true);

        // auto start = high_resolution_clock::now();
        Wigderson(adj, V, colors, c, present);
        // auto stop = high_resolution_clock::now();

        auto start = high_resolution_clock::now();
        add_node(adj, adjVec, colors, present, c, V, E, i);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);

        //cout<<V<<" vertices: "<<duration.count() << " microseconds\n";
        //printGraph(adjVec, V);
	    //displayColors(colors);

        vs.push_back(V);
        ts.push_back(duration.count());


    }

    for(int i = 0; i < vs.size(); i++)
        cout<<vs[i]<<endl;

    for(int i = 0; i < vs.size(); i++)
        cout<<ts[i]<<endl;


    // vector<int> colors(V,-1);
    // int c = 1;
    // vector<bool> present(V, true);

    // Wigderson(adj, V, colors, c, present);
    // printGraph(adjVec, V);
	// displayColors(colors);

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
	// 		add_node(adj, adjVec, colors, present, c, V, E);
    //         printGraph(adjVec, V);
    //         displayColors(colors);
	// 		break;
	// 	}

	// 	case 2:
	// 	{
	// 		delete_node(adj, adjVec, colors, present, V, E);
    //         printGraph(adjVec, V);
    //         displayColors(colors);
	// 		break;
	// 	}

	// 	case 3:
	// 	{
	// 		int y;
    //         cout<<"\n\nenter no of colors to check whether graph can be colored with at max: ";
    //         cin>>y;
    //         kChromaticValidation(adjVec, V, y);
	// 		break;
	// 	}

	// 	case 4:
	// 	{
	// 		int x;
    //         cout<<"\n\nenter the vertex to check for rainbow neighborhood: ";
    //         cin>>x;
    //         bool rainbow = rainbowNeighborhood(adjVec, x-1, colors, c);
    //         if(rainbow)
    //             cout<<"\nvertex "<<x<<" is in a rainbow neighborhood";
    //         else
    //             cout<<"\nvertex "<<x<<" is not in a rainbow neighborhood";
	// 		break;
	// 	}

	// 	case 5:
	// 	{
	// 		vector<int> k(V+1, 0);
    //         chromaticPolynomial(adjVec, V, E, k);
    //         string polynomial = generatePoly(V, k);
    //         cout<<"\n\nthe chromatic polynomial is:\n";
    //         cout<<polynomial;
	// 		break;
	// 	}

	// 	default:
	// 	{
	// 		cout << "\ninvalid choice";
	// 		break;
	// 	}

    //     }
		

	// 	cout << "\n\nperform another operation?(1-yes): ";
	// 	cin >> ch;

	// } while (ch == 1);

    cout<<"\n\n";
    system("pause");
    return 0;
}

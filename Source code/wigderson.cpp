#include <bits/stdc++.h>
#include <vector>
#include <unordered_set>
using namespace std;


	
// }
// void delete_node(int x,vector< unordered_set<int> > &f, vector<int>&colors, vector<bool> &present){
//  unordered_set<int>temp=f[x];
//  f.erase(f.begin()+x-1);
//  colors.erase(colors.begin()+x-1);	
//  present.erase(present.begin()+x-1);
//  for(itr = temp.begin(); itr != temp.end(); itr++){
//  f[*itr].erase(f[*itr].find(x));
//  }	
// }

void ColorNeighbourhood(vector< unordered_set<int> > f, int i, int &c, vector<int>&colors, vector<bool> &present) {

    int cIncrement = 1;

    unordered_set<int> :: iterator itr;
    unordered_set<int> :: iterator itr2;
    //itr indicates value of neighbor of i
    //itr2 indicates value of neighbor of neighbor of i

	for(itr = f[i].begin(); itr != f[i].end(); itr++) {

        if(present[*itr] == false)
            continue;

        if(colors[*itr] != -1)
            continue;
        
        for(itr2 = f[*itr].begin(); itr2 != f[*itr].end(); itr2++) {
            
            if(f[i].count(*itr2)) {

                cIncrement = 2;
                //2-colorable case

                if(colors[*itr] == -1 && colors[*itr2] == -1) {
                    colors[*itr] = c;
                    colors[*itr2] = c+1;
                }

                else if(colors[*itr] == c && colors[*itr2] == -1) {
                    colors[*itr2] = c+1;
                }

                else if(colors[*itr] == c+1 && colors[*itr2] == -1) {
                    colors[*itr2] = c;
                }

                else if(colors[*itr2] == c && colors[*itr] == -1) {
                    colors[*itr] = c+1;
                }

                else if(colors[*itr2] == c+1 && colors[*itr] == -1) {
                    colors[*itr] = c;
                }
            }

        }

        if(colors[*itr] == -1)
            colors[*itr] = c;

    }

    c += cIncrement;

    
    for(itr = f[i].begin(); itr != f[i].end(); itr++) {

        present[*itr] = false;

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
				
				if(colors[*itr] == col) {
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

}

void Wigderson(vector< unordered_set<int> > arrNei, int n, vector<int> &colors, int &c, vector<bool> present) {

	for(int i = 0; i < n; i++) {

        int noOfNeighboursPresent = 0;

        unordered_set<int> :: iterator itr;        

        if(present[i]) {

            for(itr = arrNei[i].begin(); itr != arrNei[i].end(); itr++) {

                if(present[*itr] == true) {
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

void addEdge(vector< unordered_set<int> > &adj, int u, int v)
{
    adj[u].insert(v);
    adj[v].insert(u);
}

void add_node(vector< unordered_set<int> > &f, vector<int> &colors, vector<bool> &present, int &c) {

    int t;
    unordered_set<int> neighbors;

	cout<<"\nEnter the no of nieghbours of new node \n";
    cin>>t;
	
    cout <<"Enter the nieghbours:\n";     
    for(int i=0; i<t; i++) {
        int r;
        cin>>r;
        neighbors.insert(r - 1);
    }

	f.push_back(neighbors);
	colors.push_back(-1);
	present.push_back(true);
	colorRemainingVertices(f, c, colors, present);

    cout<<"\ncolor of new node is "<<colors[colors.back()];

}

int main() {

    int V, E;

    cout<<"enter the no of vertices: ";
    cin>>V;
    vector< unordered_set<int> > adj(V);
    vector<int> k(V+1, 0);

    cout<<"enter the no of edges: ";
    cin>>E;

    cout<<"\nenter the edges (start vertex   end vertex):\n";
    for(int i = 0; i < E; i++) {

        int u, v;
        cin>>u>>v;

        addEdge(adj, u-1, v-1);

    }

    vector<int> colors(V,-1);
    int c = 1;
    vector<bool> present(V, true);

    Wigderson(adj, V, colors, c, present);

    cout<<endl;

    for(int i=0; i < colors.size(); i++)
        cout<<"vertex"<<i+1<<"\t"<<colors[i]<<"\n";

    add_node(adj, colors, present, c);

    cout<<"\n\n";
    system("pause");
    return 0;
}

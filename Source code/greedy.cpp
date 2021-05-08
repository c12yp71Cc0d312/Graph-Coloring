#include <bits/stdc++.h>
#include <vector>
using namespace std;
void add_node(vector< vector<int> > g){
	cout<<"\nEnter the no of nieghbours of new node \n";
        int t;
        cin>>t;
	vector<int> a;
        cout <<"Enter the nieghbours\n";     
        for(int k=0;k<t;k++){
            int r;
            cin>>r;
            a.push_back(r);
        }
	g.push_back(a);
	greedyColor(g);	
}
void delete_node(vector< vector<int> > g){
	cout<<"\nEnter the node to be deleted\n";
	int x;
	cin>>x;
	g.erase(g.begin()-x);
	greedyColor(g);
 }
void greedyColor(vector< vector<int> > g) {

	int n = g.size();
    
	int colors[n] = { 0 };
	
	int c;
	int maxC = 1;
	
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
		
		if(colors[i] == 0) {
			maxC++;
			colors[i] = maxC;
		}
		
	}
	
	for(int i = 0; i < n; i++) {
		
		cout<<"\ncolor of vertex "<<i+1<<" is: "<<colors[i];
		
	}
	
}

int main() {
	
	int v;
	
	cout<<"enter no of vertices: ";
	cin>>v;
	
	vector< vector<int> > g(v);
	
	for(int i = 0; i < v; i++) {
		int n;
		cout<<"enter no of neighbors of vertex "<<i+1<<": ";
		cin>>n;
		
		cout<<"enter the neighbours: ";
		int x;
		for(int j = 0; j < n; j++) {
			cin>>x;
			g[i].push_back(x-1);
		}
	}
	
	greedyColor(g);
	
}

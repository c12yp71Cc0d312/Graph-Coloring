#include <bits/stdc++.h>
#include <vector>
#include <unordered_set>
using namespace std;
void add_node(vector< unordered_set<int> > &f, vector<int>&colors, vector<bool> &present){
	cout<<"\nEnter the no of nieghbours of new node \n";
        int t;
        cin>>t;
	unordered_set<int> a;
        cout <<"Enter the nieghbours\n";     
        for(int k=0;k<t;k++){
            int r;
            cin>>r;
            a.insert(r);
        }
	f.push_back(a);
	colors.push_back(-1);
	present.push_back(false);
	colorRemainingVertices( f, 1, colors, present);
	
}
void delete_node(int x,vector< unordered_set<int> > &f, vector<int>&colors, vector<bool> &present){
 unordered_set<int>temp=f[x];
 f.erase(f.begin()+x-1);
 colors.erase(colors.begin()+x-1);	
 present.erase(present.begin()+x-1);
 for(itr = temp.begin(); itr != temp.end(); itr++){
 f[*itr].erase(f[*itr].find(x));
 }	
}
void ColorNeighbourhood(vector< unordered_set<int> > f, int i, int &c, vector<int>&colors, vector<bool> &present) {

    int cIncrement = 1;

    unordered_set<int> :: iterator itr;
    unordered_set<int> :: iterator itr2;
    //itr indicates value of neighbor of i
    //itr2 indicates value of neighbor of neighbor of i

	for(itr = f[i].begin(); itr != f[i].end(); itr++) {

        if(present[*itr-1] == false)
            continue;

        if(colors[*itr-1] != -1)
            continue;
        
        for(itr2 = f[*itr-1].begin(); itr2 != f[*itr-1].end(); itr2++) {
            
            if(f[i].count(*itr2)) {

                cIncrement = 2;
                //2-colorable case

                if(colors[*itr-1] == -1 && colors[*itr2-1] == -1) {
                    colors[*itr-1] = c;
                    colors[*itr2-1] = c+1;
                }

                else if(colors[*itr-1] == c && colors[*itr2-1] == -1) {
                    colors[*itr2-1] = c+1;
                }

                else if(colors[*itr-1] == c+1 && colors[*itr2-1] == -1) {
                    colors[*itr2-1] = c;
                }

                else if(colors[*itr2-1] == c && colors[*itr-1] == -1) {
                    colors[*itr-1] = c+1;
                }

                else if(colors[*itr2-1] == c+1 && colors[*itr-1] == -1) {
                    colors[*itr-1] = c;
                }
            }

        }

        if(colors[*itr-1] == -1)
            colors[*itr-1] = c;

    }

    c += cIncrement;

    
    for(itr = f[i].begin(); itr != f[i].end(); itr++) {

        present[*itr-1] = false;

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
				
				if(colors[*itr-1] == col) {
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

void Wigderson(vector< unordered_set<int> > arrNei, int n, vector<int>&colors) {
	
	int c = 1;

    vector<bool> present(n, true);

	for(int i = 0; i < n; i++) {

        int noOfNeighboursPresent = 0;

        unordered_set<int> :: iterator itr;        

        if(present[i]) {

            for(itr = arrNei[i].begin(); itr != arrNei[i].end(); itr++) {

                if(present[*itr-1] == true) {
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

int main() {
	int n;
	cout<<"enter the no of vertices in the graph: ";
	cin>>n;
	vector< unordered_set<int> > f(n);
    vector<int> colors(n,-1);
    for(int i =0;i<n;i++){
        cout<<"\nEnter the no of nieghbours of "<<i+1<<"\n";
        int t;
        cin>>t;
        cout <<"Enter the nieghbours\n";     
        for(int k=0;k<t;k++){
            int r;
            cin>>r;
            f[i].insert(r);
        }
        
    }
    cout<<"\n\n";
    unordered_set<int> :: iterator itr;
   /* for(int i=0;i<n;i++){
       for (itr = f[i].begin(); itr != f[i].end(); itr++)
        cout << *itr << " ";
       cout<<"\n";
    }
    */
	//okk now we need to implement neighbor coloring....as mentioned in line 16
    Wigderson(f,n,colors);
    for(int i=0;i<colors.size();i++)
    cout<<"vertex"<<i+1<<"\t"<<colors[i]<<"\n";

    return 0;
}

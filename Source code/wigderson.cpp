#include <bits/stdc++.h>
#include <vector>
#include <unordered_set>
using namespace std;

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

        if(colors[i] == -1)
            continue;
		
		for(int j = c; j <= maxC; j++) {
			
			int col = j;
			
			bool canColor = true;

            unordered_set<int> :: iterator itr;
			
			for(itr = arrNei[i].begin(); itr != arrNei[i].end(); itr++) {

                if(present[*itr-1] == 0)
                    continue;
				
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
		
		if(colors[i] == 0) {
			maxC++;
			colors[i] = maxC;
		}
		
	}

}

void Wigderson(vector< unordered_set<int> > arrNei, int n, vector<int>&colors) {
	
	int c=1;

    vector<bool> present(n,true);

	for(int i=1;i<=n;i++){
            if(arrNei[i-1].size() >= ceil(sqrt(n)) && present[i-1] ) {
                ColorNeighbourhood(arrNei, i-1, c, colors, present);
            
        }
    }

    //colorRemainingVertices(arrNei, c, colors, present);


    // acc to wigderson algo, for remaining vertices, we color using greedy algo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // for(int i=0;i<n;i++)
    // if(present[i]){
    //    colors[i]=c;
    //    present[i]=false;
    // }

    

	
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

    cout<<"\n0 to exit";
    int z;
    cin>>z;

    return 0;
}

/*  
5
1 - 2 3    -   
2 - 1 3    -    
3 - 1 2 4 5
4 - 3
5 - 3
hlo
shriram chck if the output is crt i made one small change only after u went

*/


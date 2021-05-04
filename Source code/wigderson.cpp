#include <bits/stdc++.h>
#include <vector>
using namespace std;
//nee code pannu i will see
//im also thinking only....what we have to do is given a vertex
//we have to color its neighbours alone 1-colorable or 2-colorable
//for ex, if all the neighbors of a vertex are not connected to each other
//and they are only connected to the vertex, everything(all neighbors) will be 1-colorable,
//else, 2-colorable case will arise
//discord vvaa da peslam its tough to type and understand...ok
// evalo pannika? sshriram irukiya?


void ColorNeighbourhood(vector< unordered_set<int> > f, int i, int &c, vector<int>&colors, vector<bool> &present) {
    bool abc=false;

    unordered_set<int> :: iterator itr;
    unordered_set<int> :: iterator itr2;
    //itr indicates neighbor of i
    //itr2 indicates neighbor of neighbor of i

	for(itr = f[i].begin(); itr != f[i].end(); itr++) {

        if(present[*itr-1] == false)
            continue;

        present[*itr-1] = false;
        
        for(itr2 = f[*itr].begin(); itr2 != f[*itr].end(); itr2++) {
            
            if(f[i].count(*itr2)) {
                abc=true;
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

            else
                colors[*itr-1]=1;


        }



    }
        if(abc)
            c=c+2;
        else
            c++;
}

void Wigderson(vector< unordered_set<int> > arrNei, int n, vector<int>&colors) {
	
	int c=1;

    vector<bool> present(n,true);

	for(int i=1;i<=n;i++){
            if(arrNei[i-1].size() >= ceil(sqrt(n)) && present[i-1] ) {
                ColorNeighbourhood(arrNei, i-1,c, colors, present);
            
        }
    }

    // acc to wigderson algo, for remaining vertices, we color using greedy algo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    for(int i=0;i<n;i++)
    if(present[i]){
       colors[i]=c;
       present[i]=false;
    }

    

	
}

int main() {
	int n;
	cout<<"enter the no of vertices in the graph: ";
	cin>>n;
	std::vector<std::unordered_set<int>> f(n);
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


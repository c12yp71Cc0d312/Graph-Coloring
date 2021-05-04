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

struct NodeColor {
	
	int color;
	
};

void WPALGO(int adjMat[20][20], int n) {
	
	priority_queue<NodeDegree> nodes;
	
	//init
	vector<NodeColor> nodeColor;
	for(int i = 0; i < n; i++) {
		
		NodeColor n = {-1};
		nodeColor.push_back(n);
		
	}
	
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
	
	int c = 1;
	
	while(nodes.size() > 0) {
		
		int highestDegVertex = nodes.top().nodeNum;
		
		if(nodeColor[highestDegVertex].color != -1) {
			nodes.pop();
			continue;
		}

		
		for(int i = 0; i < n; i++) {
			
			if(adjMat[highestDegVertex][i] == 0 && nodeColor[i].color == -1) {
				
				nodeColor[i].color = c;
				
			}
			/
		}
		
		c++;
		nodes.pop();
		
	}
	
	for(int i = 0; i < n; i++) {
		
		cout<<"\ncolor of node "<<i+1<<" is "<<nodeColor[i].color;
		
	}
	
}

int main() {
    
	char c='y';
    do {
	int n;
	
	cout<<"enter the no of vertices in the graph: ";
	cin>>n;
	
	int adjMat[20][20];
	
	cout<<"\nenter the adjacency matrix of the graph: ";
	
	for(int i = 0; i < n; i++) {
		
		for(int j = 0; j < n; j++) {
			
			cin>>adjMat[i][j];
			
		}
		
	}
	
	WPALGO(adjMat, n);
	cout<<"\nDo u want to continue? y/n";
    cin>>c;
    }while(c=='y');
	return 0;
}


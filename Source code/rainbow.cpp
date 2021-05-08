#include <bits/stdc++.h>
#include <vector>
#include <unordered_set>
using namespace std;

struct node {
    int clr;
    unordered_set<int> neigh;
};

void rainbowNeighbor(vector<node> vert, int n, int k) {
    for(int i =0; i<n; i++)
    {
        cout << "vertex " << i+1 <<endl;
        unordered_set<int> :: iterator itr;
        unordered_set<int> tempClr;
        for(itr = vert[i].neigh.begin(); itr != vert[i].neigh.end(); itr++)
        {
            tempClr.insert(vert[*itr-1].clr);
            cout << vert[*itr-1].clr << endl;
        }
        if(tempClr.size() == k-1)
            cout << "size is k-1 hence this vertex is a rainbow Neighbor" << endl;
    }
}


int main() {
	int n;
	vector<node> vert(n);
	vector<node> vv(5);
	vv = { {1, {2, 3}}, {2, {1, 3}}, {3, {1,2,4,5}}, {1, {3}}, {1, {3}} };
	unordered_set<int> :: iterator itrr;
	for(int i = 0; i< n; i++)
	{
	    vert[i].clr = -1;
	}
    rainbowNeighbor(vv, 5, 3);

    cout<<"\n\n";
    system("pause");
    return 0;
}
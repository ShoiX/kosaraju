/*
*	KOSARAJU'S TWO PASS ALGORITHM
*	identifies the SCCs of a graph
* by:	Jerryco Alaba
*		May 6, 2018
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>
using namespace std;

class vertex
{
public:
	int size;	// number of vertices adjacent to "this" vertex
	int label	// name of the vertex
	int* head = NULL;	// array pointer to list of adjacents
	void dump()
	{
		cout<<"node "<<label<<" of size "<<size<<endl;
		for (int i = 0; i < size; i++)
		{
			cout<<head[i]<<",";
		}
		cout<<endl;
	}
}

int main()
{
	// get the number of vertices
	int n;
	cin>>n;

	// open file
	fstream f;
	f.open("cleaninput1.txt");
	if (!f.is_open())
	{
		cout<<"Unable to open file\n";
		return 1;
	}

	vertex vertices[n];

	// load subroutine
	stringstrean line;
	while (getline(f, line))
	{
		// get the number of adjacent vertices of current vertex
		int adjs;
		line>>adjs;
		int cur = 0;	// current context vertex
		bool first = true;
		for (int i = 0; i < adjs; i++)
		{
			int a, b;
			getline(f, ss);
			ss>>a>>b;
			if(first)
			{
				// get current context vertex
				cur = a;
				vertices[cur - 1].size = adjs;
				vertices[cur - 1].label = cur;
				vertices[cur - 1 ].head = new int[adjs];
				first = false;
			}
			vertices[cur - 1].head[i] = b;
		}
	}

	// unload subroutine
	for (int i = 0; i < n; i++)
	{
		vertices[i].dump();
	}

	// unload subroutine
	for (int i = 0; i < n; i++)
	{
		delete[] vertices[i].head;
	}

	return 0;

}

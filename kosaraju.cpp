/*
*	KOSARAJU'S TWO PASS ALGORITHM
*	identifies the SCCs of a graph
* by:	Jerryco Alaba
*
*/

#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
#include <chrono>
#include <fstream>
#include <stdlib.h>	
#define INITLIMIT 900000
using namespace std;
	
class vertex
{
public:
	int label = 0;	// name of the vertex
	// vector for vertices adjacent (in and out)
	vector<int> outward;
	vector<int> inward;
	int order;
	bool first_pass = false;
	bool second_pass = false;

	vertex()
	{
		this->outward.reserve(10);
		this->inward.reserve(10);
	}
};

int finish_time = 0;
vertex** order;

void DFS1(int cur, vector<vertex> &vertices)
{
	vertices[cur-1].first_pass = true;
	for (int i = 0, j = vertices[cur-1].inward.size(); i < j; i++)
	{
		int cur_vec = vertices[cur - 1].inward[i];
		if (!vertices[cur_vec - 1].first_pass)
		{
			DFS1(cur_vec, vertices);
		}
	}
	// set the finishing time
	vertices[cur - 1].order = finish_time;
	order[finish_time] = &vertices[cur - 1];
	finish_time += 1;
	return;
}

/* DUMP subroutine*/
void gen_dump(vector<vertex> &vertices, int n)
{
	cout<<"Graph size: "<<vertices.size()<<endl;
	for(int i = 0; i < n; i++)
	{
		cout<<"vertex "<<vertices[i].label<<" order: "<<vertices[i].order<<endl<<"outward: ";
		for (int k = 0, l = vertices[i].outward.size(); k < l; k++)
			cout<<vertices[i].outward[k]<<" ";
		cout<<endl<<"inward: ";

		for (int m = 0, n = vertices[i].inward.size(); m < n; m++)
			cout<<vertices[i].inward[m]<<" ";
		cout<<endl;
	}
}

void order_dump(vector<vertex> &vertices, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout<<"pos "<<i<<": "<<order[i]->label<<endl;
	}
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout<<"usage: ./kosaraju file.txt [1/2]\n";
		return 1;	
	}
	std::vector<vertex> vertices;
	vertices.reserve(INITLIMIT);

	fstream f;
	f.open(argv[1]);
	if (!f.is_open())
	{
		cout<<"Unable to open file\n";
		return 1;
	}

	/* LOAD SUBROUTINE */
	string line;
	int a, b;
	int n = 0;	// number of vertices created
	while (getline(f, line))
	{
		stringstream s(line);
		s>>a>>b;
		
		int high = max(a, b);
		if (high > n)
		{
			vertices.resize(high);
			n = high;
		}

		vertices[a-1].label = (vertices[a - 1].label == 0) ? a : vertices[a-1].label;
		vertices[b-1].label = (vertices[b - 1].label == 0) ? b : vertices[b-1].label; 

		vertices[a-1].outward.push_back(b);
		vertices[b-1].inward.push_back(a);
	}

	n = vertices.size();
	// first DFS pass
	order = new vertex*[n];
	for(int i = n; i > 0; i--)
	{
		if (!vertices[i - 1].first_pass)
		{
			DFS1(i, vertices);
		}
	}
	if (argc == 3)
	{
		if (atoi(argv[2]) == 1)
		{
			gen_dump(vertices, n);
		}
		else if(atoi(argv[2]) == 2)
		{
			order_dump(vertices, n);
		}
	}

	f.close();
}

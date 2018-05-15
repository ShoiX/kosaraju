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
#define top 5
using namespace std;
	
class vertex
{
public:
	int label = 0;	// name of the vertex
	// vector for vertices adjacent (in and out)
	vector<vertex*> outward;
	vector<vertex*> inward;
	int order;
	bool first_pass = false;
	bool second_pass = false;

	vertex()
	{
		this->outward.reserve(10);
		this->inward.reserve(10);
	}
};

class scc
{
public:
	std::vector<vertex*> components;

	scc()
	{
		components.reserve(200);
	}

};

int finish_time = 0;
vertex** order;


// first pass of DFS
void DFS1(vertex* cur)
{
	cur->first_pass = true;
	for (int i = 0, j = cur->inward.size(); i < j; i++)
	{
		vertex* next_vec = cur->inward[i];
		if (!next_vec->first_pass)
		{
			DFS1(next_vec);
		}
	}
	// set the finishing time
	cur->order = finish_time;
	order[finish_time] = cur;
	finish_time += 1;
	return;
}

void DFS2(vertex* cur, scc* tmp)
{
	cur->second_pass = true;
	tmp->components.push_back(cur);
	for (int i = 0, j = cur->outward.size(); i < j; i++)
	{
		vertex* next_vec = cur->outward[i];
		if (!next_vec->second_pass)
		{
			DFS2(next_vec, tmp);	
		}
	}
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
			cout<<vertices[i].outward[k]->label<<" ";
		cout<<endl<<"inward: ";

		for (int m = 0, n = vertices[i].inward.size(); m < n; m++)
			cout<<vertices[i].inward[m]->label<<" ";
		cout<<endl;
	}
}

void order_dump(vector<vertex> &vertices, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout<<"pos "<<i + 1<<": "<<order[i]->label<<endl;
	}
}

void scc_dump(vector<scc> &SCCs)
{
	int len = SCCs.size();
	cout<<"number of SCCs: "<<len<<endl;
	for (int i = 0; i < len; i++)
	{
		cout<<"scc no. "<<i + 1<<": ";
		for (int j = 0, k = SCCs[i].components.size(); j < k; j++)
		{
			cout<<SCCs[i].components[j]->label<<" ";
		}
		cout<<endl;
	}
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout<<"usage: ./kosaraju file.txt [1/2/3/4]\n";
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

		vertices[a-1].outward.push_back(&vertices[b -  1]);
		vertices[b-1].inward.push_back(&vertices[a - 1]);
	}

	n = vertices.size();
	// first DFS pass
	order = new vertex*[n];
	for(int i = n; i > 0; i--)
	{
		if (!vertices[i - 1].first_pass)
		{
			DFS1(&vertices[i - 1]);
		}
	}

	// second DFS pass
	std::vector<scc> SCCs;
	SCCs.reserve(200000);
	scc* toplist[top];
	int ctr = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		if (!order[i]->second_pass)
		{
			scc tmp;
			DFS2(order[i], &tmp);
			SCCs.push_back(tmp);

			int SCCs_size = SCCs.size();

			// build the list of the largest SCCs of the graph
			if(ctr < top)
			{
				toplist[ctr] = &SCCs[SCCs_size - 1];
				ctr++;
			}
			else
			{
				for (int j = 0; j < top; j++)
				{
					if (tmp.components.size() > toplist[i]->components.size())
					{
						toplist[i] = &SCCs[SCCs_size - 1];
						break;
					}
				}
			}
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
		else if (atoi(argv[2]) == 3)
		{
			scc_dump(SCCs);
		}
		else if (atoi(argv[2]) == 4)
		{
			gen_dump(vertices, n);
			order_dump(vertices, n);
		}
	}
	delete[] order;
	f.close();
}

#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"
#include <map>
#include <set>
#include <vector>
// #include <fstream>
// #include <string>

bool operator == (edge a, edge b)
{
	if ((a.Origin == b.Origin) && (a.Dest==b.Dest) && (a.weight==b.weight))
		return true;
	else
		return false;
}

bool operator < (edge a, edge b)
{
	if (a.weight < b.weight)
		return true;
	return false;
}

bool operator > (edge a, edge b)
{
	if (a.weight > b.weight)
		return true;
	return false;
}
bool operator < (node a, node b)
{
}

bool operator > (node a, node b)
{
}
bool operator == (node a, node b)
{
	if((a.name == b.name) && (a.x == b.x) && (a.y == b.y))
		return true;
	return false;
}
Graph::Graph(char* file)
{
	fstream f;

	std::map <string, node*> node_list;
    f.open(file);
    string word;
    string node_name,xc,yc;
    string start,end,dist;
    while (f >> word)
    {
        if (word == "NODES")
        {
            // cout<<"Storing node"<<endl;

            while (f >> word)
            {
                if (word != "ARCS")
                {
                    node_name= word;
                    f >> xc;
                    f >> yc;
                    // cout<< node_name<<xc<<yc<<endl;
                    node* data = new node();
                    data->name = node_name;
                    data->x = strtof((xc).c_str(),0);
                    data->y = strtof((yc).c_str(),0);
                    data->visit =0;
                    node_list[data->name]=data;
                    cities.push_back(data);
                }
                else
                    break;
            }
            // cout<<"STORING ARCS"<<endl;
            while (f >> word)
            {
                start = word;
                f >> end;
                f >> dist;
                edge* edata = new edge();

                edata->Origin=node_list[start];
                edata->weight=strtof((dist).c_str(),0);
                edata->Dest = node_list[end];
                arcs.push_back(*edata);

                // node_list[end]->edges.push_back(*edata);						//Storing the arc in that node
                // node_list[start]->edges.push_back(*edata);						//Storing the arc in that node
               	// cout<< edata->Origin << edata->Dest<< dist<<endl;
            }
            break;
        }
        // cout<<"Hahahaha"<<endl;																			//This should never get printed
    }
    // cout<<"Done"<<endl;
    
    // cout<<cities[4]->name<<endl;
    // for (std::map<string,node*>::iterator it=node_list.begin(); it!=node_list.end(); ++it)
    //     std::cout << it->first << " => " << it->second << '\n';
    // cout<<node_list["Dallas"]->edges.size();
     // display(cities[4]);
    
 //    for(int i=0; i< cities.size(); i++)
	// {
	// 	cout<<cities[i]->name <<" ";
	// 	for(int j=0; j< cities[i]->edges.size(); j++)
	// 		cout<<cities[i]->edges[j].Origin->name << " "<<cities[i]->edges[j].Dest->name<<" " ;
	// 	cout<<endl;
	// }

	// making pqueue
	// pqueue<edge>* hp = new pqueue<edge>(100);
	// for(int i=0; i< arcs.size(); i++)
	// {
	// 	hp->insertKey(arcs[i]);
	// }
	// cout<<arcs.size()<<endl;
	// for(int i=0; i< arcs.size(); i++)
	// {
	// 	edge h = hp->extractMin();
	// 	cout<<h.Origin->name<<" ";
	// 	cout<<endl;
	// }
}
node* Graph::getCity(string s)
{
	for(int i=0; i< cities.size(); i++)
	{
		if(cities[i]->name == s)
			return cities[i];
	}
	return NULL;

}
void Graph::display(node* temp)
{
	if(temp->visit)
		return;

	cout << "AT: " << temp->name;
	temp->visit = 1;
	for(int i=0; i< temp->edges.size(); i++)
	{
		if(!temp->edges[i].Origin->visit || !temp->edges[i].Dest->visit)
		cout << "->" << temp->edges[i].weight << endl;
		display(temp->edges[i].Origin);
		display(temp->edges[i].Dest);
	}


}
vector<node*> Graph::Prims()
{
}


vector<node*> Graph::Kruskal()
{
	vector<node*> ret;
	pqueue<edge>* hp = new pqueue<edge>(100);
	for(int i=0; i< arcs.size(); i++)
	{
		hp->insertKey(arcs[i]);
	}
	// cout<<arcs.size()<<endl;

	//making the set for each node. These sets stored in a vector.
	vector<set<node*>> set_vector;
	for(int i=0; i< cities.size(); i++)
	{
		set<node*> temp;							//make individual sets
		temp.insert(cities[i]);
		set_vector.push_back(temp);
	}
	
	for(int i=0; i< hp->heap_size; i++)
	{
		edge temp = hp->extractMin();
		node* o = temp.Origin;
		node* d = temp.Dest;

		int index_origin = 0;
		int index_dest = 0;

		//Find these nodes in the vector of sets
		for (int i = 0; i < set_vector.size(); i++)
		{
			if (set_vector[i].find(o) != set_vector[i].end())
			{
				index_origin = i;
				break;	
			}	
		}
		for (int i = 0; i < set_vector.size(); i++)
		{
			if (set_vector[i].find(d) != set_vector[i].end())
			{
				index_dest = i;
				break;	
			}	
		}	

		// If an edge e connects two different sets
		if (index_dest!= index_origin)
		{
			//two sets of nodes that are now connected by e are merged into a single set.
			set_vector[index_origin].insert(set_vector[index_dest].begin(), set_vector[index_dest].end());

			o->edges.push_back(temp);
			d->edges.push_back(temp);
			// std::set_union(set_vector[index_origin].begin(), set_vector[index_origin].end(),
   //                 set_vector[index_dest].begin(),set_vector[index_dest].end(),                  
   //                 std::back_inserter(set_vector[index_origin]));

			//previous extra set has to be deleted
			set_vector.erase(set_vector.begin() + index_dest);

			cout << temp.Origin->name << " " << temp.Dest->name << " " << temp.weight << endl;
			ret.push_back(o);
			ret.push_back(d);
		}

	}
	return ret;


}
vector<string> Graph::Dijkstra(string city, string destination, float &d)
{
}
#endif

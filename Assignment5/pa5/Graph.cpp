#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"
#include <map>
#include <set>
#include <vector>
#include <cfloat>
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
	if (a.dist < b.dist)
		return true;
	return false;
}

bool operator > (node a, node b)
{
	if (a.dist > b.dist)
		return true;
	return false;
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
                    data->visit = 0;
                    data->dist =FLT_MAX;  					//for djikstras
                    data->prev = NULL;

                    node_list[data->name]=data; 			//populating map
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
                edge* edataO = new edge();
                edge* edataD = new edge();

                // edata->Origin=node_list[start];
                // edata->weight=strtof((dist).c_str(),0);
                // edata->Dest = node_list[end];
                edataO->Origin=node_list[start];
                edataO->weight=strtof((dist).c_str(),0);
                edataO->Dest = node_list[end];

                arcs.push_back(*edataO);

                edataD->Origin=node_list[end];
                edataD->weight=strtof((dist).c_str(),0);
                edataD->Dest = node_list[start];

                //COMMENT THESE TO DISPLAY MST CORRECTLY
                node_list[end]->edges.push_back(*edataD);						//Storing the outgoing arc in that node
                node_list[start]->edges.push_back(*edataO);						//Storing the outgoing arc in that node
               	
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
	float total=0;
	vector<node*> ret;
	pqueue<edge>* hp = new pqueue<edge>(arcs.size()+1);

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
		cities[i]->edges.clear();					//clearing all other edges. only mst edges would be stored
	}

	int k = hp->heap_size;
	for(int i=0; i< k; i++)
	{
		// cout<<i<<endl;
		edge temp = hp->extractMin();
		node* o = temp.Origin;
		node* d = temp.Dest;

		edge temp2;
		temp2.Origin = d;
		temp2.Dest = o;
		temp2.weight = temp.weight;

		// cout<<->name << " " <<d->name<<" "<<temp.weight<<endl;
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
			// d->edges.push_back(temp);


			// o->edges.push_back(temp2);
			d->edges.push_back(temp2);

			// std::set_union(set_vector[index_origin].begin(), set_vector[index_origin].end(),
   //                 set_vector[index_dest].begin(),set_vector[index_dest].end(),                  
   //                 std::back_inserter(set_vector[index_origin]));

			//previous extra set has to be deleted
			set_vector.erase(set_vector.begin() + index_dest);
			//add each new arc, print it to the console
			cout<<o->name <<" "<<d->name<< " "<< temp.weight<<endl;

			total+=temp.weight;
			ret.push_back(o);
			ret.push_back(d);
		}

	}
	cout<<"Total size is: "<<total<<endl;
	cout<<"================================================="<<endl;
	return ret;


}
vector<string> Graph::Dijkstra(string city, string destination, float &d)
{
	node* start = getCity(city);
	node* end = getCity(destination);
	bool found = false;
	vector<string> ret;

	// pqueue<node>* hp = new pqueue<node>(100);					//priority queue of nodes
	// Heap would store nodes rather than pointer to nodes(as given in the overloading functions) hence there was no way
	// to access the original pointers to these nodes when they were extracted from the heap. Hence i used simple vectors

	set<node*> visited_nodes;
	visited_nodes.insert(start);

	start->dist = 0;
	node* current = start;

	vector<node*> node_queue;
	for (int i = 0; i < cities.size(); i++)
	{
		if (cities[i] != current)
			node_queue.push_back(cities[i]);
	}


	while(!found)
	{
		for(int i = 0; i<current->edges.size();i++)
		{
			node* edge_dest = current->edges[i].Dest;

			if (visited_nodes.find(edge_dest) != visited_nodes.end())				//Its in the set
			{
				if ((current->dist + current->edges[i].weight)< edge_dest->dist)				//Only update if it is the shorter path
				{
					edge_dest->prev = current;
					edge_dest->dist = current->dist + current->edges[i].weight;
				}
			}
			else																	//Need to insert it in the set
			{
				edge_dest->prev = current;
				edge_dest->dist = current->edges[i].weight + current->dist;
				visited_nodes.insert(edge_dest);									//Insert the pointer to new node in set
				// hp->insertKey(*edge_dest);											//Insert that node in the priority queue
			}	

		}

		// node x = hp->extractMin()


		//removing the min value from vector of nodes
		int  x = 0;
		float min_val=node_queue[0]->dist;
		for (int i = 0; i < node_queue.size(); i++)
		{
			if (node_queue[i]->dist < min_val)
			{
				min_val = node_queue[i]->dist;
				x = i; 
			}
		}

		node* min = node_queue[x];
		//remoove the min from the list(heap)
		node_queue.erase(node_queue.begin()+x);

		if (min->name == end->name)
		{
			float total = min->dist;
			found = true;
			while(min->prev!=NULL)
			{
				ret.push_back(min->name);
				min = min->prev;
			}
			ret.push_back(min->name);
			cout<<"Minimum distance is "<<total<<endl;
			
		}
		else
		{
			current = min;
		}
	}
	std::reverse(ret.begin(),ret.end()); 

	// Resetting back for future queries
	for(int i=0; i< cities.size(); i++)
	{
		cities[i]->dist = FLT_MAX;
		cities[i]->prev = NULL;
	}

	//Print func
	for(int i=0; i< ret.size(); i++)
	{
		cout<<ret[i]<<" ";
	}
	
	return ret;
}

#endif

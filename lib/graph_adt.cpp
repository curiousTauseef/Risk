#include "graph_adt.h"


//02 ;; Return the set of all the vertices of the graph.
std::set<std::string> GraphADT::nodes() const{
	std::set<std::string> export_nodes(set_of_vertices);
	return export_nodes;
	}

//03 ;; Return the set of all the edges of the graph.
std::set<std::string> GraphADT::edges() const{
	std::set<std::string> export_edges(set_of_edges);
	return export_edges;
	}

//04 ;; Return the number of vertices currently present in the graph.
int GraphADT::countAllNodes() const {return number_of_vertices; }

//05 ;; Return the number of edges currently present in the graph.
int GraphADT::countAllEdges() const {return number_of_edges; }

//06 ;; Return the edge between vertices v and w;
// An error occurs if there is no such edge.
Edge GraphADT::getEdge(std::string v, std::string w) const{
	Edge save(thegraph.at(v).at(w));
	return save;}

//07 ;; Return the set of the edges incident on vertex v.
std::set<std::string> GraphADT::incidentEdges(std::string v) const{
	std::set<std::string> set_of_incidents;
	if( thegraph.find(v)!= thegraph.end()){
		node_hashmap::const_iterator node_iterator = thegraph.at(v).begin();
		while(node_iterator != thegraph.at(v).end()){
			set_of_incidents.insert(node_iterator->first);
			*node_iterator++;
			}
		}
	else
		std::cout<<"ERROR: Invalid node"<< std::endl;
	return set_of_incidents;
	}

//08 ;; Return the end-node of edge e distinct from node v
// an error occurs if e is not incident on v.
std::string GraphADT::opposite(std::string u, std::string e) const {
	node_hashmap::const_iterator node_iterator = thegraph.at(u).begin();
	while( node_iterator != thegraph.at(u).end()){
		if( strcmp( e.c_str(), thegraph.at(u).at(node_iterator->first).element.c_str() )==0 )
			return (node_iterator->first);
		*node_iterator++;
		}
	return std::string();
	}

//09 ;; Return the set of the end nodes of edge e.
std::set<std::string> GraphADT::endNodes(std::string edge) const{
	std::set<std::string> setOfEndNodes;
	graph_hashmap::const_iterator graphiter= thegraph.begin();
	while(graphiter != thegraph.end()){
		node_hashmap::const_iterator nodeiter = thegraph.at(graphiter->first).begin();
		while(nodeiter != thegraph.at(graphiter->first).end()){
			if( std::strcmp(thegraph.at(graphiter->first).at(nodeiter->first).edgename.c_str(), edge.c_str()) == 0){
				//std::cout<<"< "<<graphiter->first<<", "<<nodeiter->first<<" >";
				setOfEndNodes.insert(graphiter->first);
				setOfEndNodes.insert(nodeiter->first);
				return setOfEndNodes;
				}
			*nodeiter++;
			}
		*graphiter++;
		}
	return setOfEndNodes;
	}

//10 ;; Test whether nodes v and w are adjacent.
bool GraphADT::areAdjacent(std::string v, std::string w) const{
	if (set_of_vertices.find(v) != set_of_vertices.end() &&
		set_of_vertices.find(w) != set_of_vertices.end()){
		return ( thegraph.at(v).find(w) != thegraph.at(v).end() &&
				 thegraph.at(w).find(v) != thegraph.at(w).end());}
	else
		std::cout<<"ERROR: Cannot find either vertex "<<v<<" or "<<w<<std::endl;
	return false;
	}

//11 ;; Insert a new node
bool GraphADT::insertNode(std::string nodename) {
	if (thegraph.find(nodename) == thegraph.end()){
		//  node_hashmap x;
		thegraph[nodename]= node_hashmap(); //x
		number_of_vertices++;
		set_of_vertices.insert(nodename);
		return true;
		}
	else
		std::cout<<"Error: Could not add vertex."<<std::endl;
		return false;
	}

bool GraphADT::renameNode(std::string oldname, std::string newname){
    set_of_vertices.erase(oldname);
    set_of_vertices.insert(newname);
	auto graph_iter = thegraph.find(oldname);
	if( graph_iter == thegraph.end()){
        return false;
    }
    else{
		thegraph[newname] = node_hashmap(graph_iter->second); //copy everything the node had into a new node
		thegraph.erase(oldname);
		for (graph_iter = thegraph.begin(); graph_iter != thegraph.end(); *graph_iter++){ //iterate through all the nodes
			auto node_iter = (graph_iter->second).find(oldname);
			if (node_iter != (graph_iter->second).end()){
				std::string save = (node_iter->second).edgename;
                Edge e;
                e.edgename = save;
                e.element = save;
                (thegraph[graph_iter->first])[newname] = e;
                (thegraph[graph_iter->first]).erase(oldname);
			}
		}
	}
    return true;
}

//12 ;; Remove node v and all its incident edges
bool GraphADT::removeNode(std::string vertexname){
	if ( set_of_vertices.find(vertexname) != set_of_vertices.end()){
		graph_hashmap::const_iterator graphiter = thegraph.begin();
		while (graphiter != thegraph.end()){
			std::string save = thegraph[graphiter->first][vertexname].edgename;
			set_of_edges.erase(save);
			number_of_edges--;
			thegraph[graphiter->first].erase(vertexname);
			*graphiter++;}
		thegraph.erase(vertexname);
		set_of_vertices.erase(vertexname);
		number_of_vertices--;
        return true;
		}
    else{
        std::cout<<"ERROR: Named vertex " << vertexname << " does not exist."<<std::endl;
        return false;
        }
	}

void GraphADT::insertEdge(std::string v, std::string w) {
	this->insertEdge(v,w, std::to_string(this->number_of_edges+1));
	}

//;13 ;; Create and insert a new undirected edge with
//end vertices v and w and storing element x
void GraphADT::insertEdge(std::string v, std::string w, std::string x) {
	if( thegraph.find(v) != thegraph.end() && thegraph.find(w) != thegraph.end()){
		if(thegraph[v].find(w) == thegraph[v].end() && thegraph[w].find(v) == thegraph[w].end()){
			Edge e;
			e.edgename = x;
			e.element = x;
			(thegraph[v])[w]= e;
			(thegraph[w])[v]= e;
			set_of_edges.insert(x);
			number_of_edges++;
			}
		else
			std::cout<<"ERROR: The edge " << v << " to " << w << " already exists." << std::endl;
		}
	else
		std::cout << "ERROR: Cannot proceed, one or more vertices don't exist." << std::endl;
	}

//14 ;; Remove edge (v, w)
void GraphADT::removeEdge(std::string v, std::string w) {
	if( thegraph.find(v) != thegraph.end() && thegraph.find(w) != thegraph.end()){
		std::string edge = thegraph[v][w].edgename;
		(thegraph[v]).erase(w);
		(thegraph[w]).erase(v);
		set_of_edges.erase(edge);
		number_of_edges--;
		}
	else
		std::cout << "ERROR: Either " << v << " or " << w << " vertices were not found.";
	}

//;15 ;; Return the element associated with edge e.
std::string GraphADT::getEdgeElem(std::string edgename) const {
	std::unordered_map<std::string, std::unordered_map<std::string, Edge> >::const_iterator graphiter = thegraph.begin();
	std::string found = "Not found.";
	while(graphiter != thegraph.end()){
		std::unordered_map<std::string, Edge>::const_iterator node_iter = ((*graphiter).second).begin();
		while(node_iter != ((*graphiter).second).end()){
			if( std::strcmp(edgename.c_str(), (node_iter->second).edgename.c_str() ) == 0)
				return (node_iter->second).element;
			*node_iter++;
			}
		*graphiter++;
		}
	return found;
	}

//16 ;; Replace the element stored at edge e with x
void GraphADT::replaceEdgeElem(std::string edge, std::string x){
	std::unordered_map<std::string, std::unordered_map<std::string, Edge> >::const_iterator graphiter = thegraph.begin();
	while(graphiter != thegraph.end()){
		std::unordered_map<std::string, Edge>::const_iterator node_iter = ((*graphiter).second).begin();
		while(node_iter != ((*graphiter).second).end()){
			if( std::strcmp( edge.c_str(), (node_iter->second).edgename.c_str() ) == 0){
				thegraph[graphiter->first][node_iter->first].element= x;
				thegraph[node_iter->first][graphiter->first].element= x;
				return;
				}
			*node_iter++;
			}
		*graphiter++;
		}
	std::cout<<"ERROR: Edge not found.";
	}


//17 Pretty-printing the set.
void printSet(const std::set<std::string>& set){
	int c=0;
	std::cout<<"< ";
	std::set<std::string>::const_iterator setiter = set.begin();
	while( setiter != set.end() ){
		std::cout<<((c++>0)?", ":"")<<*setiter++;}
	std::cout<<" >"<<std::endl;}

void printEdge(const Edge& e){
	std::cout<<"\nEdgename: "<<e.edgename<<"\nElement: "<<e.element<<std::endl;}

/*
 * Copy constructor
 */
GraphADT::GraphADT(const GraphADT& other) {
	graph_hashmap::const_iterator g_iter = other.thegraph.begin();
	while (g_iter != other.thegraph.end()){
		thegraph[g_iter->first]= node_hashmap(g_iter->second);
		*g_iter++;
		}
	set_of_vertices = string_set(other.set_of_vertices);
	set_of_edges = string_set(other.set_of_edges);
	number_of_edges= other.number_of_edges;
	number_of_vertices= other.number_of_vertices;
	}


bool GraphADT::isEqual(const GraphADT& graph2) const {
	graph_hashmap::const_iterator g_iter = this->thegraph.begin();
	std::set<std::string> notvisited(graph2.set_of_vertices);
	while(g_iter != thegraph.end()){
		if( graph2.set_of_vertices.find(g_iter->first) == graph2.set_of_vertices.end())
			return false;
		else{
			node_hashmap::const_iterator n_iter = thegraph.at(g_iter->first).begin();
			while (n_iter != thegraph.at(g_iter->first).end() ){// g_iter->second.end();
				Edge thisedge = this->thegraph.at(g_iter->first).at(n_iter->first);
				if( graph2.set_of_edges.find(n_iter->second.edgename) == graph2.set_of_edges.end())
					return false;
				else{
					Edge otheredge = graph2.thegraph.at(g_iter->first).at(n_iter->first);
					if ( strcmp(thisedge.edgename.c_str(),
								otheredge.edgename.c_str())!=0 ||
						 strcmp(otheredge.element.c_str(),
								thisedge.element.c_str())!=0  )
						return false;
				}
				*n_iter++;
			}
		}
		notvisited.erase(g_iter->first);
		*g_iter++;
	}
	return (notvisited.size() == 0);
}

bool GraphADT::emptyGraph() {
	return (number_of_vertices==0);
}

GraphADT GraphADT::graph_intersection(const GraphADT& g2) const {
	GraphADT output;
	graph_hashmap::const_iterator g1_it = this->thegraph.begin();
	while(g1_it != this->thegraph.end()){
		//If the vertex in g1 does not exist in g2, then skip it.
		if( g2.set_of_vertices.find(g1_it->first) != g2.set_of_vertices.end()) {
			output.thegraph[g1_it->first]= node_hashmap();
			//cycle through all the edges contained in the node hashmap
			node_hashmap::const_iterator node_iter = g1_it->second.begin();
			while (node_iter != g1_it->second.end() ){
				if( this->thegraph.at(g1_it->first).find(node_iter->first) != thegraph.at(g1_it->first).end() &&
						g2.thegraph.at(g1_it->first).find(node_iter->first) != g2.thegraph.at(g1_it->first).end()){

					output.insertEdge(g1_it->first,node_iter->first);
					  }
				*node_iter++;
				}
			}
		*g1_it++;
		}
	return output;
	}


GraphADT GraphADT::graph_union(const GraphADT& g2) const {
	GraphADT output = copyGraph();
	graph_hashmap::const_iterator g2_it = g2.thegraph.begin();
	while(g2_it != this->thegraph.end()){
		if ( output.thegraph.find(g2_it->first) == output.thegraph.end())
			output.insertNode(g2_it->first);
		//cycle through all the edges contained in the node hashmap
		node_hashmap::const_iterator node_iter = g2_it->second.begin();
		while (node_iter != g2_it->second.end() ){
			if (!output.areAdjacent(g2_it->first,node_iter->first))
				output.insertEdge(g2_it->first,node_iter->first);
			*node_iter++;
			}
		*g2_it++;
		}
	return output;
	}

GraphADT GraphADT::copyGraph() const {
	GraphADT output;
	graph_hashmap::const_iterator g_iter = thegraph.begin();
	while (g_iter != thegraph.end()){
		output.thegraph[g_iter->first]= node_hashmap(g_iter->second);
		*g_iter++;}
	output.set_of_vertices = string_set(set_of_vertices);
	output.set_of_edges = string_set(set_of_edges);
	output.number_of_edges= number_of_edges;
	output.number_of_vertices= number_of_vertices;
	return output;
}

GraphADT GraphADT::graph_difference(GraphADT const& g2) const{
	GraphADT output = copyGraph();
	graph_hashmap::const_iterator g_iter = g2.thegraph.begin();
	while( g_iter != g2.thegraph.end()){
		if(output.set_of_vertices.find(g_iter->first) != output.set_of_vertices.end())
			output.removeNode(g_iter->first);
		*g_iter++;
		}
	return output;
	}


GraphADT GraphADT::graph_complement() const{
	GraphADT output = copyGraph();
	graph_hashmap::const_iterator g_iter = thegraph.begin();
	string_set::const_iterator g2_iter;
	while (g_iter != thegraph.end()){
		g2_iter = set_of_vertices.begin();
		while ( g2_iter != set_of_vertices.end()){
			if (strcmp(g_iter->first.c_str(),(*g2_iter).c_str()) ){ //avoid self-loops
				if( areAdjacent(g_iter->first, *g2_iter) )
					output.removeEdge(g_iter->first, *g2_iter);
				else
					if (!output.areAdjacent(g_iter->first, *g2_iter))
						output.insertEdge(g_iter->first, *g2_iter);
				}
			*g2_iter++;
			}
		*g_iter++;
		}
	return output;
}


void GraphADT::printGraph() const {
	std::cout<<"______________\nPrinting Graph"<<std::endl;
	graph_hashmap::const_iterator g_iter = thegraph.begin();
	while ( g_iter != thegraph.end()){
		std::cout<<"("<<g_iter->first<<")  | ";
		node_hashmap::const_iterator n_iter = g_iter->second.begin();
		while ( n_iter != g_iter->second.end()){
			std::cout<<" < ("<<n_iter->first<<"), «"<<n_iter->second.edgename<<"» > ";
			*n_iter++;
			}
		std::cout<<std::endl;
		*g_iter++;
		}
	std::cout<<"\n\n"<<std::endl;
	}




bool DirectedGraphADT::areAdjacent(std::string v, std::string w) const{
  return false;
}

bool SubGraphADT::renameNode(std::string oldname, std::string newname){
    if(!GraphADT::renameNode(oldname, newname))
        return false;
    else{
        std::string continent_name = countries_continents[oldname];
        allSubgraphs.at(continent_name).erase(oldname);
        allSubgraphs.at(continent_name).insert(newname);
        countries_continents.erase(oldname);
        countries_continents[newname] = continent_name;
    }
    return true;
}

bool SubGraphADT::removeNode(std::string node){
    if(!GraphADT::removeNode(node)){
        return false;
    }
    else{
        std::string continent_name = countries_continents[node];
        allSubgraphs.at(continent_name).erase(node);
        countries_continents.erase(node);
        if(allSubgraphs.at(continent_name).size() == 0){
            allSubgraphs.erase(continent_name);
            return true;
        }
        return false;
    }
}

bool SubGraphADT::insertNode(std::string name_of_country, std::string name_of_continent){
	if (!GraphADT::insertNode(name_of_country))
		return false;
	if(allSubgraphs.find(name_of_continent) == allSubgraphs.end())
		allSubgraphs[name_of_continent]= std::set<std::string>();
	allSubgraphs.at(name_of_continent).insert(name_of_country);
	countries_continents[name_of_country]=name_of_continent;
	return true;
}

string_set SubGraphADT::subgraphContents(const std::string& name_continent){
    if (allSubgraphs.find(name_continent) != allSubgraphs.end()){
        string_set setOfCountries(allSubgraphs.at(name_continent));
        return setOfCountries;
    }
    else
        return string_set();
}

std::string SubGraphADT::getSubgraphName(const std::string& name_country){
	return countries_continents.at(name_country);
}


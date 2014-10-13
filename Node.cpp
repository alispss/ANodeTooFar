// ----------------------------
// projects/node/node.c++
// Copyright (C) 2014
// Alison Spiess
// ----------------------------

// --------
// includes
// --------

#include <iostream> // endl, istream, ostream
#include <utility>  // make_pair, pair
#include <map>
#include <vector>
#include <set>
#include <list>

// WARNING : nothing here has been tested

// ------------
// node_read
// ------------

std::map<int, std::list<int> > graph;
std::vector<std::pair<int, int> > cases;
int caseNo;

// Return false = no more graphs
// Return true = more grpahs
int node_read (std::istream& r) 
{
    graph.clear();
    cases.clear();
    while(true)
    {
        // get number of edges
        int edges;
        r >> edges;
        //std::cout << "Number of Edges: " << edges << std::endl;
        if( edges == 0 )
            return false;

        // read those edges
        for( int i = 0; i < edges; ++i )
        {
            int a, b;
            r >> a >> b;
            //std::cout << "Edge " << i << ": " << a << " " << b << std::endl;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        // read cases
        while(true)
        {
            int a, b;
            r >> a >> b;
            if( a == 0 && b == 0 )
                return true;

            cases.push_back(std::make_pair(a, b));
            //std::cout << "Case: " << a << " " << b << std::endl;
        }
    }
}


// -------------
// node_print
// -------------

inline void node_print (std::ostream& w, int startNode, int ttl, std::map<int , int>& touched) 
{
    std::cout << "Case " << caseNo << ": " << graph.size() - touched.size() << " nodes not reachable from node " << startNode << " with TTL = " << ttl << "." << std::endl;
}


// --------------
// recursive depth first search
// --------------

void depth_first_search(int node, int ttl, std::map<int, int>& touched)
{
    //std::cout << "Node: " << node << ", ttl: " << ttl << std::endl;
    // No more depth
    if(ttl == -1)
        return;

    // Add to nodes we've touched
    touched[node] = ttl;

    // Go through all the adjacent nodes as long as we haven't been there before
    for(int next : graph[node])
    {
        if(touched.find(next) == touched.end() || touched[next] < ttl-1 )
        depth_first_search(next, ttl-1, touched);
    }
}

// ------------
// node_eval
// ------------

void node_eval (std::ostream& w) 
{
    std::map<int, int> touched;
    // Traverse each case & print results
    for(int i = 0 ; i < cases.size() ; ++i)
    {
        caseNo++;
        touched.clear();

        std::pair<int, int> pair = cases[i];

        int startNode = pair.first;
        int ttl = pair.second;

        depth_first_search(startNode, ttl, touched);

        node_print(w, startNode, ttl, touched);

    }
}


// -------------
// node_solve
// -------------

inline void node_solve (std::istream& r, std::ostream& w) 
{
    caseNo = 0;
    while(node_read(r))
    {
        node_eval(w);
    }
}

// ----
// main
// ----

int main () 
{
    node_solve(std::cin, std::cout);
    return 0;
}
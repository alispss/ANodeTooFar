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
        if( edges == 0 )
            return false;

        // read those edges
        for( int i = edges; i < edges; ++i )
        {
            int a, b;
            r >> a >> b;
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
        }
    }
}


// -------------
// node_print
// -------------

inline void node_print (std::ostream& w, int startNode, int ttl, std::set<int>& touched) 
{
    std::cout << "Case " << caseNo << ": " << graph.size() - touched.size() << " nodes not reachable from node " << startNode << " with TTL = " << ttl << "." << std::endl;
}


// --------------
// recursive depth first search
// --------------

void depth_first_search(int node, int ttl, std::set<int>& touched)
{
    // No more depth
    if(ttl == 0)
        return;

    // Add to nodes we've touched
    touched.insert(node);

    // Go through all the adjacent nodes as long as we haven't been there before
    for(int next : graph[node])
    {
        if(touched.find(next) != touched.end())
            depth_first_search(next, ttl-1, touched);
    }
}

// ------------
// node_eval
// ------------

int node_eval (std::ostream& w) 
{
    std::set<int> touched;

    // Traverse each case & print results
    while(!cases.empty())
    {
        caseNo++;
        touched.clear();

        std::pair<int, int> pair = cases.back();
        cases.pop_back();

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
    while(node_read(r))
    {
        caseNo = 0;
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
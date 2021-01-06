// this is the ONLY file you should edit and submit to D2L
//Author:Quenten Welch 30054505
//Date Nov 30 2020


#include "common.h"
#include "deadlock_detector.h"
#include <iostream>
#include <string>
#include <map>
#include  <unordered_map>
#include <vector>
/// this is the function you need to implement
/// parameter edges[] contains a list of request and assignment edges
///   example of a request edge, process "p1" resource "r1"
///     "p1 -> r1"
///   example of an assignment edge, process "XYz" resource "XYz"
///     "XYz <- XYz"
/// Parameters edge_index and cycle[] are used to return
/// results back to the caller.
///
/// You need to process edges[] one edge at a time, and run a deadlock
/// detection after each edge.
///
/// As soon as you detecte a deadlock, you need to set edge_index to the index of the edge
/// in edges[] that caused the deadlock. For example, edges[7] caused the deadlock,
/// then set edge_index=7. You must also populete cycle[] with the names of
/// processes that are in a deadlock. You can then return from the function without
/// processing any other edges.
///
/// To indicate deadlock was detected after processing all edges, you must
/// set edge_index = -1 and clear cycle[] e.g. by calling cycle.clear()
///

class Graph {
	public:
	std::unordered_map<std::string, std::vector<std::string>> adj_list;
	std::unordered_map<std::string, int> out_counts;
}g ;


bool is_proccess(std::string x){
  auto check = split(x);
  if(check[1].compare("proc") == 0){
return true;}
else{
return false;
}

}






void detect_deadlock(
    const std::vector<std::string> & edges,
    int & edge_index,
    std::vector<std::string> & cycle
)
{

cycle.clear();
edge_index = -1;
std::vector<std::string> zeros;
std::string right = "->";

    for(int i = 0; i < (int) edges.size(); i++){
        std::vector<std::string> edge = split(edges[i]);
	if (edge[1].compare(right) == 0){
	    g.out_counts[edge[0]] ++;
	    g.adj_list[edge[2]].push_back(edge[0] + " proc"); }

	else{g.adj_list[edge[0] + " proc" ].push_back(edge[2]);
	   g.out_counts[edge[2]] ++;
}
std::cout << i << std::endl;
//for(auto const& pair: g.out_counts){
//std::cout <<pair.first << " count " << pair.second <<std::endl;
//}
//start topological sort
auto out = g.out_counts;
zeros = {};
for(auto const& pair: g.adj_list){

if(g.out_counts[pair.first] == 0 )
	zeros.push_back(pair.first);

}
//for(int i = 0; i < zeros.size(); i++){
//std::cout <<"zeros "<< zeros[i]<<std::endl;
//}

while ((int) zeros.size() > 0) {
	auto n = zeros.back();
        zeros.pop_back();
	for(const auto &n2 : g.adj_list[n]){
		out[n2]--;
		if(out[n2] == 0){
		zeros.push_back(n2);
		}

}

}

 cycle.clear();
 for(auto const& pair : g.adj_list){
   auto checker = pair.first;

   if(out[split(checker)[0]] > 0 && is_proccess(checker) ){
     cycle.push_back(split(checker)[0]);
   }
 }
 if(cycle.size() > 1){
   edge_index = i;
   return;
 }

    }


cycle.clear();
}

#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <queue>

int toid(int x) { return x -1 ; } 

const int infinity_c = std::numeric_limits<int>::max() ; 

using path_t = std::pair<int, int> ; 

struct edge_t { 
	explicit edge_t(int id): 
		id(id) {}
	int id ; 
	int cost = infinity_c;
        bool is_dest = false;
	int cost_from_g = infinity_c;
	int cost_from_h = infinity_c;
	std::vector<path_t> neig; 
}; 

using pq_elem_t = std::pair<int, int> ; 

struct pq_comp_t {
	bool operator()(const pq_elem_t&a, const pq_elem_t&b)  {
		return a.second <  b.second;
	}
}; 


using pq_t = std::priority_queue<
		pq_elem_t,
                std::vector<pq_elem_t>,
		pq_comp_t
                >  ;

bool found_all_ends(std::vector<bool>& vis , std::vector<edge_t>& g)
{
	
	for (const auto& X : g) { 
		if (X.is_dest && !vis[X.id]) {
			return false;
		}
	}

	return true; 
}







void solve(std::vector<edge_t>& graf, int s, int g, int h) 
{
	auto visited = std::vector<bool>(graf.size(), false);
	pq_t pq ; 
	
	pq.push({s, 0}); 

	while (!visited[g] && !visited[h] ){ 
		auto [id, unused] = pq.top();
		pq.pop();	
		if (visited[id]) { 
			continue;
		}
		visited[id] = true;
		for (const auto [neig, cost]: graf[id].neig ) {
			int newcost = graf[id].cost + cost ;
			if (newcost < graf[neig].cost){
				graf[neig].cost = newcost;
				pq.push({neig, newcost});
			}			
		}
	}
	pq = pq_t();
	graf[g].cost_from_g = 0 ; 
	pq.push({g,graf[g].cost_from_g}); 
	
	visited = std::vector<bool>(graf.size(), false);

	while (!found_all_ends(visited, graf)){
		auto [id, unused] = pq.top();
		pq.pop();	
		if (visited[id]) { 
			continue;
		}
		visited[id] = true;
		for (const auto [neig, cost]: graf[id].neig ) {
			int newcost = graf[id].cost_from_g + cost ;
			if (newcost < graf[neig].cost_from_g){
				graf[neig].cost_from_g = newcost;
				pq.push({neig, newcost});
			}			
		}
	}
	pq = pq_t();
	graf[h].cost_from_h = 0 ; 
	pq.push({h,graf[h].cost_from_h}); 
	
	visited = std::vector<bool>(graf.size(), false);

	while (!found_all_ends(visited, graf)){
		auto [id, unused] = pq.top();
		pq.pop();	
		if (visited[id]) { 
			continue;
		}
		visited[id] = true;
		for (const auto [neig, cost]: graf[id].neig ) {
			int newcost = graf[id].cost_from_h + cost ;
			if (newcost < graf[neig].cost_from_h){
				graf[neig].cost_from_h = newcost;
				pq.push({neig, newcost});
			}			
		}
	}

	std::vector<int> res ; 
	int minimum = infinity_c; 
	const int minG = graf[g].cost;
	const int minH = graf[h].cost; 

	for (auto X: graf) { 
		if (!X.is_dest) {
			continue;
		}
		if (minimum > minG + X.cost_from_h){
			minimum = minG + X.cost_from_h;
			res.clear();
			res.push_back(X.id);
		}
		if (minimum ==  minG + X.cost_from_h){
			res.push_back(X.id);
		}
		if (minimum > minH + X.cost_from_g){
			minimum = minH + X.cost_from_g;
			res.clear();
			res.push_back(X.id);
		}
		if (minimum ==  minH + X.cost_from_g){
			res.push_back(X.id);
		}
	}
	
	std::sort(res.begin(), res.end(), std::greater<int>());
	for (auto X: res) {
		std::cout << X+1 << ' '; 

	}
	std::cout << '\n';

}

int main() 
{
	int COUNT ;
	std::cin >> COUNT;
	for (int i = 0 ; i < COUNT ; i++ ) {
		int n, m, t;
		std::cin >> n >> m >> t ; 
		std::vector<edge_t> graf;
		for (int j = 0 ; j < n ; j ++) { 
	      		graf.push_back(edge_t(j));
		}
		int s,g,h; 
		std::cin >> s >> g >> h ; 
		graf[toid(s)].cost = 0 ; 
		
		for (int j = 0 ; j < m ; j ++) { 
			int a, b , d ;
			std::cin >>a>>b>>d;
			if ( (a==g && b==h) || (a==h&&b==g) ) {
				continue;
			}
			graf[toid(a)].neig.push_back({toid(b), d});
			graf[toid(b)].neig.push_back({toid(a), d});
		}
		for (int j = 0 ; j < t ; j ++) { 
			int x;
			std::cin >> x ; 
			graf[toid(x)].is_dest = true; 
		}
		
		solve(graf,toid(s),toid(g),toid(h)); 		
	
	}		




	return 0 ;
}

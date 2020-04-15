#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdint>
#include <numeric>
#include <limits> 

const int64_t infinity_c = std::numeric_limits<int64_t>::max();
int64_t add(int64_t a, int64_t b)
{
	if (a == infinity_c || b == infinity_c) { 
		return infinity_c;
	} else { 
		return a + b ;
	} 
}

struct edge_t {
	int id;
	int64_t in;
	int64_t out_down = infinity_c;
	int64_t out_up = 0; 
	int64_t cost; 
	std::vector<int> neig_ids; 
	bool is_leaf = true; 
};

void dfs_ordering(std::vector<int> &result, const std::vector<edge_t> &m, int pos)
{
	if ( m[pos].is_leaf ) { 
	 	return ; 
	} 	
	result.push_back(pos);
	for (auto x: m[pos].neig_ids){
		dfs_ordering(result, m, x);
	}
	
}

int64_t solve(std::vector<edge_t> &net, std::vector<bool> &b)
{
	std::vector<int> ordering;
	ordering.reserve(net.size());
	auto boss_index = int(std::distance(
		b.begin(),
		std::find(b.begin(), b.end(), true)
	));
	dfs_ordering(ordering, net, boss_index);

	for (auto index = ordering.rbegin(); index != ordering.rend(); index++) {
		auto &e = net[*index];
		e.in = std::accumulate(
			e.neig_ids.begin(),
			e.neig_ids.end(),
			e.cost,
			[&net](int64_t acc, int id){
				return add(
				  acc,
		   		  net[id].out_up
				); 
			}
		);
		e.out_up = std::accumulate(
			e.neig_ids.begin(),
			e.neig_ids.end(),
			int64_t(0),
			[&net](int64_t acc, int id){
				return add(
				  acc,
				  std::min(net[id].in,net[id].out_down)
				); 
			}
		);
		e.out_down = 
		    std::accumulate(
			e.neig_ids.begin(),
			e.neig_ids.end(),
			int64_t(0),
			[&net](int64_t acc, int id){
				return add(
				  acc,
				  std::min(net[id].in,net[id].out_down)
				); 
			}
		    ) + 
		    std::accumulate(
			e.neig_ids.begin(),
			e.neig_ids.end(),
			infinity_c,
			[&net](int64_t acc, int id) { 
				return std::min(acc, std::max(int64_t(0), net[id].in - net[id].out_down));
			}
		    );
	}
	return std::min(net[boss_index].in, net[boss_index].out_down);
	
}

int main()
{
	int n;
	std::cin >> n ; 

	std::vector<edge_t> net; 
	net.reserve(n);
	auto bossmap = std::vector<bool>(n, true);
	for (int i = 0; i < n ; i++) { 
		edge_t e;
	       	e.id = i ; 	
		std::cin >> e.cost;
		int b; 
		std::cin >> b;
		if (b > 0){
			e.neig_ids.reserve(b);
			e.is_leaf=false;
			for (int j = 0 ; j < b ; j ++ ) {
				int s ;
				std::cin >> s;
				bossmap[s]=false;
				e.neig_ids.push_back(s);
			}
		} else { 
			e.in = e.cost;
		}

		net.push_back(e);
	}
	std::cout << solve(net, bossmap); 
	return 0 ;
}

#include <iostream>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <string>
#include <array>
#include <cstdint>
#include <vector>

struct edge_t
{
	int id;
	uint16_t neigmap = 0 ; 
	bool locked = false; 
};

using color_map_t = std::array<uint16_t, 12>;
color_map_t color_map = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ; 

int find(const std::vector<edge_t>& g, int index, int presult )
{
        if (std::size_t(index) >= g.size()) {
                return presult;
        }
	if (g[index].locked){
		return find(g, index+1, presult);
	}
	int result = 12;
	for (int i = 1 ; i <= 11 ; i ++ ){  
		if (!( color_map[i] & g[index].neigmap )) { 
			color_map[i] |= 1<<index;
			int partial = find(g, index+1, std::max(presult,i) );
			color_map[i] ^= 1<<index;
			if (partial < result){
				result = partial;
			}
		}
	}
	
	return result;
}

int solve(std::vector<edge_t>& g)
{
	if (g.size() == 1) { 
		return 1; 
	}
	for (uint32_t i = g[0].neigmap , j = 0 ; i > 0 ; i >>=1, j++) {
		if (i&1){
			color_map[2] |= (1<<j);
			g[j].locked = true;
			break;
		}
	}
	g[0].locked = true; 
	color_map[1] |= (1<<0);
	return find(g,1,2); 
}

int main()
{
	int n ; 
	std::cin >> n;
	std::cin.ignore();
	auto g= std::vector<edge_t>(n);

	for (int id = 0 ; id < n ; id++ ) { 
		g[id].id = id; 
		std::string line;
		std::getline(std::cin, line);
		std::istringstream linestream(line);
		std::for_each(
			std::istream_iterator<int>(linestream),
	                std::istream_iterator<int>(),
			[&g,id](int x){ g[id].neigmap |= 1<<x; } 
		);
	}
	std::cout << solve(g); 	
	return 0;
}

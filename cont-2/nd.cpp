#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set> 
#include <iostream> 




struct node_t
{
	node_t(int id, int x, int y) : 
		id(id) , x(x), y(y) {}

	int x;
	int y;
	int id; 
	int rank = 0 ;
	std::vector<int> neig;
};



bool fits(node_t a, node_t b){
	return a.x < b.x && a.y < b.y; 
}

void solve(std::vector<node_t>& m){ 
	
	

	for (int i = 0 ; i < m.size() ; i++ ){ 
		for (int j = 0 ; j < m.size() ; j++ ){
			if (fits(m[i], m[j]) 	   ) { 
				m[j].neig.push_back(i); 
			}
		}
	}		

	auto comp = [](std::pair<int, int>&a , const  std::pair<int, int>& b){
		return a.second < b.second;  
	}; 
	std::priority_queue<
		std::pair<int, int>, 
		std::vector<std::pair<int, int>>,
	       	decltype(comp)> queue(comp);

	for (int i = 0 ; i < m.size() ; i ++ ){ 
		queue.push({i, m[i].rank});
	}

	while (queue.size() > 0 ) { 
		auto  [id, rank]= queue.top() ;
		queue.pop();

		if (rank != m[id].rank){
		       continue ;
		}	       

		for(auto neigid: m[id].neig){ 
			if (m[neigid].rank < m[id].rank + 1 ) { 
				m[neigid].rank = m[id].rank + 1 ; 
				queue.push({neigid, m[neigid].rank }); 
			} 
		}

	}

	std::vector<int>rankcount(m.size() + 1,0 ) ; 
	for (const auto node: m){ 
		rankcount[node.rank] ++ ; 
	}

	std::cout << *std::max_element(rankcount.begin(), rankcount.end()) << '\n';



}


int main()
{
	int C ; 
	std::cin >> C ; 
	for (int i = 0 ; i < C ; i ++ ) { 
		int m ; 
		std::cin >> m ; 
		std::vector<node_t> matr; 
		for (int j = 0 ; j < m ; j ++ ) { 
			int x, y;
			std::cin >> x >> y ; 
			matr.push_back(node_t(j, x, y));
		}
		solve(matr) ; 
	}

	return 0 ;
}

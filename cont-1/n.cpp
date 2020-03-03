#include <cassert>
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <queue>


struct state_t{
	int pos_;
	int jump_;
	int cost_;
	bool operator> (const state_t& o) const {
		return cost_ > o.cost_; 
	}
	bool operator==(const state_t& o ) const {
		return  cost_ == o.cost_
		   	&& jump_ == o.jump_
			&& pos_ == o.pos_;
	}
};

struct state_hash_t{
	std::size_t operator() (const state_t& s) const {
		return s.pos_ ^ (s.jump_ << 1) ^ (s.cost_ << 2);
	}
};

using pq_t = std::priority_queue<
		state_t, 
		std::vector<state_t>, 
		std::greater<state_t> 
		>  ;

int solve(const std::vector<int>& c)
{
	const int goal = c.size() - 1; 
	pq_t pq; 
	pq.push({1,1 ,c[1] });
	std::unordered_set<state_t, state_hash_t> existing ;
	existing.insert({ 1,  1 , c[1] });


	while (true) { 
		assert(!pq.empty());

		auto cs = pq.top();
		pq.pop();
		
		if (cs.pos_ == goal){
			return cs.cost_;
		}
		
		if ( cs.pos_ != 0 && cs.pos_ - cs.jump_ > -1){
			int newpos = cs.pos_ - cs.jump_; 
			state_t ns = {
				newpos,
				cs.jump_,
				cs.cost_ + c[newpos]
		       	};
			if (existing.find(ns) == existing.end()){
				pq.push(ns);
				existing.insert(ns);	
			}
		}

		if ( cs.pos_ + cs.jump_ + 1 <= goal ){
			int newpos = cs.pos_ + cs.jump_ +1;
			state_t ns = {
				newpos,
				cs.jump_ +1,
				cs.cost_ + c[newpos]
		       	};
			if (existing.find(ns) == existing.end()){
				pq.push(ns);
				existing.insert(ns);	
			}

		}
		
	}


	assert(!"Whoa Buddy");
	return -1 ; 
}





int main()
{
	int N;
	std::cin >> N;

	std::vector<int> costs;
	costs.reserve(N);
	for (int i = 0 ; i < N ; i ++)  { 
		int c;
		std::cin >> c;
		costs.push_back(c);
	}

	std::cout << solve(costs) << std::endl;
	
	return 0 ;		

}

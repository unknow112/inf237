#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector> 
struct activity_t{
	int from;
	int to;
	int index;
};

void format_result(int casen, bool is_succ, const std::vector<char> &s){
	std::cout << "Case #" << casen << ": ";
	if (is_succ) {
		std::copy(s.begin(), s.end(), std::ostream_iterator<char>(std::cout, ""));
	} else {
		std::cout << "IMPOSSIBLE";
	}
	std::cout << '\n';
}

void solve(int casen, std::vector<activity_t>& tsks) 
{
	auto result = std::vector<char>(tsks.size());
	
	std::sort(
	    tsks.begin(), 
	    tsks.end(), 
	    [](const activity_t& a, const activity_t &b){ 
	        return a.from < b.from ;
	    }
	);
	
	int C_until = 0;
	int J_until = 0;
	for (const auto &act: tsks){
		if (C_until <= act.from ) {
			result[act.index] = 'C';
			C_until = act.to; 
			continue;
		} 
		if (J_until <= act.from ) {
			result[act.index] = 'J';
			J_until = act.to; 
			continue;
		} 
		format_result(casen, false, result);
		return; 

	}
	format_result(casen, true, result);


}

 

int main()
{
	int t;
	std::cin >> t;
	for (int casen = 1 ; casen <= t ; casen++){
		int n;
		std::cin >> n ; 
		auto eh =std::vector<activity_t>(n);
		for (int i = 0 ; i < n ; i++){
			eh[i].index = i; 
			std::cin >> eh[i].from >> eh[i].to;
		}
		solve(casen, eh);
	}
	return 0 ;
}


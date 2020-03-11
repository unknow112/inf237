#include <iostream>
#include <string>

const std::string imp = "impossible";

int main(){
	int L,W;
	std::cin >> L >> W ; 

	if (L*26 < W  || W < L ) { 
		std::cout <<imp ;
		return 0 ;
	}
	
	int chlievik = W / L ; 

	auto res = std::string(L,  'a'+chlievik - 1 ) ; 
	if (chlievik*L == W) {
		std::cout << res ; 
		return 0 ;
	}
	int remain = W - chlievik * L ;
	
	for (auto& l: res) {
		int max = std::min (remain, 'z' - l  ); 
		l += max ;
		remain -= max; 
		if (remain == 0) {
			break ; 
		}
	}
	
	std::cout << res ;

	return 0 ;
}

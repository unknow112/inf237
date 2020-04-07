#include <iostream>
#include <cstdint>
#include <vector>


struct block_t {
	uint32_t overlaps = 0; 
	int id;
	int area;
	int w;
	int h;
	int x;
	int y;
};

bool overlap(const block_t &a, const block_t &b)
{
	if (a.id == b.id) {
		return false;
	}
	return !( a.x + a.w <= b.x
		  || b.x + b.w <= a.x
		  || a.y + a.h <= b.y
		  || b.y + b.h <= a.y
		);

}

//bool overlap(const block_t &a, const block_t &b)
//{
//	if (a.id == b.id){ 
//		return false;
//	}
//
//	bool x_overlap = false;
//	if (a.x < b.x) { 
//		x_overlap = b.x - a.x < a.w;
//	} else { 
//		x_overlap = a.x - b.x < b.w;
//	} 
//
//	bool y_overlap = false; 
//	if (a.y < b.y) { 
//		y_overlap = b.y - a.y < a.h;
//	} else { 
//		y_overlap = a.y - b.y < b.h;
//	}
//
//	return x_overlap && y_overlap;
//}




int solve(std::vector<block_t>& articles)
{
	for (auto &a: articles ) {
		a.area = a.w * a.h;
	       for (const auto &b: articles) {
		       if (overlap(a,b)){
			       a.overlaps |= (1<<b.id);
		       }
	       }
	}	       
	int total = int(articles.size());
	uint32_t max = (1<<total) ; 
	int result = 0 ; 
	for (uint32_t perm = 0 ; perm < max ; perm++) {
		int perm_area = 0 ; 
		for (uint32_t i = perm, j = 0 ; i > 0 ; i >>=1, j++) {
			if (!(i & 1)){
				continue ; 
			}	
		       if  (!(articles[j].overlaps & perm)) { 
				perm_area += articles[j].area;
		       } else {
				perm_area = 0 ; 
				break;
			}
		}
		if (perm_area > result) {
			result = perm_area;
		}
	}
	return result;
}

int main()
{
	int n = 0 ;
	std::cin >> n ;
	for (; n > 0 ; std::cin>> n) {
		std::vector<block_t> articles;
		for (int i=0 ; i < n ; i ++ ) {
			block_t tmp;
			tmp.id=i;
			std::cin >> tmp.w  >> tmp.h >> tmp.x >> tmp.y;
			articles.push_back(tmp);
		}
		int res= solve(articles);
		std::cout << res << '\n' ;
	}

}

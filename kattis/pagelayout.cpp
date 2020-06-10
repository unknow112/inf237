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


int find(const std::vector<block_t>& ar, uint32_t comb, int index, int presult )
{
	if (std::size_t(index) >= ar.size()) {
		return presult;
	}
	if (ar[index].overlaps & comb) { 
		return find(ar, comb, index+1, presult);
	} else {
		return std::max( 
			find(ar, uint32_t(comb | (1<<(index))), 
			     index+1, presult+ar[index].area),
			find(ar, comb, index+1, presult)
		);	
	}


}


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
	return find(articles, uint32_t(0), 0, 0);
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
		std::cout << res << '\n';
	}

}

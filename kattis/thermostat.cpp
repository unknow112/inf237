#include <vector>
#include <cstdint>
#include <cmath>
#include <iostream> 


struct unit_t
{
	unit_t() = default;
	unit_t (int64_t low, int64_t high):
		low(low), 
		high(high),
		abs_top(high-low)
	{}
	int64_t low;
	int64_t high;
	int64_t abs_top;
};

int64_t euclid(int64_t a, int64_t b)
{
	return ((a%b) == 0 ) ? b : euclid(b, a%b );
}
void query(const std::vector<unit_t>& t, int64_t from, int64_t to, int64_t val)
{
	int64_t numerator = (val - t[from].low)
		        * t[to].abs_top
			+ t[to].low 
			* t[from].abs_top;
	int64_t denominator = t[from].abs_top;
	int64_t gcd = euclid(std::abs(numerator), std::abs(denominator)); 
	if (denominator < 0 ){ 
		numerator *= -1;
		denominator *= -1; 
	}
	std::cout << int64_t(numerator/gcd) << '/' << int64_t(denominator/gcd) <<'\n';
}




int main() 
{ 
	int64_t N, Q;
	std::cin >> N >> Q;
	std::vector<unit_t> table; 
	table.reserve(N+1); 
	table.push_back({});
	for (int64_t i = 0 ; i < N ; i ++ ) { 
		int64_t l, h;
		std::cin >> l >> h;
		table.push_back({l,h}); 
	}
	for (int64_t i = 0 ; i < Q ; i ++ ) { 
		int64_t from, to, val ; 
		std::cin >> from >> to >> val ; 
		query(table, from, to, val);
	}
	return 0 ;
} 

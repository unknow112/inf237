#include <cassert>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

struct point_t 
{
	point_t() = default;
	point_t(double x, double y): 
		x(x), y(y)
	{}
	double x;
	double y;
}; 


double area(const std::vector<point_t> &p)
{
	double result = 0.0;
	for (std::size_t i = 0 ; i < p.size() ; i++ ){
		result += p[i].x * p[(i+1)%p.size() ].y -
			p[i].y * p[(i+1)%p.size() ].x ;
	}
	return std::abs(result/2);
		
}
const auto x_axis_segment = std::make_pair(point_t(0.,0.), point_t(1.,0.));

struct cosine_compare_f
{
	explicit cosine_compare_f(point_t p):
		p_(p), px_(p.x+1 , p.y) 
	{}

	bool operator()(point_t a, point_t b)
	{
		return cos_with(a) > cos_with(b); 
	}

private:
	double cos_with(point_t a) {
		return  ( std::pow(px_.x-a.x,2) 
			  + std::pow(px_.y-a.y,2) 
			  - std::pow(p_.x - a.x ,2) 
			  - std::pow(p_.y - a.y, 2)   
			  -1 ) /
			(2*std::sqrt(std::pow( p_.x - a.x,2 ) 
				     + std::pow(p_.y - a.y, 2))); 
	}
	const point_t p_;
	const point_t px_;
};

enum orientation_t
{
	clockwise,
	cclockwise
};

orientation_t orientation(point_t a, point_t b, point_t c )
{
	double res = (b.y - a.y)*(c.x - b.x) 
		- (c.y - b.y)*(b.x - a.x);

	if (res < 0) {
		return orientation_t::cclockwise;
	} else { 
		return orientation_t::clockwise;
	}
}
double solve(std::vector<point_t> &p)
{
	if (p.size() < 3) { 
		return 0 ; 
	} 
	auto leftmost = std::min_element(
		p.begin(), 
		p.end(), 
		[](point_t a, point_t b){
			if (a.y == b.y) {
				return a.x < b.x ;
			} else { 
				return a.y < b.y ; 
			}
		}
	); 
	std::swap(*leftmost, p.front());
	std::sort(p.begin() + 1 , p.end(), cosine_compare_f(p.front()));
	auto solution = std::vector<point_t>(p.begin(), p.begin() + 2 );
	solution.reserve(p.size());
	auto current = p.begin() + 2; 
	while (current  != p.end()) { 
		assert(p.size() >= 2);
		if (orientation(*(solution.end() - 2), 
				*(solution.end() - 1), 
				*current) == orientation_t::cclockwise
		) { 
			solution.pop_back();
			if (solution.size() >= 2) { 
				continue;
			}
		}
		solution.push_back(*current);
		current ++ ; 
	}
	return area(solution);	
}

int main() 
{
	
	int n;
	std::cin>>n;
	std::cout << std::setprecision(1)<< std::fixed;
	for ( ; n > 0 ; std::cin >> n){
		std::vector<point_t> f;
		for (int i = 0 ; i < n ; i++ ) { 
			point_t p ;
			std::cin >>p.x >> p.y;
			f.push_back(p);
		}
		std::cout << solve(f) << '\n';
	}

	return 0;
}

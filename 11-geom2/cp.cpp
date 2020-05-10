#include <cassert>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>


struct point_t {
	double x;
	double y;
	int id;
};

double euclid(point_t a, point_t b)
{
	return  std::sqrt(
		std::pow(a.x-b.x,2) 
		+ std::pow(a.y-b.y,2) 
	);
}

struct result_t
{
	result_t()=default;
	result_t(point_t a, point_t b):
		a(a),b(b),dist(euclid(a,b))
	{}
	point_t a;
	point_t b;
	double dist = std::numeric_limits<double>::max();
	bool operator<(const result_t& o) const
	{
		return dist < o.dist;
	}

};

using point_t_v_i = decltype(std::vector<point_t>().begin());

bool ord_by_x(point_t a, point_t b)
{
	return a.x < b.x ;
}

bool ord_by_y(point_t a, point_t b)
{
	return a.y < b.y ;
}

auto solve(point_t_v_i first, point_t_v_i last) 
{
	auto size = std::distance(first, last);
	assert(size > 1);
       	if (size == 2){ 
		return result_t(*first, *(first+1));
	}
	if (size == 3){
		return std::min({
			result_t(*first, *(first+1)),
			result_t(*first, *(first+2)),
			result_t(*(first+1), *(first+2))
		});
	}
	auto split = first + int(size / 2);
	auto sub_res = std::min( solve(first, split), solve(split, last));
	double split_x = (*(split-1)).x;
	point_t_v_i left_edge = std::upper_bound(
		first, 
		split, 
		split_x - sub_res.dist,
		[](double x, point_t p){
			return x < p.x; 
		}
	);
	point_t_v_i right_edge = std::lower_bound(
		split,
		last,
		split_x + sub_res.dist,
		[](point_t p, double x){
			return p.x < x;
		}
	);
	std::sort(left_edge, split, ord_by_y);
	std::sort(split, right_edge, ord_by_y);
	result_t corner_res; 
	point_t_v_i sr = split;
	for (auto l = left_edge; l != split; l ++) {
		while (sr != right_edge 
		       && (*sr).y + sub_res.dist< (*l).y
		) { 
			sr++;
		}
		for(auto r = sr; 
		    r != right_edge && (*r).y < (*l).y + sub_res.dist; 
		    r++ 
		) {
			corner_res = std::min(corner_res, result_t(*l, *r));
		}	
	}
	std::sort(left_edge, right_edge, ord_by_x); 


	return std::min( sub_res, corner_res);
}

int main()
{
	int n;
	std::cin>>n;
	std::cout << std::setprecision(2)<< std::fixed;
	std::vector<point_t> ps;
	for ( ; n > 0 ; std::cin >> n){
		ps.reserve(n);
		for (int i = 0 ; i < n ; i ++ ) {
			double x,y;
			std::cin >> x >> y; 
			ps.push_back({x,y,i});
		}
		std::sort( ps.begin(), ps.end(), ord_by_x);
		auto res = solve(ps.begin(), ps.end());
		std::cout << res.a.x << ' ' << res.a.y 
			<< ' ' << res.b.x << ' ' << res.b.y 
			<< '\n';

		ps.clear();
	}
	return 0 ; 
} 

#include <cassert>
#include <utility> 
#include <iostream> 
#include <vector>




struct point_t
{
	double x_;
	double y_;

};

using line_t = std::pair<point_t, point_t > ;

enum orientation_t
{
	clockwise,
	cclockwise
};

orientation_t orientation(point_t a, point_t b, point_t c )
{
	double res = (b.y_ - a.y_)*(c.x_ - b.x_) 
		- (c.y_ - b.y_)*(b.x_ - a.x_);

	if (res < 0) {
		return orientation_t::cclockwise;
	} else { 
		return orientation_t::clockwise;
	}
}

bool lines_intersect(line_t a, line_t b)
{
	return orientation(a.first,a.second,b.first) != orientation(a.first, a.second, b.second)
	       && orientation(b.first,b.second,a.first) != orientation(b.first,b.second,a.second);}

int solve(std::vector<line_t>& l) 
{
	int count = 0 ; 


	for (auto as = l.begin(); as != l.end() ; as++ ) {
		for (auto bs = as + 1 ; bs != l.end() ; bs++) {
			for (auto cs = bs + 1 ; cs != l.end() ; cs++) { 
				if ( lines_intersect(*as, *bs) && lines_intersect(*bs, *cs) && lines_intersect(*cs, *as) 
				) { 

					count++; 
			
				}



			}



		}
	}



	return count;
}

int main()
{

	int n; 
	std::cin >> n;

	std::vector<std::pair<point_t, point_t > > lines ;
	while (n > 0){

		for (int i = 0 ; i < n ; i ++) { 
			double x1,y1,x2,y2;
			std::cin >> x1 >> y1 >> x2 >> y2;
			lines.push_back({{x1,y1},{x2,y2}});
		}

		std::cout << solve(lines) << '\n';


		lines.clear(); 
		std::cin >> n;
	}

}
	

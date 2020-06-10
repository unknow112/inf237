#include <cassert> 
#include <cmath>
#include <iomanip>
#include <vector>
#include <iostream> 


struct point_t{
	double x;
	double y;
};

double area(point_t a, point_t b, point_t c)
{
	return std::abs((a.x * (b.y - c.y)
		+ b.x * (c.y - a.y) 
		+ c.x * (a.y - b.y) 
	       )) / 2;
}

int main ()
{
	point_t a, b, c;
	int tc;
	std::cin >> a.x >> a.y 
		 >> b.x >> b.y 
		 >> c.x >> c.y 
		 >> tc;	
	
	double A = area(a,b,c);
	
	int count = 0 ; 
	for (int i = 0 ; i < tc ; i ++ ) {
		point_t d ;
       		std::cin >> d.x >> d.y;
 		
		if (A == area(a,b,d) + area(a,d,c) + area(d,b,c)) {
			count++;
		}		
		

	}
	std::cout << std::setprecision(1)<< std::fixed << A << '\n' << count << '\n';
	
	return 0; 
}

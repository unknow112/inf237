#include <iostream>
#include <cmath>



int main () 

{ 


	int c ; 
	std::cin >> c; 
	
	unsigned long long res = 0 ; 
	for ( int i = 0 ; i < c ; i ++ ) { 
		char x ; 
		std::cin >> x ; 
		if ('O' == x) {
			res += std::pow( 2 , (c - i - 1)) ;
		}

	}
	std::cout << res ; 


	return 0 ;

}





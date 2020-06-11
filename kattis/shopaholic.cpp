
#include <cassert>
#include <algorithm>
#include <vector>
#include <iostream>




int main()
{
	int c;
	std::cin >> c;
	
	std::vector<int> prices(c);
	for (int i= 0 ; i < c ; i++ ){
		std::cin >> prices[i];
	}

	std::sort(prices.begin(), prices.end(), std::greater<>());
	
	int res = 0 ;
	for (int i= 2 ; i < c ; i+=3 ){
		res += prices[i];
	}

	std::cout << res <<'\n';
	return 0 ;


}

#include <iostream>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>


const std::string S_OK = "safe and sound";

const std::string S_BAD = "bumper tap at time ";

const int MIN_DIFF = 5;


struct car_t
{
	explicit car_t(int pos):
	       pos_(pos){}

	int pos_ = -1;
	bool is_moving_ = false;
	std::vector<int> changes_ ; 
};

enum car_n
{
	A,
	B
};


int main()
{
	int  y; 
	
	std::cin >> y;
	car_t A{y};

	
	std::cin >> y;
	car_t B{y};

	std::cin >> y;
	A.changes_.reserve(y);
	for(int i=0; i < y ; i++) {
		int x;
		std::cin >> x;
		A.changes_.push_back(x);
	}

	std::cin >> y;
	B.changes_.reserve(y);
	for(int i=0; i < y ; i++) {
		int x;
		std::cin >> x;
		B.changes_.push_back(x);
	}



	int t = 0;
	
	auto t_A = A.changes_.begin();
	auto t_B= B.changes_.begin();
	while ( t_A != A.changes_.end() && t_B != B.changes_.end()){
		if  ( *t_A == *t_B  ) {
			if (A.is_moving_){
				A.pos_ += *t_A - t ;
			} 
			if (B.is_moving_) { 
				B.pos_ += *t_B - t; 
			}
			B.is_moving_ = ! B.is_moving_;
			A.is_moving_ = ! A.is_moving_;	
			t = *t_A  ;
			if (std::abs(A.pos_ - B.pos_) < MIN_DIFF) { 
				std::cout << S_BAD << t;
				return 0;
			}
			t_A ++;
			t_B ++;
		} else if ( *t_A < *t_B) { 
			if (A.is_moving_){
				A.pos_ += *t_A - t ;
			} 
			if (B.is_moving_) { 
				B.pos_ += *t_B - t; 
			}
			t = *t_A;
			A.is_moving_ = ! A.is_moving_;	
			if (std::abs(A.pos_ - B.pos_) < MIN_DIFF) { 
				std::cout << S_BAD << t;
				return 0;
			}
			t_A ++;
		
		} else {
			if (A.is_moving_){
				A.pos_ += *t_B - t ;
			} 
			if (B.is_moving_) { 
				B.pos_ += *t_B - t; 
			}
			t = *t_B;
			A.is_moving_ = ! A.is_moving_;	
			if (std::abs(A.pos_ - B.pos_) < MIN_DIFF) { 
				std::cout << S_BAD << t;
				return 0;
			}
			t_B ++;

		}

	}

	auto& longer = A;
	auto& shorter = B;
	auto t_longer = t_A;
	if (t_A == A.changes_.end()) {
		std::swap(longer, shorter);
		t_longer = t_B;
	} 


	for( ; t_longer != longer.changes_.end() ; t_longer++) { 
 		if (shorter.is_moving_) {
			shorter.pos_ += *t_longer - t ; 
		}
 		if (longer.is_moving_) {
			longer.pos_ += *t_longer - t ; 
		}
		t = *t_longer; 
		if (std::abs(shorter.pos_ - longer.pos_) < MIN_DIFF ){
			std::cout << S_BAD  << t; 
			return 0 ;
		}
		
		longer.is_moving_ = ! longer.is_moving_;
	}
	if (A.is_moving_ == B.is_moving_){
		std::cout << S_OK ; 
		return 0 ;
	} else  {
		if ( (A.is_moving_ && (A.pos_ > B.pos_)   ) || ( B.is_moving_ && B.pos_> A.pos_) ){
			std::cout << S_OK ; 
			return 0;
		} else { 
			std::cout << S_BAD << std::abs(A.pos_  - B.pos_) - MIN_DIFF - 1 + t ;
			return 0;
		}
	}
}


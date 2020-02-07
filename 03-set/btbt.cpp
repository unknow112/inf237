#include <cassert>
#include <iostream>
#include <cmath>
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
	
	void update(int at) {
		if (is_moving_){ 
			pos_ += at - t_;	
			t_ = at;	
		} else { 
			t_ = at; 
		}
	}

	void startstop(){
		is_moving_ = ! is_moving_;
	}

	int t_  = 0; 
	int pos_ = -1;
	bool is_moving_ = false;
	std::vector<int> changes_ ; 
};

bool is_colision(const car_t&a, const car_t&b)
{
	assert ( a.t_ == a.t_ ) ; 
	return std::abs(a.pos_ - b.pos_) < MIN_DIFF;
}

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

	
	auto t_A = A.changes_.begin();
	auto t_B = B.changes_.begin();
	while (true) {
		if ( t_A == A.changes_.end() || t_B == B.changes_.end() ) {
			break;
		}
		if ( *t_A == *t_B ){
			A.update(*t_A);
			B.update(*t_B);
			A.startstop();
			B.startstop();
			t_A++ ; t_B++ ; 
		} else if ( *t_A < *t_B ) {
			A.update(*t_A);
			A.startstop();
			B.update(*t_A);
			t_A++;
		} else { 
			A.update(*t_B);
			B.update(*t_B);
			B.startstop();
			t_B++; 
		}

		if (is_colision(A,B)) {
			std::cout << S_BAD << A.t_ << std::endl;	
			return 0 ;
		}

	}
	if (t_A == A.changes_.end() && t_B == B.changes_.end()){
		std::cout << S_OK << std::endl;
		return 0 ;
	}
	// let the longer one be A 
	if (t_A == A.changes_.end()){
		std::swap(A,B);
		std::swap(t_A, t_B);	
	}	
        for (; t_A != A.changes_.end() ; t_A++ ) { 
		A.update(*t_A);
		B.update(*t_A);
		A.startstop();
		if (is_colision(A,B)) {
			std::cout << S_BAD << A.t_ << std::endl ;
			return 0 ; 
		}
	}
	if (A.is_moving_ == B.is_moving_) {
		std::cout << S_OK << std::endl;
		return 0 ; 
	} else if (A.is_moving_ && A.pos_ > B.pos_ ) {
		std::cout << S_OK << std::endl;
		return 0;
	} else if (B.is_moving_ && B.pos_ > A.pos_ ) {
		assert(!"hmmm");
		return 0;
	} else {
		int bumptime = A.t_ + std::abs(A.pos_ - B.pos_) - MIN_DIFF + 1;
		std::cout << S_BAD << bumptime << std::endl;
		return 0;
	}
	assert(!"Whoa dont go here");
	return 0 ;
}

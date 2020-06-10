#include <iostream>


int main(){
        int n;
        std::cin >> n;
        for (int i=0;i<n ; i++){
                int a ;
                std::cin >> a; 
                std::cout << a << ((a % 2 == 0 )? " is even":" is odd") << std::endl;
        }
}

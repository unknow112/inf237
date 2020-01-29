#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>


int main()
{

        int64_t n, m;
        std::cin >> n >> m ;
        std::vector <int64_t> can_sizes;
        can_sizes.reserve(n);
        std::vector <int64_t> colors_amout;
        colors_amout.reserve(m);
        
        for (int64_t i = 0 ; i < n ; i++) {
                int64_t x;
                std::cin >> x;
                can_sizes.push_back(x);
        }
        for (int64_t i = 0 ; i < m ; i++) {
                int64_t x;
                std::cin >> x;
                colors_amout.push_back(x);
        }
        std::sort(can_sizes.begin(), can_sizes.end());
        std::sort(colors_amout.begin(), colors_amout.end());


        int64_t wasted = 0;
        auto can = can_sizes.begin();
        for (auto color: colors_amout){
                while ( color > *can ){
                        can++;
                }
                wasted += *can - color;

        }



        std::cout << wasted ;
          


}


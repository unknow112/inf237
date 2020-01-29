#include <iostream>
#include <vector>
#include <algorithm>




int main()
{

        int n, m;
        std::cin >> n >> m ;
        std::vector <int> can_sizes;
        can_sizes.reserve(n);
        std::vector <int> colors_amout;
        colors_amout.reserve(m);
        
        for (int i = 0 ; i < n ; i++) {
                int x;
                std::cin >> x;
                can_sizes.push_back(x);
        }
        for (int i = 0 ; i < m ; i++) {
                int x;
                std::cin >> x;
                colors_amout.push_back(x);
        }
        std::sort(can_sizes.begin(), can_sizes.end());
        std::sort(colors_amout.begin(), colors_amout.end());


        int wasted = 0;
        auto can = can_sizes.begin();
        for (auto color: colors_amout){
                while ( color > *can ){
                        can++;
                }
                wasted += *can - color;

        }



        std::cout << wasted ;
          


}


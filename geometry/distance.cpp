#include <vector>
#include <climits>
#include <cstring>
#include "iostream"

int main(){
    int n, k;
    std::cin >> n >> k;
    std::vector<long long> elems(n, 0);
    std::vector<std::vector<long long>> difs(n);

    for (int i = 0; i < n; ++i){
        std::cin >> elems[i];
        for (int j = 0; j < i; ++j){
            long long dif = llabs(elems[i] - elems[j]);
            difs[i].push_back(dif);
            difs[j].push_back(dif);
        }
    }
    // a = difs[i]
    // n = difs[i].size()
    // max = min
    // m = k
    for (int i = 0; i < n; ++i){
        long long mins[k];
        int l = 0;
        for (int j = 0; j < difs[i].size(); ++j){
            int m = 0;
            while (m < l && difs[i][j] >= mins[m]) m++;

            if(m == l){
                if(l < k){
                    mins[l++] = difs[i][j];
                }
            }else{
                memmove(mins + m + 1, mins + m, (l < k ? l - m: l - m - 1) * sizeof(long long));
                mins[m] = difs[i][j];
                if(l < k) ++l;
            }
        }
        long long sum = 0;
        for (int j = 0; j < k; ++j){
            sum += mins[j];
        }
        std::cout << sum << " ";
    }

    return 0;
}

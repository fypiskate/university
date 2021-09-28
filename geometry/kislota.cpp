#include "iostream"
#include "vector"

int main(){
    int n;
    std::cin >> n;
    std::vector<long long> reservs(n, 0);
    for (int i = 0; i < n; ++i){
        std::cin >> reservs[i];
    }
    long long count = 0;
    for (int i = 1; i < n; ++i){
        long long dif = reservs[i] - reservs[i-1];
        if (dif < 0) {
            count = -1;
            break;
        }else if (dif == 0){
            continue;
        }else{
            count += dif;
        }
    }
    std::cout << count;
    return 0;
}

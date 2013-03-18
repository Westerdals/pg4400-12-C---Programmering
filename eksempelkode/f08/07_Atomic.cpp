#include <thread>
#include <iostream>
#include <vector>
#include <atomic>
int main(){
    std::atomic<int> counter(0);
    std::vector<std::thread> threads;
    for(int i = 0; i < 5; ++i){
        threads.push_back(std::thread([&counter](){
            for(int i = 0; i < 100000; ++i){
                counter++;
            }
        }));
    }
    for(auto& thread : threads){
        thread.join();
    }
    std::cout << counter << std::endl;
    return 0;
}

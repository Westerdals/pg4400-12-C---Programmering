#include <thread>
#include <iostream>
#include <vector>
int main(){
    int counter=0;
    std::mutex mutex;
    std::vector<std::thread> threads;
    for(int i = 0; i < 5; ++i){
        threads.push_back(std::thread([&counter,&mutex](){
            for(int i = 0; i < 100000; ++i){
                std::lock_guard<std::mutex> guard(mutex);
                if(counter >= 1000)
                    return; 
                counter++; //NOT ATOMIC 
            }
        }));
    }
    for(auto& thread : threads){
        thread.join();
    }
    std::cout << counter << std::endl;
    return 0;
}

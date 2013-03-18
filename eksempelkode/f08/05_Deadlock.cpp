#include <thread>
#include <iostream>
#include <vector>
int main(){
    int counter=0;
    std::mutex mutexA,mutexB;
    std::vector<std::thread> threads;
    for(int i = 0; i < 5; ++i){
        threads.push_back(std::thread([&counter,&mutexA,&mutexB](){
            for(int i = 0; i < 100000; ++i){
                if(i%2==0){
                    mutexA.lock();
                    mutexB.lock();
                }
                else{
                    mutexB.lock();
                    mutexA.lock();
                }
                counter++; //NOT ATOMIC 
                mutexB.unlock();
                mutexA.unlock();
            }
        }));
    }
    for(auto& thread : threads){
        thread.join();
    }
    std::cout << counter << std::endl;
    return 0;
}

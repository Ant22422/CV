// Arow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <thread>
#include <mutex>
std::mutex g_queue;

void arow1(const int& val) {
    for (int i = 0; i <= 500; i++) {
        g_queue.lock();
        std::cout << val <<"->" << std::endl;
        g_queue.unlock();
        Sleep(1000);
    }
}

int main()
{
    
        std::thread firstArow(arow1,1);
        std::thread secondArow(arow1, 2);
        std::thread threeArow(arow1, 3);
        std::thread fourArow(arow1, 4);
    Sleep(15000);
    firstArow.join();
    secondArow.join();
    threeArow.join();
    fourArow.join();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

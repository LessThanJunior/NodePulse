#include <iostream>
#include "collector.hpp"

int main() {
    SystemCollector collector;
    auto snapshot = collector.collect();
    
    std::cout << "-------CPU-------\n";
    std::cout << "CPU Model: " << snapshot.metrics.cpu.model << "\n";
    std::cout << "CPU Cores: " << snapshot.metrics.cpu.cores << "\n";
    std::cout << "CPU Threads: " << snapshot.metrics.cpu.cores << "\n";
    std::cout << "CPU Usage: " << snapshot.metrics.cpu.usage << "%\n";

    std::cout << "\n------Memory------\n";
    std::cout << "Memory Usage: " << snapshot.metrics.memory.usage/1024./1024 << "GB \n";
    std::cout << "Memory Free: " << snapshot.metrics.memory.free/1024./1024 << "GB \n";
}
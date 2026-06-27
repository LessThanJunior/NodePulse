#include <iostream>
#include "collector.hpp"

int main() {
    SystemCollector collector;
    auto snapshot = collector.collect();
    
    std::cout << "CPU Cores: " << snapshot.metrics.cpu.cores << "\n";
    std::cout << "CPU Usage: " << snapshot.metrics.cpu.usage << "%\n";
}
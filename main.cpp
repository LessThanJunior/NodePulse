#include <chrono>
#include <array>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <thread>
#include "collector.hpp"

int main() {
    SystemCollector collector;
    while(true){
        auto previousSnapshot = collector.collect();
        std::this_thread::sleep_for(std::chrono::seconds(SystemCollector::seconds));
        auto currentSnapshot = collector.collect();
        std::time_t now = std::time(nullptr);

        std::cout << "-------CPU-------\n";
        std::cout << "CPU Model: " << previousSnapshot.metrics.cpu.model << "\n";
        std::cout << "CPU Cores: " << previousSnapshot.metrics.cpu.cores << "\n";
        std::cout << "CPU Threads: " << previousSnapshot.metrics.cpu.cores << "\n";
        std::cout << "CPU Usage: " << previousSnapshot.metrics.cpu.usage << "%\n";

        std::cout << "\n------Memory------\n";
        std::cout << "Memory Usage: " << std::setprecision(2) << previousSnapshot.metrics.memory.usage / 1024. / 1024. << "GB \n";
        std::cout << "Memory Free: " << std::setprecision(2) << previousSnapshot.metrics.memory.free / 1024. / 1024. << "GB \n";

        std::cout << "\n------Network------\n";
        std::cout << "Network received: " << std::fixed << std::setprecision(2) 
            << (currentSnapshot.metrics.network.receivedBytes - previousSnapshot.metrics.network.receivedBytes) / 1000. << "kB \n";
        std::cout << "Network transmitted: " << std::fixed << std::setprecision(2) 
            << (currentSnapshot.metrics.network.transmittedBytes - previousSnapshot.metrics.network.transmittedBytes) / 1000. << "kB \n";


        std::cout << "\n------GPU---------\n";
        std::cout << "Gpu temperature: " << previousSnapshot.metrics.gpu.temp << "\n";
        std::cout << "Gpu usage: " << previousSnapshot.metrics.gpu.usage << "\n";
        std::cout << "Time now: " << std::ctime(&now);
        std::cout << "\n";
    }
}
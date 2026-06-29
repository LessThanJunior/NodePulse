#include <iomanip>
#include <iostream>
#include "collector.hpp"

int main() {
    SystemCollector collector;
    while(true){
        auto snapshot = collector.collect();
        std::time_t now = std::time(nullptr);

        std::cout << "-------CPU-------\n";
        std::cout << "CPU Model: " << snapshot.metrics.cpu.model << "\n";
        std::cout << "CPU Cores: " << snapshot.metrics.cpu.cores << "\n";
        std::cout << "CPU Threads: " << snapshot.metrics.cpu.cores << "\n";
        std::cout << "CPU Usage: " << snapshot.metrics.cpu.usage << "%\n";

        std::cout << "\n------Memory------\n";
        std::cout << "Memory Usage: " << std::setprecision(3) << snapshot.metrics.memory.usage / 1024. / 1024. << "GB \n";
        std::cout << "Memory Free: " << std::setprecision(3) << snapshot.metrics.memory.free / 1024. / 1024. << "GB \n";

        std::cout << "\n------Network------\n";
        std::cout << "Network received: " << std::fixed << std::setprecision(2) << snapshot.metrics.network.receivedBytes / 1000. << "kB \n";
        std::cout << "Network transmitted: " << std::fixed << std::setprecision(2) << snapshot.metrics.network.transmittedBytes / 1000. << "kB \n";

        std::cout << "Time now: " << std::ctime(&now);
        std::cout << "\n";
    }
}
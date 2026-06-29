#include "collector.hpp"
#include "metrics.hpp"
#include <chrono>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <thread>

std::string splitAfter(const std::string& message, char delimiter){
    size_t indexSplit = message.find(delimiter);
    std::string substringUnformatted = message.substr(indexSplit + 1);
    return substringUnformatted;
}

std::string splitBefore(const std::string& message, char delimiter){
    size_t indexSplit = message.find(delimiter);
    std::string substringUnformatted = message.substr(0, indexSplit);
    return substringUnformatted;
}

void trim(std::string& message){
    message.erase(std::remove(message.begin(), message.end(), ' '));
}

uint16_t SystemCollector::seconds = 1;

void SystemCollector::setTimeout(uint16_t seconds){
    this->seconds = seconds;
}

CpuData LinuxBackend::readCpu(){
    CpuData cpu;
    std::fstream stream;
    stream.open("/proc/cpuinfo", std::ios_base::in);
    if(!stream.is_open())
        std::cerr << "Can't open file /proc/cpuinfo\n";

    std::string cpuInfo;
    int row = 1;
    while(std::getline(stream, cpuInfo)){
        std::string formatted = splitAfter(cpuInfo, ':');
        if(row == 5) cpu.model = formatted.substr(1);
        else if(row == 11) { trim(formatted); cpu.threads = std::stoul(formatted); }
        else if(row == 13) { trim(formatted); cpu.cores = std::stoul(formatted); }
        else if(row > 13) break;
        row++;
    }
    stream.close();
    cpu.usage = 80;
    return cpu; 
}

MemoryData LinuxBackend::readMemory(){
    MemoryData memory;
    std::fstream stream;
    stream.open("/proc/meminfo", std::ios_base::in);
    if(!stream.is_open())
        std::cerr << "Can't open file /proc/meminfo\n";

    std::string memoryInfo;
    int row = 1;
    uint64_t total = 0;

    while(std::getline(stream, memoryInfo)){
        std::string formatted = splitAfter(memoryInfo, ':');
        trim(formatted);

        if(row == 1) total = std::stoull(formatted);
        else if(row == 3) memory.free = std::stoull(formatted);
        else if(row > 3) break;
        row++;
    }
    memory.usage = total - memory.free;
    stream.close();
    return memory;
};

void setNetworkData(const std::string& interfaceName, NetworkData& network){
    std::fstream stream;
    stream.open("/proc/net/dev", std::ios_base::in);
    if(!stream.is_open())
        std::cerr << "Can't open file /proc/net/dev\n";

    std::string networkInfo;
    std::getline(stream, networkInfo);
    std::getline(stream, networkInfo);

    while (std::getline(stream, networkInfo)) {
        if(splitBefore(networkInfo, ':') == interfaceName){
            std::string data = splitAfter(networkInfo, ':');
            std::stringstream stringstream(data);
            unsigned long long dummy;
            stringstream >> network.receivedBytes;
            for(int i = 0; i < 7; i++) stringstream >> dummy;
            stringstream >> network.transmittedBytes;
        }
    }
}

NetworkData LinuxBackend::readNetwork(){
    NetworkData previous, current;
    setNetworkData("enp3s0", previous);
    std::this_thread::sleep_for(std::chrono::seconds(SystemCollector::seconds));
    setNetworkData("enp3s0", current);
    NetworkData speed;
    speed.receivedBytes = current.receivedBytes - previous.receivedBytes;
    speed.transmittedBytes = current.transmittedBytes - previous.transmittedBytes;
    return speed;
};

DiskData LinuxBackend::readDisk(){
    DiskData disk;
    disk.free = 20;
    disk.usage = 124;
    return disk;
};

SystemMetricsSnapshot SystemCollector::collect(){
    SystemMetricsSnapshot snapshot;
    snapshot.metrics.cpu = backend->readCpu();
    snapshot.metrics.memory = backend->readMemory();
    snapshot.metrics.disk = backend->readDisk();
    snapshot.metrics.network = backend->readNetwork();
    return snapshot;
};
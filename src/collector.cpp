#include "collector.hpp"
#include "metrics.hpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <algorithm>

std::string substr(const std::string& message, char delimiter){
    size_t indexSplit = message.find(delimiter);
    std::string substringUnformatted = message.substr(indexSplit + 1);
    return substringUnformatted;
}

void trim(std::string& message){
    message.erase(std::remove(message.begin(), message.end(), ' '));
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
        std::string formatted = substr(cpuInfo, ':');
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
        std::string formatted = substr(memoryInfo, ':');
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

NetworkData LinuxBackend::readNetwork(){
    NetworkData network;
    network.networkRx = 20.3;
    network.networkTx = 14.3;
    network.ip = "###.###.###.##";
    return network;
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
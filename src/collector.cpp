#include "collector.hpp"
#include "metrics.hpp"

CpuData LinuxBackend::readCpu(){
    CpuData cpu;
    cpu.cores = 4;
    cpu.usage = 80;
    return cpu; 
}

MemoryData LinuxBackend::readMemory(){
    MemoryData memory;
    memory.free = 20;
    memory.usage = 124;
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
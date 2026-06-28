#ifndef METRICS_HPP
#define METRICS_HPP
#include <string>
#include <cstdint>

struct SystemInfo{
    std::string os;
    std::string hostname;
    std::string agentVersion;
    std::string kernelVersion;
};

struct CpuData{
    double usage;
    uint16_t temp;
    uint16_t cores;
    uint16_t threads;
    std::string model;
};

struct MemoryData{
    // in kB;
    uint64_t usage;
    uint64_t free;
};

struct DiskData{
    uint64_t usage; 
    double free;
};

struct NetworkData{
    double networkRx;
    double networkTx;
    std::string ip;
};

struct SystemMetrics{
    CpuData cpu;
    MemoryData memory;
    DiskData disk;
    NetworkData network;
};

struct SystemMetricsSnapshot{
    SystemInfo info;
    SystemMetrics metrics;
};





#endif
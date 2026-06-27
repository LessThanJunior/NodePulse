#ifndef METRICS_HPP
#define METRICS_HPP
#include <string>

struct SystemInfo{
    std::string os;
    std::string hostname;
    std::string agentVersion;
    std::string kernelVersion;
};

struct CpuData{
    double usage;
    int cores;
};

struct MemoryData{
    double usage;
    double free;
};

struct DiskData{
    double usage;
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
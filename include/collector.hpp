#ifndef COLLECTOR_HPP
#define COLLECTOR_HPP
#include "metrics.hpp"
#include <memory>

class BaseCollector{
public:
    virtual SystemMetricsSnapshot collect() = 0;
    virtual ~BaseCollector() = default; 
};

class BaseBackend{
public:
    virtual CpuData readCpu() = 0;
    virtual MemoryData readMemory() = 0;
    virtual NetworkData readNetwork() = 0;
    virtual DiskData readDisk() = 0;
    virtual ~BaseBackend() = default;
};

class WindowsBackend : public BaseBackend{
public:
    CpuData readCpu() override;
    MemoryData readMemory() override;
    NetworkData readNetwork() override;
    DiskData readDisk() override;
};

class LinuxBackend : public BaseBackend{
public:
    CpuData readCpu() override;
    MemoryData readMemory() override;
    NetworkData readNetwork() override;
    DiskData readDisk() override;
};

class BaseBackendFactory{
public:
    static std::unique_ptr<BaseBackend> create(){
        #if __linux__
            return std::make_unique<LinuxBackend>();

        #elif _WIN32
            return std::make_unique<WindowsBackend>();

        #endif
    }
};

class SystemCollector : public BaseCollector{
    std::unique_ptr<BaseBackend> backend;
public:
    static uint16_t seconds;
    SystemCollector() : backend(BaseBackendFactory::create()){}
    SystemMetricsSnapshot collect() override;
    void setTimeout(uint16_t seconds);
};

#endif
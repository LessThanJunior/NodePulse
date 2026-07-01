#ifndef COLLECTOR_HPP
#define COLLECTOR_HPP
#include "metrics.hpp"
#include <memory>
#include <string>

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

class GpuBase{
public:
    virtual GpuData readGpu() = 0; 
    virtual ~GpuBase() = default;
};

class GpuNvidia : public GpuBase{
public:
    GpuData readGpu() override;
};

class GpuBaseFactory{
    public:
    static std::unique_ptr<GpuBase> create(){
        std::string command = "nvidia-smi --version";
        std::unique_ptr<FILE, decltype(&pclose)> nvidia(popen(command.c_str(), "r"), pclose);
        if(nvidia){
            return std::make_unique<GpuNvidia>();
        }
    }
};

class SystemCollector : public BaseCollector{
    std::unique_ptr<BaseBackend> backend;
    std::unique_ptr<GpuBase> gpuBackend;
public:
    static uint16_t seconds;
    SystemCollector() : backend(BaseBackendFactory::create()), gpuBackend(GpuBaseFactory::create()){}
    SystemMetricsSnapshot collect() override;
    void setTimeout(uint16_t seconds);
};

#endif
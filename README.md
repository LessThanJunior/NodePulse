# NodePulse

NodePulse is a cross-platform lightweight system monitoring agent written in C++. It collects system metrics (CPU, Memory, Disk, Network) and sends them to a remote RESTful API / WebSocket server for real-time monitoring and remote device management.

## Features

- **Cross-Platform Support:** Native backends for both Linux and Windows.
- **Resource Monitoring:** Tracks CPU cores/usage, RAM, Disk space, and Network interfaces.
- **Remote Control (In Progress):** Remote command execution and screen streaming.

## Architecture

The project utilizes a Factory Pattern to decouple the OS-specific data collection from the main logic:
- `SystemCollector`: The high-level orchestrator that manages data snapshots.
- `LinuxBackend` / `WindowsBackend`: OS-specific implementations for low-level system calls.

## Usage

Here is a quick example of how to collect metrics locally:

```cpp
#include <iostream>
#include "collector.hpp"

int main() {
    SystemCollector collector;
    auto snapshot = collector.collect();
    
    std::cout << "CPU Cores: " << snapshot.metrics.cpu.cores << "\n";
    std::cout << "CPU Usage: " << snapshot.metrics.cpu.usage << "%\n";
}

```

## Building the Project

### Prerequisites

* C++17 compatible compiler (GCC, Clang, or MSVC)
* CMake (version 3.20 or higher)

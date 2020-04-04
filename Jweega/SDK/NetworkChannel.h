#pragma once

#include "VirtualMethod.h"

class NetworkChannel {
public:
    VIRTUAL_METHOD(float, getLatency, 9, (int flow), (this, flow))
    VIRTUAL_METHOD(float, getAvgLatency, 10, (int flow), (this, flow))

    std::byte pad[44];
    int chokedPackets;
};

#ifndef PQ_COMMON_H
#define PQ_COMMON_H
#include <queue>
#include <mutex>
#include "struct_packet.h"

// Buffer for incoming flow (3 buffers)
extern std::mutex flowBufferLocks[5];
extern std::queue<struct_packet> flowBuffers[5];

// Buffer for internal (classed) 3 buffers
extern std::mutex trafficClassedBufferLocks[3];
extern std::queue<struct_packet> trafficClassedBuffers[3];

void logger(std::ofstream& log, struct_packet packet, bool calculateTime = false);

#endif //PQ_COMMON_H

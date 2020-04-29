#include <iostream>
#include <thread>
#include "thread_trafficClassificator.h"
#include "common.h"
#include "thread_flowGenerator.h"

// declare from common (global)
std::mutex trafficClassedBufferLocks[];
std::queue<struct_packet> trafficClassedBuffers[];

void pushToSpecificPriorityQueue(struct_packet packet, const int definedClassification[])
{
    if(definedClassification[0] == packet.trafficType)
    {
        std::lock_guard<std::mutex> lock2(trafficClassedBufferLocks[0]);
        trafficClassedBuffers[0].push(packet);
    }
    else if(definedClassification[1] == packet.trafficType)
    {
        std::lock_guard<std::mutex> lock2(trafficClassedBufferLocks[1]);
        trafficClassedBuffers[1].push(packet);
    }
    else
    {
        std::lock_guard<std::mutex> lock2(trafficClassedBufferLocks[2]);
        trafficClassedBuffers[2].push(packet);
    }
}

void thread_trafficClassificator(int threadId, const int definedClassification[])
{
    using namespace std::literals::chrono_literals;

    while(true)
    {
        for(unsigned int i = 0; i < sizeof(flowBuffers)/sizeof(flowBuffers[0]); i++)
        {
            while (!flowBuffers[i].empty())
            {
                std::lock_guard<std::mutex> lock1(flowBufferLocks[i]);
                struct_packet packet = flowBuffers[i].front();
                packet.classifiedAt = packet.scheduledAt = std::chrono::high_resolution_clock::now();
                pushToSpecificPriorityQueue(packet, definedClassification);
                flowBuffers[i].pop();
            }
        }
        std::this_thread::sleep_for(20ms);
    }
}
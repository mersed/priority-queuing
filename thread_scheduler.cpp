#include <iostream>
#include <thread>
#include <fstream>
#include "thread_scheduler.h"
#include "common.h"

struct struct_statistic {

};

void thread_scheduler(int threadId)
{
    using namespace std::literals::chrono_literals;

    std::ofstream log;
    log.open("../logs/scheduler", std::fstream::out);

    std::ofstream queuesStatisticsLog;
    queuesStatisticsLog.open("../logs/queues_statistic", std::fstream::out);
    while(true)
    {

        if(!trafficClassedBuffers[0].empty()) {
            while (!trafficClassedBuffers[0].empty())
            {
                std::lock_guard<std::mutex> lock2(trafficClassedBufferLocks[0]);
                struct_packet packet = trafficClassedBuffers[0].front();
                packet.scheduledAt = std::chrono::high_resolution_clock::now();
                logger(log, packet, true);
                trafficClassedBuffers[0].pop();
            }
        }
        else if(!trafficClassedBuffers[1].empty()) {
            while (!trafficClassedBuffers[1].empty())
            {
                std::lock_guard<std::mutex> lock2(trafficClassedBufferLocks[1]);
                struct_packet packet = trafficClassedBuffers[1].front();
                packet.scheduledAt = std::chrono::high_resolution_clock::now();
                logger(log, packet, true);
                trafficClassedBuffers[1].pop();
            }
        }
        else if(!trafficClassedBuffers[2].empty()) {
                while (!trafficClassedBuffers[2].empty())
                {
                    std::lock_guard<std::mutex> lock2(trafficClassedBufferLocks[2]);
                    struct_packet packet = trafficClassedBuffers[2].front();
                    packet.scheduledAt = std::chrono::high_resolution_clock::now();
                    logger(log, packet, true);
                    trafficClassedBuffers[2].pop();
                }
        }

        // Lets log queue stats here
        // queuesStatisticsLog << "Number of packets in high traffic queue: " +

        std::this_thread::sleep_for(12ms);
    }
}
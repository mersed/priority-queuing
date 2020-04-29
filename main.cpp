#include <iostream>
#include <thread>
#include <chrono>
#include "thread_flowGenerator.h"
#include "thread_trafficClassificator.h"
#include "thread_scheduler.h"

using namespace std::literals::chrono_literals;

int main()
{
    // Traffic type TRAFFIC_TYPE_STREAMING_MEDIA (10)
    // Traffic type TRAFFIC_TYPE_GAMING (20)
    // Traffic type TRAFFIC_TYPE_WEB (30)

    // Simulation of PC1
    int flow1PacketProbabilities[] = {80, 10, 10};
    std::thread flow1Worker(
        thread_flowGenerator,                   // Thread function
        0,                                      // Thread id
        std::chrono::milliseconds(100),     // Generate one packet every ...
        flow1PacketProbabilities,               // Generate packets of 3 different traffic types with these probabilities
        500,                                    // Number of packets to be generated
        "192.168.100.10"                        // Ip representation of machine generating packets
    );

    // Simulation of PC2
    int flow2PacketProbabilities[] = {80, 10, 10};
    std::thread flow2Worker(
        thread_flowGenerator,
        1,
        std::chrono::milliseconds(100),
        flow2PacketProbabilities,
        500,
        "192.168.100.50"
    );

    // Simulation of PC3
    int flow3PacketProbabilities[] = {80, 10, 10};
    std::thread flow3Worker(
        thread_flowGenerator,
        2,
        std::chrono::milliseconds(100),
        flow3PacketProbabilities,
        500,
        "192.168.100.100"
    );

    // Simulation of PC4
    int flow4PacketProbabilities[] = {1, 1, 98};
    std::thread flow4Worker(
        thread_flowGenerator,
        3,
        std::chrono::milliseconds(100),
        flow4PacketProbabilities,
        500,
        "192.168.100.150"
    );

    // Simulation of PC5
    int flow5PacketProbabilities[] = {1, 98, 1};
    std::thread flow5Worker(
        thread_flowGenerator,
        4,
        std::chrono::milliseconds(100),
        flow5PacketProbabilities,
        500,
        "192.168.100.200"
    );

    // Worker thread for classification of packets
    int definedClassification[] = {
        TRAFFIC_TYPE_STREAMING_MEDIA,
        TRAFFIC_TYPE_GAMING,
        TRAFFIC_TYPE_WEB
    };
    std::thread classificationThread(thread_trafficClassificator, 50, definedClassification);

    // Worker thread for scheduling
    std::thread schedulingThread(thread_scheduler, 51);

    flow1Worker.join();
    flow2Worker.join();
    flow3Worker.join();
    flow4Worker.join();
    flow5Worker.join();
    classificationThread.join();
    schedulingThread.join();
    return 0;
}

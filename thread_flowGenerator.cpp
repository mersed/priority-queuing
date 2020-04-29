#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include "thread_flowGenerator.h"
#include "struct_packet.h"
#include "common.h"

// declare from common (global)
std::mutex flowBufferLocks[];
std::queue<struct_packet> flowBuffers[];

struct struct_statistic {
    int counter = 0;
    int totalStreamPackets = 0;
    int totalGamingPackets = 0;
    int totalWebPackets = 0;
};

static int randomWithProbabilities(const int x, const int y, const int z, const int px, const int py, const int pz)
{
    srand(time(NULL));
    int r = rand() % 100 + 1;

    if (r <= px)
        return x;
    if (r <= (px+py))
        return y;
    else
        return z;
}

static int generateTrafficType(const int trafficProbabilities[])
{
    int trafficType = randomWithProbabilities(
            TRAFFIC_TYPE_STREAMING_MEDIA,
            TRAFFIC_TYPE_GAMING,
            TRAFFIC_TYPE_WEB,
            trafficProbabilities[0],
            trafficProbabilities[1],
            trafficProbabilities[2]
    );

    return trafficType;
}

std::string mapTrafficTypeToIndicator(int trafficType)
{
    std::string trafficTypeIndicator = "STREAMING_MEDIA";
    if(trafficType == TRAFFIC_TYPE_GAMING)
    {
        trafficTypeIndicator = "GAMING";
    }
    else if(trafficType == TRAFFIC_TYPE_WEB)
    {
        trafficTypeIndicator = "WEB";
    }

    return trafficTypeIndicator;
}

void pushPacketToFlow(const int threadId, const struct_packet packet)
{
    std::lock_guard<std::mutex> lock(flowBufferLocks[threadId]);
    flowBuffers[threadId].push(packet);
}

void thread_flowGenerator(
    const int threadId,
    const std::chrono::milliseconds trafficRate,
    const int trafficProbabilities[],
    const int numberOfPackets,
    const std::string ipAddress
)
{
    using namespace std::literals::chrono_literals;

    std::ofstream log;
    log.open("../logs/flow-generator-" + boost::lexical_cast<std::string>(threadId), std::fstream::out);
    struct_statistic statistic;
    while(statistic.counter < numberOfPackets)
    {
        const int trafficType = generateTrafficType(trafficProbabilities);

        struct_packet packet = {
            "packet-" + boost::lexical_cast<std::string>(threadId) + "-" + boost::lexical_cast<std::string>(statistic.counter),
            trafficType,
            ipAddress,
            "Packet data for " + mapTrafficTypeToIndicator(trafficType),
            std::chrono::high_resolution_clock::now()
        };

        pushPacketToFlow(threadId, packet);
        logger(log, packet);

        std::this_thread::sleep_for(trafficRate);

        // Update statistic
        statistic.counter++;
        if(packet.trafficType == TRAFFIC_TYPE_GAMING)
        {
            statistic.totalGamingPackets++;
        }
        else if(trafficType == TRAFFIC_TYPE_WEB)
        {
            statistic.totalWebPackets++;
        }
        else {
            statistic.totalStreamPackets++;
        }


        log.flush();
    };

    // Write total stats
    log << "---------------------------------------" << std::endl;
    log << "---------------------------------------" << std::endl;
    log << "---------------------------------------" << std::endl;
    log << "Generation statistic: ";
    log << "Total number of packets: " << boost::lexical_cast<std::string>(statistic.counter) << std::endl;
    log << "---------------------------------------" << std::endl;
    log << "Total number of streaming packets: " << boost::lexical_cast<std::string>(statistic.totalStreamPackets) << std::endl;
    log << "Total number of gaming packets: " << boost::lexical_cast<std::string>(statistic.totalGamingPackets) << std::endl;
    log << "Total number of web packets: " << boost::lexical_cast<std::string>(statistic.totalWebPackets) << std::endl;
    log.flush();
    log.close();
}
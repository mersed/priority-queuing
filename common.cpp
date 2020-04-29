#include <iostream>
#include <fstream>
#include "common.h"

void logger(std::ofstream& log, struct_packet packet, bool calculateTime)
{
    log << "Packet: {" << std::endl;
    log << "    packetId: " << packet.packetId << "," << std::endl;
    log << "    trafficType: " << packet.trafficType << "," << std::endl;
    log << "    ipAddress: " << packet.ipAddress << "," << std::endl;
    log << "    data: " << packet.data << std::endl;
    if(calculateTime)
    {
        auto now = std::chrono::high_resolution_clock::now();
        double elapsed_time_ms = std::chrono::duration<double, std::milli>(now-packet.classifiedAt).count();
        log << "    elapsed time before processing: " << elapsed_time_ms << std::endl;
    }
    log << "}" << std::endl;
    log << "-------------------------------------------------------" << std::endl;
}
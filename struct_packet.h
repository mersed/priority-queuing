#ifndef STRUCT_PACKET_H
#define STRUCT_PACKET_H

struct struct_packet {
    std::string packetId;
    int trafficType;
    std::string ipAddress;
    std::string data;
    std::chrono::time_point<std::chrono::high_resolution_clock> generatedAt;
    std::chrono::time_point<std::chrono::high_resolution_clock> classifiedAt;
    std::chrono::time_point<std::chrono::high_resolution_clock> scheduledAt;
};

#endif

#include <string>

#define TRAFFIC_TYPE_STREAMING_MEDIA 10
#define TRAFFIC_TYPE_GAMING 20
#define TRAFFIC_TYPE_WEB 30

void thread_flowGenerator(
    const int threadId,
    const std::chrono::milliseconds trafficRate,
    const int trafficProbabilities[],
    const int numberOfPackets,
    const std::string ipAddress
);
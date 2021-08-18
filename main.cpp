#include <iostream>
#include <string>
#include <fmt/format.h>
#include <sw/redis++/redis++.h>

using namespace sw::redis;

int main(int, char**) {

    // Create an Redis object, which is movable but NOT copyable.
    auto redis = Redis("tcp://127.0.0.1:6379");

    std::string room_id = "room1";
    std::string user_id = "user1";

    // for example add user1 to the room1.users list
    redis.rpush(fmt::format("{}.users", room_id), user_id);

    // Create a Subscriber.
    auto sub = redis.subscriber();

    sub.on_pmessage([](std::string pattern, std::string channel, std::string msg) {
        std::cout << pattern << ", " << channel << ", " << msg << std::endl;
    });

    // Subscribe to channels and patterns.
    sub.psubscribe("__keyspace@0__:room1.*");

    // Consume messages in a loop.
    while (true) { // TODO: make seperate thread
        try {
            sub.consume();
        } catch (const Error &err) {
            std::cout << "Error: " << err.what() << std::endl;
        }
    }

    return 0;
}

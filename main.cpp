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

    sub.on_pmessage([&redis](std::string pattern, std::string channel, std::string msg) {

        std::cout << pattern << ", " << channel << ", " << msg << std::endl;
        std::string key = channel.substr(channel.find(':') + 1, -1);

        if (msg.compare("set") == 0) {

            auto event_id = redis.get(key);
            if (event_id) {
                // Dereference val to get the returned value of std::string type.
                std::cout << key << ": " << *event_id << std::endl;
            }   // else key doesn't exist.
        }

        if (msg.compare("rpush") == 0) {

            std::vector<std::string> values = {};
            redis.lrange(key, 0, -1, std::back_inserter(values));

            std::cout << key << ": ";
            for (auto i: values)
                std::cout << i << ' ';
            std::cout << std::endl;
        }

    });

    // Subscribe to the keys starting with our room number
    sub.psubscribe(fmt::format("__key*__:{}.*", room_id));

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

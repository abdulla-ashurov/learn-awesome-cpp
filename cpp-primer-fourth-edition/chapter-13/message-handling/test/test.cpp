#include "catch_amalgamated.hpp"
#include "../include/message.hpp"

TEST_CASE("Test constructor of Message class") {
    SECTION("default value constructor") {
        Message msg;
        REQUIRE(msg.get().size() == 0);
    }

    SECTION("with parameter constructor") {
        std::string expected_msg = "Hello world!";
        Message msg(expected_msg);
        REQUIRE(msg.get() == expected_msg);
    }
}

TEST_CASE("Test Message.save() method") {
    SECTION("Test Message.save() method") {
        Message msg("Hello world!");
        Folder folder("messages");
        msg.save(folder);
    }
}

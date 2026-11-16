# pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <toml++/toml.hpp>

namespace MovieBooking {

/**
* @brief Configuration structure for the movie booking application.
*/
struct Config {
    std::string ip = "127.0.0.1";
    uint16_t port = 8080;
    uint16_t threads = 4;
    /**
    * @brief Loads configuration from a TOML file.
    * @param path Path to the configuration file.
    * @return Config structure with loaded values or defaults.
    */
    static Config LoadConfig(const std::string& path);
};

}
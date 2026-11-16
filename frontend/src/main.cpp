#include "api_client.h"
#include "menu.h"
#include "toml_wrapper.h"

#include <drogon/drogon.h>

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    MovieBooking::Config config = MovieBooking::Config::LoadConfig("config.toml");
    std::thread eventLoopThread([]()
    {
        drogon::app().run();
    });

    while (!drogon::app().isRunning())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    {
        MovieBooking::ApiClient apiClient("http://" + config.ip + ":" + std::to_string(config.port));
        
        if (!apiClient.IsHealthy())
        {
            std::cout << "Backend is not healthy. Exiting." << std::endl;
            drogon::app().quit();
            eventLoopThread.join();
            return 1;
        }
        else
        {
            std::cout << "Backend is healthy. Starting application..." << std::endl;
        }

        MovieBooking::Menu menu(apiClient);
        menu.Run();
    }

    drogon::app().quit();
    eventLoopThread.join();

    return 0;
}
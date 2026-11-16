#include "api_client.h"
#include "menu.h"

#include <drogon/drogon.h>

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    std::thread eventLoopThread([]()
    {
        drogon::app().run();
    });

    while (!drogon::app().isRunning())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    {
        MovieBooking::ApiClient apiClient("http://127.0.0.1:8080");

        std::cout << "Checking backend connection..." << std::endl;

        const MovieBooking::ApiResponse response =
            apiClient.Get("/api/health");

        if (!response.transportSuccess)
        {
            std::cout << "Backend connection failed: "
                      << response.error << "\n";
        }
        else
        {
            if (!response.error.empty())
            {
                std::cout << response.error << std::endl;
                std::cout << response.rawBody << std::endl;
            }
            else
            {
                std::cout << "Backend response: success" << std::endl;
            }
        }

        MovieBooking::Menu menu(apiClient);
        menu.Run();
    }

    drogon::app().quit();
    eventLoopThread.join();

    return 0;
}
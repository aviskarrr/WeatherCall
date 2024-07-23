#include <iostream>
#include "fetchData.h"

int main() {
    // API Key
    const std::string api_key = "24e63da0cfa5cb0c569304f4951ea32b";

    while (true) {
        std::cout << "Enter city name: ";
        std::string city;
        std::getline(std::cin, city);

        // Initialize the WeatherClient with the API key
        WeatherClient weatherClient(api_key);
        weatherClient.fetchWeather(city);
    }

    return 0;
}

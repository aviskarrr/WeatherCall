#include <iostream>
#include "fetchData.h"
#include"Geoapify.h"
#include"FetchAQI.h"

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



        std::string geoapifyApiKey = "479900fcbe104f1d9869d2d0276a8e6f";
        std::string openWeatherApiKey = "24e63da0cfa5cb0c569304f4951ea32b";
        std::string cityName = "Kathmandu";

        // Create instances of the classes with API keys
        Geoapify geoapify(geoapifyApiKey);
        FetchAQI fetchAQI(openWeatherApiKey);

        // Get latitude and longitude for the specified city
        std::pair<double, double> latLon = geoapify.getLatLong(cityName);
        double lat = latLon.first;
        double lon = latLon.second;

        if (lat != 0.0 && lon != 0.0) {
            // Fetch AQI data
            std::string aqiCategory = fetchAQI.fetchAQIData(lat, lon);

            // Output the AQI category
            std::cout << "AQI Category: " << aqiCategory << std::endl;
        }
        else {
            std::cerr << "Failed to get lat-long for the city." << std::endl;
        }

    }

    return 0;
}

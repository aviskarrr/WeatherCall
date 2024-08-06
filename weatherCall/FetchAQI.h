#pragma once
#include <string>

class FetchAQI {
public:
    FetchAQI(const std::string& apiKey);
    std::string fetchWeatherData(double lat, double lon) const;
    std::string fetchAQIData(double lat, double lon) const;

private:
    std::string apiKey;
};


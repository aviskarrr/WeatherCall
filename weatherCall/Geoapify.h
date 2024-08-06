#pragma once

#include<string>
#include <utility>

class Geoapify {
public:
    Geoapify(const std::string& apiKey);
    std::pair<double, double> getLatLong(const std::string& cityName) const;

private:
    std::string apiKey;
};


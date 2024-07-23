#pragma once

#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <string>

using namespace web;
using namespace web::http;
using namespace web::http::client;

class WeatherClient {
public:
    WeatherClient(const std::string& api_key);
    void fetchWeather(const std::string& city);

private:
    std::string api_key_;
    void parseResponse(const json::value& body);
};

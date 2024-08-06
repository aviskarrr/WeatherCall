#include "FetchAQI.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <stdexcept>

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

FetchAQI::FetchAQI(const std::string& apiKey) : apiKey(apiKey) {}

std::string FetchAQI::fetchWeatherData(double lat, double lon) const {
    http_client client(U("http://api.openweathermap.org/data/2.5/weather"));
    uri_builder builder;
    builder.append_query(U("lat"), lat);
    builder.append_query(U("lon"), lon);
    builder.append_query(U("appid"), utility::conversions::to_string_t(apiKey));

    auto requestTask = client.request(methods::GET, builder.to_string())
        .then([](http_response response) -> pplx::task<utility::string_t> {
        if (response.status_code() == status_codes::OK) {
            return response.extract_string();
        }
        throw std::runtime_error("Failed to get response from OpenWeatherMap");
            })
        .then([](utility::string_t body) -> std::string {
        return utility::conversions::to_utf8string(body);
            });

    try {
        return requestTask.get();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return "";
    }
}

std::string FetchAQI::fetchAQIData(double lat, double lon) const {
    http_client client(U("http://api.openweathermap.org/data/2.5/air_pollution"));
    uri_builder builder;
    builder.append_query(U("lat"), lat);
    builder.append_query(U("lon"), lon);
    builder.append_query(U("appid"), utility::conversions::to_string_t(apiKey));

    auto requestTask = client.request(methods::GET, builder.to_string())
        .then([](http_response response) -> pplx::task<json::value> {
        if (response.status_code() == status_codes::OK) {
            return response.extract_json();
        }
        throw std::runtime_error("Failed to get response from OpenWeatherMap");
            })
        .then([](json::value jsonObject) -> std::string {
        // Assuming AQI is in jsonObject["list"][0]["main"]["aqi"]
        int aqiIndex = jsonObject[U("list")][0][U("main")][U("aqi")].as_integer();

        // Map AQI index to category
        std::string aqiCategory;
        switch (aqiIndex) {
        case 1:
            aqiCategory = "Good";
            break;
        case 2:
            aqiCategory = "Fair";
            break;
        case 3:
            aqiCategory = "Moderate";
            break;
        case 4:
            aqiCategory = "Poor";
            break;
        case 5:
            aqiCategory = "Very Poor";
            break;
        default:
            aqiCategory = "Unknown";
            break;
        }

        return aqiCategory;
            });

    try {
        return requestTask.get();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return "Error";
    }
}

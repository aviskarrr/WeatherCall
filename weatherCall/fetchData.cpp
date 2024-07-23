#include "fetchData.h"
#include <iostream>

WeatherClient::WeatherClient(const std::string& api_key) : api_key_(api_key) {}

void WeatherClient::fetchWeather(const std::string& city) {
    // Create an HTTP client
    http_client client(U("https://api.openweathermap.org/data/2.5"));
    uri_builder builder(U("/weather"));
    builder.append_query(U("q"), utility::conversions::to_string_t(city));
    builder.append_query(U("appid"), utility::conversions::to_string_t(api_key_));

    // Create an HTTP request
    http_request request(methods::GET);
    request.set_request_uri(builder.to_string());

    // Send the request
    client.request(request).then([this](http_response response) {
        return response.extract_json();
        }).then([this](json::value body) {
            parseResponse(body);
            }).wait();
}

void WeatherClient::parseResponse(const json::value& body) {
    try {
        std::cout << "\tTemperature: " << body.at(U("main")).at(U("temp")).as_double() << " K" << std::endl;
        std::cout << "\tHumidity: " << body.at(U("main")).at(U("humidity")).as_double() << "%" << std::endl;
        std::cout << "\tWeather: " << utility::conversions::to_utf8string(body.at(U("weather")).at(0).at(U("main")).as_string()) << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing response: " << e.what() << std::endl;
    }
}

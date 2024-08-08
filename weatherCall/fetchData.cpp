#include "fetchData.h"
#include <iostream>
#include <string>

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


        // Extract temperature in Kelvin
        double tempKelvin = body.at(U("main")).at(U("temp")).as_double();
        // Convert temperature to Celsius and Fahrenheit
        double tempCelsius = tempKelvin - 273.15;
        double tempFahrenheit = tempCelsius * 9.0 / 5.0 + 32.0;


        std::wcout << L"\tTemperature: " << tempCelsius << L" \u00B0C / " << tempFahrenheit << L" \u00B0F (" << tempKelvin << L" K)" << std::endl;
        std::wcout << L"\tHumidity: " << body.at(U("main")).at(U("humidity")).as_double() << L"%" << std::endl;
        std::wcout << L"\tWeather: " << utility::conversions::to_utf16string(body.at(U("weather")).at(0).at(U("main")).as_string()) << std::endl;


        //std::cout << "\tTemperature: " << body.at(U("main")).at(U("temp")).as_double() << " K" << std::endl;
        //std::cout << "\tHumidity: " << body.at(U("main")).at(U("humidity")).as_double() << "%" << std::endl;
        //std::cout << "\tWeather: " << utility::conversions::to_utf8string(body.at(U("weather")).at(0).at(U("main")).as_string()) << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing response: " << e.what() << std::endl;
    }
}

#include "Geoapify.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <stdexcept>

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

Geoapify::Geoapify(const std::string& apiKey) : apiKey(apiKey) {}

std::pair<double, double> Geoapify::getLatLong(const std::string& cityName) const {
    http_client client(U("https://api.geoapify.com/v1/geocode/search"));
    uri_builder builder;
    builder.append_query(U("text"), utility::conversions::to_string_t(cityName));
    builder.append_query(U("apiKey"), utility::conversions::to_string_t(apiKey));

    auto requestTask = client.request(methods::GET, builder.to_string())
        .then([](http_response response) -> pplx::task<json::value> {
        if (response.status_code() == status_codes::OK) {
            return response.extract_json();
        }
        throw std::runtime_error("Failed to get response from Geoapify");
            })
        .then([](json::value jsonObject) -> std::pair<double, double> {
        double lat = jsonObject[U("features")][0][U("geometry")][U("coordinates")][1].as_double();
        double lon = jsonObject[U("features")][0][U("geometry")][U("coordinates")][0].as_double();
        return { lat, lon };
            });

    try {
        return requestTask.get();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return { 0.0, 0.0 };
    }
}

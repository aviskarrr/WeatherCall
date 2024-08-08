#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include "fetchData.h"
#include "Geoapify.h"
#include "FetchAQI.h"

void printMenu() {
    std::cout << "\nWeather and AQI Application\n";
    std::cout << "1. Fetch Weather Data\n";
    std::cout << "2. Fetch AQI Data\n";
    std::cout << "3. Exit\n";
    std::cout << "Choose an option: ";
}



//void textAnimation(const char* str, int delay = 10) {
//    int i = 0;
//    while (str[i] != '\0') {
//        std::cout << str[i];
//        i++;
//        Sleep(delay);
//    }
//}



void textAnimation(const char* str, int delayMs = 10) {
    int i = 0;
    while (str[i] != '\0') {
        std::cout << str[i];
        i++;
        std::cout.flush(); // Ensure the character is printed immediately
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
}

// Function to display an animated introduction
void showIntro() {
    const char* introText =
        R"(
            _         _             _                     _ 
           / \   __ _| | ____ _ ___| |____   ____ _ _ __ (_)              
          / _ \ / _` | |/ / _` / __| '_ \ \ / / _` | '_ \| |           
         / ___ \ (_| |   < (_| \__ \ | | \ V / (_| | | | | |
        /_/   \_\__,_|_|\_\__,_|___/_| |_|\_/ \__,_|_| |_|_|

        )"

        R"(
                _                                  
                          (`  ).                   _           
                         (     ).              .:(`  )`.       
            )           _(       '`.          :(   .    )      
                    .=(`(      .   )     .--  `.  (    ) )      
                   ((    (..__.:'-'   .+(   )   ` _`  ) )                 
            `.     `(       ) )       (   .  )     (   )  ._   
              )      ` __.:'   )     (   (   ))     `-'.-(`  ) 
            )  )  ( )       --'       `- __.'         :(      )) 
            .-'  (_.'          .')                    `(    )  ))
                              (_  )                     ` __.:'        
)"
        "\n"
        "==========================================================================\n";

    textAnimation(introText, 5);  // Adjust delay for better readability
    std::cout << std::endl;
}

int main() {
    showIntro();

    // API Keys
    const std::string geoapifyApiKey = "479900fcbe104f1d9869d2d0276a8e6f";
    const std::string openWeatherApiKey = "24e63da0cfa5cb0c569304f4951ea32b";

    // Create instances of the classes with API keys
    Geoapify geoapify(geoapifyApiKey);
    FetchAQI fetchAQI(openWeatherApiKey);
    WeatherClient weatherClient(openWeatherApiKey);

    while (true) {
        // Display menu
        printMenu();

        int choice;
        std::cin >> choice;
        std::cin.ignore(); // Ignore newline character left in the buffer

        if (choice == 1) {
            std::cout << "Enter city name: ";
            std::string city;
            std::getline(std::cin, city);

            // Initialize the WeatherClient with the API key
            WeatherClient weatherClient(openWeatherApiKey);
            weatherClient.fetchWeather(city);

        }
        else if (choice == 2) {
            std::cout << "Enter city name: ";
            std::string city;
            std::getline(std::cin, city);

            // Get latitude and longitude for the specified city
            std::pair<double, double> latLon = geoapify.getLatLong(city);
            double lat = latLon.first;
            double lon = latLon.second;

            if (lat != 0.0 && lon != 0.0) {
                // Fetch AQI data
                std::string aqiCategory = fetchAQI.fetchAQIData(lat, lon);

                // Output the AQI category
                std::cout << "\nCity: " << city << "\n";
                std::cout << "Latitude: " << std::fixed << std::setprecision(6) << lat << "\n";
                std::cout << "Longitude: " << std::fixed << std::setprecision(6) << lon << "\n";
                std::cout << "AQI Category: " << aqiCategory << "\n";
            }
            else {
                std::cerr << "Failed to get latitude and longitude for the city.\n";
            }

        }
        else if (choice == 3) {
            std::cout << "Exiting the application. Goodbye!\n";
            break;
        }
        else {
            std::cerr << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}

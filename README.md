# Weather App

A simple console application that fetches and displays current weather information for a specified city using the OpenWeatherMap API.

## Features

- Fetches weather data such as temperature, humidity, and weather conditions.
- Uses C++ REST SDK (cpprestsdk) for HTTP requests and JSON parsing.

## Prerequisites

- [Visual Studio 2022 Community Edition](https://visualstudio.microsoft.com/vs/community/)
- [C++ REST SDK](https://github.com/microsoft/cpprestsdk) (cpprestsdk)
- [OpenWeatherMap API Key](https://openweathermap.org/api)

## Setup

1. **Clone the Repository**

   ```bash
   git clone https://github.com/yourusername/your-repository.git
   cd your-repository
2. **Install Dependencies**

Ensure you have the C++ REST SDK installed. If you are using NuGet Package Manager, install the cpprest package.


Open the NuGet Package Manager Console in Visual Studio
Install-Package cpprestsdk


3. **Configure the Project**

Open the solution file (.sln) in Visual Studio.
Ensure that the project is set up to include the necessary libraries and dependencies.

4. **Add Your API Key**

Open fetchData.cpp.

Replace `"24e63da0cfa5cb0c569304f4951ea32b"` with your own OpenWeatherMap API key.

```cpp
const std::string api_key = "YOUR_API_KEY_HERE";
```
## Usage

1. **Build the Project**

In Visual Studio, right-click on the project and select Build.

2. **Run the Application**

After building, run the application.

Enter a city name when prompted to receive weather information.

```bash
Enter city name: London
```
Example Output


```
Enter city name: London
    Temperature: 289.15 K
    Humidity: 81%
    Weather: Clouds
```
## Troubleshooting

Ensure that you have a valid API key and have replaced it in fetchData.cpp.
Make sure all dependencies are correctly installed and linked.
If you encounter issues with missing DLLs, ensure that the DLLs for cpprestsdk are available in your executable's directory or in your system's PATH.
License
This project is licensed under the MIT License. See the LICENSE file for details.

Acknowledgments
OpenWeatherMap API for providing the weather data.
C++ REST SDK for the HTTP client and JSON handling.
vbnet
Copy code

## Instructions to Use

1. **Replace placeholders** like `https://github.com/yourusername/your-repository.git` and `YOUR_API_KEY_HERE` with your actual repository URL and API key.
2. **Include a `LICENSE` file** in your repository if you choose to license your project.

Feel free to modify or expand the `README` to better fit your project's specifics and any additional details you'd like

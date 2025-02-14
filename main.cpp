#include "TimeSeries.h"
#include "country.h"
#include <iostream>
#include <string>

int main() {
    Country* country = nullptr;
    std::string command;

    while (std::cin >> command) {
        
        //checks if the first input is one of the defined commands
        if (command == "LOAD") {
            //takes the second input to be the country name
            std::string countryName;
            std::cin >> countryName;
            delete country; // delete the old country object
            country = new Country(countryName); // create the new country object with the passed country name
            std::cout << "success" << std::endl;
        
        //logic for the PRINT command
        } else if (command == "PRINT") {
            std::string seriesCode;
            std::cin >> seriesCode;
            if (country) country->print(seriesCode);
            else std::cout << "failure" << std::endl;
        
        //logic for the ADD command
        } else if (command == "ADD") {
            std::string seriesCode;
            int year;
            double value;
            std::cin >> seriesCode >> year >> value;
            if(country) {
                country->addSeriesData(seriesCode, year, value);
            }
            else {std::cout << "failure" << std::endl;}
            
        
        //logic for the UPDATE command
        } else if (command == "UPDATE") {
            std::string seriesCode;
            int year;
            double value;
            std::cin >> seriesCode >> year >> value;
            //check if the country exists and if it does then update the series
            if (country) {
                country->update(seriesCode, year, value);
            } else {
                std::cout << "failure" << std::endl;
            }
        
        //logic for the LIST command
        } else if (command == "LIST") {
            //check if the country exists and if it does then list the series
            if (country) {
                country->listSeries();
            } else {
                std::cout << "failure" << std::endl;
            }
        
        //logic for the DELETE command
        } else if (command == "DELETE") {
            std::string seriesCode;
            std::cin >> seriesCode;
            if (country) {
                country->deleteSeries(seriesCode);
            } else {
                std::cout << "failure" << std::endl;
            }
        
        //logic for the BIGGEST command, prints the series code with the highest mean
        } else if (command == "BIGGEST") {
            if (country) {
                TimeSeries* biggest_series = country->biggestSeries();
                std::cout << biggest_series->get_series_code() << std::endl;
            } else {
                std::cout << "failure" << std::endl;
            }
        
        
        } else if (command == "EXIT") {
            break;
        }
    }

    delete country;
    return 0;
}

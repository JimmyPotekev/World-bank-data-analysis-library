#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <limits>
#include "TimeSeries.h"


//CHATGPT CITATION:
//I used chatgpt to help me set up the structure of my header file including the constructor and destructor. My prompt was
// as follows: "please show me how to structure the syntax for a c++ class"

//CHATGPT CITATION:
//I used chatgpt to help me relearn the concept of pointers and dynamic memory allocation. My prompt was
// as follows: "I need help with pointers and dynamic memory allocation. I need to know how to use them in a c++ program"

//CHATGPT CITATION:
//I used chatgpt to help me understnad the provided formula for the best fit slope and y intercept. My prompt was
// as follows: "I need help understanding the provided formula for the best fit slope and y intercept. Please explain it to me"


//CONSTRUCTOR
TimeSeries::TimeSeries(std::string csv_line) : data_line(csv_line),series_name("temp_name"), series_code("temp_code"), size(0), capacity(2) 
{
    years = new int[capacity];
    daten = new double[capacity];
    load();
}


//DESTRUCTOR
TimeSeries::~TimeSeries() 
{
    delete[] years;
    delete[] daten;
    years = nullptr;
    daten = nullptr;
}

//HELPER FUNCTION
std::string TimeSeries::get_series_name() const{
    return series_name;
}

std::string TimeSeries::get_series_code() const{
    return series_code;
}

void TimeSeries::resize_array(){
    int new_capacity = capacity;

    if(size == capacity){
        new_capacity = capacity * 2;
    }
    else if(size == capacity/4 && capacity > 2){ //ensures that the capacity is not less than 2
        new_capacity = capacity / 2;
    }

    int* new_years = new int[new_capacity];
    double* new_daten = new double[new_capacity];
    
    //copy the old arrays to the new ones
    for(int i = 0; i < size; i++){
        new_years[i] = years[i];
        new_daten[i] = daten[i];
    }

    //delete the old arrays
    delete[] years;
    delete[] daten;

    //assign the new arrays to the old ones
    years = new_years;
    daten = new_daten;
    capacity = new_capacity;
}

//REQUIRED FUNCTIONS
double TimeSeries::mean() const{
    double sum{0};
    int num_invalid=0;
    for(int i{0}; i<size; i++){
        if(daten[i] != -1){
            sum += daten[i];
        }
        else{
            num_invalid++;
        }
    }
    if(num_invalid == size){
        return -1;
    }
    return sum / (size - num_invalid);
}
        
bool TimeSeries::is_monotonic() const {  
    
    //assume for now that the series is increasing and decreasing
    bool increasing = true;
    bool decreasing = true;

    // Find first valid data point
    int start = 0;
    while (start < size && daten[start] == -1) {
        start++;
    }
    
    // If no valid data points found
    if (start >= size) {
        return false;
    }

    // if the array is empty or has only one element then it's already monotonic
    if (size <= 1) {
        std::cout << "series is monotonic" << std::endl;
        return true;
    }

    // compare each element to the previous one, if the comparison contradicts the assumption above then 
    //
    for (int i = start + 1; i < size; i++) {
        // Skip invalid data points
        if (daten[i] == -1) {
            continue;
        }
        
        if (daten[i] < daten[start]) {
            increasing = false;
        }
        if (daten[i] > daten[start]) {
            decreasing = false;
        }
        
        // If it's not increasing and not decreasing then the array isn't monotonic
        if (!increasing && !decreasing) {
            std::cout << "series is not monotonic" << std::endl;
            return true;
        }
        
        // Update start to current valid point
        start = i;
    }
    std::cout << "series is monotonic" << std::endl;
    return true;
}

void TimeSeries::best_fit(double &m, double &b) const{
    double sum_x = 0;    // sum of years(x)
    double sum_y = 0;    // sum of data points(y)
    double sum_xy = 0;  
    double sum_xx = 0;   
    
    // Calculate sums
    int num_invalid = 0;
    for(int i = 0; i < size; i++) {
        if(daten[i] != -1){
            sum_x += years[i];
            sum_y += daten[i];
            sum_xy += years[i] * daten[i];
            sum_xx += years[i] * years[i];
        }
        else{
            num_invalid++;
        }
    }
    
    //ensure only valid data is counted in the data size
    int valid_size = size - num_invalid;
    // calculates slope m = (n*sum_xy - sum_x*sum_y)/(n*sum_xx - sum_x*sum_x)
    m = (valid_size * sum_xy - sum_x * sum_y) / (valid_size * sum_xx - sum_x * sum_x);
    // calculates y intercept b = (sum_y - m*sum_x)/n
    b = (sum_y - m * sum_x) / valid_size;
}

// COMMAND FUNCTIONS
bool TimeSeries::add(int year, double data_point){
    resize_array();

    //if all entries are before the input we add to the end of the array
    for(int i = 0; i < capacity; i++){
        if(i == size){
            years[i] = year;
            daten[i] = data_point;
            size++;
            return true;
        }

        //if the data point alrady exists then we replace invalid data or skip valid data
        else if(years[i] == year){
            if(daten[i]==-1) {
                daten[i] = data_point;
                return true;
            }
            return false;
        }

        //if the current year is greateer than the input year then we shift the array and
        else if(years[i] > year){
            int* shifted_years = new int[capacity];           //create a new array to store the shifted years
            double* shifted_daten = new double[capacity];      //create a new array to store the shifted data
             
            //copy the old array up to the current index
            for(int j = 0; j < i; j++){
                shifted_years[j] = years[j];
                shifted_daten[j] = daten[j];
            }

            //add the new data point to the array
            shifted_years[i] = year;
            shifted_daten[i] = data_point;

            //copy the remaining elements from the old array
            for(int k = i + 1; k < size + 1; k++){
                shifted_years[k] = years[k-1];
                shifted_daten[k] = daten[k-1];
            }

            //delete the old arrays
            delete[] years;
            delete[] daten;

            years = shifted_years;
            daten = shifted_daten;
            size++;
            return true;
        }
    }
    return false;
}

bool TimeSeries::update(int year, double data_point){
    for(int i = 0; i < size; i++){
        if(years[i] == year && daten[i] != -1){
            daten[i] = data_point;
            return true;
        }
        else if(years[i] == year && daten[i] == -1){
            return false;
        }
    }
    return false;
}

void TimeSeries::print() const{
    if(size == 0){
        std::cout << "failure" << std::endl;
        return;
    }
    for(int i = 0; i < size; i++){
        if(daten[i] != -1){
            std::cout << "(" << years[i] << "," << daten[i] << ") ";
        }
    }
    std::cout << std::endl;
}

void TimeSeries::load() {
    // 'data_line' is the line of data from the csv file
    std::stringstream line_stream(data_line);

    //pass over the first 2 fields
    std::getline(line_stream, series_name, ','); //this line is not meant to store anything
    std::getline(line_stream, series_name, ','); //this line is not meant to store anything

    //now line_stream starts at the series name
    std::getline(line_stream, series_name, ',');
    std::getline(line_stream, series_code, ',');
    std::string field;
    int year = 1960;

    while (std::getline(line_stream, field, ',')) {
        // Only add valid data points, skip -1 values
        if (field != "-1") {
            add(year, std::stod(field));
        }
        year++;
    }
}
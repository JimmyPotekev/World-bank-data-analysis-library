#ifndef TIMESERIES_H
#define TIMESERIES_H
#include <string>
#include <sstream>

//CHATGPT CITATION:
//I used chatgpt to help me set up the structure of my header file including the constructor and destructor. My prompt was
// as follows: "please show me how to structure the syntax for a c++ class"

class TimeSeries{
    private:
        std::string data_line; //holds the line of data from the csv file
        std::string series_name; //holds the name of the series
        std::string series_code; //holds the code of the series
        
        int* years;      //Array containing the years with valid data - basically the x axis
        double* daten;    //Array containing the data points - basically the y values
        int size;        //The current number of elements in the array
        int capacity;    //The max number of the element that array can currently hold

        void resize_array();  // helps to resize the array
        void load(); //called by the constructor to load the data from the csv file

    public:
        //Constructor and Destructor
        TimeSeries(const std::string csv_line); //default constructor
        ~TimeSeries();


        //methods
        double mean() const;
        bool is_monotonic() const;
        void best_fit(double &m, double &b) const;

        // command methods
        bool add(int year, double data_point);
        bool update(int year, double data_point);
        void print() const;
        

        //helper functions
        void read_data(const std::string file_name);
        std::string get_series_name() const;
        std::string get_series_code() const;
};

#endif
/*CHATGPT CITATION: i asked chatgpt to show me how to use a struct within a class. my prompt was as follows: "how do i use a struct within a class in c++? i'm not 
really sure how it differs from a class and how i would define the syntax for such a strucure/data type"
*/

#ifndef COUNTRY_H
#define COUNTRY_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "TimeSeries.h"

class Country{
    private:
        std::string name;
        std::string code;

        struct ListNode {
            std::string series_code;
            TimeSeries* data;
            ListNode* next;
            

            ListNode(const std::string& code, TimeSeries* ts);
        };

        ListNode* head;
        ListNode* tail;

        //private helper functions
        TimeSeries* createSeries(const std::stringstream& line_stream);
        void insert(ListNode* node);
        // ListNode* search(ListNode* node, const std::string& code) const;
        void loadCountry(const std::string& country_name);

    public:
        Country(const std::string country_name);
        ~Country();

        //public methods
        void addSeriesData(const std::string& seriesCode, int year, double value);

        TimeSeries* findSeries(const std::string& seriesCode);

        void listSeries();

        void deleteSeries(const std::string& seriesCode);

        TimeSeries* biggestSeries();

        void update(const std::string& seriesCode, int year, double value);

        void print(const std::string& seriesCode);

};

#endif
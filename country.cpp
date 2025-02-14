/*CHATGPT CITATION: i asked chatgpt to give me the pros and cons of using a linked list vs a bst. i gave a brief description of the project and suggested
my thoughts on why i would like to do a bst but why i'm leaning towards a linked list. I wanted to check if my reasoning was well thought out. my prompt was as follows:
"i'm working a data project in c++ where i take csv data for multiple countries and store multiple time series object for a single country. I will be making a 
country class that contains a data structure to keep track of these time series objects. I'm deciding between a binary search tree and a linked list. I would like to 
a binary search tree because it's a newer concept to me and i'd like to get familiar with it. Another pro is the it would be good for searching, adding, or updating 
specific objects or nodes within my DS. the problem is that this would be difficult to implement because storing the series in a tree would disrupt the order in which
time series are read from the file. on top of that, the way i would need to store the series, using the series code as a key, wouldn't necesarrily guaruntee a balanced
tree. I'm thinking of going with a linked list because of the simplicity and scalability, even though it's a bit slower to access data. what are your thoughts?" 
*/

/*CHATGPT CITATION: I knew i needed to create a country class that contains some sort of DS to manage the time series objects. as mentienod above i chose a linked
list. because of this i was worreid about the work of having to create another separate class to manage the nodes of the linked list withtin the country class.
i asked chatgpt if it had any suggestions of ways to make this simpler. my prompt related to the one i gave above, and goes as follows: "ok, thank you helpling me
decide which data stucutre to use. I've decided to go with a linked list for now and maybe scale to a BST later on. So for my country class i am going to contain a
linked list. I will need a way to manage this linked list. The only way I can think of doing this is with another class (either within the country class or in a 
separate file). I will need a class to manage the linked list because each node has different data type atriubutes and objects and I need a way to contain this in a 
single data type or node/structure of some kind. Is there a simpler way to do this? I don't really want to have to deal with more files or classes if i don't need to."
as a response chatgpt suggest the use of a struct instead of a class because i can define the attributes of the node within the country class. although this doesn't
really effect my data design design or implementation that much, it greatly simplifies the syntax for my code. 
*/

/*CHATGPT CITATION: i asked chatgpt to help me figure out how to manaage nodes of a linked list in c++.
I knew I needed a country class that would contain DS(i chose a linked list) but was unsure how i
would implement managing the nodes of a linked list. I was considering creating an entire serarate class
called something like "linkedListNodeManager" but chatgpt suggested that i could just use a struct
inside the country class.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "country.h"

//LISTNODE CONSTRUCTOR
Country::ListNode::ListNode(const std::string& code, TimeSeries* ts)
    : series_code(code), data(ts), next(nullptr) {}

//CONSTRUCTOR
Country::Country(const std::string country_name)
    : name(country_name), code(""), head(nullptr) {
        loadCountry(country_name);
    }



//DESTRUCTOR
Country::~Country() {
    ListNode* curr = head;
    //loop through the linked list and delete each node
    while(curr != nullptr){
        ListNode* next = curr->next;
        delete curr->data;  // Delete the TimeSeries object
        delete curr;  // Just delete the node itself
        curr = next;
    }
    head = nullptr;
    tail = nullptr;
}


//PRIVATE HELPER FUNCTIONS
//insert a new node into the linked list
void Country::insert(ListNode* node){
    if(head == nullptr){
        head = node;
        tail = node;
    }
    else{
        tail->next = node;
        tail = node;
    }
}

//didn't end up needing this but keeping it in case i want to implement later
// Country::ListNode* Country::search(ListNode* node, const std::string& code) const {
//     return nullptr;
// }

void Country::loadCountry(const std::string& country_name){
    //open the file
    std::ifstream file("lab2_multidata.csv");
    std::string line; //stores a line of the file as a string
    

    //read each line 
    int i = 0;
    while(std::getline(file, line)){
        std::stringstream line_stream(line); //converts the line into a stringstream so it can be parsed
        std::string c_name; //country name of that line
        std::string s_code; //series code of that line

        
        std::getline(line_stream, c_name, ','); //read the first field of the line - the country name
        
        
        //checks if the given country matches the country name on that line
        if(c_name == country_name){
            std::getline(line_stream, code, ','); //read the second field of the line - the country code
            //create first node
            if(i == 0){
                TimeSeries* ts = new TimeSeries(line_stream.str()); // creates new ts passing the line_stream as a string
                
                std::getline(line_stream, s_code, ','); // this is the series name field, just passing over it - not needed
                std::getline(line_stream, s_code, ','); // this asigns the series code to the s_code
                head = new ListNode(s_code, ts); // create the head node from the time series object
                tail = head;
            }
            //create new node and insert it into the linked list
            else{
                TimeSeries* ts = new TimeSeries(line_stream.str()); // creates new ts passing the line_stream as a string
                std::getline(line_stream, s_code, ','); // this is the series name field, just passing over it - not needed
                std::getline(line_stream, s_code, ','); // this asigns the series code to the s_code
                ListNode* newNode = new ListNode(s_code, ts);
                insert(newNode);

            }
            
            //increment i
            i++;
        }
    }
}




//PUBLIC METHODS
//logic for adding data to a specific series in the ll
void Country:: addSeriesData(const std::string& seriesCode, int year, double value){
    TimeSeries* ts = findSeries(seriesCode); //finds the series in the ll and returns the timeseries object, if not found returns nullptr
    if(ts != nullptr){
        if(ts->add(year, value)) { //adds the data to the timeseries object
            std::cout << "success" << std::endl;
        } else {
            std::cout << "failure" << std::endl;
        }
    }
    else{
        std::cout << "failure" << std::endl;
    }
}

//logic behind taking user input and finding the series data
TimeSeries* Country::findSeries(const std::string& seriesCode){
    ListNode* curr = head;
    while(curr != nullptr){
        std::string current_code = curr->series_code;
        if(current_code == seriesCode){
            return curr->data;
        }
        curr = curr->next;
    }
    return nullptr;
}

//Public method to list all TimeSeries in dataset order
void Country::listSeries(){
    //print country name and code
    std::cout << name << " " << code << " ";
    // print each series name
    ListNode* curr = head;
    while(curr != nullptr){
        std::string series_name = curr->data->get_series_name();
        std::cout << series_name << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}   

//Public method to delete a series from the linked list
void Country::deleteSeries(const std::string& seriesCode){

    ListNode* curr = head;
    ListNode* prev = nullptr;
    if(head != nullptr && head->series_code == seriesCode){
        head = head->next;
        delete curr->data;
        delete curr;
        curr = nullptr;
        std::cout << "success" << std::endl;
        return;
    }
    else{
        while(curr != nullptr){
            if(curr->series_code == seriesCode){
                if(curr == tail){
                    tail = prev;
                    if(tail->next != nullptr){
                        tail->next = nullptr;
                    }
                }
                prev->next = curr->next;
                delete curr->data;
                delete curr;
                curr = nullptr;
                std::cout << "success" << std::endl;
                return;
            }
            if(curr != nullptr){
                prev = curr;
                curr = curr->next;
            }
        }
    }
    std::cout << "failure" << std::endl;
}

TimeSeries* Country::biggestSeries(){

    ListNode* biggest_node = head; //keeps track of node with biggest mean
    ListNode* curr = head; //node to interate through the LL
    double biggest_mean = biggest_node->data->mean();
    while(curr->next != nullptr){   
        //compare current node's mean to the biggest mean
        if(biggest_mean < curr->data->mean()){
            biggest_node = curr;
            biggest_mean = curr->data->mean();
        }
        //go to next node
        curr = curr->next;
    }
    //returns timeseries with the biggest mean
    return biggest_node->data;
}

//similar logic to addSeriesData but instead updates the data in the timeseries object
void Country::update(const std::string& seriesCode, int year, double value){
    TimeSeries* ts = findSeries(seriesCode);
    if(ts != nullptr){
        if(ts->update(year, value)) {
            std::cout << "success" << std::endl;
        } else {
            std::cout << "failure" << std::endl;
        }
    }
    else{
        std::cout << "failure" << std::endl;
    }
}

//similar logic to addSeriesData but instead prints the data in the timeseries object
void Country::print(const std::string& seriesCode){
    TimeSeries* ts = findSeries(seriesCode);
    if(ts != nullptr){
        ts->print();
    } else {
        std::cout << "failure" << std::endl;
    }
}

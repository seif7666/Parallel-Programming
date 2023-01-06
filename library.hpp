#ifndef LIBRARY_HPP
#define LIBRARY_HPP
#include <iostream>
#include<thread>
#include <vector>
#include <chrono>
#define SIZE 10000
typedef long TYPE;
using namespace std;

class Timer{
    string name;
    public:
    Timer(string name){
        this->name= name;
        this->start= this->timeSinceEpochMillisec();
    }
    void done(){
        time_t end=this->timeSinceEpochMillisec();
        cout<<this->name<<" time is : "<<(end-this->start)<<" ms"<<endl;
    }

    private:
    uint64_t start;
    uint64_t timeSinceEpochMillisec() {
        using namespace std::chrono;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }
};

void initialize_vector(vector<TYPE>&A);
void compute_serial(vector<TYPE>&A,vector<TYPE>&rowVector,vector<TYPE>&columnVector,TYPE rows,TYPE columns);
void compute_parallel(vector<TYPE>&A,vector<TYPE>&rowVector,vector<TYPE>&columnVector,TYPE rows,TYPE columns);
bool evaluate(vector<TYPE>&A,vector<TYPE>&B,int size);


#include "library.cpp"
#endif

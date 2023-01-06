#include "library.hpp"

int main(){
    vector<TYPE>matrix((long)SIZE*(long)SIZE);
    vector<TYPE>rowSum(SIZE);
    vector<TYPE>columnSum(SIZE);

    Timer* initializeTime= new Timer("Initializer");
    initialize_vector(matrix); 
    initializeTime->done();
    free(initializeTime);
    // Now we need to compute the sum. For each row and for each column.
    //Estimate Sum
    compute_serial(matrix,rowSum,columnSum,SIZE,SIZE);
    if(evaluate(rowSum,columnSum,SIZE))
        cout<<"Calculations are correct!"<<endl;
    else
        cout<<"Calculations are wrong!"<<endl;
    compute_parallel(matrix,rowSum,columnSum,SIZE,SIZE);
    if(evaluate(rowSum,columnSum,SIZE))
        cout<<"Calculations are correct!"<<endl;
    else
        cout<<"Calculations are wrong!"<<endl;
}
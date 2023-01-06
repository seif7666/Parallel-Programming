#include "library.hpp"

void initialize_vector(vector<TYPE> &A)
{
    for (TYPE i : A)
        A[i] = 1;
}
void compute_serial(vector<TYPE> &A, vector<TYPE> &rowVector, vector<TYPE> &columnVector, int rows, int columns)
{
    Timer SerialTime("Serialization");
    for (int row = 0; row < rows; row++)
    {
        TYPE rowSum = 0;
        for (int col = 0; col < columns; col++)
        {
            TYPE val = A[row * columns + col];
            rowVector[row] += val;
            columnVector[col] += val;
        }
    }
    SerialTime.done();
}

bool evaluate(vector<TYPE> &A, vector<TYPE> &B, int size)
{
    for (int i = 0; i < size; i++)
        if (A[i] != B[i])
            return false;
    return true;
}

void compute_parallel(vector<TYPE> &A, vector<TYPE> &rowVector, vector<TYPE> &columnVector, TYPE rows, TYPE columns)
{
    while (true)
    {
        TYPE numThreads;
        cin >> numThreads;
        Timer timer("Parallelism");
        int chunkSize = rows / numThreads;
        auto rowBlock = [&](const int &id) -> void
        {
            int startRow = chunkSize * id;
            int endingRow = startRow + chunkSize;
            endingRow = endingRow > rows ? rows : endingRow;
            for (int row = startRow; row < endingRow; row++)
            {
                for (int col = 0; col < columns; col++)
                {
                    rowVector[row] += A[row * columns + col];
                }
            }
        };
        auto columnBlock = [&](const int &id) -> void
        {
            int startCol = chunkSize * id;
            int endingCol = startCol + chunkSize;
            endingCol = endingCol > rows ? rows : endingCol;
            for (int row = 0; row < rows; row++)
            {
                for (int col = startCol; col < endingCol; col++)
                {
                    columnVector[col] += A[row * columns + col];
                }
            }
        };
        vector<thread> rowThreads;
        vector<thread> colThreads;
        for (TYPE id = 0; id < numThreads; id++)
            rowThreads.emplace_back(rowBlock, id);
        for (TYPE id = 0; id < numThreads; id++)
            colThreads.emplace_back(columnBlock, id);

        for (thread &threadI : rowThreads)
            threadI.join();
        for (auto &thread : colThreads)
            thread.join();
        timer.done();
    }
}

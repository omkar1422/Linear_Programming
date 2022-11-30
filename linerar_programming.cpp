#include <bits/stdc++.h>
using namespace std::chrono;
using namespace std;

void luDecomposition(vector<vector<int>> arr, vector<int> &voters)
{

    int row = arr.size();

    vector<vector<int>> lower(row, vector<int>(row, 0));
    vector<vector<int>> upper(row, vector<int>(row, 0));

    // Decomposition of matrix into lower and upper triangular matrix.
    for (int i = 0; i < row; i++)
    {

        // Upper Triangular.
        for (int k = i; k < row; k++)
        {
            int sum = 0;
            for (int j = 0; j < i; j++)
            {
                sum += (lower[i][j] * upper[j][k]);
            }
            upper[i][k] = arr[i][k] - sum;
        }

        // Lower Triangular.
        for (int k = i; k < row; k++)
        {
            // Diagonal will be 1.
            if (i == k)
            {
                lower[i][k] = 1;
            }
            else
            {
                int sum = 0;
                for (int j = 0; j < i; j++)
                {
                    sum += (lower[k][j] * upper[j][i]);
                }
                lower[k][i] = (arr[k][i] - sum) / upper[i][i];
            }
        }
    }

    vector<float> y(arr.size());

    for (int i = 0; i < lower.size(); i++)
    {
        float sum = 0;
        for (int j = 0; j < i; j++)
        {
            sum += (lower[i][j] * y[j]);
        }
        y[i] = float((voters[i] - sum) / lower[i][i]);
    }

    vector<int> x(arr.size());
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        float sum = 0;
        for (int j = row - 1; j > i; j--)
        {
            sum += (upper[i][j] * x[j]);
        }
        x[i] = float((y[i] - sum) / upper[i][i]);
    }

    for (auto itr : x)
    {
        cout << itr << " ";
    }
}

int main()
{
    vector<vector<int>> arr = {
        {-2, 8, 1, 10}, {5, 2, 3, 6}, {3, -5, 10, -2}, {6, -2, 4, 5}};

    vector<int> voters(arr.size());
    cout << "Enter the voters : " << endl;
    for (int i = 0; i < arr.size(); i++)
    {
        cin >> voters[i];
    }

    auto start = high_resolution_clock::now();

    luDecomposition(arr, voters);
    cout << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Execution Time in microseconds :  ";
    cout << (duration.count()) << endl;

    return 0;
}
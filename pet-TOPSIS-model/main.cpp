#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>
#include <vector>

using namespace std;

vector<vector<double>> originMatrix;
vector<double> v;
vector<double> weights;

// reading in
void readingIn() {
    int row, column;
    cin >> row >> column;

    // reading in decision matrix
    for (int i = 0; i < row; i++)
    {
        v.clear();
        for (int j = 0; j < column; j++)
        {
            int num=0;
            cin >> num;
            v.push_back(num);
        }
        originMatrix.push_back(v);
    }

    // reading in weights
    for (int i = 0; i < column; i++)
    {
        double w;
        cin >> w;
        weights.push_back(w);
    }
}
// normaize the matrix
vector<vector<double>> normalize(const vector<vector<double>> &matrix) {
    size_t rows = matrix.size();
    size_t columns = matrix[0].size();
    vector<vector<double>> normalizedMatrix(rows, vector<double>(columns));

    // culculate the euclidean norm
    for (size_t j = 0; j < columns; j++)
    {
        double columnNorm = 0;
        for (const auto &row : matrix)
        {
            columnNorm += row[j] * row[j];
        }
        columnNorm = sqrt(columnNorm);

        for (size_t i = 0; i < rows; i++)
        {
            normalizedMatrix[i][j] = matrix[i][j] / columnNorm;
        }
    }

    return normalizedMatrix;
}

// calculate weight normalized matrix
vector<vector<double>> multiplyWeights(const vector<vector<double>> &matrix, const vector<double> &weights)
{
    size_t rows = matrix.size();
    size_t columns = matrix[0].size();
    vector<vector<double>> weightedMatrix(rows, vector<double>(columns));

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            weightedMatrix[i][j] = matrix[i][j] * weights[j];
        }
    }
    return weightedMatrix;
}

// determine the positive ideal solution
vector<double> idealSolution(const vector<vector<double>> &matrix, const vector<double> &weoghts)
{
    size_t columns = matrix[0].size();
    vector<double> ideal(columns, numeric_limits<double>::min());
    for (const auto &row : matrix)
    {
        for (size_t j=0; j < columns; j++)
        {
            ideal[j] = max(ideal[j], row[j]);
        }
    }
    return ideal;
}

// determine the negative ideal solution
vector<double> negIdealSolution(const vector<vector<double>> &matrix, const vector<double> &weights)
{
    size_t columns = matrix[0].size();
    vector<double> negIdeal(columns, numeric_limits<double>::max());
    for (const auto &row : matrix)
    {
        for (size_t j=0; j < columns; j++)
        {
            negIdeal[j] = min(negIdeal[j], row[j]);
        }
    }
    return negIdeal;
}

// calculate the euclidean distance
vector<double> distance(const vector<vector<double>> &matrix, const vector<double> &target)
{
    size_t rows = matrix.size();
    vector<double> distances(rows, 0);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < target.size(); j++)
        {
            distances[i] += (matrix[i][j] - target[j]) * (matrix[i][j] - target[j]);
        }
        distances[i] = sqrt(distances[i]);
    }
    return distances;
}

// calculate the realtively closeness to the ideal solution
vector<double> closenessCoefficients(const vector<double> &distanceIdeal, const vector<double> &distanceNegIdeal)
{
    size_t size = distanceIdeal.size();
    vector<double> coeffients(size);

    for (size_t i = 0; i < size; i++) {
        coeffients[i] = distanceNegIdeal[i] / (distanceIdeal[i] + distanceNegIdeal[i]);
    }
    return coeffients;
}

// determine the best alternative
long bestAlternative(const vector<double> &closenessCoefficients) {
    return distance(closenessCoefficients.begin(), closenessCoefficients.end());
}

int main()
{
    readingIn();
    /*vector<vector<double>> originMatrix = {
        {9, 7, 1, 2},
        {11, 3, 5, 7},
        {6, 5, 4, 6},
        {8, 9, 3, 7},
        {8, 10, 7, 3},
        {7, 9, 4, 5}
    };
    vector<double> weights = {0.4, 0.3, 0.1, 0.2};*/

    // normaize the matrix
    vector<vector<double>> normalizedMatrix = normalize(originMatrix);

    // calculate weight normalized matrix
    vector<vector<double>> weightedMatrix = multiplyWeights(normalizedMatrix, weights);

    // determine the (negative) ideal solution
    vector<double> posIdealSolVector = idealSolution(weightedMatrix, weights);
    vector<double> negIdealSolVector = negIdealSolution(weightedMatrix, weights);

    // calculate the separation measures (euclidean distances)
    vector<double> euclideanDistanceIdeal = distance(weightedMatrix, posIdealSolVector);
    vector<double> euclideanDistanceNegIdeal = distance(weightedMatrix, negIdealSolVector);

    // calculate the realtively closeness to the ideal solution
    vector<double> closenessCoefficientsVector = closenessCoefficients(euclideanDistanceIdeal, euclideanDistanceNegIdeal);

    // determine the best alternative
    long bestAlternate = bestAlternative(closenessCoefficientsVector);

    // print the solution
    cout << "closest coefficients: ";
    for (const auto &coeff : closenessCoefficientsVector) {
        cout << coeff << " ";
    }
    cout << endl;
    cout << "Best alternative: " << bestAlternate + 1 << endl;

    return 0;
}

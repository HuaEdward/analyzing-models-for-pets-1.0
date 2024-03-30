#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

// Test for example:
// Input: Cat 6 1 7 4 7 3 7 78 2 0 1 10 3 7 10 27 1 1 8 7 5 5 4 62 4 0 9 20 3 18 5 32 2 1 10 100 4 22 18 45 0 0 4 50 8 15 9 38 3
// Matrix after forwardization: 1 7 4 7 3 7 0.536585 1 0 1 10 3 7 10 0.962963 1 1 8 7 5 5 4 0.926829 0.333333 0 9 20 3 18 5 1 1 1 10 100 4 22 18 1 1 0 4 50 8 15 9 1 0.666667
// Output: 0.63818 0.0880036 0.642584 0.305568 0.879334 0.26832

using namespace std;

vector<vector<double>> originMatrix;
vector<double> v;
vector<double> weights, weightsC, weightsD, weightsR, weightsH, weightsL;
bool err = false;

// reading in
void readingIn() {
    // weights
    weightsC = {0.3453, 0.2018, 0.1249, 0.1144, 0.0679, 0.0679, 0.0389, 0.0389};
    weightsD = {0.2864, 0.1835, 0.1861, 0.1100, 0.0758, 0.0802, 0.0464, 0.0316};
    weightsH = {};
    weightsR = {};
    weightsL = {};
    
    // reading in specie
    string spec;
    cin >> spec;
    
    if (spec == "Cat") {
        weights = weightsC;
    }
    
    else if (spec == "Dog") {
        weights = weightsD;
    }
    
    else if (spec == "Rabbit") {
        weights = weightsR;
    }
    
    else if (spec == "Hamster") {
        weights = weightsH;
    }
    
    else if (spec == "Lizard") {
        weights = weightsL;
    }
    
    else {
        cout << "The model of this specie is still in progress :)";
        err = true;
    }
    
    // reading in decision matrix
    int row, column;
    column = 8;
    cin >> row;
    
    for (int i = 0; i < row; i++) {
        v.clear();
        for (int j = 0; j < column; j++) {
            double num = 0;
            cin >> num;
            v.push_back(num);
        }
        originMatrix.push_back(v);
    }
}

// forwardization
vector<vector<double>> forwardization(const vector<vector<double>> &matrix) {
    vector<vector<double>> forwardedMatrix;
    forwardedMatrix = matrix;
    
    int minBestAge = 28;
    int maxBestAge = 59;
    int minBestNumofC = 0;
    int maxBestNumofC = 2;
    
    for (int j = 6; j <= 7; j++) {
        for (int i = 0; i < matrix.size(); i++) {
            if (j == 6) {
                double M = 0;
                M = max(minBestAge - 1, 100 - maxBestAge);
                if (matrix[i][j] < minBestAge) {
                    forwardedMatrix[i][j] =
                    1 - (minBestAge - matrix[i][j]) / (minBestAge - 1);
                } else if (matrix[i][j] >= minBestAge && matrix[i][j] <= maxBestAge) {
                    forwardedMatrix[i][j] = 1;
                } else if (matrix[i][j] > maxBestAge) {
                    forwardedMatrix[i][j] =
                    1 - (matrix[i][j] - maxBestAge) / (100 - maxBestAge);
                }
            }
            
            if (j == 7) {
                double M = 0;
                M = max(minBestNumofC - 0, 5 - maxBestNumofC);
                if (matrix[i][j] < minBestNumofC) {
                    forwardedMatrix[i][j] =
                    1 - (minBestNumofC - matrix[i][j]) / (minBestNumofC - 0);
                } else if (matrix[i][j] >= minBestNumofC &&
                           matrix[i][j] <= maxBestNumofC) {
                    forwardedMatrix[i][j] = 1;
                } else if (matrix[i][j] > maxBestNumofC) {
                    forwardedMatrix[i][j] =
                    1 - (matrix[i][j] - maxBestNumofC) / (5 - maxBestNumofC);
                }
            }
        }
    }
    
    return forwardedMatrix;
}

// normaize the matrix
vector<vector<double>> normalize(const vector<vector<double>> &matrix) {
    size_t rows = matrix.size();
    size_t columns = matrix[0].size();
    vector<vector<double>> normalizedMatrix(rows, vector<double>(columns));
    
    // culculate the euclidean norm
    for (size_t j = 0; j < columns; j++) {
        double columnNorm = 0;
        for (const auto &row : matrix) {
            columnNorm += row[j] * row[j];
        }
        columnNorm = sqrt(columnNorm);
        
        for (size_t i = 0; i < rows; i++) {
            normalizedMatrix[i][j] = matrix[i][j] / columnNorm;
        }
    }
    
    return normalizedMatrix;
}

// calculate weight normalized matrix
vector<vector<double>> multiplyWeights(const vector<vector<double>> &matrix,
                                       const vector<double> &weights) {
    size_t rows = matrix.size();
    size_t columns = matrix[0].size();
    vector<vector<double>> weightedMatrix(rows, vector<double>(columns));
    
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            weightedMatrix[i][j] = matrix[i][j] * weights[j];
        }
    }
    return weightedMatrix;
}

// determine the positive ideal solution
vector<double> idealSolution(const vector<vector<double>> &matrix,
                             const vector<double> &weoghts) {
    size_t columns = matrix[0].size();
    vector<double> ideal(columns, numeric_limits<double>::min());
    for (const auto &row : matrix) {
        for (size_t j = 0; j < columns; j++) {
            ideal[j] = max(ideal[j], row[j]);
        }
    }
    return ideal;
}

// determine the negative ideal solution
vector<double> negIdealSolution(const vector<vector<double>> &matrix,
                                const vector<double> &weights) {
    size_t columns = matrix[0].size();
    vector<double> negIdeal(columns, numeric_limits<double>::max());
    for (const auto &row : matrix) {
        for (size_t j = 0; j < columns; j++) {
            negIdeal[j] = min(negIdeal[j], row[j]);
        }
    }
    return negIdeal;
}

// calculate the euclidean distance
vector<double> distance(const vector<vector<double>> &matrix,
                        const vector<double> &target) {
    size_t rows = matrix.size();
    vector<double> distances(rows, 0);
    
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < target.size(); j++) {
            distances[i] += (matrix[i][j] - target[j]) * (matrix[i][j] - target[j]);
        }
        distances[i] = sqrt(distances[i]);
    }
    return distances;
}

// calculate the realtively closeness to the ideal solution
vector<double> closenessCoefficients(const vector<double> &distanceIdeal,
                                     const vector<double> &distanceNegIdeal) {
    size_t size = distanceIdeal.size();
    vector<double> coeffients(size);
    
    for (size_t i = 0; i < size; i++) {
        coeffients[i] =
        distanceNegIdeal[i] / (distanceIdeal[i] + distanceNegIdeal[i]);
    }
    return coeffients;
}

int main() {
    // reading in matrix and weights
    readingIn();
    if (err == true) {
        return 0;
    }
    
    // forwardization of matrix
    vector<vector<double>> forwardedMatrix = forwardization(originMatrix);
    
    // normaize the matrix
    vector<vector<double>> normalizedMatrix = normalize(forwardedMatrix);
    
    // calculate weight normalized matrix
    vector<vector<double>> weightedMatrix = multiplyWeights(normalizedMatrix, weights);
    
    // determine the (negative) ideal solution
    vector<double> posIdealSolVector = idealSolution(weightedMatrix, weights);
    vector<double> negIdealSolVector = negIdealSolution(weightedMatrix, weights);
    
    // calculate the separation measures (euclidean distances)
    vector<double> euclideanDistanceIdeal =
    distance(weightedMatrix, posIdealSolVector);
    vector<double> euclideanDistanceNegIdeal =
    distance(weightedMatrix, negIdealSolVector);
    
    // calculate the realtively closeness to the ideal solution
    vector<double> closenessCoefficientsVector =
    closenessCoefficients(euclideanDistanceIdeal, euclideanDistanceNegIdeal);
    
    cout << "closest coefficients: ";
    for (const auto &coeff : closenessCoefficientsVector) {
        cout << coeff << " ";
    }
    cout << endl;
    
    return 0;
}

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

// Test for example:

// Input: Cat 6 1 7 4 7 3 7 78 2 0 0 1 10 3 7 10 27 1 1 1 8 7 5 5 4 62 4 0 0 9 20 3 18 5 32 2 2 1 10 100 4 22 18 45 0 3 0 4 50 8 15 9 38 3 2

// Input: Dog 6 1 3 4 7 3 5 78 2 0 0 8 10 3 7 8 27 1 1 1 5 7 5 5 2 62 4 0 0 7 20 3 18 7 32 2 2 1 9 100 4 22 9 45 0 3 0 10 50 8 15 4 38 3 2

// Input: Hamster 6 0 6 4 7 3 7 78 2 0 0 9 10 3 7 5 27 1 1 0 8 7 5 5 3 62 4 0 0 5 20 3 18 4 32 2 2 1 7 100 4 22 8 45 0 3 0 4 50 8 15 2 38 3 2

// Input: Rabbit 6 1 4 4 7 3 2 78 2 0 0 8 10 3 7 1 27 1 1 1 3 7 5 5 1 62 4 0 0 2 20 3 18 3 32 2 2 1 4 100 4 22 2 45 0 3 0 7 50 8 15 1 38 3 2

// Input: Lizard 6 0 2 4 7 3 0 78 2 0 0 1 10 3 7 1 27 1 1 0 5 7 5 5 0 62 4 0 0 3 20 3 18 1 32 2 2 0 9 100 4 22 2 45 0 3 1 6 50 8 15 1 38 3 2

// Output (Cat): 0.63818 0.0880036 0.642584 0.305568 0.879334 0.26832

using namespace std;

vector<vector<double>> originMatrix;
vector<double> v;
vector<double> weights, weightsC, weightsD, weightsR, weightsH, weightsL;
bool err = false;

// reading in
void readingIn() {
    // weights
    weightsC = {0.3044, 0.1806, 0.1084, 0.0941, 0.0564, 0.0564, 0.0332, 0.0332, 0.1333};
    weightsD = {0.2488, 0.1544, 0.1566, 0.0908, 0.0626, 0.0659, 0.0392, 0.0271, 0.1544};
    weightsH = {0.3107, 0.1337, 0.1825, 0.0713, 0.0492, 0.0930, 0.0339, 0.0239, 0.1019};
    weightsR = {0.2787, 0.2053, 0.1310, 0.0510, 0.0852, 0.0708, 0.0337, 0.0276, 0.1168};
    weightsL = {0.2367, 0.2778, 0.1397, 0.1087, 0.0777, 0.0501, 0.0280, 0.0194, 0.0618};
    
    // reading in specie
    string spec;
    cin >> spec;
    
    if (spec == "CAT" || spec == "Cat") {
        weights = weightsC;
    }
    
    else if (spec == "DOG" || spec == "Dog") {
        weights = weightsD;
    }
    
    else if (spec == "RABBIT" || spec == "Rabbit") {
        weights = weightsR;
    }
    
    else if (spec == "HAMSTER" || spec == "Hamster") {
        weights = weightsH;
    }
    
    else if (spec == "LIZARD" || spec == "Lizard") {
        weights = weightsL;
    }
    
    else {
        cout << "The model of this specie is still in progress :)";
        err = true;
    }
    
    // reading in decision matrix
    int row, column;
    column = 9;
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
    
    
    for (int j = 6; j <= 8; j++) {
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
            
            if (j == 8) {
                double M = 0;
                vector<double> all;
                for (int i=0; i<matrix.size(); i++) {
                    all.push_back(matrix[i][j]);
                    M = *max_element(all.begin(), all.end());
                }
                
                forwardedMatrix[i][j] = M - matrix[i][j];
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
    cout << "Input to the code as: the specie of the pet (Cat, Dog, Rabbit, Hamster, Lizard) + number of rows of the table + each number in the table (from column to row)" << endl;
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

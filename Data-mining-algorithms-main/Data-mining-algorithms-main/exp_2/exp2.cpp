#include <iostream>
#include<bits/stdc++.h>

using namespace std;

vector<int> readCSV(const string& filename) {
    vector<int> data;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int value;
        while (ss >> value) {
            data.push_back(value);
            if (ss.peek() == ',') {
                ss.ignore();
            }
        }
    }

    file.close();
    return data;
}

void writeCSV(const vector<double>& values, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    for (const auto& value : values) {
        file << value << endl;
    }

    file.close();
}

vector<double> minMaxNormalization(const vector<int>& data, int r1, int r2) {
    double maxVal = *max_element(data.begin(), data.end());
    double minVal = *min_element(data.begin(), data.end());
    vector<double> normalizedValues(data.size());
    
    for (size_t i = 0; i < data.size(); i++) {
        normalizedValues[i] = double((data[i] - minVal) * (r2 - r1)) / (maxVal - minVal) + r1;
    }

    return normalizedValues;
}

vector<double> zScoreNormalization(const vector<int>& data) {
    double mean = accumulate(data.begin(), data.end(), 0.0) / data.size();
    double stdDev = sqrt(accumulate(data.begin(), data.end(), 0.0,
                          [mean](double acc, int val) {
                              return acc + pow(val - mean, 2);
                          }) / data.size());

    vector<double> normalizedValues(data.size());
    
    for (size_t i = 0; i < data.size(); i++) {
        normalizedValues[i] = (data[i] - mean) / stdDev;
    }

    return normalizedValues;
}

int main() {
    string inputFilename = "exp2_input_MinMax.csv";
    string outputMinMaxFilename = "output_minmax_normalized.csv";
    string outputZScoreFilename = "output_zscore_normalized.csv";

    int n;
    cout << "Enter The Number of values:";
    cin >> n;

    vector<int> data = readCSV(inputFilename);

    if (data.size() != n) {
        cerr << "Error: Input data size does not match the specified number of values." << endl;
        return 1;
    }

    int r1, r2;
    cout << "Enter starting and ending range for normalization:";
    cin >> r1 >> r2;

    vector<double> minMaxValues = minMaxNormalization(data, r1, r2);
    writeCSV(minMaxValues, outputMinMaxFilename);
    cout << "Min-Max Normalization completed. Results written to " << outputMinMaxFilename << endl;

    vector<double> zScoreValues = zScoreNormalization(data);
    writeCSV(zScoreValues, outputZScoreFilename);
    cout << "Z-Score Normalization completed. Results written to " << outputZScoreFilename << endl;

    return 0;
}

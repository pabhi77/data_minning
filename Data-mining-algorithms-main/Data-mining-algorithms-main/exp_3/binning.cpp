#include <iostream>
#include<bits/stdc++.h>

using namespace std;

// Equal Width Binning
vector<vector<double>> equalWidthBinning(const vector<double>& data, int numBins) {
    double minVal = *min_element(data.begin(), data.end());
    double maxVal = *max_element(data.begin(), data.end());
    double binWidth = (maxVal - minVal) / numBins;

    vector<vector<double>> bins(numBins);

    for (const double& val : data) {
        int binIndex = (val - minVal) / binWidth;
        if (binIndex == numBins) {
            binIndex--;  // Ensure the last value is included in the last bin
        }
        bins[binIndex].push_back(val);
    }

    return bins;
}

// Equal Frequency Binning
vector<vector<double>> equalFrequencyBinning(const vector<double>& data, int numBins) {
    vector<double> sortedData = data;
    sort(sortedData.begin(), sortedData.end());

    int pointsPerBin = data.size() / numBins;
    vector<vector<double>> bins(numBins);
    int dataIndex = 0;

    for (int binIndex = 0; binIndex < numBins; binIndex++) {
        for (int i = 0; i < pointsPerBin && dataIndex < data.size(); i++) {
            bins[binIndex].push_back(sortedData[dataIndex]);
            dataIndex++;
        }
    }

    return bins;
}

// Function to read CSV file
vector<double> readCSV(const string& filename) {
    vector<double> data;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        double value;
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

// Function to write CSV file
void writeCSV(const vector<vector<double>>& bins, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    for (const auto& bin : bins) {
        for (size_t i = 0; i < bin.size(); ++i) {
            file << bin[i];
            if (i < bin.size() - 1) {
                file << ",";
            }
        }
        file << endl;
    }

    file.close();
}

int main() {
    // Input CSV file
    string inputFilename = "input.csv";

    // User input for the number of bins
    int numBins;
    cout << "Enter the number of bins: ";
    cin >> numBins;

    // Equal-Width Output CSV file
    string outputWidthFilename = "output_data_width.csv";

    // Equal-Frequency Output CSV file
    string outputFreqFilename = "output_data_freq.csv";

    // Read data from CSV
    vector<double> data = readCSV(inputFilename);

    if (data.empty()) {
        return 1;  // Exit if there was an error reading the CSV file
    }

    // Perform equal-width binning
    vector<vector<double>> widthBins = equalWidthBinning(data, numBins);
    writeCSV(widthBins, outputWidthFilename);

    cout << "Equal-Width Binning completed. Results written to " << outputWidthFilename << endl;

    // Perform equal-frequency binning
    vector<vector<double>> frequencyBins = equalFrequencyBinning(data, numBins);
    writeCSV(frequencyBins, outputFreqFilename);

    cout << "Equal-Frequency Binning completed. Results written to " << outputFreqFilename << endl;

    return 0;
}

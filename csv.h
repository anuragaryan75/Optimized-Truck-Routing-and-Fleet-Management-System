#include <bits/stdc++.h>

using namespace std;

class csv {
    vector<vector<string>> data;
    string filename;

public:
	csv(string filename){
		this -> filename = filename;
	}

    vector<vector<string>> loadData() {
        ifstream file(filename);

        if (!file.is_open()) {
            cout << "Error opening file: " << filename << endl;
            return data;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            
            vector<string> row;
            string cell;

            while (getline(ss, cell, ',')) {
                row.push_back(cell);
            }
            data.push_back(row);
        }

        file.close();
        return data;
    }

    void printData() {
        for (auto row : data) {
            for (auto cell : row) {
                cout << cell << " ";
            }
            cout << "\n";
        }
    }

    void overwriteData(vector<vector<string>>& newData) {
        ofstream file(filename);

        if (!file.is_open()) {

            file.open(filename, ios::out);
            if (!file.is_open()) {
                cerr << "Error creating file: " << filename << endl;
                return;
            }
        }

        for (auto row : newData) {
            for (int i = 0; i < row.size(); ++i) {
                file << row[i];
                if (i != row.size() - 1) {
                    file << ",";
                }
            }
            file << "\n";
        }

        file.close();
    }
};

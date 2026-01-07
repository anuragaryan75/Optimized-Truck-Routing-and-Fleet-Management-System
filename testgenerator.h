#include <bits/stdc++.h>
#include <random>
#include "box.h"
#include "truck.h"

using namespace std;

class testGenerator{

	
public:
	vector <string> locations;
	testGenerator(){
		locations = {
			"Delhi", "Lucknow", "Noida", "Rawalpindi", "Kottayam"
		};
	}

	void saveBoxData(string filename, vector <Box> &data){
		vector <vector <string>> upload;

		for(auto it : data){
			vector <string> tmp = {to_string(it.id), it.src, it.dest, to_string(it.volume), to_string(it.value)};
			upload.push_back(tmp);
		}

		csv myFile(filename);
		myFile.overwriteData(upload);
	}

	void saveTruckData(string filename, vector <Truck> &data){
		vector <vector <string>> upload;

		for(auto it : data){
			vector <string> tmp = {it.number, it.src, it.dest, to_string(it.capacity), to_string(it.cost)};
			upload.push_back(tmp);
		}

		csv myFile(filename);
		myFile.overwriteData(upload);
	}

	

	void generateBox(int count){
		vector <Box> boxData;
		// Weight

		Box row;
		
		for(int i = 0; i < count; ++i){
			row.src = locations[rand() % 5];
			row.dest = locations[rand() % 5];

			while(row.dest == row.src){
				row.dest = locations[rand() % 5];
			}

			row.id = (10000 + (rand() % 10000));
			row.volume = 5 + (rand() % 5);
			row.value = 5 + (rand() % 5);

			boxData.push_back(row);
		}

		saveBoxData("box.csv", boxData);
	}

	void generateTruck(int count){
		srand(time(NULL)); // Seed for rand()
		vector <Truck> truckData;
		// Capacity Cost

		Truck row;

		for(int i = 0; i < count; ++i){
			row.number = "UP32-" + to_string(10000 + rand() % 10000);

			row.src = locations[rand() % locations.size()];
			row.dest = locations[rand() % locations.size()];

			while(row.dest == row.src){
				row.dest = locations[rand() % locations.size()];
			}

			row.capacity = 20 + (rand() % 10);
			row.cost = 12 + (rand() % 15);

			truckData.push_back(row);
		}

		saveTruckData("truck.csv", truckData);
	}	
};
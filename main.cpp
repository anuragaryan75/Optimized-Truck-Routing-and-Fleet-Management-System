#include <bits/stdc++.h>
#include <conio.h>

// Custom Headers //
#include "csv.h"
#include "testgenerator.h"
#include "graph.h"
#include "triesearch.h"
#include "design.h"

using namespace std;

Map myMap;
Trie myTrie;
testGenerator gn;

MenuItem mainMenu({"Generate Data", "Display Data", "View Assigned", "Exit"});
MenuItem generateMenu({"Generate Truck Data", "Generate Box Data", "Generate Map Data"});
MenuItem displayMenu({"Display Truck Data", "Display Box Data", "Display Map Data"});

void printData(vector<vector<string>>& data){
    for(auto& row : data){
        for(auto& col : row){
            cout << col << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void addData(){

}

vector<vector<string>> loadAndPrint(string filename){
    csv data(filename);
    cout << "Filename : " << filename << "\n------------------------------------------\n";
    vector<vector<string>> dt = data.loadData();
    printData(dt);
    return dt;
}

vector<vector<string>> loadOnly(string filename){
    csv data(filename);
    vector<vector<string>> dt = data.loadData();
    return dt;
}

void truckGenerate(){
	gn.generateTruck(3);
	loadAndPrint("truck.csv");
}

void boxGenerate(){
	gn.generateTruck(100);
	loadAndPrint("box.csv");
}
void mapGenerate(){
	gn.generateTruck(5);
	loadAndPrint("map.csv");
}

void generate(){
   
    gn.generateBox(100);
    gn.generateTruck(3);
    myMap.generateMap(10);

    // for(auto city : myMap.code){
    // 	myTrie.insert(city.first);
    // }
}


vector <int> fillPrices(vector<vector<string>>& box, int W){
    int n = box.size();

    if(n == 0) return {};

    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= W; ++j){
            if(j >= stoi(box[i - 1][3])){
                dp[i][j] = max(dp[i - 1][j], stoi(box[i - 1][4]) + dp[i - 1][j - stoi(box[i - 1][3])]);
            }
            else{
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    int i, j;
    i = n, j = W;

    vector <int> selectedId;

    while(i >= 0 || j >= 0){
    	if(dp[i][j] == dp[i - 1][j]){
    		--i;
    	}
    	else{
    		selectedId.push_back(stoi(box[i - 1][0]));
    		j -= stoi(box[i - 1][3]);
    		--i;
    	}

    	if(i <= 0 || j <= 0) break;
    }

    return selectedId;
}

bool coveredInPath(string boxSrc, string boxDest, vector <string> path){
	for(auto &city : path){
		if(boxSrc == path[0] && city == boxDest){
			return 1;
		}
	} 

	return 0;
}

void generateMenuFunction(){
	while(1){
		generateMenu.display();
		char ch = getch();
		if(ch == 'q') break;
		else if(tolower(ch) == 'w'){
			generateMenu.moveUp();
		}
		else if(tolower(ch) == 's'){
			generateMenu.moveDown();
		}
		else if(tolower(ch) == 'x'){
			if(generateMenu.selected == 0){
				// truckGenerate();
				cout << "Generated truck.csv successful\n";
				char ch = getch();
			}
			else if(generateMenu.selected == 1){
				// boxGenerate();
				cout << "Generated box.csv successful\n";
				char ch = getch();
			}
			else{
				// mapGenerate();
				cout << "Generated map.csv successful\n";
				char ch = getch();
			}
		}
	}
}


void search(map <string, vector <pair <int, int>>> dxy){
	for(auto &xyz : dxy){
		for(auto &boxes : xyz.second){
			cout << "Truck ID : " << xyz.first << "\nBox ID : " << boxes.first << "\nIteration : " << boxes.second << "\n\n";
		}
	}
	cout << "\n";
}

void assignFunction(){
	system("cls");
	generate();


	vector<vector<string>> boxData = loadAndPrint("box.csv");
    vector<vector<string>> truckData = loadAndPrint("truck.csv");
    vector<vector<string>> mapData = loadAndPrint("map.csv");



	sort(truckData.begin(), truckData.end(), [](vector<string>& a, vector<string>& b) {
        return stoi(a[4]) < stoi(b[4]);
    });

    map <pair <string, string>, int> costings;
    map <pair <string, string>, vector <string>> paths;

    cout << "Paths\n------------------------------------------\n";
    for(auto& truck : truckData){
    	cout << truck[1] << " " << truck[2] << " : ";
    	pair <vector <string>, int> path = myMap.getShortestPath(truck[1], truck[2]);

    	costings[{truck[1], truck[2]}] = path.second;
    	paths[{truck[1], truck[2]}] = path.first;

    	for(auto cityName : path.first){
    		cout << cityName << " ";
    	}
    	cout << path.second << "\n";
    }

    cout << "\nAssigned Trucks\n------------------------------------------\n";

    map <string, vector <pair <int, int>>> dxy;

    vector <bool> done(boxData.size(), false);
    for(auto& truck : truckData){
        vector<vector<string>> filteredBox;

        int itr = 0;

        while(1){
	        int i = 0;
	        filteredBox.clear();
	        for(auto& box : boxData){
	            if(!done[i++] && coveredInPath(box[1], box[2], paths[{truck[1], truck[2]}])){
	                filteredBox.push_back(box);
	            }
	        }

	        if(filteredBox.size() == 0) break;

	        vector <int> assigned = fillPrices(filteredBox, stoi(truck[3]));

	        i = 0;
	        for(auto&box : boxData){
	        	for(auto &id : assigned){
	        		if(stoi(box[0]) == id){
	        			done[i] = true;
	        		}
	        	}
	        	++i;
	        }

	        for(auto &id : assigned){
	        	dxy[{truck[0]}].push_back({id, itr});
	        }
	        ++itr;
	        // for(auto &id : assigned){
	        // 	cout << "Box with ID : " << id << " assigned to Truck : " << truck[0] << " for iteration #" << itr << "\n";
	        // }
	        // ++itr;
    	}

    	cout << "Cost for " << truck[0] << " : " << itr * costings[{truck[1], truck[2]}] << "\n";
    }

    search(dxy);
    char ch = getch();
}

void displayMenuFunction(){
	while(1){
		displayMenu.display();
		char ch = getch();
		if(ch == 'q') break;
		else if(tolower(ch) == 'w'){
			displayMenu.moveUp();
		}
		else if(tolower(ch) == 's'){
			displayMenu.moveDown();
		}
		else if(tolower(ch) == 'x'){
			if(displayMenu.selected == 0){
				loadAndPrint("truck.csv");
				char ch = getch();
			}
			else if(displayMenu.selected == 1){
				loadAndPrint("box.csv");
				char ch = getch();
			}
			else{
				loadAndPrint("map.csv");
				char ch = getch();
			}
		}
	}
}

int main(){
	while(1){
		
		mainMenu.display();
		char ch = getch();
		if(ch == 'q') break;
		else if(tolower(ch) == 'w'){
			mainMenu.moveUp();
		}
		else if(tolower(ch) == 's'){
			mainMenu.moveDown();
		}
		else if(tolower(ch) == 'x'){
			if(mainMenu.selected == 0){
				generateMenuFunction();
			}
			else if(mainMenu.selected == 1){
				displayMenuFunction();
			}
			else if(mainMenu.selected == 2){
				assignFunction();
			}
			else{
				break;
			}
		}
	}

    // generate(); // Generate test file for box.csv and truck.csv

    

    
    

    return 0;
}

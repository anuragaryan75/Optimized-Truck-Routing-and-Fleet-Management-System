#include <bits/stdc++.h> // Assuming all necessary headers are included in this file

class Map : public testGenerator {
public:
    map<int, vector<pair<int, int>>> adjList;
    map<string, int> codes;
    map <int, string> revCodes;
    int x;

    Map() {
        x = 0;
    }

    void addEdge(string src, string dest, int distance) {
        if (!codes.count(src)) codes[src] = x++;
        if (!codes.count(dest)) codes[dest] = x++;

        int xsrc = codes[src];
        int xdest = codes[dest];

        revCodes[xsrc] = src;
        revCodes[xdest] = dest;

        adjList[xsrc].push_back({xdest, distance});
        adjList[xdest].push_back({xsrc, distance});
    }

    pair <vector<string>, int> getShortestPath(string src, string dest) {
        int srcCode = codes[src];
        int destCode = codes[dest];

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector <int> dist(x, INT_MAX);
        vector <int> pred(x, -1); // Stores predecessors of vertices
        dist[srcCode] = 0;
        pq.push({0, srcCode});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pred[v] = u; // Update predecessor of v
                    pq.push({dist[v], v});
                }
            }
        }

        // Constructing the shortest path
        stack<int> path;
        int current = destCode;
        while (current != -1) {
            path.push(current);
            current = pred[current];
        }

        vector<string> retPath;
        while (!path.empty()) {
            retPath.push_back(revCodes[path.top()]);
            path.pop();
        }

        return {retPath, dist[codes[dest]]};
    }


    void generateMap(int count) {
        srand(time(NULL)); // Seed for rand()

        for (int i = 0; i < count; ++i) {
            int src = rand() % locations.size();
            int dest = rand() % locations.size();
            int wt = 30 + rand() % 120;

            this -> addEdge(locations[src], locations[dest], wt);
        }

        saveMapData("map.csv");
    }

    void saveMapData(string filename) {
        vector<vector<string>> upload;

        for (auto root : adjList) {
            vector<string> tmp;
            tmp.push_back(revCodes[root.first]);

            for (auto child : root.second) {
                tmp.push_back(revCodes[child.first]);
                tmp.push_back(to_string(child.second));
            }

            upload.push_back(tmp);
        }

        csv myFile(filename); // Assuming csv is defined and properly instantiated
        myFile.overwriteData(upload);
    }
};

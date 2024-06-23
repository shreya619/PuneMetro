#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <algorithm> // for transform
#include <cctype> // for tolower

using namespace std;

const double INF = numeric_limits<double>::infinity(); // Represents infinity for distances

// Function to get the index of a station name in the distance matrix
int getStationIndex(const string& stationName, const vector<string>& stations) {
    for (int i = 0; i < stations.size(); i++) {
        string lowerStation = stations[i];
        transform(lowerStation.begin(), lowerStation.end(), lowerStation.begin(), ::tolower);
        if (lowerStation == stationName) {
            return i;
        }
    }
    return -1; // Station not found
}

// Function to implement Dijkstra's algorithm
pair<vector<double>, vector<int>> dijkstra(const vector<vector<double>>& distanceMatrix, int source) {
    int numStations = distanceMatrix.size();
    vector<double> distances(numStations, INF); // Distances from source to all stations
    vector<int> previous(numStations, -1); // To store the path
    distances[source] = 0; // Distance to source is 0

    vector<bool> visited(numStations, false); // Visited stations

    // Priority queue to efficiently select the next closest unvisited station
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({0, source}); // Push source with distance 0

    while (!pq.empty()) {
        int currentStation = pq.top().second;
        pq.pop();

        if (visited[currentStation]) {
            continue; // Skip already visited stations
        }

        visited[currentStation] = true;

        for (int neighbor = 0; neighbor < numStations; neighbor++) {
            // Update distance if there's an edge and it improves the path
            if (distanceMatrix[currentStation][neighbor] != 0 && distances[currentStation] + distanceMatrix[currentStation][neighbor] < distances[neighbor]) {
                distances[neighbor] = distances[currentStation] + distanceMatrix[currentStation][neighbor];
                previous[neighbor] = currentStation; // Store the path
                pq.push({distances[neighbor], neighbor});
            }
        }
    }

    return {distances, previous};
}

// Function to get the path from the source to the destination
vector<int> getPath(int source, int destination, const vector<int>& previous) {
    vector<int> path;
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    if (path[0] == source) {
        return path;
    }
    return {}; // Return empty path if there's no valid path from source to destination
}

int main() {
    vector<string> stations = {
        "PCMC", "Sant Tukaram Nagar", "Nashik Phata", "Kasarwadi", "Phugewadi", "Dapodi", 
        "Bopodi", "Khadki", "Range Hills", "Shivaji Nagar", "Civil Court", "Vanaz", "Anand Nagar", 
        "Ideal Colony", "Nal Stop", "Garware College", "Deccan Gymkhana", "Chatrapati Shivaji Udyan", 
        "PMC", "Mangalwar Peth", "Pune Railway Station", "Ruby Hall Clinic", "Bund Garden", 
        "Kalyani Nagar", "Ramwadi"
    };

    vector<vector<double>> distanceMatrix = {
        {0, 5.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {5.4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1.1, 0, 0.85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0.85, 0, 1.6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1.6, 0, 0.95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0.95, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 2, 0, 2.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 2.5, 0, 1.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1.5, 0, 0, 0, 0, 0, 0, 0, 0, 0.9, 1.1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.95, 0, 1.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.5, 0, 1.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.5, 0, 1.8, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.8, 0, 1.1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.1, 0, 1.4, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.4, 0, 1.1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.1, 0, 1.2, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.2, 0, 1.3, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.3, 0, 1.2, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.2, 0, 0.9, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.9, 0, 1.2, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.2, 0, 1.5},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.5, 0}
    };

    // Ask user for source and destination stations
    string sourceStation, destinationStation;
    cout << "Enter source station: ";
    getline(cin, sourceStation);
    cout << "Enter destination station: ";
    getline(cin, destinationStation);

    // Convert input to lowercase for case-insensitive comparison
    transform(sourceStation.begin(), sourceStation.end(), sourceStation.begin(), ::tolower);
    transform(destinationStation.begin(), destinationStation.end(), destinationStation.begin(), ::tolower);

    int sourceIndex = getStationIndex(sourceStation, stations);
    int destinationIndex = getStationIndex(destinationStation, stations);

    if (sourceIndex == -1 || destinationIndex == -1) {
        cout << "Invalid source or destination station name." << endl;
        return 1;
    }

    // Run Dijkstra's algorithm to find the shortest paths from the source
    auto result = dijkstra(distanceMatrix, sourceIndex);
    vector<double> distances = result.first;
    vector<int> previous = result.second;

    if (distances[destinationIndex] == INF) {
        cout << "No path exists between " << stations[sourceIndex] << " and " << stations[destinationIndex] << "." << endl;
    } else {
        cout << "The shortest distance from " << stations[sourceIndex] << " to " << stations[destinationIndex] << " is " << distances[destinationIndex] << " km." << endl;
        
        // Get and print the path
        vector<int> path = getPath(sourceIndex, destinationIndex, previous);
        cout << "Path: ";
        for (int i = 0; i < path.size(); i++) {
            cout << stations[path[i]];
            if (i < path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }

    return 0;
}

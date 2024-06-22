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
vector<double> dijkstra(const vector<vector<double>>& distanceMatrix, int source) {
    int numStations = distanceMatrix.size();
    vector<double> distances(numStations, INF); // Distances from source to all stations
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
                pq.push({distances[neighbor], neighbor});
            }
        }
    }

    return distances;
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
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.8, 0, 0.95, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.95, 0, 0.65, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.65, 0, 0.75, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.75, 0, 2.9, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.1, 0, 0, 0, 0, 0, 0, 0, 2.9, 0, 0.8, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.8, 0, 0, 0.7, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.8, 0.7, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3.1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.1, 0, 2},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0},
    };

    // Get source and destination from user
    string sourceStation, destinationStation;
    cout << "Enter source station: ";
    getline(cin, sourceStation);
    cout << "Enter destination station: ";
    getline(cin, destinationStation);

    // Convert station names to lower case for case-insensitive comparison
    transform(sourceStation.begin(), sourceStation.end(), sourceStation.begin(), ::tolower);
    transform(destinationStation.begin(), destinationStation.end(), destinationStation.begin(), ::tolower);

    // Find the indices of the source and destination stations
    int sourceIndex = getStationIndex(sourceStation, stations);
    int destinationIndex = getStationIndex(destinationStation, stations);

    if (sourceIndex == -1 || destinationIndex == -1) {
        cout << "Invalid station name(s). Please check the input." << endl;
        return 1;
    }

    // Run Dijkstra's algorithm to find shortest paths from the source station
    vector<double> distances = dijkstra(distanceMatrix, sourceIndex);

    // Output the distance to the destination station
    double distance = distances[destinationIndex];
    if (distance == INF) {
        cout << "No path found from " << sourceStation << " to " << destinationStation << "." << endl;
    } else {
        cout << "Shortest distance from " << sourceStation << " to " << destinationStation << " is " << distance << " km." << endl;
    }

    return 0;
}

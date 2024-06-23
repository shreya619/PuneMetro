#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <limits>

using namespace std;

const double INF = numeric_limits<double>::infinity();

struct Edge {
    string dest;
    double weight;
};

vector<string> corridor1 = {
    "PCMC", "Sant Tukaram Nagar", "Nashik Phata", "Kasarwadi", "Phugewadi", "Dapodi",
    "Bopodi", "Khadki", "Range Hills", "Shivaji Nagar", "Civil Court"
};

vector<string> corridor2 = {
    "Vanaz", "Anand Nagar", "Ideal Colony", "Nal Stop", "Garware College", "Deccan Gymkhana",
    "Chatrapati Shivaji Udyan", "PMC", "Civil Court", "Managlwar Peth", "Pune Railway Station",
    "Ruby Hall Clinic", "Bund Garden", "Kalyani Nagar", "Ramwadi"
};

unordered_map<string, vector<Edge>> graph;

void addEdge(const string& u, const string& v, double weight) {
    graph[u].push_back(Edge{v, weight});
    graph[v].push_back(Edge{u, weight});
}

unordered_map<string, double> dijkstra(const string& source, unordered_map<string, string>& previous) {
    unordered_map<string, double> distances;
    for (const auto& pair : graph) {
        distances[pair.first] = INF;
    }
    distances[source] = 0;

    auto cmp = [&distances](const string& left, const string& right) {
        return distances[left] > distances[right];
    };
    priority_queue<string, vector<string>, decltype(cmp)> pq(cmp);
    pq.push(source);

    while (!pq.empty()) {
        string u = pq.top();
        pq.pop();

        for (const Edge& edge : graph[u]) {
            string v = edge.dest;
            double weight = edge.weight;
            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                pq.push(v);
                previous[v] = u;
            }
        }
    }

    return distances;
}

int calculateSwitches(const vector<string>& path, const string& source, const string& destination) {
    int switches = 0;
    string currentCorridor = "";

    // Check if both source and destination are in Corridor 2
    bool sourceInCorridor2 = find(corridor2.begin(), corridor2.end(), source) != corridor2.end();
    bool destinationInCorridor2 = find(corridor2.begin(), corridor2.end(), destination) != corridor2.end();

    if (sourceInCorridor2 && destinationInCorridor2) {
        return 0; // No switching needed
    }

    for (const string& station : path) {
        if (find(corridor1.begin(), corridor1.end(), station) != corridor1.end()) {
            if (currentCorridor != "corridor1") {
                switches++;
                currentCorridor = "corridor1";
            }
        } else if (find(corridor2.begin(), corridor2.end(), station) != corridor2.end()) {
            if (currentCorridor != "corridor2") {
                switches++;
                currentCorridor = "corridor2";
            }
        }
    }

    return switches - 1; // Subtract 1 because the first corridor doesn't count as a switch
}

vector<string> getPath(const string& start, const string& end, const unordered_map<string, string>& previous) {
    vector<string> path;
    for (string at = end; at != ""; at = previous.at(at)) {
        path.push_back(at);
        if (at == start) break;
    }
    reverse(path.begin(), path.end());
    return path;
}

double calculatePathDistance(const vector<string>& path, const unordered_map<string, double>& distances) {
    if (path.empty()) return 0.0;
    return distances.at(path.back());
}

double calculateFare(double distance, bool hasNcmcCard) {
    double fare = 0.0;
    if (distance <= 1) {
        fare = hasNcmcCard ? 9 : 10;
    } else if (distance <= 2) {
        fare = hasNcmcCard ? 13.5 : 15;
    } else if (distance <= 4) {
        fare = hasNcmcCard ? 18 : 20;
    } else if (distance <= 8) {
        fare = hasNcmcCard ? 22.5 : 25;
    } else if (distance <= 16) {
        fare = hasNcmcCard ? 27 : 30;
    } else {
        fare = hasNcmcCard ? 32.5 : 35;
    }
    return fare;
}

int main() {
    // Initialize the graph with distances
    addEdge("PCMC", "Sant Tukaram Nagar", 5.4);
    addEdge("Sant Tukaram Nagar", "Nashik Phata", 2);
    addEdge("Nashik Phata", "Kasarwadi", 1);
    addEdge("Kasarwadi", "Phugewadi", 1.1);
    addEdge("Phugewadi", "Dapodi", 0.85);
    addEdge("Dapodi", "Bopodi", 1.6);
    addEdge("Bopodi", "Khadki", 0.95);
    addEdge("Khadki", "Range Hills", 2);
    addEdge("Range Hills", "Shivaji Nagar", 2.5);
    addEdge("Shivaji Nagar", "Civil Court", 1.5);
    addEdge("Vanaz", "Anand Nagar", 0.95);
    addEdge("Anand Nagar", "Ideal Colony", 1.5);
    addEdge("Ideal Colony", "Nal Stop", 1.5);
    addEdge("Nal Stop", "Garware College", 1.8);
    addEdge("Garware College", "Deccan Gymkhana", 0.95);
    addEdge("Deccan Gymkhana", "Chatrapati Shivaji Udyan", 0.65);
    addEdge("Chatrapati Shivaji Udyan", "PMC", 0.75);
    addEdge("PMC", "Civil Court", 2.9);
    addEdge("Civil Court", "Managlwar Peth", 1.1);
    addEdge("Managlwar Peth", "Pune Railway Station", 0.8);
    addEdge("Pune Railway Station", "Ruby Hall Clinic", 0.7);
    addEdge("Ruby Hall Clinic", "Bund Garden", 1);
    addEdge("Bund Garden", "Kalyani Nagar", 3.1);
    addEdge("Kalyani Nagar", "Ramwadi", 2);

    string sourceStation, destinationStation;
    cout << "Enter source station: ";
    getline(cin, sourceStation);
    cout << "Enter destination station: ";
    getline(cin, destinationStation);

    unordered_map<string, string> previous;

    // Run Dijkstra's algorithm and get distances from the source
    unordered_map<string, double> distances = dijkstra(sourceStation, previous);

    // Get the path and calculate the number of switches
    vector<string> path = getPath(sourceStation, destinationStation, previous);
    int switches = calculateSwitches(path, sourceStation, destinationStation);

    // Calculate the total distance for the path
    double totalDistance = calculatePathDistance(path, distances);

    cout << "Shortest path: ";
    for (const string& station : path) {
        cout << station << " ";
    }
    cout << endl;

    cout << "Number of switches: " << switches << endl;
    cout << "Total distance: " << totalDistance << " km" << endl;

    // Ask the user if they have an NCMC card
    string hasNcmcCardStr;
    cout << "Do you have an NCMC card? (yes/no): ";
    getline(cin, hasNcmcCardStr);
    bool hasNcmcCard = (hasNcmcCardStr == "yes");

    // Calculate and display the fare
    double fare = calculateFare(totalDistance, hasNcmcCard);
    cout << "Total fare: ₹" << fare << endl;

    return 0;
}


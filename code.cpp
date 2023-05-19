#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

#define MAX_INT 2147483647

// function to calculate the total cost


double calculateCost(double distance, int timeOnRoad, int timeOnPitStops) {
    double fuelCost = distance * 0.45;
    double driverCost = timeOnRoad * 10;
    double pitStopCost = timeOnPitStops * 25;
    double totalCost = fuelCost + driverCost + pitStopCost;
    return totalCost;
}


// function to find the shortest path using Dijkstra's algorithm

void dijkstra(unordered_map<string, vector<pair<string, double>>>& graph, string start, unordered_map<string, int>& waitTimes) 
{
    // create priority queue to store unvisited nodes

    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;

    // create a map to store the distances

    unordered_map<string, double> distances;

    // initialize all distances to infinity

    for (auto node : graph)
        distances[node.first] = MAX_INT;

    // set the distance of the starting node to 0

    distances[start] = 0;

    // add the starting node to the priority queue

    pq.push({0, start});

    // while the priority queue is not empty

    while (!pq.empty()) {

        // remove the node with the lowest tentative distance

        auto current = pq.top();
        pq.pop();

        // for each neighbor of the current node

        for (auto neighbor : graph[current.second])
         {
            // calculate the tentative distance

            double distance = distances[current.second] + neighbor.second + waitTimes[neighbor.first];

            // if the tentative distance is less than the current

            // distance, update the distance and add the neighbor to the priority

            if (distance < distances[neighbor.first])
             {

                distances[neighbor.first] = distance;
                pq.push({distance, neighbor.first});

            }
        }
    }

    // for each city

    for (auto city : graph)
     {
        // calculate the total cost

        double totalCost = calculateCost(distances[city.first], distances[city.first] / 80, waitTimes[city.first]);

        // print the shortest path and the total cost

        cout << "Starting from " << city.first<<endl;

        cout << " Total cost: " << totalCost << endl;
    }
}

int main() {
    unordered_map<string, vector<pair<string, double>>> graph = {

        {"mumbai", {{"benguluru", 3}, {"hyderabad", 2}, {"kolkata", 6}, {"lucknow", 7}, {"newdelhi", 5}}},

        {"benguluru", {{"mumbai", 3}, {"hyderabad", 1}, {"kolkata", 6}, {"lucknow", 6}, {"newdelhi", 8}}},

        {"hyderabad", {{"mumbai", 2}, {"benguluru", 1}, {"kolkata", 4}, {"lucknow", 5}, {"newdelhi", 7}}},

        {"kolkata", {{"mumbai", 6}, {"benguluru", 6}, {"hyderabad", 4}, {"lucknow", 3}, {"newdelhi", 5}}},

        {"lucknow", {{"mumbai", 7}, {"benguluru", 6}, {"hyderabad", 5}, {"kolkata", 3}, {"newdelhi", 2}}},
        
        {"newdelhi", {{"mumbai", 5}, {"benguluru", 8}, {"hyderabad", 7}, {"kolkata", 5}, {"lucknow", 2}}}
    };
    unordered_map<string, int> waitTimes = {
        {"mumbai", 4},
        {"benguluru", 7},
        {"hyderabad", 3},
        {"kolkata", 2},
        {"lucknow", 1},
        {"newdelhi", 5}
    };
    string start = "mumbai";
    dijkstra(graph, start, waitTimes);
    return 0;
}

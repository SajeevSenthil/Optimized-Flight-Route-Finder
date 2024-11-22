#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <queue>
#include <iomanip>
#include <deque>

using namespace std;

const vector<string> airport_names = {
    "Agartala (IXA)", "Agatti (AGX)", "Agra (AGR)", "Ahmedabad (AMD)", "Aizawl (AJL)", 
    "Amritsar (ATQ)", "Aurangabad (IXU)", "Ayodhya (AYJ)", "Bagdogra (IXB)", "Bareilly (BEK)", 
    "Belagavi (IXG)", "Bengaluru (BLR)", "Bhopal (BHO)", "Bhubaneswar (BBI)", "Chandigarh (IXC)", 
    "Chennai (MAA)", "Coimbatore (CJB)", "Darbhanga (DBR)", "Dehradun (DED)", "Delhi (DEL)", 
    "Deoghar (DGH)", "Dharamshala (DHM)", "Dibrugarh (DIB)", "Dimapur (DMU)", "Diu (DIU)", 
    "Durgapur (RDP)", "Gaya (GAY)", "Goa (GOI)", "Gondia (GDB)", "Gorakhpur (GOP)", 
    "Guwahati (GAU)", "Gwalior (GWL)", "Hirasar (HSR)", "Hubli (HBX)", "Hyderabad (HYD)", 
    "Imphal (IMF)", "Indore (IDR)", "Itanagar (HGI)", "Jabalpur (JLR)", "Jagdalpur (JGB)", 
    "Jaipur (JAI)", "Jaisalmer (JSA)", "Jammu (IXJ)", "Jharsuguda (JRG)", "Jodhpur (JDH)", 
    "Jorhat (JRH)", "Kadapa (CDP)", "Kannur (CNN)", "Kanpur (KNU)", "Khajuraho (HJR)", 
    "Kochi (COK)", "Kolhapur (KLH)", "Kolkata (CCU)", "Kozhikode (CCJ)", "Kurnool (KJB)", 
    "Leh (IXL)", "Lucknow (LKO)", "Madurai (IXM)", "Mangaluru (IXE)", "Mumbai (BOM)", 
    "Mysuru (MYQ)", "Nagpur (NAG)", "Nashik (ISK)", "North Goa (GOX)", "Pantnagar (PGH)", 
    "Patna (PAT)", "Port Blair (IXZ)", "Prayagraj (IXD)", "Pune (PNQ)", "Raipur (RPR)", 
    "Rajahmundry (RJA)", "Rajkot (RAJ)", "Ranchi (IXR)", "Salem (SXV)", "Shillong (SHL)", 
    "Shirdi (SAG)", "Shivamogga (RQY)", "Silchar (IXS)", "Srinagar (SXR)", "Surat (STV)", 
    "Thiruvananthapuram (TRV)", "Tiruchirappalli (TRZ)", "Tirupati (TIR)", "Tuticorin (TCR)", 
    "Udaipur (UDR)", "Vadodara (BDQ)", "Varanasi (VNS)", "Vijayawada (VGA)", "Visakhapatnam (VTZ)"
};

const double INF = numeric_limits<double>::infinity();
deque<pair<int, int>> recent_routes;

vector<vector<double>> loadAdjacencyMatrix(const string& filename) {
    ifstream file(filename);
    vector<vector<double>> adjacency_matrix;
    string line;
    bool first_row = true;

    while (getline(file, line)) {
        if (first_row) {
            first_row = false;
            continue;
        }

        istringstream ss(line);
        string cell;
        vector<double> row;
        bool first_column = true;

        while (getline(ss, cell, ',')) {
            if (first_column) {
                first_column = false;
                continue;
            }

            try {
                double value = stod(cell);
                row.push_back(value);
            } catch (const invalid_argument&) {
                row.push_back(INF);
            }
        }

        if (!row.empty()) {
            adjacency_matrix.push_back(row);
        }
    }

    file.close();
    return adjacency_matrix;
}

void printPath(const vector<int>& parent, int vertex) {
    if (vertex < 0) return;
    printPath(parent, parent[vertex]);
    if (parent[vertex] != -1) cout << " -> ";
    cout << airport_names[vertex];
}

void dijkstra(const vector<vector<double>>& adj_matrix, int src, int dest) {
    int V = adj_matrix.size();
    vector<double> dist(V, INF);
    vector<int> parent(V, -1);
    dist[src] = 0;

    using pii = pair<double, int>;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        double distance = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (distance > dist[u]) continue;

        for (int v = 0; v < V; ++v) {
            if (adj_matrix[u][v] != INF && dist[u] + adj_matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adj_matrix[u][v];
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[dest] != INF) {
        cout << "Travel Time: " << dist[dest] << " minutes\nPath: ";
        printPath(parent, dest);
        cout << endl;
    } else {
        cout << "No path exists.\n";
    }

    recent_routes.push_back({src, dest});
    if (recent_routes.size() > 5) recent_routes.pop_front();
}

void dijkstraWithStopover(const vector<vector<double>>& adj_matrix, int src, int stopover, int dest) {
    cout << "Calculating shortest path to the stopover...\n";
    dijkstra(adj_matrix, src, stopover);

    cout << "Calculating shortest path from the stopover to the destination...\n";
    dijkstra(adj_matrix, stopover, dest);
}

void displayRecentRoutes() {
    if (recent_routes.empty()) {
        cout << "No recent routes available.\n";
    } else {
        cout << "Recent Routes:\n";
        for (auto& route : recent_routes) {
            cout << airport_names[route.first] << " -> " << airport_names[route.second] << endl;
        }
    }
}

int main() {
    string filename = "Cost_with_destinations.csv";
    vector<vector<double>> adjacency_matrix = loadAdjacencyMatrix(filename);

    cout << "\nList of Airports:\n";
    for (size_t i = 0; i < airport_names.size(); ++i) {
        cout << i << ": " << airport_names[i] << endl;
    }

    while (true) {
        cout << "\n===== Flight Network Menu =====\n";
        cout << "1. Shortest Path\n";
        cout << "2. Shortest Path with Stopover\n";
        cout << "3. Recently Used Routes\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 4) break;

        int src, dest, stopover;
        if (choice == 1) {
            cout << "Enter the source airport index: ";
            cin >> src;
            cout << "Enter the destination airport index: ";
            cin >> dest;
            dijkstra(adjacency_matrix, src, dest);
        } else if (choice == 2) {
            cout << "Enter the source airport index: ";
            cin >> src;
            cout << "Enter the stopover airport index: ";
            cin >> stopover;
            cout << "Enter the destination airport index: ";
            cin >> dest;
            dijkstraWithStopover(adjacency_matrix, src, stopover, dest);
        } else if (choice == 3) {
            displayRecentRoutes();
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}

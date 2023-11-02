#include <iostream>
#include <vector>
using namespace std;

// Function to find the maximum clique in the graph
int maxClique(int n, vector<vector<bool>>& mat, vector<int>& result) {
    int maxSize = 0;  // To store the size of the maximum clique
    vector<int> currentClique;  // To store the current clique being explored
    vector<int> maxClique;  // To store the maximum clique found so far
    vector<int> candidates;  // To store the candidate vertices for the clique
    vector<int> notCandidates;  // To store the vertices not to be included in the clique
    
    // Initialize the candidates set with all vertices
    for (int i = 0; i < n; ++i) {
        candidates.push_back(i);
    }
    
    // Call the recursive function to find the maximum clique
    findClique(n, mat, candidates, notCandidates, currentClique, maxSize, maxClique);
    
    // Copy the maximum clique to the result vector
    result = maxClique;
    
    return maxSize;
}

// Recursive function to find the maximum clique
void findClique(int n, vector<vector<bool>>& mat, vector<int>& candidates, 
                vector<int>& notCandidates, vector<int>& currentClique, 
                int& maxSize, vector<int>& maxClique) {
    if (candidates.empty() && notCandidates.empty()) {
        // If there are no more candidates and not candidates, we found a clique
        if (currentClique.size() > maxSize) {
            // If the current clique is larger than the maximum clique found so far, update the maximum clique
            maxSize = currentClique.size();
            maxClique = currentClique;
        }
    } else {
        // Explore the candidates
        for (int i = 0; i < candidates.size(); ++i) {
            int v = candidates[i];
            // Add the current vertex to the clique
            currentClique.push_back(v);
            
            // Calculate the new candidates and not candidates sets
            vector<int> newCandidates, newNotCandidates;
            for (int j = 0; j < candidates.size(); ++j) {
                if (mat[v][candidates[j]]) {
                    newCandidates.push_back(candidates[j]);
                }
            }
            for (int j = 0; j < notCandidates.size(); ++j) {
                if (mat[v][notCandidates[j]]) {
                    newNotCandidates.push_back(notCandidates[j]);
                }
            }
            
            // Recursively call the function with the new sets
            findClique(n, mat, newCandidates, newNotCandidates, currentClique, maxSize, maxClique);
            
            // Remove the current vertex from the clique
            currentClique.pop_back();
            
            // Move the current vertex from candidates to not candidates
            candidates.erase(candidates.begin() + i);
            notCandidates.push_back(v);
            --i;  // Adjust the loop variable since we removed an element
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of vertices: ";
    cin >> n;

    vector<vector<bool>> mat(n, vector<bool>(n, false));
    cout << "Enter the adjacency matrix (0 or 1):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int value;
            cin >> value;
            mat[i][j] = value;
        }
    }

    vector<int> result;
    int maxSize = maxClique(n, mat, result);

    cout << "Size of the maximum clique: " << maxSize << endl;
    cout << "Vertices in the maximum clique: ";
    for (int v : result) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}

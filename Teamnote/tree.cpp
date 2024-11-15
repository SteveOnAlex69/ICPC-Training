// TREE LINE 
class TreeLineAlgorithm {
public:
    TreeLineAlgorithm(int n) : n(n), adj(n), subtreeSum(n, 0), result(n, 0) {}

    // Function to add edges to the tree
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    // Function to calculate the subtree sum using DFS
    void dfs1(int node, int parent) {
        subtreeSum[node] = 0;  // Initialize the subtree sum for this node

        // Traverse all children
        for (auto &neighbor : adj[node]) {
            int child = neighbor.first;
            int weight = neighbor.second;

            if (child != parent) {
                dfs1(child, node);  // Recurse for child
                subtreeSum[node] += subtreeSum[child] + weight;  // Add child's subtree sum and weight
            }
        }
    }

    // Function to propagate the results to all nodes using DFS
    void dfs2(int node, int parent) {
        if (parent != -1) {
            // The parent's result gives us the sum for this node, so propagate it
            result[node] = result[parent] - subtreeSum[node] + (totalSum - subtreeSum[node]);
        } else {
            // For the root, the result is just its own subtree sum
            result[node] = subtreeSum[node];
        }

        // Traverse all children
        for (auto &neighbor : adj[node]) {
            int child = neighbor.first;
            if (child != parent) {
                dfs2(child, node);  // Propagate the result to the child
            }
        }
    }

    // Function to compute the solution
    void solve() {
        dfs1(0, -1);  // Calculate subtree sums from the root (node 0)
        totalSum = subtreeSum[0];  // Total sum is the sum of the entire tree
        dfs2(0, -1);  // Propagate the results from root to all nodes
    }

    // Function to print the result
    void printResults() {
        for (int i = 0; i < n; ++i) {
            cout << "Node " << i << ": " << result[i] << endl;
        }
    }

private:
    int n;  // Number of nodes in the tree
    vector<vector<pair<int, int>>> adj;  // Adjacency list (child, weight)
    vector<int> subtreeSum;  // Stores the sum of each subtree
    vector<int> result;  // Stores the result for each node
    int totalSum;  // Total sum of the entire tree
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------//


/* 
 * Usage : 
 * addPattern : Adds patterns to the trie structure.
 * build : Sets up the fail links via BFS.
 * search : Performs the search and returns the indices of patterns found in the text.
 * Time complexity : O(n + S(Ai))
*/

class AhoCorasick {
public:
    AhoCorasick() { edges.push_back({}); fail.push_back(-1); output.push_back({}); }

    void addPattern(const string& pattern, int idx) {
        int node = 0;
        for (char c : pattern) {
            if (!edges[node].count(c)) {
                edges[node][c] = edges.size();
                edges.push_back({}); fail.push_back(-1); output.push_back({});
            }
            node = edges[node][c];
        }
        output[node].insert(idx);
    }

    void build() {
        queue<int> q;
        for (auto& p : edges[0]) {
            fail[p.second] = 0;
            q.push(p.second);
        }
        while (!q.empty()) {
            int state = q.front(); q.pop();
            for (auto& p : edges[state]) {
                char c = p.first;
                int next = p.second, f = fail[state];
                while (!edges[f].count(c)) f = fail[f];
                fail[next] = edges[f][c];
                output[next].insert(output[fail[next]].begin(), output[fail[next]].end());
                q.push(next);
            }
        }
    }

    vector<int> search(const string& text) {
        vector<int> result(text.size(), -1);
        int node = 0;
        for (int i = 0; i < text.size(); ++i) {
            while (!edges[node].count(text[i])) node = fail[node];
            node = edges[node][text[i]];
            for (int idx : output[node]) result[i] = idx;
        }
        return result;
    }

private:
    vector<unordered_map<char, int>> edges;
    vector<int> fail;
    vector<set<int>> output;
};
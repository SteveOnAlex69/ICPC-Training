// Z-FUNCTION :
class ZFunction {
public:
    // Constructor to initialize the string
    ZFunction(const string& s) : S(s), n(s.length()) {}

    // Function to compute the Z-function for the string
    vector<int> computeZFunction() {
        vector<int> Z(n, 0);
        int L = 0, R = 0;  // Interval [L, R] defines the rightmost matched prefix

        // Iterate over the string and compute the Z values
        for (int i = 1; i < n; ++i) {
            // Case 1: If i is outside the current matched interval [L, R]
            if (i > R) {
                L = R = i;
                // Compare characters starting from i with the prefix
                while (R < n && S[R] == S[R - L]) {
                    R++;
                }
                Z[i] = R - L;
                R--;  // Adjust R after comparison ends
            }
            // Case 2: If i is inside the current matched interval [L, R]
            else {
                int k = i - L;
                // If the substring Z[k] is smaller than the remaining part of the interval
                if (Z[k] < R - i + 1) {
                    Z[i] = Z[k];
                }
                // Otherwise, we need to extend the match further
                else {
                    L = i;
                    while (R < n && S[R] == S[R - L]) {
                        R++;
                    }
                    Z[i] = R - L;
                    R--;  // Adjust R after comparison ends
                }
            }
        }

        return Z;
    }

    // Function to print the Z-function
    void printZFunction() {
        vector<int> Z = computeZFunction();
        cout << "Z-function: ";
        for (int z : Z) {
            cout << z << " ";
        }
        cout << endl;
    }

private:
    string S;  // Input string
    int n;     // Length of the string
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------//
// AHO CORASICK
class AhoCorasick {
public:
    // Constructor
    AhoCorasick() {
        // Initialize the root of the trie
        root = new TrieNode();
    }

    // Destructor to free dynamically allocated memory
    ~AhoCorasick() {
        deleteTrie(root);
    }

    // Add a pattern to the trie
    void addPattern(const string& pattern, int index) {
        TrieNode* node = root;
        for (char c : pattern) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        // Mark the end of the pattern and store its index
        node->output.push_back(index);
    }

    // Build the Aho-Corasick automaton (failure links)
    void build() {
        queue<TrieNode*> q;
        
        // Initialize the root's fail links
        for (auto& p : root->children) {
            p.second->fail = root;
            q.push(p.second);
        }

        // BFS to build the fail links
        while (!q.empty()) {
            TrieNode* current = q.front();
            q.pop();

            // For each child, set the fail link
            for (auto& p : current->children) {
                TrieNode* child = p.second;
                TrieNode* failNode = current->fail;

                // Follow fail links to find the longest suffix match
                while (failNode != nullptr && failNode->children.find(p.first) == failNode->children.end()) {
                    failNode = failNode->fail;
                }

                if (failNode != nullptr) {
                    child->fail = failNode->children[p.first];
                } else {
                    child->fail = root;
                }

                // Add the outputs of the fail node to the current node
                child->output.insert(child->output.end(), child->fail->output.begin(), child->fail->output.end());

                q.push(child);
            }
        }
    }

    // Search the text for all patterns
    void search(const string& text) {
        TrieNode* node = root;

        // Traverse the text and follow the trie and fail links
        for (int i = 0; i < text.length(); ++i) {
            while (node != root && node->children.find(text[i]) == node->children.end()) {
                node = node->fail;  // Follow the fail link
            }

            if (node->children.find(text[i]) != node->children.end()) {
                node = node->children[text[i]];
            }

            // Report all matched patterns (from output list)
            for (int index : node->output) {
                cout << "Pattern " << index << " found at position " << i << endl;
            }
        }
    }

private:
    // Trie Node structure
    struct TrieNode {
        map<char, TrieNode*> children;  // Children nodes (for each character)
        TrieNode* fail = nullptr;  // Failure link
        vector<int> output;  // List of pattern indices that end at this node
    };

    TrieNode* root;  // Root of the Trie

    // Recursively delete the Trie
    void deleteTrie(TrieNode* node) {
        for (auto& p : node->children) {
            deleteTrie(p.second);
        }
        delete node;
    }
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------------//
// SUFFIX ARRAY O(nlog^2)
class SuffixArray {
public:
    // Constructor that accepts the input string
    SuffixArray(const string& s) : s(s), n(s.size()) {
        suffixArray = buildSuffixArray(s);
    }

    // Function to get the suffix array
    const vector<int>& getSuffixArray() const {
        return suffixArray;
    }

    // Function to print the suffix array
    void printSuffixArray() const {
        cout << "Suffix Array: ";
        for (int i : suffixArray) {
            cout << i << " ";
        }
        cout << endl;
    }

private:
    string s;                  // The input string
    int n;                      // Length of the string
    vector<int> suffixArray;   // The suffix array

    // Function to build the suffix array using O(n * (log n)²)
    vector<int> buildSuffixArray(const string& s) {
        int n = s.size();
        vector<int> suffixArray(n), rank(n), tempRank(n), count(max(n, 256), 0);

        // Step 1: Initial ranking based on the first character
        for (int i = 0; i < n; ++i) {
            suffixArray[i] = i;
            rank[i] = s[i];
        }

        // Step 2: Sort suffixes based on the first k characters (k = 1, 2, 4, 8,...)
        for (int k = 1; k < n; k <<= 1) {
            // Step 2a: Counting sort based on the second part of the tuple (rank[i + k])
            fill(count.begin(), count.end(), 0);
            for (int i = 0; i < n; ++i) {
                int nextRank = (suffixArray[i] + k < n) ? rank[suffixArray[i] + k] : -1;
                count[nextRank + 1]++;
            }
            for (int i = 1; i < count.size(); ++i) {
                count[i] += count[i - 1];
            }

            // Step 2b: Counting sort to rank the suffixes based on the first k characters
            for (int i = n - 1; i >= 0; --i) {
                int suffixStart = suffixArray[i];
                int nextRank = (suffixStart + k < n) ? rank[suffixStart + k] : -1;
                tempRank[count[nextRank]++] = suffixStart;
            }

            suffixArray.swap(tempRank);

            // Step 2c: Update the rank array
            tempRank[suffixArray[0]] = 0;
            int currentRank = 0;
            for (int i = 1; i < n; ++i) {
                int prev = suffixArray[i - 1], curr = suffixArray[i];
                if (rank[prev] == rank[curr] && (curr + k < n && prev + k < n && rank[curr + k] == rank[prev + k])) {
                    tempRank[curr] = currentRank;
                } else {
                    tempRank[curr] = ++currentRank;
                }
            }
            rank.swap(tempRank);
        }

        return suffixArray;
    }
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------//
// SUFFIX AUTOMATON
class SuffixAutomaton {
public:
    // Constructor to build suffix automaton from the input string
    SuffixAutomaton(const string& s) : s(s), size(0), last(0) {
        build();
    }

    // Function to print the states of the suffix automaton
    void printStates() const {
        for (int i = 0; i <= size; ++i) {
            cout << "State " << i << ": ";
            for (int j = 0; j < 256; ++j) {
                if (nextState[i][j] != -1) {
                    cout << "(" << (char)j << " -> " << nextState[i][j] << ") ";
                }
            }
            cout << "Suffix Link: " << suffixLink[i] << endl;
        }
    }

private:
    string s;                    // Input string
    int size;                     // The number of states in the automaton
    int last;                     // The last state added (points to the most recent state)
    vector<int> length;          // length[i] = the length of the longest string in state i
    vector<int> suffixLink;      // suffixLink[i] = the state that corresponds to the longest suffix of the string represented by state i
    vector<vector<int>> nextState;  // nextState[i][ch] = the state to go when reading character 'ch' from state i

    // Function to build the suffix automaton
    void build() {
        int n = s.size();
        length.resize(2 * n);
        suffixLink.resize(2 * n, -1);
        nextState.assign(2 * n, vector<int>(256, -1));

        size = 0;
        last = 0;

        for (char c : s) {
            extend(c);
        }
    }

    // Function to extend the automaton with the next character
    void extend(char c) {
        int cur = ++size;  // Create a new state
        length[cur] = length[last] + 1;

        int p = last;
        while (p != -1 && nextState[p][c] == -1) {
            nextState[p][c] = cur;
            p = suffixLink[p];
        }

        if (p == -1) {
            suffixLink[cur] = 0;
        } else {
            int q = nextState[p][c];
            if (length[p] + 1 == length[q]) {
                suffixLink[cur] = q;
            } else {
                int clone = ++size;
                length[clone] = length[p] + 1;
                nextState[clone] = nextState[q];  // Copy transitions of state q
                suffixLink[clone] = suffixLink[q];

                while (p != -1 && nextState[p][c] == q) {
                    nextState[p][c] = clone;
                    p = suffixLink[p];
                }

                suffixLink[q] = suffixLink[cur] = clone;
            }
        }

        last = cur;
    }
};
//-------------------------------------------------------------------------------------------------------------------------------------------------------------//
// PALINDROME TREE
class PalindromeTree {
public:
    PalindromeTree(const string &s) : s(s), n(s.size()) {
        buildPalindromeTree();
    }

    // Function to print all distinct palindromes represented in the tree
    void printPalindromes() const {
        for (int i = 1; i <= size; ++i) {
            cout << "Palindrome: ";
            for (int j = nodes[i].start; j < nodes[i].start + nodes[i].len; ++j) {
                cout << s[j];
            }
            cout << ", Length: " << nodes[i].len << endl;
        }
    }

private:
    string s;                  // The input string
    int n;                      // Length of the string
    int size;                   // The size of the tree (number of nodes)
    vector<int> length;         // Length of the palindrome at each node
    vector<int> link;           // Palindrome link of each node
    vector<int> next[256];      // Transitions for each character
    vector<int> start;          // Starting index of each palindrome
    vector<int> end;            // Ending index of each palindrome

    struct Node {
        int len;                // Length of the palindrome
        int link;               // Suffix link (longest palindromic suffix)
        map<char, int> next;    // Transitions for each character
        int start;              // Starting index of the palindrome in the original string
    };

    vector<Node> nodes;        // The actual palindrome tree nodes

    // Function to build the palindrome tree for the input string
    void buildPalindromeTree() {
        nodes.push_back(Node());  // Dummy node for empty palindrome
        nodes.push_back(Node());  // Dummy node for a palindrome of length -1

        length.push_back(0);
        link.push_back(1);  // The palindrome link of the first real palindrome node is the root of length -1.
        
        start.push_back(-1);  // Empty palindrome node start index
        end.push_back(-1);    // Empty palindrome node end index

        size = 1;             // Initially, we only have 2 nodes, one for empty palindrome and one for length -1 palindrome.

        int last = 1;  // The last added node, initially points to the node for the empty palindrome.

        for (int i = 0; i < n; ++i) {
            char c = s[i];
            int curr = last;

            // Find the largest palindrome that ends with s[i]
            while (true) {
                int left = i - length[curr] - 1;
                if (left >= 0 && s[left] == c) break;
                curr = link[curr];
            }

            // If such a palindrome does not exist, create a new one
            if (next[curr].find(c) == next[curr].end()) {
                int clone = ++size;
                length.push_back(length[curr] + 2);
                start.push_back(i - length[curr] - 1);
                end.push_back(i);

                // Set the palindrome link for the new node
                int currLink = link[curr];
                while (true) {
                    int left = i - length[currLink] - 1;
                    if (left >= 0 && s[left] == c) break;
                    currLink = link[currLink];
                }

                link.push_back(next[currLink][c]);
                next[curr][c] = clone;
            }

            last = next[curr][c];
        }
    }
};

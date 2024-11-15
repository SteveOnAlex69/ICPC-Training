// Trie
class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert a word into the Trie
    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEnd = true;
    }

    // Search for a word in the Trie
    bool search(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return node->isEnd;
    }

    // Check if any word starts with the given prefix
    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        return true;
    }
};

// Lazy Segment Tree.

Fast Segment Tree.
class SegmentTree {
private:
    vector<int> tree;
    int n;

    // Combine function for the desired operation (sum, min, max, etc.)
    int combine(int a, int b) {
        return a + b; // Adjust this for different operations
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(2 * n);

        // Initialize leaves
        for (int i = 0; i < n; ++i) {
            tree[n + i] = arr[i];
        }

        // Build the tree
        for (int i = n - 1; i > 0; --i) {
            tree[i] = combine(tree[2 * i], tree[2 * i + 1]);
        }
    }

    // Point update: arr[idx] = val
    void update(int idx, int val) {
        idx += n; // Move index to the leaf
        tree[idx] = val;
        while (idx > 1) {
            idx /= 2;
            tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
        }
    }

    // Range query: [L, R)
    int query(int L, int R) {
        L += n; // Move to the leaf layer
        R += n;
        int result = 0; // Change this based on the neutral element for your operation (e.g., INT_MAX for min)

        while (L < R) {
            if (L & 1) {
                result = combine(result, tree[L]);
                ++L;
            }
            if (R & 1) {
                --R;
                result = combine(result, tree[R]);
            }
            L /= 2;
            R /= 2;
        }
        return result;
    }
};

// Fast Lazy Segment Tree
// CHT

	/////////////////////////////
struct Line {
    long long m, c; // Line represented as y = mx + c
    Line(long long m = 0, long long c = 0) : m(m), c(c) {}

    // Function to evaluate line y = mx + c at a given x
    long long value(long long x) const {
        return m * x + c;
    }

    // Function to determine the intersection point with another line
    double intersectX(const Line& other) const {
        return static_cast<double>(c - other.c) / (other.m - m);
    }
};

class ConvexHullTrick {
public:
    // Adds a new line to the convex hull
    void addLine(long long m, long long c) {
        Line newLine(m, c);
        // Remove lines that are not needed due to the new line
        while (hull.size() >= 2 && badLine(hull[hull.size() - 2], hull.back(), newLine)) {
            hull.pop_back();
        }
        hull.push_back(newLine);
    }

    // Queries the maximum y-value for a given x
    long long query(long long x) {
        // Maintain a pointer to the current best line
        if (ptr >= hull.size()) ptr = hull.size() - 1;
        while (ptr + 1 < hull.size() && hull[ptr + 1].value(x) > hull[ptr].value(x)) {
            ++ptr;
        }
        return hull[ptr].value(x);
    }

private:
    vector<Line> hull; // Stores the lines of the convex hull
    size_t ptr = 0; // Pointer to the current best line for query

    // Check if the middle line is "bad" (can be removed)
    bool badLine(const Line& l1, const Line& l2, const Line& l3) {
        return (l3.c - l1.c) * (l1.m - l2.m) <= (l2.c - l1.c) * (l1.m - l3.m);
    }
};
/////////////////////
// Lichao Tree
class LiChaoTree {
public:
    struct Node {
        Line line;
        Node *left = nullptr, *right = nullptr;
    };

    LiChaoTree(long long minX, long long maxX) : minX(minX), maxX(maxX) {
        root = new Node();
    }

    void addLine(Line newLine) {
        addLine(root, minX, maxX, newLine);
    }

    long long query(long long x) {
        return query(root, minX, maxX, x);
    }

private:
    Node* root;
    long long minX, maxX;

    void addLine(Node* node, long long l, long long r, Line newLine) {
        long long mid = (l + r) / 2;
        bool leftBetter = newLine.value(l) > node->line.value(l);
        bool midBetter = newLine.value(mid) > node->line.value(mid);

        if (midBetter) swap(node->line, newLine);
        if (l == r) return;

        if (leftBetter != midBetter) {
            if (!node->left) node->left = new Node();
            addLine(node->left, l, mid, newLine);
        } else {
            if (!node->right) node->right = new Node();
            addLine(node->right, mid + 1, r, newLine);
        }
    }

    long long query(Node* node, long long l, long long r, long long x) {
        if (!node) return LLONG_MIN;
        long long mid = (l + r) / 2;
        if (x <= mid) {
            return max(node->line.value(x), query(node->left, l, mid, x));
        } else {
            return max(node->line.value(x), query(node->right, mid + 1, r, x));
        }
    }
};
/////////////////////////////

// Persistent Segment Tree
class PersistentSegmentTree {
private:
    int n;
    vector<Node*> roots; // Store roots of different versions

    // Build initial segment tree
    Node* build(int start, int end) {
        if (start == end) return new Node(0); // Initialize with zero; customize as needed
        int mid = (start + end) / 2;
        return new Node(0, build(start, mid), build(mid + 1, end));
    }

    // Create new version with point update
    Node* update(Node* prev, int start, int end, int idx, int val) {
        if (start == end) return new Node(prev->value + val); // Update node value
        int mid = (start + end) / 2;
        if (idx <= mid)
            return new Node(prev->value + val, update(prev->left, start, mid, idx, val), prev->right);
        else
            return new Node(prev->value + val, prev->left, update(prev->right, mid + 1, end, idx, val));
    }

    // Query for a range [L, R]
    int query(Node* node, int start, int end, int L, int R) {
        if (start > R || end < L) return 0; // Return 0 for sum; adjust for other ops
        if (L <= start && end <= R) return node->value;
        int mid = (start + end) / 2;
        return query(node->left, start, mid, L, R) + query(node->right, mid + 1, end, L, R);
    }

public:
    PersistentSegmentTree(int size) : n(size) {
        roots.push_back(build(0, n - 1)); // Initial version
    }

    // Update tree version by creating a new version
    void update(int idx, int val) {
        roots.push_back(update(roots.back(), 0, n - 1, idx, val));
    }

    // Query a specific version
    int query(int version, int L, int R) {
        return query(roots[version], 0, n - 1, L, R);
    }
};

//Treap
class Treap {
private:
    TreapNode* root = nullptr;

    int getSize(TreapNode* node) {
        return node ? node->size : 0;
    }

    void updateSize(TreapNode* node) {
        if (node) node->size = 1 + getSize(node->left) + getSize(node->right);
    }

    // Split into two treaps with keys <= key and > key
    void split(TreapNode* node, int key, TreapNode*& left, TreapNode*& right) {
        if (!node) {
            left = right = nullptr;
        } else if (key < node->key) {
            split(node->left, key, left, node->left);
            right = node;
        } else {
            split(node->right, key, node->right, right);
            left = node;
        }
        updateSize(node);
    }

    // Merge two treaps
    TreapNode* merge(TreapNode* left, TreapNode* right) {
        if (!left || !right) return left ? left : right;
        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            updateSize(left);
            return left;
        } else {
            right->left = merge(left, right->left);
            updateSize(right);
            return right;
        }
    }

    // Insert a new node
    TreapNode* insert(TreapNode* node, int key) {
        if (!node) return new TreapNode(key);
        if (key == node->key) return node; // Avoid duplicates; can be customized
        if (key < node->key) {
            node->left = insert(node->left, key);
            if (node->left->priority > node->priority) {
                node = rotateRight(node);
            }
        } else {
            node->right = insert(node->right, key);
            if (node->right->priority > node->priority) {
                node = rotateLeft(node);
            }
        }
        updateSize(node);
        return node;
    }

    TreapNode* rotateRight(TreapNode* node) {
        TreapNode* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        updateSize(node);
        updateSize(newRoot);
        return newRoot;
    }

    TreapNode* rotateLeft(TreapNode* node) {
        TreapNode* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        updateSize(node);
        updateSize(newRoot);
        return newRoot;
    }

    // Delete a node with a given key
    TreapNode* erase(TreapNode* node, int key) {
        if (!node) return nullptr;
        if (key == node->key) {
            TreapNode* merged = merge(node->left, node->right);
            delete node;
            return merged;
        } else if (key < node->key) {
            node->left = erase(node->left, key);
        } else {
            node->right = erase(node->right, key);
        }
        updateSize(node);
        return node;
    }

    // In-order traversal (for debugging)
    void inOrder(TreapNode* node) {
        if (!node) return;
        inOrder(node->left);
        cout << node->key << " ";
        inOrder(node->right);
    }

public:
    Treap() {
        srand(time(0));
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void erase(int key) {
        root = erase(root, key);
    }

    void display() {
        inOrder(root);
        cout << endl;
    }
};

// AHO CORASICK
/*
 * Usage :
 * ~AhoCorasick() : Destructor to free dynamically allocated memory.
 * addPattern() : Add a pattern to the trie.
 * build() : Build the Aho-Corasick automaton (failure links).
 * search() : Search the text for all patterns.
 * deleteTrie() : Recursively delete the Trie.
*/

class AhoCorasick {
public:
    AhoCorasick() {
        root = new TrieNode();
    }

    ~AhoCorasick() {
        deleteTrie(root);
    }

    void addPattern(const string& pattern, int index) {
        TrieNode* node = root;
        for (char c : pattern) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->output.push_back(index);
        return;
    }

    void build() {
        queue<TrieNode*> q;
        
        for (auto& p : root->children) {
            p.second->fail = root;
            q.push(p.second);
        }

        while (!q.empty()) {
            TrieNode* current = q.front();
            q.pop();
            for (auto& p : current->children) {
                TrieNode* child = p.second;
                TrieNode* failNode = current->fail;

                while (failNode != nullptr && failNode->children.find(p.first) == failNode->children.end()) {
                    failNode = failNode->fail;
                }

                if (failNode != nullptr) {
                    child->fail = failNode->children[p.first];
                } else {
                    child->fail = root;
                }

                child->output.insert(child->output.end(), child->fail->output.begin(), child->fail->output.end());

                q.push(child);
            }
        }
        return;
    }

    void search(const string& text) {
        TrieNode* node = root;

        for (int i = 0; i < text.length(); ++i) {
            while (node != root && node->children.find(text[i]) == node->children.end()) {
                node = node->fail;
            }

            if (node->children.find(text[i]) != node->children.end()) {
                node = node->children[text[i]];
            }

            for (int index : node->output) {
                cout << "Pattern " << index << " found at position " << i << endl;
            }
        }
        return;
    }

private:
    struct TrieNode {
        map<char, TrieNode*> children;
        TrieNode* fail = nullptr;
        vector<int> output;
    };

    TrieNode* root;

    void deleteTrie(TrieNode* node) {
        for (auto& p : node->children) {
            deleteTrie(p.second);
        }
        delete node;
        return;
    }
};
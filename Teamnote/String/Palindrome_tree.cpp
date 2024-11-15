// PALINDROME TREE
/* 
 * Usage : 
 * printPalindromes() : Function to print all distinct palindromes represented in the tree.
 * buildPalindromeTree() : Function to build the palindrome tree for the input string.
*/

class PalindromeTree {
public:
    PalindromeTree(const string &s) : s(s), n(s.size()) {
        buildPalindromeTree();
    }

    void printPalindromes() const {
        for (int i = 1; i <= size; ++i) {
            cout << "Palindrome: ";
            for (int j = nodes[i].start; j < nodes[i].start + nodes[i].len; ++j) {
                cout << s[j];
            }
            cout << ", Length: " << nodes[i].len << endl;
        }
        return;
    }

private:
    string s;                 
    int n;                      
    int size;                   
    vector<int> length;        
    vector<int> link;          
    vector<int> next[256];     
    vector<int> start;          
    vector<int> end;           

    struct Node {
        int len;             
        int link;            
        map<char, int> next;   
        int start;             
    };

    vector<Node> nodes;        

    void buildPalindromeTree() {
        nodes.push_back(Node());  
        nodes.push_back(Node()); 

        length.push_back(0);
        link.push_back(1); 
        
        start.push_back(-1);  
        end.push_back(-1);   

        size = 1;            

        int last = 1;  

        for (int i = 0; i < n; ++i) {
            char c = s[i];
            int curr = last;

            while (true) {
                int left = i - length[curr] - 1;
                if (left >= 0 && s[left] == c) break;
                curr = link[curr];
            }

            if (next[curr].find(c) == next[curr].end()) {
                int clone = ++size;
                length.push_back(length[curr] + 2);
                start.push_back(i - length[curr] - 1);
                end.push_back(i);

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
        return;
    }
};
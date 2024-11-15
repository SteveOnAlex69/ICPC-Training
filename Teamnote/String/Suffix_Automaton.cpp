// SUFFIX AUTOMATON
/*
 * Usage : 
 * printStates() : Function to print the states of the suffix automaton.
 * build() : Function to build the suffix automaton.
 * extend() : Function to extend the automaton with the next character.
*/

class SuffixAutomaton {
public:
    SuffixAutomaton(const string& s) : s(s), size(0), last(0) {
        build();
    }

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
        return;
    }

private:
    string s;          
    int size;                
    int last;            
    vector<int> length;
    vector<int> suffixLink;   
    vector<vector<int>> nextState;  

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
        return;
    }

    void extend(char c) {
        int cur = ++size; 
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
                nextState[clone] = nextState[q]; 
                suffixLink[clone] = suffixLink[q];

                while (p != -1 && nextState[p][c] == q) {
                    nextState[p][c] = clone;
                    p = suffixLink[p];
                }

                suffixLink[q] = suffixLink[cur] = clone;
            }
        }
        last = cur;
        return;
    }
};
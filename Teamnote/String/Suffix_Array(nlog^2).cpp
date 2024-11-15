// SUFFIX ARRAY O(nlog^2)
/* 
 * Usage : 
 * buildSuffixArray() : Function to build the suffix array using O(n * (log n)²).
 * getSuffixArray() : Function to get the suffix array.
 * printSuffixArray : Function to print the suffix array
*/

class SuffixArray {
public:
    SuffixArray(const string& s) : s(s), n(s.size()) {
        suffixArray = buildSuffixArray(s);
    }

    const vector<int>& getSuffixArray() const {
        return suffixArray;
    }

    void printSuffixArray() const {
        cout << "Suffix Array: ";
        for (int i : suffixArray) {
            cout << i << " ";
        }
        cout << endl;
        return;
    }

private:
    string s;     
    int n;               
    vector<int> suffixArray; 

    vector<int> buildSuffixArray(const string& s) {
        int n = s.size();
        vector<int> suffixArray(n), rank(n), tempRank(n), count(max(n, 256), 0);

        for (int i = 0; i < n; ++i) {
            suffixArray[i] = i;
            rank[i] = s[i];
        }

        for (int k = 1; k < n; k <<= 1) {
            fill(count.begin(), count.end(), 0);
            for (int i = 0; i < n; ++i) {
                int nextRank = (suffixArray[i] + k < n) ? rank[suffixArray[i] + k] : -1;
                count[nextRank + 1]++;
            }
            for (int i = 1; i < count.size(); ++i) {
                count[i] += count[i - 1];
            }

            for (int i = n - 1; i >= 0; --i) {
                int suffixStart = suffixArray[i];
                int nextRank = (suffixStart + k < n) ? rank[suffixStart + k] : -1;
                tempRank[count[nextRank]++] = suffixStart;
            }

            suffixArray.swap(tempRank);

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
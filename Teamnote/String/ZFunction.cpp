// Z-FUNCTION :
/*
 * Usage : 
 * computeZFunction() : Function to compute the Z-function for the string
 * printZFunction() : Print Z Function.
*/

class ZFunction {
public:
    ZFunction(const string& s) : S(s), n(s.length()) {}

    vector<int> computeZFunction() {
        vector<int> Z(n, 0);
        int L = 0, R = 0; 

        for (int i = 1; i < n; ++i) {
            if (i > R) {
                L = R = i;
                while (R < n && S[R] == S[R - L]) {
                    R++;
                }
                Z[i] = R - L;
            }
            else {
                int k = i - L;
                if (Z[k] < R - i + 1) {
                    Z[i] = Z[k];
                }
                else {
                    L = i;
                    while (R < n && S[R] == S[R - L]) {
                        R++;
                    }
                    Z[i] = R - L;
                }
            }
        }

        return Z;
    }

    void printZFunction() {
        vector<int> Z = computeZFunction();
        cout << "Z-function: ";
        for (int z : Z) {
            cout << z << " ";
        }
        cout << endl;
    }
private:
    string S;
    int n;
};
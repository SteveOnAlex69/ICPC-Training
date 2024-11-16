
/* WE HAVE TWO VECTOR INT AND HOW TO COMPUTE IT !!! */

class BigInt {
public:
    vector<int> digits; // Store digits in reverse order

    BigInt(long long n = 0) { 
        while (n) { 
            digits.push_back(n % 10); 
            n /= 10; 
        }
    }

    void print() {
        for (int i = digits.size() - 1; i >= 0; --i) 
            cout << digits[i];
        cout << endl;
    }

    BigInt operator + (const BigInt& b) {
        BigInt res;
        int carry = 0, i = 0;
        while (i < digits.size() || i < b.digits.size() || carry) {
            int sum = carry;
            if (i < digits.size()) sum += digits[i];
            if (i < b.digits.size()) sum += b.digits[i];
            res.digits.push_back(sum % 10);
            carry = sum / 10;
            ++i;
        }
        return res;
    }

    BigInt operator * (const BigInt& b) {
        BigInt res;
        res.digits.resize(digits.size() + b.digits.size(), 0);
        for (int i = 0; i < digits.size(); ++i)
            for (int j = 0; j < b.digits.size(); ++j)
                res.digits[i + j] += digits[i] * b.digits[j];
        for (int i = 0; i < res.digits.size(); ++i) {
            if (res.digits[i] >= 10) {
                res.digits[i + 1] += res.digits[i] / 10;
                res.digits[i] %= 10;
            }
        }
        while (res.digits.size() > 1 && res.digits.back() == 0)
            res.digits.pop_back();
        return res;
    }
};
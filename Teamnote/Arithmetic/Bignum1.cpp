
/* WE HAVE TWO VECTOR INT AND HOW TO COMPUTE IT !!! */

class BigNumber {
public:
    BigNumber(std::string val) : value(std::move(val)) {
        value = stripLeadingZeros(value);
    }

    BigNumber operator+(const BigNumber& other) const {
        std::string x = value, y = other.value, result;
        std::reverse(x.begin(), x.end());
        std::reverse(y.begin(), y.end());

        int carry = 0;
        size_t max_len = std::max(x.size(), y.size());
        for (size_t i = 0; i < max_len || carry; ++i) {
            int digitX = (i < x.size()) ? x[i] - '0' : 0;
            int digitY = (i < y.size()) ? y[i] - '0' : 0;
            int sum = digitX + digitY + carry;
            result.push_back((sum % 10) + '0');
            carry = sum / 10;
        }

        std::reverse(result.begin(), result.end());
        return BigNumber(stripLeadingZeros(result));
    }

    BigNumber operator-(const BigNumber& other) const {
        std::string x = value, y = other.value;
        if (x.size() < y.size() || (x.size() == y.size() && x < y)) 
            throw std::invalid_argument("Negative result not supported.");
        
        std::reverse(x.begin(), x.end());
        std::reverse(y.begin(), y.end());
        
        std::string result;
        int borrow = 0;
        for (size_t i = 0; i < x.size(); ++i) {
            int digitX = x[i] - '0', digitY = (i < y.size()) ? y[i] - '0' : 0;
            int diff = digitX - digitY - borrow;
            if (diff < 0) { diff += 10; borrow = 1; }
            else borrow = 0;
            result.push_back(diff + '0');
        }
        
        std::reverse(result.begin(), result.end());
        return BigNumber(stripLeadingZeros(result));
    }

    BigNumber operator*(const BigNumber& other) const {
        std::string x = value, y = other.value;
        size_t m = x.size(), n = y.size();
        std::vector<int> result(m + n, 0);

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                result[i + j] += (x[i] - '0') * (y[j] - '0');
                result[i + j + 1] += result[i + j] / 10;
                result[i + j] %= 10;
            }
        }

        std::string resultStr;
        for (int i = result.size() - 1; i >= 0; --i)
            if (!(resultStr.empty() && result[i] == 0)) resultStr.push_back(result[i] + '0');
        
        return resultStr.empty() ? BigNumber("0") : BigNumber(resultStr);
    }

    BigNumber operator/(const BigNumber& other) const {
        if (other.value == "0") throw std::invalid_argument("Division by zero.");
        
        std::string x = value, y = other.value, result;
        std::string current;
        
        for (char c : x) {
            current += c;
            int quotient = 0;
            while (compare(current, y) >= 0) {
                current = subtractStrings(current, y);
                ++quotient;
            }
            result += std::to_string(quotient);
        }

        return BigNumber(stripLeadingZeros(result.empty() ? "0" : result));
    }

    friend std::ostream& operator<<(std::ostream& os, const BigNumber& num) {
        os << num.value;
        return os;
    }

private:
    std::string value;

    static std::string stripLeadingZeros(const std::string& str) {
        size_t first_non_zero = str.find_first_not_of('0');
        return first_non_zero == std::string::npos ? "0" : str.substr(first_non_zero);
    }

    int compare(const std::string& x, const std::string& y) const {
        if (x.size() > y.size()) return 1;
        if (x.size() < y.size()) return -1;
        return x.compare(y);
    }

    std::string subtractStrings(std::string x, const std::string& y) const {
        int borrow = 0;
        std::string result;
        for (size_t i = 0; i < x.size(); ++i) {
            int digitX = x[i] - '0', digitY = (i < y.size()) ? y[i] - '0' : 0;
            int diff = digitX - digitY - borrow;
            if (diff < 0) { diff += 10; borrow = 1; }
            else borrow = 0;
            result.push_back(diff + '0');
        }
        return stripLeadingZeros(result);
    }
};

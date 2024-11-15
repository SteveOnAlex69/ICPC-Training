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
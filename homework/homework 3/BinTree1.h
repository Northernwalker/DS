//����������ṹ��
struct BinNode {
    char ch;
    int freq;
    BinNode* left;
    BinNode* right;
    BinNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};
//����Ƚ������������ȶ���
struct Compare {
    bool operator()(BinNode* a, BinNode* b) {
        return a->freq > b->freq;
    }
};
//�����������
class BinTree {
public:
    BinTree() : root(nullptr) {}
    ~BinTree() { clear(); }
    void clear() { clear(root); }
    void insert(char ch, int freq) { insert(root, ch, freq); }
    BinNode* getRoot() const { return root; }
private:
    BinNode* root;
    void clear(BinNode* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
    void insert(BinNode*& node, char ch, int freq) {
        if (!node) {
            node = new BinNode(ch, freq);
            return;
        }
        if (freq < node->freq) {
            insert(node->left, ch, freq);
        }
        else {
            insert(node->right, ch, freq);
        }
    }
}; 

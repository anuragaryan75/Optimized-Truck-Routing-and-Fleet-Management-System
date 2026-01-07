class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
    }
};

class Trie {
public:

    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }

    bool search(string word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        return current->isEndOfWord;
    }

    vector<string> startsWith(string prefix) {
        TrieNode* current = root;
        vector<string> result;
        // Traverse to the node corresponding to the prefix
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                // Prefix not found, return empty vector
                return result;
            }
            current = current->children[c];
        }
        // Perform DFS to collect all words starting with the prefix
        startsWithDFS(current, prefix, result);

        return result;
    }

    void startsWithDFS(TrieNode* node, string prefix, vector<string>& result) {
        // If current node is end of word, add it to result
        if (node->isEndOfWord) {
            result.push_back(prefix);
        }
        // Recursively search through children
        for (auto& child : node->children) {
            startsWithDFS(child.second, prefix + child.first, result);
        }   
    }

};

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

class TrieNode_SortedArray
{
public:
    vector<pair<wchar_t, TrieNode_SortedArray *>> children;
    bool isEnd = false;

    int checkChild(wchar_t c)
    {
        int left = 0, right = children.size() - 1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (children[mid].first == c)
                return mid;
            else if (children[mid].first < c)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1;
    }

    int findPos(wchar_t c)
    {
        int left = 0, right = children.size();
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (children[mid].first < c)
                left = mid + 1;
            else
                right = mid;
        }
        return left;
    }

    TrieNode_SortedArray *searching(wchar_t c)
    {
        int index = checkChild(c);
        return (index != -1) ? children[index].second : nullptr;
    }

    TrieNode_SortedArray *inserting(wchar_t c)
    {
        int index = checkChild(c);
        if (index != -1)
            return children[index].second;

        int insertPos = findPos(c);
        TrieNode_SortedArray *newNode = new TrieNode_SortedArray();
        children.insert(children.begin() + insertPos, {c, newNode});
        return newNode;
    }
};

class TrieSortedArray
{
private:
    TrieNode_SortedArray *root = new TrieNode_SortedArray();

    void print(TrieNode_SortedArray *node, wstring prefix, int dep)
    {
        for (auto &[ch, child] : node->children)
        {
            wstring indent(dep * 2, L' ');
            wcout << indent << L"|-- " << ch;
            if (child->isEnd)
                wcout << L" (end)";
            wcout << endl;
            print(child, prefix + ch, dep + 1);
        }
    }
    bool del(TrieNode_SortedArray *node, const wstring &word, size_t dep)
    {
        if (!node)
            return false;
        if (dep == word.size())
        {
            if (!node->isEnd)
                return false;
            node->isEnd = false;
            return node->children.empty();
        }

        wchar_t c = word[dep];
        int index = node->checkChild(c);
        if (index == -1)
            return false;

        TrieNode_SortedArray *child = node->children[index].second;
        bool need = del(child, word, dep + 1);
        if (need)
        {
            delete child;
            node->children.erase(node->children.begin() + index);
            return node->children.empty() && !node->isEnd;
        }
        return false;
    }

    void getPrefix(TrieNode_SortedArray *node, wstring prefix, vector<wstring> &results)
    {
        if (node->isEnd)
            results.push_back(prefix);

        for (auto &[ch, child] : node->children)
        {
            getPrefix(child, prefix + ch, results);
        }
    }

public:
    void insert(const wstring &word)
    {
        TrieNode_SortedArray *node = root;
        for (wchar_t c : word)
        {
            node = node->inserting(c);
        }
        node->isEnd = true;
    }

    bool search(const wstring &word)
    {
        TrieNode_SortedArray *node = root;
        for (wchar_t c : word)
        {
            node = node->searching(c);
            if (!node)
                return false;
        }
        return node->isEnd;
    }

    bool deletion(const wstring &word)
    {
        return del(root, word, 0);
    }

    vector<wstring> startsWith(const wstring &prefix)
    {
        vector<wstring> results;
        TrieNode_SortedArray *node = root;

        for (wchar_t c : prefix)
        {
            node = node->searching(c);
            if (!node)
                return results;
        }

        getPrefix(node, prefix, results);
        return results;
    }

    void printTrie()
    {
        wcout << L"Trie (Sorted Array - Binary Search):\n";
        print(root, L"", 0);
    }

    void searchTime(const wstring &word)
    {
        auto start = chrono::high_resolution_clock::now();
        bool found = search(word);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;

        wcout << L"Sorted Array - Word '" << word << L"': " << (found ? L"Found" : L"Not Found") << L" (Time: " << duration.count() << L" s)\n";
    }
};

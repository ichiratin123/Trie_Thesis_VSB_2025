#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <locale>
#include <codecvt>

using namespace std;

class TrieNode_NonSortedArray
{
public:
    vector<pair<wchar_t, TrieNode_NonSortedArray *>> children;
    bool isEnd = false;

    TrieNode_NonSortedArray *searching(wchar_t c)
    {
        for (auto &[ch, child] : children)
        {
            if (ch == c)
                return child;
        }
        return nullptr;
    }

    TrieNode_NonSortedArray *inserting(wchar_t c)
    {
        for (auto &[ch, child] : children)
        {
            if (ch == c)
                return child;
        }
        TrieNode_NonSortedArray *newNode = new TrieNode_NonSortedArray();
        children.push_back({c, newNode});
        return newNode;
    }
};

class TrieUnsortedArray
{
private:
    TrieNode_NonSortedArray *root = new TrieNode_NonSortedArray();

    void print(TrieNode_NonSortedArray *node, wstring prefix, int dep)
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

    void getPrefix(TrieNode_NonSortedArray *node, wstring prefix, vector<wstring> &results)
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
        TrieNode_NonSortedArray *node = root;
        for (wchar_t c : word)
        {
            node = node->inserting(c);
        }
        node->isEnd = true;
    }

    bool search(const wstring &word)
    {
        TrieNode_NonSortedArray *node = root;
        for (wchar_t c : word)
        {
            node = node->searching(c);
            if (!node)
                return false;
        }
        return node->isEnd;
    }

    bool del(TrieNode_NonSortedArray *node, const wstring &word, size_t dep)
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
        for (auto it = node->children.begin(); it != node->children.end(); ++it)
        {
            if (it->first == c)
            {
                bool need = del(it->second, word, dep + 1);
                if (need)
                {
                    delete it->second;
                    node->children.erase(it);
                    return node->children.empty() && !node->isEnd;
                }
                return false;
            }
        }
        return false;
    }

    void deletion(const wstring &word)
    {
        del(root, word, 0);
    }

    vector<wstring> startsWith(const wstring &prefix)
    {
        vector<wstring> results;
        TrieNode_NonSortedArray *node = root;

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
        wcout << L"Trie (Non sorted Array):\n";
        print(root, L"", 0);
    }

    void searchTime(const wstring &word)
    {
        auto start = chrono::high_resolution_clock::now();
        bool found = search(word);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        wcout << L"non sorted Array - Word '" << word << L"': " << (found ? L"Found" : L"Not Found") << L" (Time: " << duration.count() << L" s)\n";
    }
};

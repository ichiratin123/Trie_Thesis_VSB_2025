#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

class TrieNode_Compressed
{
public:
    vector<pair<wchar_t, pair<wstring, TrieNode_Compressed *>>> children;
    bool isEnd = false;
};

class SortedCompressedTrie
{
private:
    TrieNode_Compressed *root;

    TrieNode_Compressed *checkChild(TrieNode_Compressed *node, wchar_t c, wstring &label)
    {
        int left = 0, right = node->children.size() - 1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (node->children[mid].first == c)
            {
                label = node->children[mid].second.first;
                return node->children[mid].second.second;
            }
            else if (node->children[mid].first < c)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return nullptr;
    }

    int findPos(TrieNode_Compressed *node, wchar_t c)
    {
        int left = 0, right = node->children.size();
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (node->children[mid].first < c)
                left = mid + 1;
            else
                right = mid;
        }
        return left;
    }

    void inserting(TrieNode_Compressed *node, wchar_t c, const wstring &label, TrieNode_Compressed *child)
    {
        size_t insertPos = findPos(node, c);
        if (insertPos < node->children.size() && node->children[insertPos].first == c)
        {
            node->children[insertPos].second = {label, child};
        }
        else
        {
            node->children.insert(node->children.begin() + insertPos, {c, {label, child}});
        }
    }

    void print(TrieNode_Compressed *node, wstring prefix)
    {
        for (auto &[c, pairData] : node->children)
        {
            wcout << prefix << L"|-- \"" << pairData.first << L"\"";
            if (pairData.second->isEnd)
                wcout << L" (end)";
            wcout << endl;
            print(pairData.second, prefix + L"  ");
        }
    }

public:
    SortedCompressedTrie()
    {
        root = new TrieNode_Compressed();
    }

    void insert(const wstring &word)
    {
        TrieNode_Compressed *node = root;
        size_t i = 0;

        while (i < word.length())
        {
            wchar_t c = word[i];
            wstring label;
            TrieNode_Compressed *child = checkChild(node, c, label);

            if (!child)
            {
                inserting(node, c, word.substr(i), new TrieNode_Compressed{{}, true});
                return;
            }

            size_t j = 0;
            while (j < label.size() && i < word.size() && label[j] == word[i])
            {
                ++j;
                ++i;
            }

            if (j == label.size())
            {
                node = child;
            }
            else
            {
                wstring remainLabel = label.substr(j);
                wstring remainWord = word.substr(i);

                TrieNode_Compressed *newChild = new TrieNode_Compressed();
                inserting(newChild, remainLabel[0], remainLabel, child);

                if (!remainWord.empty())
                {
                    inserting(newChild, remainWord[0], remainWord, new TrieNode_Compressed{{}, true});
                }
                else
                {
                    newChild->isEnd = true;
                }
                inserting(node, c, label.substr(0, j), newChild);
                return;
            }
        }
        node->isEnd = true;
    }

    bool search(const wstring &word)
    {
        TrieNode_Compressed *node = root;
        size_t i = 0;

        while (i < word.length())
        {
            wchar_t c = word[i];
            wstring label;
            TrieNode_Compressed *child = checkChild(node, c, label);

            if (!child)
                return false;

            if (word.compare(i, label.size(), label) != 0)
                return false;

            i += label.size();
            node = child;
        }
        return node->isEnd;
    }

    bool del(TrieNode_Compressed *node, const wstring &word, size_t i)
    {
        if (!node || i >= word.size())
            return false;

        wchar_t c = word[i];
        int left = 0, right = node->children.size() - 1;
        int foundIndex = -1;

        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (node->children[mid].first == c)
            {
                foundIndex = mid;
                break;
            }
            else if (node->children[mid].first < c)
                left = mid + 1;
            else
                right = mid - 1;
        }

        if (foundIndex == -1)
            return false;

        wstring &label = node->children[foundIndex].second.first;
        TrieNode_Compressed *child = node->children[foundIndex].second.second;

        size_t j = 0;
        while (j < label.size() && i + j < word.size() && label[j] == word[i + j])
        {
            ++j;
        }

        if (j < label.size() || i + j > word.size())
            return false;
        if (i + j == word.size())
        {
            if (!child->isEnd)
                return false;

            child->isEnd = false;
            if (child->children.empty())
            {
                delete child;
                node->children.erase(node->children.begin() + foundIndex);
                return node->children.empty() && !node->isEnd;
            }
            return false;
        }
        bool need = del(child, word, i + j);
        if (need)
        {
            delete child;
            node->children.erase(node->children.begin() + foundIndex);
            return node->children.empty() && !node->isEnd;
        }

        return false;
    }

    void deletion(const wstring &word)
    {
        del(root, word, 0);
    }

    void printTrie()
    {
        wcout << L"Sorted Compressed Trie:\n";
        print(root, L"");
    }

    void searchTime(const wstring &word)
    {
        auto start = chrono::high_resolution_clock::now();
        bool found = search(word);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;

        wcout << L"Sorted Compressed Trie - Word '" << word << L"': " << (found ? L"Found" : L"Not Found")
              << L" (Time: " << duration.count() << L" s)\n";
    }
};

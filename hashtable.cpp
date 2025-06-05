#include <iostream>
#include <string>
#include <chrono>
#include <vector>
using namespace std;

class TrieNode_HashTable;
class HashTable
{
public:
    wchar_t key;
    TrieNode_HashTable *child;
    bool used = false;
};

class TrieNode_HashTable
{
public:
    HashTable *table;
    int capacity;
    int count;
    bool isEnd;

    TrieNode_HashTable(int cap = 2) : capacity(cap), count(0), isEnd(false)
    {
        table = new HashTable[capacity];
    }

    int hash(wchar_t c)
    {
        return ((c * 2654435761u) >> 5) % capacity; // Knuth's multiplicative method
    }

    void reSet(wchar_t c, TrieNode_HashTable *child)
    {
        int idx = hash(c);
        while (table[idx].used)
        {
            idx = (idx + 1) % capacity;
        }
        table[idx] = {c, child, true};
        count++;
    }

    void resize()
    {
        int oldCap = capacity;
        HashTable *oldTable = table;

        capacity *= 2;
        table = new HashTable[capacity];
        count = 0;

        for (int i = 0; i < oldCap; ++i)
        {
            if (oldTable[i].used)
            {
                reSet(oldTable[i].key, oldTable[i].child);
            }
        }
        delete[] oldTable;
    }

    TrieNode_HashTable *get(wchar_t c)
    {
        int idx = hash(c);
        int start = idx;
        while (table[idx].used)
        {
            if (table[idx].key == c)
                return table[idx].child;
            idx = (idx + 1) % capacity;
            if (idx == start)
                break;
        }
        return nullptr;
    }

    void set(wchar_t c, TrieNode_HashTable *child)
    {
        if (count > capacity * 0.7) // load factor setting 70%
            resize();
        int idx = hash(c);
        while (table[idx].used)
        {
            if (table[idx].key == c)
                return;
            idx = (idx + 1) % capacity;
        }
        table[idx] = {c, child, true};
        count++;
    }

    bool remove(wchar_t c)
    {
        int idx = hash(c);
        int start = idx;
        while (table[idx].used)
        {
            if (table[idx].key == c)
            {
                delete table[idx].child;
                table[idx] = {L'\0', nullptr, false};
                count--;
                return true;
            }
            idx = (idx + 1) % capacity;
            if (idx == start)
                break;
        }
        return false;
    }

    bool isEmpty()
    {
        for (int i = 0; i < capacity; ++i)
        {
            if (table[i].used)
                return false;
        }
        return true;
    }
};

class TrieHashTable
{
private:
    TrieNode_HashTable *root = new TrieNode_HashTable();

    bool del(TrieNode_HashTable *node, const wstring &word, size_t depth)
    {
        if (!node)
            return false;

        if (depth == word.length())
        {
            if (!node->isEnd)
                return false;
            node->isEnd = false;
            return node->isEmpty();
        }

        wchar_t c = word[depth];
        TrieNode_HashTable *child = node->get(c);
        if (!child)
            return false;
        bool need = del(child, word, depth + 1);
        if (need)
        {
            node->remove(c);
            return !node->isEnd && node->isEmpty();
        }
        return false;
    }

    void print(TrieNode_HashTable *node, wstring prefix, size_t dep)
    {
        for (int i = 0; i < node->capacity; ++i)
        {
            if (node->table[i].used)
            {
                wchar_t c = node->table[i].key;
                TrieNode_HashTable *child = node->table[i].child;
                wstring indent(dep * 2, L' ');
                wcout << indent << L"|-- " << c;
                if (child->isEnd)
                    wcout << L" (end)";
                wcout << endl;
                print(child, prefix + c, dep + 1);
            }
        }
    }
    void getPrefix(TrieNode_HashTable *node, wstring prefix, vector<wstring> &results)
    {
        if (node->isEnd)
            results.push_back(prefix);

        for (int i = 0; i < node->capacity; ++i)
        {
            if (node->table[i].used)
            {
                wchar_t c = node->table[i].key;
                TrieNode_HashTable *child = node->table[i].child;
                getPrefix(child, prefix + c, results);
            }
        }
    }

public:
    void insert(const wstring &word)
    {
        TrieNode_HashTable *node = root;
        for (wchar_t c : word)
        {
            TrieNode_HashTable *next = node->get(c);
            if (!next)
            {
                next = new TrieNode_HashTable();
                node->set(c, next);
            }
            node = next;
        }
        node->isEnd = true;
    }

    bool search(const wstring &word)
    {
        TrieNode_HashTable *node = root;
        for (wchar_t c : word)
        {
            node = node->get(c);
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
        TrieNode_HashTable *node = root;

        for (wchar_t c : prefix)
        {
            node = node->get(c);
            if (!node)
                return results;
        }

        getPrefix(node, prefix, results);
        return results;
    }

    void printTrie()
    {
        wcout << L"Trie structure:\n";
        print(root, L"", 0);
    }

    void searchTime(const wstring &word)
    {
        auto start = chrono::high_resolution_clock::now();
        bool found = search(word);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;

        wcout << L"hash table - Word '" << word << L"': " << (found ? L"Found" : L"Not Found") << L" (Time: " << duration.count() << L" s)\n";
    }
};

#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

class SequentialArray
{
private:
    vector<wstring> wordList;

public:
    void insert(const wstring &word)
    {
        wordList.push_back(word);
    }

    bool search(const wstring &word) const
    {
        for (const auto &w : wordList)
        {
            if (w == word)
                return true;
        }
        return false;
    }

    bool deletion(const wstring &word)
    {
        for (auto it = wordList.begin(); it != wordList.end(); ++it)
        {
            if (*it == word)
            {
                wordList.erase(it);
                return true;
            }
        }
        return false;
    }

    vector<wstring> startsWith(const wstring &prefix) const
    {
        vector<wstring> results;

        for (const auto &word : wordList)
        {
            if (word.length() < prefix.length())
                continue;

            bool match = true;
            for (size_t i = 0; i < prefix.length(); ++i)
            {
                if (word[i] != prefix[i])
                {
                    match = false;
                    break;
                }
            }

            if (match)
                results.push_back(word);
        }

        return results;
    }

    void searchTime(const wstring &word)
    {
        auto start = chrono::high_resolution_clock::now();
        bool found = search(word);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;

        wcout << L"sequential array - Word '" << word << L"': " << (found ? L"Found" : L"Not Found") << L" (Time: " << duration.count() << L" s)\n";
    }

    void getSize()
    {
        size_t a = wordList.size();
        wcout << L"Size of Sequential Array: " << a << " \n";
    }
};

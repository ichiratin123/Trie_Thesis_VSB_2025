#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <locale>
#include <codecvt>
#include <iomanip>
#include <random>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <psapi.h>

#include "nonsortedTrie.cpp"
#include "sortedTrie.cpp"
#include "hashtable.cpp"
#include "sequentialArray.cpp"
#include "sortedCompressed.cpp"
#include "hashQuadratic.cpp"

using namespace std;

double getMemory()
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc)))
    {
        SIZE_T mem = pmc.WorkingSetSize;
        return static_cast<double>(mem) / 1024.0 / 1024.0;
    }
    return -1.0;
}

int wmain(int argc, wchar_t *argv[])
{
    _setmode(_fileno(stdout), _O_U8TEXT);

    TrieUnsortedArray trie1;
    TrieSortedArray trie2;
    TrieHashTable trie3;
    SequentialArray sArray;
    SortedCompressedTrie ct;
    wstring word;
    TrieHashTable2 test;
    wcout << fixed << setprecision(10);

    if (argc < 2)
    {
        wcout << L"Usage: trieapp <data> <command> <word/number>\n";
        wcout << L"EX:\ntrieapp data/test.txt -s hello\n";
        wcout << L"trieapp data/test.txt -d hello\n";
        wcout << L"trieapp data/test.txt -p 1\n";
        wcout << L"1. unsorted trie\n";
        wcout << L"2. sorted trie\n";
        wcout << L"3. hash table Trie\n";
        return 1;
    }

    const wchar_t *data = argv[1];

    //-----------------------------------------------------------------------------------Insert file

    wifstream file1(argv[1]);
    file1.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    if (!file1)
    {
        wcout << L"File error: " << argv[1] << endl;
        return 1;
    }
    double x = getMemory();
    auto start1 = chrono::high_resolution_clock::now();
    while (getline(file1, word))
    {
        trie1.insert(word);
    }
    auto end1 = chrono::high_resolution_clock::now();
    file1.close();
    chrono::duration<double> insert1 = end1 - start1;
    wcout << "\nInsert time of NonSorted Array Trie: " << insert1.count() << " s";
    double a = getMemory();
    wcout << "\nInsert memory of NonSorted Array Trie: " << a - x << " MB \n";

    wifstream file2(argv[1]);
    file2.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    if (!file2)
    {
        wcout << L"File error: " << argv[1] << endl;
        return 1;
    }
    double y = getMemory();
    auto start2 = chrono::high_resolution_clock::now();
    while (getline(file2, word))
    {

        trie2.insert(word);
    }
    auto end2 = chrono::high_resolution_clock::now();
    file2.close();

    chrono::duration<double> insert2 = end2 - start2;
    wcout << "\nInsert time of sorted array binary Trie: " << insert2.count() << " s";
    double b = getMemory();
    wcout << "\nInsert memory of sorted array binary Trie: " << b - y << " MB\n";

    wifstream file3(argv[1]);
    file3.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    if (!file3)
    {
        wcout << L"File error: " << argv[1] << endl;
        return 1;
    }
    double z = getMemory();
    auto start3 = chrono::high_resolution_clock::now();
    while (getline(file3, word))
    {
        trie3.insert(word);
    }
    auto end3 = chrono::high_resolution_clock::now();
    file3.close();
    chrono::duration<double> insert3 = end3 - start3;
    wcout << "\nInsert time of hash table Trie: " << insert3.count() << " s";
    double c = getMemory();
    wcout << "\nInsert memory of hash table Trie: " << c - z << " MB\n";

    wifstream file4(argv[1]);
    file4.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    if (!file4)
    {
        wcout << L"File error: " << argv[1] << endl;
        return 1;
    }
    double u = getMemory();
    auto start4 = chrono::high_resolution_clock::now();
    while (getline(file4, word))
    {
        sArray.insert(word);
    }
    auto end4 = chrono::high_resolution_clock::now();
    file4.close();
    chrono::duration<double> insert4 = end4 - start4;
    wcout << "\nInsert time of sequential array: " << insert4.count() << " s";

    double d = getMemory();
    wcout << "\nInsert memory of sequential array: " << d - u << " MB\n";

    wifstream file5(argv[1]);
    file5.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    if (!file5)
    {
        wcout << L"File error: " << argv[1] << endl;
        return 1;
    }
    double q = getMemory();
    auto start5 = chrono::high_resolution_clock::now();
    while (getline(file5, word))
    {
        ct.insert(word);
    }
    auto end5 = chrono::high_resolution_clock::now();
    file5.close();
    chrono::duration<double> insert5 = end5 - start5;
    wcout << "\nInsert time of compressed: " << insert5.count() << " s";

    double e = getMemory();
    wcout << "\nInsert memory of compressed: " << e - q << " MB\n";

    wifstream file6(argv[1]);
    file5.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
    if (!file6)
    {
        wcout << L"File error: " << argv[1] << endl;
        return 1;
    }
    double i = getMemory();
    auto start6 = chrono::high_resolution_clock::now();
    while (getline(file6, word))
    {
        test.insert(word);
    }
    auto end6 = chrono::high_resolution_clock::now();
    file6.close();
    chrono::duration<double> insert6 = end6 - start6;
    wcout << "\nInsert time of hash quadratic: " << insert6.count() << " s";

    double f = getMemory();
    wcout << "\nInsert memory of hash quadratic: " << f - i << " MB\n";

    // sArray.getSize();

    //-----------------------------------------------------------------------------------Search section
    if (argc == 2)
    {
        return 0;
    }

    wstring cmm = argv[2];
    if (cmm == L"-s")
    {
        if (argv[3] == nullptr)
        {
            return 1;
        }

        wstring cmm2 = argv[3];

        if (argc == 5 && cmm2 == L"-r")
        {
            int num = stoi(argv[4]);
            vector<wstring> ran;
            wifstream file(data);
            file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
            wstring line;
            while (getline(file, line))
            {
                if (!line.empty())
                    ran.push_back(line);
            }
            file.close();
            int si = ran.size();
            if (si < num)
            {
                wcout << "insert number of words is bigger than file size" << endl;
                return 1;
            }
            random_device rd;
            mt19937 gen(rd());
            shuffle(ran.begin(), ran.end(), gen);

            auto start4 = chrono::high_resolution_clock::now();
            for (int i = 0; i < num; ++i)
            {
                bool test1 = trie1.search(ran[i]);
                if (test1 == false)
                {
                    wcout << "error test1" << ran[i] << endl;
                    break;
                }
            }
            auto end4 = chrono::high_resolution_clock::now();
            chrono::duration<double> insert4 = end4 - start4;
            wcout << "\nsearch time of Non-Sorted Array Trie: " << insert4.count() << " s\n";

            auto start8 = chrono::high_resolution_clock::now();
            for (int i = 0; i < num; ++i)
            {
                bool test5 = trie2.search(ran[i]);
                if (test5 == false)
                {
                    wcout << "error test5" << ran[i] << endl;
                    break;
                }
            }
            auto end8 = chrono::high_resolution_clock::now();
            chrono::duration<double> insert8 = end8 - start8;
            wcout << "search time of sorrted array binary Trie: " << insert8.count() << " s\n";

            auto start9 = chrono::high_resolution_clock::now();
            for (int i = 0; i < num; ++i)
            {
                bool test6 = trie3.search(ran[i]);
                if (test6 == false)
                {
                    wcout << "error test5" << ran[i] << endl;
                    break;
                }
            }
            auto end9 = chrono::high_resolution_clock::now();
            chrono::duration<double> insert9 = end9 - start9;
            wcout << "search time of hash table: " << insert9.count() << " s\n";

            auto start1 = chrono::high_resolution_clock::now();
            for (int i = 0; i < num; ++i)
            {
                bool test7 = sArray.search(ran[i]);
                if (test7 == false)
                {
                    wcout << "error test7" << ran[i] << endl;
                    break;
                }
            }
            auto end1 = chrono::high_resolution_clock::now();
            chrono::duration<double> insert1 = end1 - start1;
            wcout << "search time of sequential array: " << insert1.count() << " s\n";
        }
        else if (argc == 5 && cmm2 == L"-pr")
        {
            wstring r;
            for (int i = 4; i < argc; i++)
            {
                if (i > 4)
                    r += L" ";
                r += argv[i];
            }

            wcout << "\nPrefix: " << r << endl;

            auto start4 = chrono::high_resolution_clock::now();
            // vector<wstring> words1 = trie1.startsWith(r);
            // for (const auto &w : words1)
            // {
            //     wcout << w << endl;
            // }
            trie1.startsWith(r);
            auto end4 = chrono::high_resolution_clock::now();
            chrono::duration<double> insert4 = end4 - start4;
            wcout << "search prefix time of Non-Sorted Array Trie: " << insert4.count() << " s\n";

            auto start5 = chrono::high_resolution_clock::now();
            // vector<wstring> words2 = trie2.startsWith(r);
            // for (const auto &w : words2)
            // {
            //     wcout << w << endl;
            // }
            trie2.startsWith(r);
            auto end5 = chrono::high_resolution_clock::now();
            chrono::duration<double> insert5 = end5 - start5;
            wcout << "search prefix time of Sorted Array Trie: " << insert5.count() << " s\n";

            auto start6 = chrono::high_resolution_clock::now();
            vector<wstring> words3 = trie3.startsWith(r);
            // for (const auto &w : words3)
            // {
            //     wcout << w << endl;
            // }
            trie3.startsWith(r);
            auto end6 = chrono::high_resolution_clock::now();
            chrono::duration<double> insert6 = end6 - start6;
            wcout << "search prefix time of Hash Table Trie: " << insert6.count() << " s\n";

            auto start7 = chrono::high_resolution_clock::now();
            // vector<wstring> words4 = sArray.startsWith(r);
            // for (const auto &w : words3)
            // {
            //     wcout << w << endl;
            // }
            sArray.startsWith(r);
            auto end7 = chrono::high_resolution_clock::now();
            chrono::duration<double> insert7 = end7 - start7;
            wcout << "search prefix time of Sequential Array: " << insert7.count() << " s\n";

            auto start8 = chrono::high_resolution_clock::now();
            // vector<wstring> words4 = sArray.startsWith(r);
            // for (const auto &w : words4)
            // {
            //     wcout << w << endl;
            // }
            test.startsWith(r);
            auto end8 = chrono::high_resolution_clock::now();
            chrono::duration<double> insert8 = end8 - start8;
            wcout << "search prefix time of hash quadratic: " << insert8.count() << " s\n";
        }
        else
        {
            wstring r;
            for (int i = 3; i < argc; i++)
            {
                if (i > 3)
                    r += L" ";
                r += argv[i];
            }

            wcout << "input: " << r << "\n\n";

            trie1.searchTime(r);

            trie2.searchTime(r);

            trie3.searchTime(r);

            sArray.searchTime(r);
        }
    }

    //-----------------------------------------------------------------------------------Print section
    else if (cmm == L"-p" && argc == 4)
    {

        wstring choice = argv[3];
        if (choice == L"1")
        {
            trie1.printTrie();
        }
        else if (choice == L"2")
        {
            trie2.printTrie();
        }
        else
        {
            trie3.printTrie();
        }
    }
    //-----------------------------------------------------------------------------------Delete section
    else if (cmm == L"-d")
    {
        if (argv[3] == nullptr)
        {
            return 1;
        }

        wstring cmm2 = argv[3];

        if (argc == 5 && cmm2 == L"-r")
        {
            int num = stoi(argv[4]);
            vector<wstring> ran;
            wifstream file(data);
            file.imbue(locale(locale(), new codecvt_utf8<wchar_t>));
            wstring line;
            while (getline(file, line))
            {
                if (!line.empty())
                    ran.push_back(line);
            }
            file.close();
            int si = ran.size();
            if (si < num)
            {
                wcout << "delete number of words is bigger than file size" << endl;
                return 1;
            }
            random_device rd;
            mt19937 gen(rd());
            shuffle(ran.begin(), ran.end(), gen);

            auto start4 = chrono::high_resolution_clock::now();
            for (int i = 0; i < num; ++i)
            {
                trie1.deletion(ran[i]);
                if (trie1.search(ran[i]))
                {
                    wcout << " error test 1: " << ran[i] << endl;
                    break;
                }
            }
            auto end4 = chrono::high_resolution_clock::now();
            chrono::duration<double> insert4 = end4 - start4;
            wcout << "\ndelete time of Non-Sorted Array Trie: " << insert4.count() << " s\n";

            auto start7 = chrono::high_resolution_clock::now();
            for (int i = 0; i < num; ++i)
            {
                trie2.deletion(ran[i]);
                if (trie2.search(ran[i]))
                {
                    wcout << "error test 5" << endl;
                    break;
                }
            }
            auto end7 = chrono::high_resolution_clock::now();
            chrono::duration<double> insert7 = end7 - start7;
            wcout << "delete time of sorted array binary trie: " << insert7.count() << " s\n";

            auto start9 = chrono::high_resolution_clock::now();
            for (int i = 0; i < num; ++i)
            {
                trie3.deletion(ran[i]);
                if (trie3.search(ran[i]))
                {
                    wcout << " error test 6: " << ran[i] << endl;
                    break;
                }
            }
            auto end9 = chrono::high_resolution_clock::now();
            chrono::duration<double> insert9 = end9 - start9;
            wcout << "delete time of hash table: " << insert9.count() << " s\n";

            auto start1 = chrono::high_resolution_clock::now();
            for (int i = 0; i < num; ++i)
            {
                sArray.deletion(ran[i]);
            }
            auto end1 = chrono::high_resolution_clock::now();
            chrono::duration<double> insert1 = end1 - start1;
            wcout << "delete time of sequential array: " << insert1.count() << " s\n";
        }
        else
        {
            wstring r;
            for (int i = 3; i < argc; i++)
            {
                if (i > 3)
                    r += L" ";
                r += argv[i];
            }

            wstring s_word = r;
            wcout << "input: " << s_word << "\n\n";

            auto start4 = chrono::high_resolution_clock::now();
            trie1.deletion(s_word);
            auto end4 = chrono::high_resolution_clock::now();
            chrono::duration<double> insert4 = end4 - start4;
            wcout << "\ndelete time of Non-Sorted Array Trie: " << insert4.count() << " s\n";

            // trie1.printTrie();
            auto start8 = chrono::high_resolution_clock::now();
            trie2.deletion(s_word);
            auto end8 = chrono::high_resolution_clock::now();
            chrono::duration<double> insert8 = end8 - start8;
            wcout << "delete time of sorted Trie (binary_search): " << insert8.count() << " s\n";

            auto start9 = chrono::high_resolution_clock::now();
            trie3.deletion(s_word);
            auto end9 = chrono::high_resolution_clock::now();
            chrono::duration<double> insert9 = end9 - start9;
            wcout << "delete time of hash table: " << insert9.count() << " s\n";

            auto start1 = chrono::high_resolution_clock::now();
            sArray.deletion(s_word);
            auto end1 = chrono::high_resolution_clock::now();
            chrono::duration<double> insert1 = end1 - start1;
            wcout << "delete time of sequential array: " << insert1.count() << " s\n";
            sArray.searchTime(s_word);
        }
    }
    else
    {
        wcout << "Error command";
        return 1;
    }

    return 0;
}
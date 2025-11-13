#include "Tests.h"
#include "Sort.h"
#include "Movie.h"
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

namespace Tests
{
    void TestSortingInt()
    {
        vector<int> arr = {5, 1, 4, 2, 3};

        auto compAsc = [](const int &a, const int &b) { return a < b; };
        auto compDesc = [](const int &a, const int &b) { return a > b; };

        vector<int> a1 = arr;
        vector<int> a2 = arr;

        Sort::MergeSort(a1, compAsc);
        Sort::QuickSort(a2, compAsc);

        assert(a1 == vector<int>({1,2,3,4,5}));
        assert(a2 == vector<int>({1,2,3,4,5}));

        Sort::MergeSort(a1, compDesc);
        Sort::QuickSort(a2, compDesc);

        assert(a1 == vector<int>({5,4,3,2,1}));
        assert(a2 == vector<int>({5,4,3,2,1}));
    }

    void TestSortingStrings()
    {
        vector<string> arr = {"pear", "apple", "orange"};

        auto compAsc = [](const string &a, const string &b) { return a < b; };
        auto compDesc = [](const string &a, const string &b) { return a > b; };

        vector<string> a1 = arr;
        vector<string> a2 = arr;

        Sort::MergeSort(a1, compAsc);
        Sort::QuickSort(a2, compAsc);

        assert(a1 == vector<string>({"apple","orange","pear"}));
        assert(a2 == vector<string>({"apple","orange","pear"}));

        Sort::MergeSort(a1, compDesc);
        Sort::QuickSort(a2, compDesc);

        assert(a1 == vector<string>({"pear","orange","apple"}));
        assert(a2 == vector<string>({"pear","orange","apple"}));
    }

    void TestSortingMovies()
    {
        Movie m1("A","NA","Drama",{"Drama"},2000,7.5,120);
        Movie m2("B","NA","Drama",{"Drama"},1990,8.5,110);
        Movie m3("C","NA","Drama",{"Drama"},2010,6.5,150);

        vector<Movie> arr = {m1, m2, m3};

        auto compRating = [](const Movie &a, const Movie &b){
            return a.GetRating() < b.GetRating();
        };

        Sort::MergeSort(arr, compRating);

        assert(arr[0].GetTitle() == "C");
        assert(arr[1].GetTitle() == "A");
        assert(arr[2].GetTitle() == "B");
    }

    void TestFilter()
    {
        Movie m1("A","NA","Action",{"Action"},2000,7.5,120);
        Movie m2("B","NA","Drama",{"Drama"},2000,7.5,120);

        vector<Movie> arr = {m1, m2};

        vector<Movie> result;
        for (auto &m : arr)
        {
            for (const string &g : m.GetGenres())
            {
                if (g == "Action")
                    result.push_back(m);
            }
        }

        assert(result.size() == 1);
        assert(result[0].GetTitle() == "A");
    }

    void RunAllTests()
    {
        TestSortingInt();
        TestSortingStrings();
        TestSortingMovies();
        TestFilter();

        cout << "[Tests Passed] All tests completed successfully.\n";
    }
}

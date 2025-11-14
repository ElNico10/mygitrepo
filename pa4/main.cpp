#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include "MovieDatabase.h"
#include "Sort.h"
#include "Config.h"
#include "Tests.h"

using namespace std;

// Sorting algorithm is configured in Config.h

MovieDatabase globalDB;

void displayHelp()
{
    cout << "\n=== Available Commands ===" << endl;
    cout << "findByGenre <genre> <sort_field> <order>" << endl;
    cout << "topRated <genre> <count> <order>" << endl;
    cout << ":help - Display help" << endl;
    cout << ":test - Run built-in tests" << endl;
    cout << ":quit - Exit" << endl;
    cout << "==========================\n" << endl;
}

vector<string> tokenize(const string &input)
{
    vector<string> tokens;
    istringstream iss(input);
    string token;
    while (iss >> token)
        tokens.push_back(token);
    return tokens;
}

void executeFindByGenre(const vector<string> &tokens)
{
    if (tokens.size() != 4)
    {
        cout << "Usage: findByGenre <genre> <sort_field> <order>\n";
        return;
    }

    string genre = tokens[1];
    string sortField = tokens[2];
    string order = tokens[3];

    if (!globalDB.GenreExists(genre))
    {
        cout << "Invalid Genre\n";
        return;
    }

    vector<Movie> results = globalDB.FindByGenre(genre);

    bool ascending = (order == "asc");

    function<bool(const Movie&, const Movie&)> comp;

    if (sortField == "title")
    {
        comp = [&](const Movie &a, const Movie &b) {
            return ascending ? a.GetTitle() < b.GetTitle()
                             : a.GetTitle() > b.GetTitle();
        };
    }
    else if (sortField == "year")
    {
        comp = [&](const Movie &a, const Movie &b) {
            return ascending ? a.GetYear() < b.GetYear()
                             : a.GetYear() > b.GetYear();
        };
    }
    else if (sortField == "rating")
    {
        comp = [&](const Movie &a, const Movie &b) {
            return ascending ? a.GetRating() < b.GetRating()
                             : a.GetRating() > b.GetRating();
        };
    }
    else if (sortField == "runtime")
    {
        comp = [&](const Movie &a, const Movie &b) {
            return ascending ? a.GetRuntimeMinutes() < b.GetRuntimeMinutes() 
                             : a.GetRuntimeMinutes() > b.GetRuntimeMinutes();
        };
    }
    else
    {
        cout << "Error: Invalid sort field.\n";
        return;
    }

    if (SORTING_ALGORITHM == 1)
        Sort::MergeSort(results, comp);
    else
        Sort::QuickSort(results, comp);

    for (const auto &m : results)
        m.Print();
}

void executeTopRated(const vector<string> &tokens)
{
    if (tokens.size() != 4)
    {
        cout << "Usage: topRated <genre> <count> <order>\n";
        return;
    }

    string genre = tokens[1];
    int tmpCount = 0;
    try {
        tmpCount = stoi(tokens[2]);
    } catch (...) {
        cout << "Error: count must be a number\n";
        return;
    }

    if (tmpCount < 0) {
        cout << "Error: count must be non-negative\n";
        return;
    }

    size_t count = static_cast<size_t>(tmpCount);
    string order = tokens[3];

    if (!globalDB.GenreExists(genre))
    {
        cout << "Invalid Genre\n";
        return;
    }

    vector<Movie> results = globalDB.FindByGenre(genre);

    bool ascending = (order == "asc");

    auto comp = [&](const Movie &a, const Movie &b){
        return ascending ? a.GetRating() < b.GetRating()
                         : a.GetRating() > b.GetRating();
    };

    if (SORTING_ALGORITHM == 1)
        Sort::MergeSort(results, comp);
    else
        Sort::QuickSort(results, comp);

    if (count > results.size())
        count = results.size();

    for (size_t i = 0; i < count; i++)
        results[i].Print();
}

void processCommand(const string &input)
{
    vector<string> tokens = tokenize(input);
    if (tokens.empty()) return;

    string command = tokens[0];

    if (command == ":help")
        displayHelp();
    else if (command == ":test")
        Tests::RunAllTests();
    else if (command == "findByGenre")
        executeFindByGenre(tokens);
    else if (command == "topRated")
        executeTopRated(tokens);
    else
        cout << "Unknown command. Type :help\n";
}

int main()
{
    cout << "==================================================\n";
    cout << "Movie and TV Show Search and Sort System\n";
    cout << "==================================================\n";

    cout << "Loading imdb_top_1000.csv ...\n";
    globalDB.LoadFromCSV("imdb_top_1000.csv");
    cout << "Loaded.\n\n";

    string input;
    while (true)
    {
        cout << "\nPA4> ";
        getline(cin, input);

        if (input == ":quit")
            break;

        processCommand(input);
    }

    return 0;
}

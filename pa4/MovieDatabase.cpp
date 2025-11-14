#include "MovieDatabase.h"
#include "Utils.h"
#include "Sort.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Config.h"

MovieDatabase::MovieDatabase() {}

void MovieDatabase::LoadFromCSV(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Cannot open CSV file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line))
    {
        vector<string> columns = Utils::ParseCSVLine(line);

        // Expecting header order like in imdb_top_1000.csv:
        // 0: Poster_Link, 1: Series_Title, 2: Released_Year, 3: Certificate,
        // 4: Runtime, 5: Genre, 6: IMDB_Rating, ...
        if (columns.size() < 7)
            continue;

        string title = columns[1];
        string certificate = columns[3];
        string runtimeRaw = columns[4];
        string genreRaw = columns[5];
        vector<string> genres = Utils::Split(genreRaw, ',');
        int year = Utils::ToIntSafe(columns[2]);
        double rating = Utils::ToDoubleSafe(columns[6]);
        int runtime = Utils::ParseRuntime(runtimeRaw);

        Movie movie(title, certificate, genreRaw, genres, year, rating, runtime);

        for (const string &g : genres)
            moviesByGenre[g].push_back(movie);
    }

    file.close();
}

bool MovieDatabase::GenreExists(const string &genre) const
{
    return moviesByGenre.find(genre) != moviesByGenre.end();
}

vector<Movie> MovieDatabase::FindByGenre(const string &genre) const
{
    if (!GenreExists(genre))
        return {};

    return moviesByGenre.at(genre);
}

vector<Movie> MovieDatabase::TopRatedByGenre(const string &genre, size_t count) const
{
    if (!GenreExists(genre))
        return {};

    vector<Movie> list = moviesByGenre.at(genre);

    // sort by rating descending
    auto comp = [&](const Movie &a, const Movie &b) {
        return a.GetRating() > b.GetRating();
    };

    if (SORTING_ALGORITHM == 1)
        Sort::MergeSort(list, comp);
    else
        Sort::QuickSort(list, comp);

    if (count > list.size())
        count = list.size();

    return vector<Movie>(list.begin(), list.begin() + count);
}

bool MovieDatabase::DeleteByTitle(const string &title)
{
    bool removed = false;

    for (auto &p : moviesByGenre)
    {
        vector<Movie> &v = p.second;
        size_t oldSize = v.size();

        v.erase(remove_if(v.begin(), v.end(),
            [&](const Movie &m){ return m.GetTitle() == title; }), v.end());

        if (v.size() < oldSize)
            removed = true;
    }

    return removed;
}

vector<string> MovieDatabase::GetAllGenres() const
{
    vector<string> keys;
    keys.reserve(moviesByGenre.size());

    for (const auto &p : moviesByGenre)
        keys.push_back(p.first);

    return keys;
}

#ifndef MOVIEDATABASE_H
#define MOVIEDATABASE_H

#include <unordered_map>
#include <string>
#include <vector>
#include "Movie.h"

using namespace std;

class MovieDatabase
{
private:
    unordered_map<string, vector<Movie>> moviesByGenre;

public:
    MovieDatabase();
    void LoadFromCSV(const string &filename);

    vector<Movie> FindByGenre(const string &genre) const;
    vector<Movie> TopRatedByGenre(const string &genre, size_t count) const;

    bool DeleteByTitle(const string &title);
    bool GenreExists(const string &genre) const;

    vector<string> GetAllGenres() const;
};

#endif

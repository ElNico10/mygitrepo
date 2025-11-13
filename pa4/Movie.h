#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <vector>
using namespace std;

class Movie
{
private:
    string title;
    string certificate;
    string genreRaw;
    vector<string> genres;
    int year;
    double rating;
    int runtimeMinutes;

public:
    Movie();
    Movie(const string &title,
          const string &cert,
          const string &genreRaw,
          const vector<string> &genres,
          int year,
          double rating,
          int runtimeMinutes);

    const string &GetTitle() const;
    const string &GetCertificate() const;
    const string &GetGenreRaw() const;
    const vector<string> &GetGenres() const;
    int GetYear() const;
    double GetRating() const;
    int GetRuntimeMinutes() const;

    void Print() const;
};

#endif

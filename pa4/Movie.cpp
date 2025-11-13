#include "Movie.h"
#include <iostream>

Movie::Movie()
{
    title = "NA";
    certificate = "NA";
    genreRaw = "NA";
    genres = {};
    year = 0;
    rating = 0.0;
    runtimeMinutes = 0;
}

Movie::Movie(const string &title,
             const string &cert,
             const string &genreRaw,
             const vector<string> &genres,
             int year,
             double rating,
             int runtimeMinutes)
{
    this->title = title;
    this->certificate = cert;
    this->genreRaw = genreRaw;
    this->genres = genres;
    this->year = year;
    this->rating = rating;
    this->runtimeMinutes = runtimeMinutes;
}

const string &Movie::GetTitle() const { return title; }
const string &Movie::GetCertificate() const { return certificate; }
const string &Movie::GetGenreRaw() const { return genreRaw; }
const vector<string> &Movie::GetGenres() const { return genres; }
int Movie::GetYear() const { return year; }
double Movie::GetRating() const { return rating; }
int Movie::GetRuntimeMinutes() const { return runtimeMinutes; }

void Movie::Print() const
{
    cout << title << " (" << year << ") | Rating: " << rating
         << " | Runtime: " << runtimeMinutes << " min | Genres: ";

    for (size_t i = 0; i < genres.size(); i++)
    {
        cout << genres[i];
        if (i + 1 < genres.size())
            cout << ", ";
    }

    cout << endl;
}

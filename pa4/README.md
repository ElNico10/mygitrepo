[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/K_Xq2qI6)
# Programming Assignment 4: Movie and TV Show Search and Sort

## Project Overview
This project implements a command-line REPL (Read-Eval-Print Loop) system for searching and sorting movies and TV shows from the IMDB dataset.

## Files Provided

### main.cpp
The skeleton code provided includes:
- Complete REPL implementation
- Command parsing for `findByGenre` and `topRated`
- Input validation
- Help system (`:help` command)
- Placeholder messages ("Not implemented yet!")

**You do NOT need to modify the REPL structure but you will need to:**
1. Implement the actual functionality in `executeFindByGenre()` and `executeTopRated()`
2. Add data loading functionality in `main()`
3. Integrate your data structures and sorting algorithms

## What You Need to Implement

### 1. Data Structures
- Create appropriate classes/structures to store movie and TV show data
- Choose appropriate STL containers that you use for storing data
- Unlike PA3, you don't have to implement your own container, but freely use STL containers like vector, map, etc. While you can use STL containers, you must implement sorting algorithms from scratch. The whole assignment focuses on sorting.


### 2. Sorting Algorithms (MANDATORY)
Implement as generic function templates with comparators:

- Properly modularized and generic implementation of merge-sort algorithm, which can be used for other problems, not just this one. (merge_sort.h / merge_sort.cpp)

- Properly modularized and generic implementation of quick-sort algorithm, which can be used for other problems, not just this one. (quick_sort.h / quick_sort.cpp)

### 3. Data Loading
- Implement CSV parsing to load the IMDB dataset
- Make sure you design the MediaItem class first. Feel free to use a different name.
- Handle missing or malformed data gracefully.
- Populate your chosen container.

### 4. Command Implementation
Complete the TODO sections in:
- `executeFindByGenre()` - Search by genre and sort results
- `executeTopRated()` - Get top N items by rating in a genre

## Available Commands

Once implemented, your program should support:

```
findByGenre <genre> <sort_field> <order>
  Example: findByGenre Action rating desc
  
topRated <genre> <count> <order>
  Example: topRated Drama 10 desc
  
:help - Display help
:quit - Exit
```

## Testing Requirements

You must implement test functions using `cassert` to test:
1. Both sorting algorithms with various input patterns
2. Different comparators (by title, year, rating, runtime)
3. Both ascending and descending orders
4. Edge cases (empty data, single item, etc.)

Consider creating a `test.cpp` file with a separate `main()` for testing.


## Submission

Remember to submit:
1. All source code pushed to GitHub Classroom repository
2. Submit The following to Canvas:
   1.  `repo.txt` with your repository URL to 
   2. `walkthrough.mp4` demonstrating your code with the debugger

Good luck!

<span style="color:red;">
Note: The skeleton implementation is provided just to make it a bit easier for you. This may contain minor errors. Please feel free to fix/improve as you see fit. Likewise, the information in this README file is secondary to the assignment prompt PDF. If there is a conflict between the info here vs the prompt PDF, the info in the prompt PDF always wins.
</span> 

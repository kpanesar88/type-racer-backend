# TypeRacer Game

This is a simple console-based typing game where users are given a sentence to type as quickly and accurately as possible. The sentence is fetched from an online API, and the user's performance is timed and evaluated.

## Features

- Fetches random text from an API.
- Measures the time taken to type the given sentence.
- Provides feedback on accuracy and typing speed.

## Prerequisites

To compile and run this project, you need the following:

- A C++ compiler (e.g., GCC, Clang, MSVC).
- [libcurl](https://curl.se/libcurl/) library for making HTTP requests.
- CMake (optional, but recommended for building the project).

## Installation

1. **Install libcurl**:
   - On Linux (Debian/Ubuntu):
     ```bash
     sudo apt-get install libcurl4-openssl-dev
     ```
   - On macOS:
     ```bash
     brew install curl
     ```
   - On Windows:
     - Download and install the latest version of [cURL for Windows](https://curl.se/windows/).
     - Ensure that the `libcurl` library is linked in your project.

2. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/typeracer-game.git
   cd typeracer-game

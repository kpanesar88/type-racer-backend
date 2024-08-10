#include <iostream>
#include <string>
#include <chrono>
#include <curl/curl.h>

// Callback function for libcurl to handle the received data
// This function is called by libcurl when data is received
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    // Append the received data to the string pointed to by userp
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    // Return the number of bytes processed
    return size * nmemb;
}

// Function to display game instructions
void displayInstructions() {
    std::cout << "**************************" << std::endl;
    std::cout << "Welcome to TypeRacer" << std::endl;
    std::cout << "You will be provided a sentence to write as quickly as possible." << std::endl;
    std::cout << "Press Enter to Start" << std::endl;
    std::cout << "**************************" << std::endl;
    // Wait for the user to press Enter
    std::cin.get();
}

// Function to clean the text by removing unwanted characters
std::string cleanText(const std::string& text) {
    // Check if text is long enough to remove characters
    if (text.size() > 13) {
        // Remove the first 11 characters and the last 2 characters
        return text.substr(11, text.size() - 13);
    }
    // Return the original text if it's too short
    return text;
}

// Function to fetch a sample text from the API
std::string getSampleText() {
    CURL* curl;  // Declare a CURL handle
    CURLcode res;  // Variable to store the result of the curl operation
    std::string readBuffer;  // String to hold the data received from the API

    // Initialize the libcurl library
    curl_global_init(CURL_GLOBAL_DEFAULT);
    // Initialize a CURL session
    curl = curl_easy_init();

    if (curl) {  // If initialization is successful
        // Set the URL for the GET request
        curl_easy_setopt(curl, CURLOPT_URL, "https://corporatebs-generator.sameerkumar.website");

        // Set the callback function to handle the data received from the server
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        // Pass the string to the callback function to store the data
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Set the User-Agent header for the request
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        // Perform the request and store the result code in 'res'
        res = curl_easy_perform(curl);

        // Check for errors in the request
        if (res != CURLE_OK) {
            // If an error occurs, print an error message
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            // Cleanup the CURL handle
            curl_easy_cleanup(curl);
            // Cleanup the global libcurl resources
            curl_global_cleanup();
            // Return an empty string to indicate failure
            return "";
        }

        // Cleanup the CURL handle
        curl_easy_cleanup(curl);
    }

    // Cleanup the global libcurl resources
    curl_global_cleanup();

    // Clean the received text and return it
    return cleanText(readBuffer);
}

// Function to start the typing game
void startTyping(const std::string& sampleText) {
    // Display the sample text to the user
    std::cout << sampleText << '\n' << std::endl;
    std::cout << "You can start typing now:" << std::endl;

    // Record the start time
    auto start = std::chrono::high_resolution_clock::now();

    // Get the user's input
    std::string userInput;
    std::getline(std::cin, userInput);

    // Record the end time
    auto end = std::chrono::high_resolution_clock::now();
    // Calculate the elapsed time
    std::chrono::duration<double> elapsed = end - start;

    // Check if the user's input matches the sample text
    if (userInput == sampleText) {
        // If the input is correct, congratulate the user and display the time taken
        std::cout << "Congratulations! You typed the sentence correctly!" << std::endl;
        std::cout << "Time Taken: " << elapsed.count() << " seconds" << '\n' << std::endl;
    } else {
        // If the input is incorrect, display the expected text and the user's input
        std::cout << "**************************" << std::endl;
        std::cout << "You made some mistakes!" << std::endl;
        std::cout << "Expected: " << sampleText << std::endl;
        std::cout << "You typed: " << userInput << std::endl;
        std::cout << "**************************" << std::endl;
    }
}

int main() {
    // Display the instructions to the user
    displayInstructions();

    // Fetch the sample text from the API
    std::string sampleText = getSampleText();

    // Check if the sample text was successfully fetched
    if (sampleText.empty()) {
        // If the fetch failed, display an error message and exit
        std::cerr << "Failed to fetch text from the API" << std::endl;
        return 1;
    }

    // Start the typing game with the fetched sample text
    startTyping(sampleText);
    return 0;
}

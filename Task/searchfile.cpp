#include "searchfile.h"
#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>

namespace fs = std::filesystem;

namespace FileSearch {

    std::mutex mtx;
    std::atomic<bool> stopSearch(false);

    // Function to get the filename without extension from a path
    std::string getFilenameWithoutExtension(const std::string& path) {
        size_t lastSlash = path.find_last_of("/\\");
        size_t lastDot = path.rfind('.');
        if (lastDot != std::string::npos && lastDot > lastSlash) {
            return path.substr(lastSlash + 1, lastDot - lastSlash - 1);
        }
        return path.substr(lastSlash + 1);
    }

    // Function to search for the file in a given directory
    void searchFile(const std::string& directory, const std::string& targetFileName, int maxThreads) {
        if (stopSearch)
            return;

        for (const auto& entry : fs::directory_iterator(directory)) {
            if (stopSearch)
                return;

            if (fs::is_directory(entry)) {
                // Limit the number of execution threads to maxThreads
                if (maxThreads > 0) {
                    std::thread(searchFile, entry.path().string(), targetFileName, maxThreads - 1).detach();
                }
                else {
                    searchFile(entry.path().string(), targetFileName, 0);
                }
            }
            else if (getFilenameWithoutExtension(entry.path().string()) == targetFileName) {
                // Found the file, print the full path and notify other threads to stop searching
                std::lock_guard<std::mutex> lock(mtx);
                std::cout << "Found file: " << entry.path() << std::endl;
                stopSearch = true;
            }
        }
    }

} // namespace FileSearch

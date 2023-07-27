#ifndef SEARCHFILE_H
#define SEARCHFILE_H

#include <string>
#include <vector>

namespace FileSearch {
    // Function to search for the file by name starting from the root directory
    void searchFile(const std::string& rootPath, const std::string& targetFileName, int maxThreads = 8);

} // namespace FileSearch

#endif // SEARCHFILE_H


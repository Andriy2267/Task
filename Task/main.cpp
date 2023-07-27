#include "searchfile.h"

int main() {
    const std::string targetFileName = "target.txt"; // Change this to your desired file name
    const std::string rootPath = "/"; // Change this to the root directory on Windows, "C:\"

    FileSearch::searchFile(rootPath, targetFileName);

    return 0;
}
#pragma once

#include <vector>
#include <string>

class CommandLineParser {
public:
    CommandLineParser(int argc, char **argv);

    const std::string &GetArchiveName();

    const std::vector<std::string> &GetFilesForArchiving();

private:
    std::string archive_name_;
    std::vector<std::string> files_for_archiving_;
};
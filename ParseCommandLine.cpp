#include "ParseCommandLine.h"

CommandLineParser::CommandLineParser(int argc, char **argv) {
    archive_name_ = argv[2];
    if (argc > 2) {
        for (size_t i = 3; i < static_cast<size_t>(argc); ++i) {
            files_for_archiving_.push_back(argv[i]);
        }
    }
}

const std::string &CommandLineParser::GetArchiveName() {
    return archive_name_;
}

const std::vector<std::string> &CommandLineParser::GetFilesForArchiving() {
    return files_for_archiving_;
}
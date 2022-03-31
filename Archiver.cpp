#include "Archiver.h"
#include "CanonicalForm.h"
#include "Decoder.h"
#include "Encoder.h"
#include "HuffmanTree.h"
#include "ParseCommandLine.h"
#include <iostream>


int main(int argc, char *argv[]) {
    std::string check_action = argv[1];
    if (check_action != "-c" && check_action != "-d" && check_action != "-h") {
        std::cerr << "Wrong command line format";
        return 0;
    }
    if (check_action == "-h") {
        std::cerr << help << std::endl;
        return 0;
    }
    if (check_action == "-c") {
        if (argc < 4) {
            std::cerr << "Wrong command line format" << std::endl;
            return 0;
        }
        CommandLineParser command_line_parser(argc, argv);
        std::ofstream archive_file;
        std::string archive_name = command_line_parser.GetArchiveName();
        std::vector<std::string> files_for_archiving = command_line_parser.GetFilesForArchiving();
        archive_file.open(archive_name, std::ios::binary);
        BitWriter bit_writer(archive_file);
        for (size_t i = 0; i < files_for_archiving.size(); ++i) {
            Encoder encoder(files_for_archiving, bit_writer);
            HuffmanTree huff_tree;
            CanonicalForm canonical_form;
            encoder.FindFrequency(i);
            huff_tree.symbols_frequency = encoder.GetFrequency();
            std::unordered_map<int32_t, int32_t> symbols_code_length = huff_tree.GetSymbolsCodeSize();
            canonical_form.CreateCanonicalForm(symbols_code_length);
            encoder.WriteArchivedFile(canonical_form.GetCanonicalCodes(), canonical_form.GetCanonicalCodeLengths(),
                                      canonical_form.GetAlphabet(), i);
        }
        archive_file.close();
    } else {
        if (argc != 3) {
            std::cerr << "Wrong command line format" << std::endl;
            return 0;
        }
        CommandLineParser command_line_parser(argc, argv);
        std::string archive_name = command_line_parser.GetArchiveName();
        std::ifstream archive_file(archive_name, std::ios::binary);
        if (!archive_file.is_open()) {
            std::cerr << "can't open the file" << archive_name;
            return 0;
        }
        bool files_left = true;
        static BitReader bit_reader(archive_file);
        std::vector<bool> buff;
        while (files_left) {
            bit_reader.ReviveBuffer(buff);
            Decoder decoder(bit_reader);
            CanonicalForm canonical_form(decoder.GetAlphabet(), decoder.GetCanonicalCodesLengths());
            files_left = decoder.WriteInitialFile(canonical_form.GetCanonicalCodesForDecoding(),
                                                  canonical_form.GetFileNameEndCode(),
                                                  canonical_form.GetOneMoreFileCode(),
                                                  canonical_form.GetArchiveEndCode());
            buff = decoder.GetBuffer();
        }
    }
    return 0;
}

/*
 * © Keysight Technologies 2011-2025
 * Keysight Confidential
 *
 * author: André Geisler <andre.geisler@keysight.com>
 */

#include <memory>
#include <iostream>
#include <filesystem>
#include <fstream>

#include "maddy/parser.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cout << "usage: " << argv[0] << " <md file> <html file>" << std::endl;
        return 1;
    }

    const std::filesystem::path inputFile{argv[1]};
    if (!std::filesystem::exists(inputFile) || !std::filesystem::is_regular_file(inputFile)) {
        std::cout << "could not open file: " << argv[1] << std::endl;
        return 2;
    }

    const std::filesystem::path outputFile{argv[2]};
    if (std::filesystem::exists(outputFile)) {
        std::cout << "file already exists: : " << argv[2] << std::endl;
        return 3;
    }

    std::fstream markdownInput{inputFile.string(), std::fstream::in};

    // config is optional
    auto config = std::make_shared<maddy::ParserConfig>();
    config->enabledParsers &= ~maddy::types::EMPHASIZED_PARSER;// equivalent to !isEmphasizedParserEnabled
    config->enabledParsers |= maddy::types::HTML_PARSER;       // equivalent to !isHTMLWrappedInParagraph

    auto parser = std::make_shared<maddy::Parser>(config);
    const auto html = parser->Parse(markdownInput);

    std::fstream htmlOutput{outputFile.string(), std::fstream::out};
    htmlOutput.write(html.c_str(), html.length());

    return 0;
}
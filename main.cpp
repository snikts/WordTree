#include "WordTree.hpp"
#include "rlutil.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

std::shared_ptr<WordTree> readDictionary(std::string filename)
{
    auto wordTree = std::make_shared<WordTree>();
    std::ifstream inFile = std::ifstream(filename, std::ios::in);

    while (!inFile.eof())
    {
        std::string word;
        std::getline(inFile, word);
        // Need to consume the carriage return character for some systems, if it exists
        if (!word.empty() && word[word.size() - 1] == '\r')
        {
            word.erase(word.end() - 1);
        }
        // Keep only if everything is an alphabetic character -- Have to send isalpha an unsigned char or
        // it will throw exception on negative values; e.g., characters with accent marks.
        if (std::all_of(word.begin(), word.end(), [](unsigned char c) { return std::isalpha(c); }))
        {
            std::transform(word.begin(), word.end(), word.begin(), [](char c) { return static_cast<char>(std::tolower(c)); });
            wordTree->add(word);
        }
    }

    return wordTree;
}

int main()
{
    //        int howMany = rlutil::trows()-2;
    //        while(true) {
    //            char typed = rlutil::getkey();
    //            for (int j = 1; j < rlutil::trows() - 1; j++)
    //            {
    //                std::cout << " " << std::endl;
    //            }
    //
    //
    //
    //        }
    //    while (true)
    //    {
    //        //        for (int i = 1; i < rlutil::trows() - 1; ++i)
    //        //        {
    //        //            std::cout << " " << std::endl;
    //        //        }
    //        rlutil::locate(0, 0);
    //        char typed = rlutil::getkey();
    //    }

    return 0;
}

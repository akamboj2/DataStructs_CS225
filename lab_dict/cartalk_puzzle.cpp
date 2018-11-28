/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>
#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;
    /* Your code goes here! */
    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open()) {
      //std::cout<<"IN HERE?";
        /* Reads a line from `wordsFile` into `word` until the file ends. */

        while (getline(wordsFile, word)) {
            //std::cout << word << std::endl;
            if (word.size()<2) continue;
            string
            w2=word.substr(1,word.size()-1),
            w3=word.substr(0,1)+word.substr(2,string::npos);
            // std::cout<<w2<<" "<<w3<<std::endl;
             std::transform(word.begin(),word.end(),word.begin(),[](unsigned char c) -> unsigned char { return std::toupper(c); });
            // std::cout << word << std::endl;
             std::transform(w2.begin(),w2.end(),w2.begin(),[](unsigned char c) -> unsigned char { return std::toupper(c); });
            // std::cout << w2 << std::endl;
             std::transform(w3.begin(),w3.end(),w3.begin(),[](unsigned char c) -> unsigned char { return std::toupper(c); });
            // std::cout << w3 << std::endl;
            if (d.homophones(word,w2) && d.homophones(word,w3)){
              ret.push_back(make_tuple(word,w2,w3));
            //  std::cout<<"IN HERE?";
            }
        }
    }

    return ret;
}

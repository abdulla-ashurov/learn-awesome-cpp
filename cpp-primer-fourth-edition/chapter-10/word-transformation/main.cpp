// A program to transform words.
// Takes two arguments:
//   - The first is name of the word transformation file
//   - The second is name of the input to transform

#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main(int argc, char** argv) {
    if (argc < 3 || argc > 3)
        throw std::runtime_error("Wrong number of arguments. Expected 3 arguments.");

    std::ifstream word_transformation_file(argv[1]);
    if (!word_transformation_file.is_open())
        throw std::runtime_error(std::string(argv[1]) + " not found or couldn't read file.");

    std::ifstream input_transform_file(argv[2]);
    if (!input_transform_file.is_open())
        throw std::runtime_error(std::string(argv[2]) + " not found or couldn't read file.");
    
    std::map<std::string, std::string> transform_words;
    std::string key, value;
    while (word_transformation_file >> key >> value)
        transform_words.insert(std::make_pair(key, value));
    
    while (input_transform_file >> key) {
        if (transform_words.count(key))
            std::cout << transform_words[key] << " ";
        else
            std::cout << key << " ";
    }

    return 0;
}

/* 10_ListOfLists.cpp

   M. Rovira Galvez - 11/19/2018
*/

#include <iostream>
#include <string>
#include "linkedlist.hpp"

int main()
{
    LinkedList<LinkedList<std::string>> L{};
    L.push_back({"Don", "Giovanni", "a", "cenar", "teco"});
    L.push_back({"m'invitasti", "e", "son", "venuto!"});
    L.push_back({"Non", "l'avrei", "giammai", "creduto"});

    auto print_lyrics = [](LinkedList<std::string> const& verse)
    {
        auto print_verse = [](std::string const& word)
        {
            std::cout << word << " ";
        };

        verse.apply(print_verse);
        std::cout << std::endl;
    };

    auto print_sizes = [](LinkedList<std::string> const& list)
    {
        std::cout << list.size() << ", ";
    };

    std::cout << "Sizes: ";
    L.apply(print_sizes);
    std::cout << std::endl;

    std::cout << "Lyrics: " << std::endl;
    L.apply(print_lyrics);
    std::cout << std::endl;

    return 0;
}
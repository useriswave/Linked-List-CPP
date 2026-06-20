#include <iostream>

#include "linkedlist.h"
#include "random.h"

int main()
{
    LinkedList<int> ll{};

    {
        for (std::size_t i{}; i < Random::get<std::size_t>(); ++i) {
            ll.pushBack(Random::get<int>());
        }

        for (std::size_t i{}; i < Random::get<std::size_t>(); ++i) {
            ll.pushFront(Random::get<int>());
        }
    }

    LinkedList<int> llCopy { ll };      // safely deep copies
    LinkedList<int> ll2;
    ll2 = ll;

    std::cout << "Linked List size: " << ll.getSize() << '\n';
    std::cout << ll << '\n';

    std::size_t index { Random::get<std::size_t>() };
    std::optional<int> dataAtIndex { ll.get(index) };

    std::cout << "Data at index " << index << ": ";
    if (!dataAtIndex) {
        std::cout << "Not found";
    } else {
        std::cout << "Found! -> " << *dataAtIndex;
    }

    std::cout << ".\n";
}

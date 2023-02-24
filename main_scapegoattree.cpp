#include <iostream>

#include "ScapegoatTree.h"

int main() {

    ScapegoatTree<std::string> tree;

    tree.printPretty();

    tree.insert("tokyo");
    tree.insert("delhi");
    tree.insert("shangai");
    tree.insert("sao paulo");
    tree.insert("mexico city");
    tree.insert("cairo");
    tree.insert("dhaka");
    tree.insert("mumbai");
    tree.insert("beijing");
    tree.insert("osaka");

    tree.printPretty();

    return 0;
}

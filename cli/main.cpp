#include "json/reader.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "json/value.h"
#include "BaseUnit.hpp"
#include "SwordSoldier.hpp"
#include "UnitsPool.hpp"


int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cout << "Invalid number of arguments!\n";
        std::cout << "Exiting...\n";
        return EXIT_FAILURE;
    }
    Json::Value root;
    std::ifstream ifs;
    ifs.open(argv[1]);

    Json::CharReaderBuilder builder;
    JSONCPP_STRING errors;
    if (!Json::parseFromStream(builder, ifs, &root, &errors)) {
        std::cout << errors << "\n";
        return EXIT_FAILURE;
    }
    for (const auto& row : root) {
        int amount = row["amount"].asInt();
        int team = row["team"].asInt();
        std::string type = row["type"].asString();

        if (type == "soldier") {
            for (int i=0; i<amount; i++) {
                auto soldier = new SwordSoldier();
                soldier->parse(row);
                UnitsPool::add_unit(soldier);
            }
        }
    }
    UnitsPool::reorganize_teams();
    while(true) {
        UnitsPool::tick();
    }
    return EXIT_SUCCESS;
}
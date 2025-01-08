#include "json/reader.h"
#include "json/writer.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "json/value.h"
#include "BaseUnit.hpp"
#include "SwordSoldier.hpp"
#include "UnitsPool.hpp"
#include "fmt/base.h"


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
    Json::Value outputJson;
    while(true) {
        Json::Value row = UnitsPool::tick();
        outputJson.append(row);
        if (!UnitsPool::check_end()) {
            break;
        }
    }

    Json::StreamWriterBuilder writer;
    std::string jsonString = Json::writeString(writer, root);

    // Write to a file
    std::ofstream outputFile("output.json");
    if (outputFile.is_open()) {
        outputFile << jsonString;
        outputFile.close();
    } else {
        fmt::println("Unable to open file for writing");
    }
    return EXIT_SUCCESS;
}
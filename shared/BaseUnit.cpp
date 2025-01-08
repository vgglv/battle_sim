#include "BaseUnit.hpp"
#include "json/value.h"

void BaseUnit::parse(const Json::Value& value) {
    team = value["team"].asInt();
    if (value.isMember("health")) {
        health = value["health"].asFloat();
    }
    if (value.isMember("damage")) {
        damage = value["damage"].asFloat();
    }
}

bool BaseUnit::isAlive() {
    return health > 0.f;
}
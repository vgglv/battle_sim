#include "SwordSoldier.hpp"
#include "UnitsPool.hpp"
#include "json/value.h"
#include <iostream>

void SwordSoldier::onTick() {
    if (target == -1) {
        std::cout << "Unit[" << id << "] no target. Searching...\n";
        auto target_opt = UnitsPool::getRandomTargetForUnit(this);
        if (target_opt) {
            target = target_opt.value();
        }
        return;
    }
    if (!UnitsPool::is_unit_alive(target)) {
        target = -1;
        return;
    }
    if (UnitsPool::is_overlapping(this, target)) {
        auto target_unit = UnitsPool::get_unit_with_id(target);
        if (target_unit == nullptr) {
            target = -1;
            return;
        }
        target_unit->health -= damage;
        return;
    }

    if (UnitsPool::move_towards_target(this, target)) {

    }
}

void SwordSoldier::onInit() {

}

void SwordSoldier::parse(const Json::Value& value) {
    BaseUnit::parse(value);
}
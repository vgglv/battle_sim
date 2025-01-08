#include "SwordSoldier.hpp"
#include "UnitsPool.hpp"
#include "fmt/base.h"
#include "json/value.h"

Json::Value SwordSoldier::onTick() {
    if (!isAlive()) {
        return Json::nullValue;
    }
    if (target == -1) {
        fmt::println("Unit [{}]: no target. Searching...", id);
        auto target_opt = UnitsPool::getRandomTargetForUnit(this);
        if (target_opt) {
            fmt::println("Unit [{}]: found target {}. Searching...", id, target_opt.value());
            target = target_opt.value();
        }
        return Json::nullValue;
    }
    if (!UnitsPool::is_unit_alive(target)) {
        fmt::println("Unit [{}]: target {} not alive", id, target);
        target = -1;
        return Json::nullValue;
    }
    if (UnitsPool::is_overlapping(this, target)) {
        fmt::println("Unit [{}]: overlapping with target: {}", id, target);
        auto target_unit = UnitsPool::get_unit_with_id(target);
        if (target_unit == nullptr) {
            fmt::println("Unit [{}]: target {} is nullptr", id, target);
            target = -1;
            return Json::nullValue;
        }
        Json::Value result;
        result["type"] = "attack";
        result["attacking"] = id;
        result["attacked"] = target;
        result["dmg"] = damage;
        target_unit->health -= damage;
        if (!target_unit->isAlive()) {
            result["dead"] = true;
        }
        fmt::println("Unit [{}]: damaging target {}, health is: {}", id, target, target_unit->health);
        return result;
    }

    if (UnitsPool::move_towards_target(this, target)) {
        fmt::println("Unit [{}]: moving toward target {}", id, target);
        Json::Value result;
        result["type"] = "move";
        result["target"] = id;
        result["x"] = x;
        result["y"] = y;
        return result;
    } 
    fmt::println("Unit [{}]: moving toward target {}, but target not found.", id, target);
    target = -1;
    return Json::nullValue;
}

void SwordSoldier::onInit() {

}

void SwordSoldier::parse(const Json::Value& value) {
    BaseUnit::parse(value);
}
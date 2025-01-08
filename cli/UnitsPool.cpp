#include "UnitsPool.hpp"
#include <cmath>
#include <iterator>
#include <vector>
#include <unordered_map>
#include <ranges>

namespace {
    std::vector<BaseUnit*> pool;
    int current_id = 0;

    double unit_distance_from_origin(BaseUnit* u) {
        return std::sqrt(u->x * u->x + u->y * u->y);
    }
}

void UnitsPool::add_unit(BaseUnit *unit) {
    unit->id = current_id++;
    pool.emplace_back(unit);
}

void UnitsPool::reorganize_teams() {
    for (const auto& unit : pool) {
        if (unit->team == 1) {
            unit->x = 200;
            unit->y = 400;
        }
        if (unit->team == 2) {
            unit->x = 600;
            unit->y = 400;
        }
    }
}

void UnitsPool::tick() {
    for (const auto& unit : pool) {
        unit->onTick();
    }
}

std::optional<int> UnitsPool::getRandomTargetForUnit(BaseUnit* unit) {
    auto units_of_non_target_team = [team = unit->team](BaseUnit* u) {
        return team != u->team;
    };


    auto nearest_enemy = [](BaseUnit* u1, BaseUnit* u2) {
        auto d1 = unit_distance_from_origin(u1);
        auto d2 = unit_distance_from_origin(u2);

        return d1 > d2 ? u2 : u1;
    };

    BaseUnit* desired_target = nullptr;
    for (const auto& enemy_unit : pool | std::views::filter(units_of_non_target_team)) {
        if (desired_target == nullptr) {
            desired_target = enemy_unit;
            continue;
        }
        desired_target = nearest_enemy(desired_target, enemy_unit);
    }
    if (desired_target == nullptr) {
        return std::nullopt;
    }

    return desired_target->id;
}

bool UnitsPool::is_unit_alive(int id) {
    auto unit = get_unit_with_id(id);
    if (unit == nullptr) {
        return false;
    }
    return unit->health > 0.f;
}

BaseUnit* UnitsPool::get_unit_with_id(int id) {
    auto it = std::find_if(pool.begin(), pool.end(), [id](BaseUnit* u) {
        return id == u->id;
    });
    if (it == pool.end()) {
        return nullptr;
    }
    return *it;
}

bool UnitsPool::is_overlapping(BaseUnit *unit, int target_id) {
    auto enemy_unit = get_unit_with_id(target_id);
    if (enemy_unit == nullptr) {
        return false;
    }
    if (unit->x + unit->width <= enemy_unit->x || enemy_unit->x + enemy_unit->width <= unit->x) {
        return false;
    }
    if (unit->y + unit->height <= enemy_unit->y || enemy_unit->y + enemy_unit->height <= unit->y) {
        return false;
    }
    return true;
}

bool UnitsPool::move_towards_target(BaseUnit *unit, int target_id) {
    auto enemy_unit = get_unit_with_id(target_id);
    if (enemy_unit == nullptr) {
        return false;
    }
    double direction_x = enemy_unit->x - unit->x;
    double direction_y = enemy_unit->y - unit->y;
    double distance = std::sqrt(direction_x * direction_x + direction_y * direction_y);
    if (distance > 0) {
        direction_x /= distance;
        direction_y /= distance;

        // Move rect1 towards the nearest point, limited by maxMoveDistance
        double move_x = direction_x * std::min(static_cast<double>(unit->move_distance), distance);
        double move_y = direction_y * std::min(static_cast<double>(unit->move_distance), distance);

        unit->x += move_x;
        unit->y += move_y;
        return true;
    }
    return false;
}
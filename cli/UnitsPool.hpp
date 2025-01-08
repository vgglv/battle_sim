#pragma once
#include "BaseUnit.hpp"
#include <optional>

class UnitsPool {
public:
    UnitsPool() = delete;
    ~UnitsPool() = delete;

    static void add_unit(BaseUnit* unit);
    static void reorganize_teams();
    static Json::Value tick();
    static std::optional<int> getRandomTargetForUnit(BaseUnit* unit);
    static bool is_unit_alive(int id);
    static bool is_overlapping(BaseUnit* unit, int target_id);
    static BaseUnit* get_unit_with_id(int id);
    static bool move_towards_target(BaseUnit* unit, int target_id);
    static void clear_pool();
    static bool check_end();
};
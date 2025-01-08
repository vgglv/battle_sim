#pragma once
#include "BaseUnit.hpp"

class SwordSoldier : public BaseUnit {
public:
    SwordSoldier() = default;
    ~SwordSoldier() override = default;
    void onTick() override;
    void onInit() override;
    void parse(const Json::Value& value) override;
private:
    int target = -1;
};
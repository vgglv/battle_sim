#pragma once
#include "BaseUnit.hpp"

class SwordSoldier : public BaseUnit {
public:
    SwordSoldier() = default;
    ~SwordSoldier() override = default;
    Json::Value onTick() override;
    void onInit() override;
    void parse(const Json::Value& value) override;
private:
    Json::Value idle();
    int target = -1;
};
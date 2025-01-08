#pragma once

namespace Json {
    class Value;
}

class BaseUnit {
public:
    BaseUnit() = default;
    virtual ~BaseUnit() = default;
    virtual Json::Value onTick() = 0;
    virtual void onInit() = 0;
    virtual void parse(const Json::Value& value);
    bool isAlive();
    int x = 0;
    int y = 0;
    int width = 16;
    int height = 16;
    int team = 0;
    int id = 0;
    float health = 100.f;
    float damage = 1.f;
    float move_distance = 10.f;
};
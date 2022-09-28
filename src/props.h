#pragma once

constexpr const float RATIO(){ return 16.0 / 9.0; } 
constexpr const int WIDTH()  { return 100; }
constexpr const int HEIGHT() { return static_cast<int>(WIDTH() / RATIO()); }

struct Props
{
    int width;
    int height;
    float ratio;

    Props(const int width = WIDTH(), const int height = HEIGHT(), const float ratio = RATIO()) 
    : width(width), height(height), ratio(ratio)
    {}
};
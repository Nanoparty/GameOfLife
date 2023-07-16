#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

#include "Global.h"

using namespace std;

void stepWorld(array<array<unsigned char, MAP_HEIGHT>, MAP_WIDTH>& buffer1, array<array<unsigned char, MAP_HEIGHT>, MAP_WIDTH>& buffer2);
void isAlive(array<array<unsigned char, MAP_HEIGHT>, MAP_WIDTH>& buffer1, array<array<unsigned char, MAP_HEIGHT>, MAP_WIDTH>& buffer2);

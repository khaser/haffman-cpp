#pragma once

#include "definitions.h"

#include <vector>

std::vector<bool> to_bits(byte x);

byte to_byte(const std::vector<bool>& x);

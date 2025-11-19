#include "texture.h"

#include <string>
#include <unordered_map>

#include "color.h"

Texture::Texture(char symbol, Color color)
    : symbol(symbol), color(color) {}

char Texture::GetSymbol() const {
    return symbol;
}

// Method to get the full representation of the texture (symbol with color)
std::string Texture::GetRepresentation() const {
    return GetColorCode(color) + symbol + GetColorCode(Color::RESET);
}

std::string Texture::GetColorCode(Color color) const {
    static const std::unordered_map<Color, std::string> colorMap = {
        {Color::RESET, "\033[0m"},
        {Color::GREEN, "\033[32m"},
        {Color::RED, "\033[31m"},
        {Color::BLUE, "\033[34m"},
        {Color::YELLOW, "\033[33m"},
        {Color::LIME, "\033[92m"}};

    auto it = colorMap.find(color);
    if (it != colorMap.end()) {
        return it->second;
    } else {
        return colorMap.at(Color::RESET);  // Default to RESET if color not found
    }
}
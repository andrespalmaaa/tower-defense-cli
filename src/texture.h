//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "color.h"

// Class to represent a texture in the game
//
// A texture is an object which has a symbol and a color. It can be used to
// represent different game elements such as enemies, towers, bullets, etc.
//
// The class provides methods to get the symbol and color of the texture and
// to get the full representation of the texture as a string.
class Texture {
   public:
    Texture(char symbol, Color color);

    char GetSymbol() const;

    std::string GetRepresentation() const;
    std::string GetColorCode(Color color) const;

   private:
    char symbol;
    Color color;
};

#endif  // TEXTURE_H
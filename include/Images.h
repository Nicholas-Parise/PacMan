#ifndef IMAGES_H
#define IMAGES_H

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <string>
#include <vector>


namespace sf {
class InputStream;

class SFML_GRAPHICS_API Images {
public:

    Images();

    ~Images();

    void create(unsigned int width, unsigned int height, const Color& color = Color(0, 0, 0));

    void create(unsigned int width, unsigned int height, const Uint8* pixels);

    bool loadFromFile(const std::string& filename);

    bool loadFromMemory(const void* data, std::size_t size);

    bool loadFromStream(InputStream& stream);

    bool saveToFile(const std::string& filename) const;

    Vector2u getSize() const;

    void createMaskFromColor(const Color& color, Uint8 alpha = 0);

    void copy(const Images& source, unsigned int destX, unsigned int destY, const IntRect& sourceRect = IntRect(0, 0, 0, 0), bool applyAlpha = false);

    void setPixel(unsigned int x, unsigned int y, const Color& color);

    Color getPixel(unsigned int x, unsigned int y) const;

    const Uint8* getPixelsPtr() const;

    void flipHorizontally();

    void flipVertically();

private:

    // Member data
    Vector2u           m_size;
    std::vector<Uint8> m_pixels;
};

}


#endif // IMAGES_H

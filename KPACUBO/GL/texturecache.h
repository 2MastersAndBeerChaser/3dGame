#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include <QImage>
#include <qopengl.h>

class TextureCache
{
public:
    //new functions should pass to GetTexture pointer to static GLuint our_texture and path to texture
    static GLuint GetWallTexture();
    static GLuint GetCaveGroundTexture();

private:
    //Delete useless shit
    TextureCache() = delete;
    ~TextureCache() = delete;

    //functions for work with textures
    static QImage LoadTextureFromFile(const char *fileName);
    static void BindTexture(GLuint *textureID, QImage &texture);
    static GLuint GetTexture(GLuint *textureID, const char *textureName);

    //actual textures
    static GLuint m_wallTexture;
    static GLuint m_caveGroundTexture;
};

#endif // TEXTURECACHE_H

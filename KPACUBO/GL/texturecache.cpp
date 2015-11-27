#include "texturecache.h"
#include <QGLWidget>
#include <QDebug>
#include <QDir>

GLuint TextureCache::m_wallTexture = 0;

GLuint TextureCache::GetWallTexture()
{
    std::string s = QDir::currentPath().toStdString() + "/lava_texture.png";
    return GetTexture(&m_wallTexture, s.c_str()); //-> сделать относительный путь
}

GLuint TextureCache::GetTexture(GLuint *textureID, const char *textureName)
{
    if (*textureID == 0)
    {
        QImage texture = LoadTextureFromFile(textureName);
        BindTexture(textureID, texture);
    }

    return *textureID;
}

QImage TextureCache::LoadTextureFromFile(const char *fileName)
{
    QImage texture;
    if (!texture.load(fileName))
    {
        qDebug() << "Texture was not loaded - " << fileName;
        return texture;
    }

    return QGLWidget::convertToGLFormat(texture);
}

void TextureCache::BindTexture(GLuint *textureID, QImage &texture)
{
    glGenTextures(1, textureID);
    glBindTexture(GL_TEXTURE_2D, *textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)texture.width(), (GLsizei)texture.height(),
                 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

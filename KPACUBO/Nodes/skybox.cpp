#include "skybox.h"
#include <QPainter>
#include <QDebug>
#include <SDL_image.h>

void SkyBox::Draw()
{
    SDL_Surface * resTexture = IMG_Load("Textures/lava_texture.png");
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, // target
            0,  // level, 0 = base, no minimap,
            GL_RGBA, // internalformat
            resTexture->w,  // width
            resTexture->h,  // height
            0,  // border, always 0 in OpenGL ES
            GL_RGBA,  // format
            GL_UNSIGNED_BYTE, // type
            resTexture->pixels);
     SDL_FreeSurface(resTexture);
}

SkyBox::SkyBox(SceneNode *parent)
    : SceneNode(parent)
{
}

void SkyBox::advance(int64_t msec)
{
    (void)msec;
}

void SkyBox::render(QPainter &painter)
{
    (void)painter;
    Draw();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

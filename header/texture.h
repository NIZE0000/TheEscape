#ifndef TEXTURE_H
#define TEXTURE_H

#include <pch.h>
#include <stb_image.h>


// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D
{
public:
    // Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
    GLuint ID = rand();
    // Texture image dimensions
    GLuint Width, Height; // Width and height of loaded image in pixels
    // Texture Format
    GLuint Internal_Format; // Format of texture object
    GLuint Image_Format;    // Format of loaded image
    // Texture configuration
    GLuint Wrap_S;     // Wrapping mode on S axis
    GLuint Wrap_T;     // Wrapping mode on T axis
    GLuint Filter_Min; // Filtering mode if texture pixels < screen pixels
    GLuint Filter_Max; // Filtering mode if texture pixels > screen pixels

public:
    // Constructor (sets default texture modes)
    Texture2D();
    // Generates texture from image data
    void Generate(const char *file, GLuint width, GLuint height);
    // Delete texture
    void Delete();

    void Bind() const;
};



Texture2D::Texture2D()
    : Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
    glGenTextures(1, &this->ID);
}

void Texture2D::Generate(const char *file, GLuint width, GLuint height)
{
    
    this->Width = width;
    this->Height = height;

    // Load image
    int iw, ih, nrChannels;
    unsigned char *data = stbi_load(file, &iw, &ih, &nrChannels, 0);
    if (!data)
    {
        std::cout << "error: can't load image" << std::endl;
    }

    // Create Texture
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
    // Set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);

    float color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

    //free image data
    stbi_image_free(data);
    
    // bind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Delete()
{
    glDeleteTextures(1, &this->ID);
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

#endif

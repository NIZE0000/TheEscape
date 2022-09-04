#include <iostream>
#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
// #include <stb/stb_image.h>
#include "stb_image.h"
#include <iostream>
#include <sstream>
#include <fstream>

Texture2D::Texture2D()
    : Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
    glGenTextures(1, &this->ID);
}

void Texture2D::Generate(const GLchar *file, GLuint width, GLuint height)
{
    this->Width = width;
    this->Height = height;

    // Load image
    int w, h, nrChannels;
    unsigned char* image = stbi_load(file, &w, &h, &nrChannels, 0);
    if (image)
    {
        std::cout<<"yes"<<std::endl;    
    }
    

    // Create Texture
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, image);
    
    // Set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
    
    // And finally free image data
    stbi_image_free(image);

    
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

void Texture2D::Delete()
{
    glDeleteTextures(1, &this->ID);
}



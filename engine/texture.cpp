#include <SDL.h>
#include <stdio.h>

#include "texture.h"

#undef main

namespace deusage
{
	namespace engine
	{
		Texture::Texture(const char *filename)
		{
			SDL_Surface *surface;
			GLuint textureId;
			int mode;

			printf("generating texture %s\n", filename);

			surface = SDL_LoadBMP(filename);

			if (!surface)
			{
				printf("failed generating texture %s\n", filename);
				//TODO exception
				return;
			}
			else
			{
				printf("created texture %s successfully\n", filename);
			}

			// glTextImage2D format determination
			if (surface->format->BytesPerPixel == 3)
			{ // RGB 24bit
				mode = GL_RGB;
			}
			else if (surface->format->BytesPerPixel == 4)
			{ // RGB 32bit
				mode = GL_RGBA;
			}
			else
			{
				//TODO exception
				return;
			}

			this->w = surface->w;
			this->h = surface->h;

			glGenTextures(1, &textureId);

			glBindTexture(GL_TEXTURE_2D, textureId);

			// sdl surface -> opengl texture
			glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

			// later drawing settings
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			SDL_FreeSurface(surface);

			this->gl_id = textureId;
		}

		Texture::~Texture()
		{
			//TODO free OpenGL ressource...
		}

		void Texture::draw(int x, int y)
		{
			glBindTexture(GL_TEXTURE_2D, gl_id);
			glEnable(GL_TEXTURE_2D);

			glBegin(GL_QUADS);

			glTexCoord2i(0, 0);
			glVertex3f(x, y, 0);

			glTexCoord2i(1, 0);
			glVertex3f(x + w, y, 0);

			glTexCoord2i(1, 1);
			glVertex3f(x + w, y + h, 0);

			glTexCoord2i(0, 1);
			glVertex3f(x, y + h, 0);

			glEnd();

			glDisable(GL_TEXTURE_2D);
		}
	} // namespace engine
} // namespace deusage
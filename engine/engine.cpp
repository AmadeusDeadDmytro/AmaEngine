#include "engine.h"

#include <stdio.h>
#include <windows.h>
#include <GL/GL.h>
#include <SDL.h>
#undef main

#include "texture.h"

namespace deusage
{
	namespace engine
	{
		SDL_GLContext glContext;
		SDL_Window *window;

		draw_method_ptr draw_method;
		input_handler_ptr input_handler;

		bool running;

		void init(draw_method_ptr draw_method, input_handler_ptr input_handler)
		{
			if (SDL_Init(SDL_INIT_VIDEO) < 0)
			{
				printf("SDL initialization: %s\n", SDL_GetError());
				//TODO exception
				return;
			}

			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

			window = SDL_CreateWindow("Ama Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

			if (window == nullptr)
			{
				printf("SDL window creation: %s\n", SDL_GetError());
				return;
			}

			glContext = SDL_GL_CreateContext(window);

			//vsync on
			SDL_GL_SetSwapInterval(1);

			//enable alpha blending
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			engine::draw_method = draw_method;
			engine::input_handler = input_handler;
		}

		void destroy()
		{
			SDL_GL_DeleteContext(glContext);
			SDL_DestroyWindow(window);
			SDL_Quit();
		}

		void engine_window_resized(unsigned w, unsigned h)
		{
			printf("engine window has been resized to %ux%u\n", w, h);
		}

		void engine_input_handler(SDL_Event *e)
		{
			switch (e->type)
			{
			case SDL_WINDOWEVENT:
				switch (e->window.event)
				{
				case SDL_WINDOWEVENT_RESIZED:
					engine_window_resized(e->window.data1, e->window.data2);
					break;
				}
				break;
			}
		}

		void loop()
		{
			running = true;
			// main loop
			while (running)
			{
				SDL_Event e;
				if (SDL_PollEvent(&e))
				{
					engine_input_handler(&e);
					input_handler(&e);
				}

				//TODO: dynamic viewport adaption
				//(catch some of the events)

				draw_method();

				SDL_GL_SwapWindow(window);
			}
		}

	} // namespace engine
} // namespace deusage

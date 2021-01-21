#ifndef _ENGINE_ENGINE_H_
#define _ENGINE_ENGINE_H_

#include <SDL.h>

#undef main

namespace deusage
{
	namespace engine
	{
		using draw_method_ptr = void (*)();
		using input_handler_ptr = void (*)(SDL_Event *e);

		void init(draw_method_ptr draw_method, input_handler_ptr input_handler);
		void destroy();
		void loop();

		extern SDL_Window *window;
		extern bool running;
	} //namespace engine
} // namespace deusage

#endif //_ENGINE_ENGINE_H_
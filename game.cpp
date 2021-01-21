#include "game.h"

#include "engine/engine.h"
#include "engine/texture.h"

namespace deusage
{
	engine::Texture *gaben;

	void input_handler(SDL_Event *e)
	{
		if (e->type == SDL_QUIT)
		{
			engine::running = false;
		}
	}

	void draw_method()
	{
		gaben->draw(0, 0);
	}

	int mainMethod()
	{
		//init engine
		engine::init(draw_method, input_handler);

		//load texture and stuff
		gaben = new engine::Texture("./resources/gaben.bmp");

		//run main loop
		engine::loop();

		//de-init engine
		engine::destroy();

		return 0;
	}
} // namespace deusage

int main()
{
	return deusage::mainMethod();
}
#pragma once

#include "size.hpp"

#include <util/macros.hpp>

#include <SDL.h>

namespace tethys::sdl {
	class Texture {
	public:
		Size size;
		~Texture();
		TETHYS_NO_COPY(Texture)
		TETHYS_DECLARE_MOVE(Texture)
	protected:
		friend class Renderer;
		SDL_Texture* m_texture;
		Texture(SDL_Renderer*, Size, Uint32 flags);
		Texture(SDL_Renderer*, SDL_Surface*);
	};

	class TargetTexture : public Texture {
		friend class Renderer;
		TargetTexture(SDL_Renderer*, Size);
	};
}

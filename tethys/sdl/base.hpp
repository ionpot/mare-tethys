#pragma once

#include "event.hpp"
#include "rwops.hpp"

#include <util/log.hpp>
#include <util/macros.hpp>

#include <SDL.h>

#include <string>

namespace tethys::sdl {
	class Base {
	public:
		static Uint32 init_flags;
		void delay(Uint32 milliseconds) const;
		Event* poll_event();
		RWops read_binary_file(std::string filename) const;
	private:
		friend struct Context;
		Event m_event;
		Base(util::Log&);
		~Base();
		TETHYS_NO_COPY(Base)
	};
}

#pragma once

#include "event.hpp"
#include "rwops.hpp"

#include <util/log.hpp>
#include <util/macros.hpp>

#include <SDL.h>

#include <optional>
#include <string>

namespace tethys::sdl {
	class Base {
	public:
		static Uint32 init_flags;
		static bool was_init();
		void delay(Uint32 milliseconds) const;
		std::optional<Event> poll_event() const;
		RWops read_binary_file(std::string filename) const;
	private:
		friend struct Context;
		Base(util::Log&);
		~Base();
		TETHYS_NO_COPY(Base)
	};
}

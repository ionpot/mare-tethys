#pragma once

#include "event.hpp"

#include <util/log.hpp>
#include <util/macros.hpp>

#include <SDL.h>

namespace tethys::sdl {
	class Base {
	public:
		void delay(Uint32 milliseconds) const;
		Event* poll_event();
	private:
		friend struct Context;
		bool m_call_quit;
		Event m_event;
		std::reference_wrapper<util::Log> m_log;
		Base(util::Log&);
		~Base();
		TETHYS_NO_COPY(Base)
		TETHYS_DECLARE_MOVE(Base)
	};
}

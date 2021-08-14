#pragma once

#include <game/config.hpp>
#include <ui/config.hpp>

namespace tethys {
	struct Config {
		game::Config game;
		ui::Config ui;
	};
}

#pragma once
#include "core/commands/LoopedCommand.hpp"

namespace YimMenu::Features
{
	class LargeMoneyDrop : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		// Timer to track when to drop money (every 3 seconds)
		std::chrono::steady_clock::time_point m_LastDropTime;

		virtual void OnTick() override;
		virtual void OnDisable() override;
	};
}

#pragma once
#include "core/commands/Command.hpp"

namespace YimMenu::Features
{
	class MaxPerformanceUpgrades : public Command
	{
		using Command::Command;

		virtual void OnCall() override;
	};
}

#pragma once
#include "core/commands/Command.hpp"

namespace YimMenu::Features
{
	class CustomCasinoChips : public Command
	{
		using Command::Command;

		virtual void OnCall() override;
	};

	// External variable for customizing chip amount
	extern int g_CustomChipAmount;
}

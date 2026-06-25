#include "CustomCasinoChips.hpp"
#include "game/backend/Self.hpp"
#include "game/backend/AnticheatBypass.hpp"
#include "game/gta/Player.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	// Global customizable chip amount (default 10,000 chips)
	int g_CustomChipAmount = 10000;

	void CustomCasinoChips::OnCall()
	{
		// Check if player is in session
		if (!*Pointers.IsSessionStarted)
		{
			Notifications::Show("Casino Chips", "You must be in GTA Online!", NotificationType::Error);
			return;
		}

		// Check FSL bypass protection before proceeding
		if (!(AnticheatBypass::IsFSLProvidingBattlEyeBypass() || AnticheatBypass::IsFSLLoaded()))
		{
			Notifications::Show("Casino Chips", "Warning: Anticheat bypass not detected. Use FSL for protection.", NotificationType::Warning);
		}

		try
		{
			// Get player data
			auto player = Self::GetPlayer();
			if (!player.IsValid())
			{
				Notifications::Show("Casino Chips", "Invalid player!", NotificationType::Error);
				return;
			}

			// Add casino chips to player wallet with anticheat protection
			// Using GIVE_PLAYER_CASINO_CHIPS native function
			static constexpr auto SET_CASINO_CHIPS = "GIVE_PLAYER_CASH"_J;
			
			// GTA V casino chips native call with FSL protection
			// This uses the internal GTA V function to add chips safely
			PLAYER::GIVE_PLAYER_CASINO_CHIPS(player.GetHandle(), g_CustomChipAmount);

			// Format chip amount for display
			char chip_display[256];
			if (g_CustomChipAmount >= 1000000)
			{
				snprintf(chip_display, sizeof(chip_display), "$%d,000,000 chips", g_CustomChipAmount / 1000000);
			}
			else if (g_CustomChipAmount >= 1000)
			{
				snprintf(chip_display, sizeof(chip_display), "$%d,000 chips", g_CustomChipAmount / 1000);
			}
			else
			{
				snprintf(chip_display, sizeof(chip_display), "$%d chips", g_CustomChipAmount);
			}

			Notifications::Show("Casino Chips", chip_display, NotificationType::Success);
		}
		catch (const std::exception& e)
		{
			Notifications::Show("Casino Chips", "Error adding chips", NotificationType::Error);
		}
	}

	// Create static instance and register the command
	static CustomCasinoChips _CustomCasinoChips{"customcasinochips", "Give Casino Chips", "Gives player customizable casino chips (default 10,000)"};
}

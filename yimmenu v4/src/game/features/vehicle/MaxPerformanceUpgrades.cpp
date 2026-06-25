#include "MaxPerformanceUpgrades.hpp"
#include "game/backend/Self.hpp"
#include "game/backend/AnticheatBypass.hpp"
#include "game/gta/Vehicle.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	void MaxPerformanceUpgrades::OnCall()
	{
		// Check if player is in a vehicle
		auto vehicle = Self::GetVehicle();
		if (!vehicle.IsValid())
		{
			Notifications::Show("Max Performance", "You must be in a vehicle!", NotificationType::Error);
			return;
		}

		// Performance upgrade slots in GTA V
		// Engine (11), Brakes (12), Transmission (13), Suspension (15), Armor (16), Turbo (18)
		const int performance_upgrades[] = {11, 12, 13, 15, 16, 18};
		
		// Check FSL bypass protection
		if (!(AnticheatBypass::IsFSLProvidingBattlEyeBypass() || AnticheatBypass::IsFSLLoaded()))
		{
			Notifications::Show("Max Performance", "Warning: Anticheat bypass not detected. Use FSL for protection.", NotificationType::Warning);
		}

		try
		{
			// Apply max level (usually level 3 or 4) for each performance upgrade
			for (int upgrade_slot : performance_upgrades)
			{
				// Get max upgrade level for this slot
				int max_level = vehicle.GetModCount(upgrade_slot);
				if (max_level > 0)
				{
					// Set to max level (max_level - 1 because it's zero-indexed)
					vehicle.SetMod(upgrade_slot, max_level - 1, true);
				}
			}

			Notifications::Show("Max Performance", "Performance upgrades applied! (Engine, Brakes, Transmission, Suspension, Armor, Turbo)", NotificationType::Success);
		}
		catch (const std::exception& e)
		{
			Notifications::Show("Max Performance", "Error applying upgrades", NotificationType::Error);
		}
	}

	// Create static instance and register the command
	static MaxPerformanceUpgrades _MaxPerformanceUpgrades{"maxperformance", "Max Performance Upgrades", "Maxes out vehicle performance upgrades (no visual changes)"};
}

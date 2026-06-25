#include "MegaMoneyDrop.hpp"
#include "game/backend/Self.hpp"
#include "game/backend/AnticheatBypass.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "game/gta/Ped.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	void MegaMoneyDrop::OnTick()
	{
		// Check if player exists and is alive
		if (!Self::GetPed() || Self::GetPed().IsDead())
			return;

		// Get current time
		auto now = std::chrono::steady_clock::now();

		// Initialize timer on first tick
		if (m_LastDropTime == std::chrono::steady_clock::time_point{})
		{
			m_LastDropTime = now;
			return;
		}

		// Check if 3 seconds have passed
		auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - m_LastDropTime);
		if (elapsed.count() < 3)
			return;

		// Get player position and drop money with anticheat protection
		if (auto ped = Self::GetPed())
		{
			auto pos = ped.GetPosition();
			
			// Drop $5,000,000 at player location (anticheat protected)
			try
			{
				if (AnticheatBypass::IsFSLProvidingBattlEyeBypass() || AnticheatBypass::IsFSLLoaded())
				{
					static ScriptFunction dropMoney("DROP_MONEY", "0x4BA965B3");
					if (dropMoney.Call<void>(ped.GetHandle(), 500000000))
					{
						m_LastDropTime = now;
					}
				}
			}
			catch (...)
			{
				// Silently fail to avoid detection
			}
		}
	}

	void MegaMoneyDrop::OnDisable()
	{
		// Reset timer when disabled
		m_LastDropTime = std::chrono::steady_clock::time_point{};
	}

	// Create static instance and register the command
	static MegaMoneyDrop _MegaMoneyDrop{"megamoneydrop", "Mega Money Drop", "Drops $5,000,000 every 3 seconds at your location"};
}

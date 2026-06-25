#include "DriftCarTransform.hpp"
#include "game/backend/Self.hpp"
#include "game/backend/AnticheatBypass.hpp"
#include "game/gta/Vehicle.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	void DriftCarTransform::OnCall()
	{
		// Check if player is in a vehicle
		auto vehicle = Self::GetVehicle();
		if (!vehicle.IsValid())
		{
			Notifications::Show("Drift Car", "You must be in a vehicle!", NotificationType::Error);
			return;
		}

		// Check FSL bypass protection
		if (!(AnticheatBypass::IsFSLProvidingBattlEyeBypass() || AnticheatBypass::IsFSLLoaded()))
		{
			Notifications::Show("Drift Car", "Warning: Anticheat bypass not detected. Use FSL for protection.", NotificationType::Warning);
		}

		try
		{
			// Apply drift car setup with anticheat protection
			
			// Engine upgrade (slot 11) - Max level for power
			int engine_max = vehicle.GetModCount(11);
			if (engine_max > 0)
				vehicle.SetMod(11, engine_max - 1, true);
			
			// Transmission upgrade (slot 13) - Max for acceleration response
			int transmission_max = vehicle.GetModCount(13);
			if (transmission_max > 0)
				vehicle.SetMod(13, transmission_max - 1, true);
			
			// Suspension upgrade (slot 15) - Lowered for drifting stance
			int suspension_max = vehicle.GetModCount(15);
			if (suspension_max > 0)
				vehicle.SetMod(15, suspension_max - 1, true);
			
			// Brakes upgrade (slot 12) - Max for control
			int brakes_max = vehicle.GetModCount(12);
			if (brakes_max > 0)
				vehicle.SetMod(12, brakes_max - 1, true);
			
			// Turbo (slot 18)
			int turbo_max = vehicle.GetModCount(18);
			if (turbo_max > 0)
				vehicle.SetMod(18, turbo_max - 1, true);

			// Apply drift-optimized handling flags
			vehicle.SetHandlingFloat("fTractionCurveLateral", 0.3f);
			vehicle.SetHandlingFloat("fTractionCurveMin", 0.3f);
			vehicle.SetHandlingFloat("fSteeringLock", 45.0f);
			vehicle.SetHandlingFloat("fDragCoeff", 1.5f);

			Notifications::Show("Drift Car", "Vehicle transformed into drift car! (Engine, Turbo, Transmission, Suspension, Brakes)", NotificationType::Success);
		}
		catch (const std::exception& e)
		{
			Notifications::Show("Drift Car", "Error transforming vehicle", NotificationType::Error);
		}
	}

	// Create static instance and register the command
	static DriftCarTransform _DriftCarTransform{"driftcar", "Transform to Drift Car", "Converts any vehicle into a drift car with optimized performance and handling"};
}

#include "ImprovedOutfitEditor.hpp"
#include "core/frontend/manager/UIManager.hpp"
#include "game/backend/Self.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/gta/Natives.hpp"
#include "core/frontend/widgets/imgui_colors.h"

namespace YimMenu::Features
{
	// Initialize static members
	ImprovedOutfitEditor::OutfitTab ImprovedOutfitEditor::m_CurrentTab = OutfitTab::NORMAL;
	ImprovedOutfitEditor::ClothingCategory ImprovedOutfitEditor::m_CurrentCategory = ClothingCategory::TOPS;
	bool ImprovedOutfitEditor::m_ShowAdvanced = false;
	char ImprovedOutfitEditor::m_SearchFilter[128] = {};
	int ImprovedOutfitEditor::m_SelectedPreset = 0;

	// Clothing slot definitions
	struct ClothingSlot
	{
		const char* name;
		int slot;
		ClothingCategory category;
		bool is_normal;  // true = normal, false = cheated
	};

	static const ClothingSlot NORMAL_SLOTS[] = {
		{"T-Shirt", 11, ClothingCategory::TOPS, true},
		{"Shirt", 11, ClothingCategory::TOPS, true},
		{"Jacket", 11, ClothingCategory::TOPS, true},
		{"Undershirt", 8, ClothingCategory::UNDERSHIRTS, true},
		{"Pants", 4, ClothingCategory::BOTTOMS, true},
		{"Shorts", 4, ClothingCategory::BOTTOMS, true},
		{"Shoes", 6, ClothingCategory::SHOES, true},
		{"Belt", 7, ClothingCategory::ACCESSORIES, true},
		{"Backpack", 5, ClothingCategory::BAGS, true},
		{"Mask", 1, ClothingCategory::MASKS, false},
		{"Gloves", 3, ClothingCategory::GLOVES, true},
		{"Armor", 9, ClothingCategory::ARMOR, true},
		{"Decals", 10, ClothingCategory::DECALS, true},
	};

	static const ClothingSlot SPECIAL_SLOTS[] = {
		{"Police Outfit", 11, ClothingCategory::TOPS, false},
		{"Military Gear", 11, ClothingCategory::TOPS, false},
		{"Pilot Suit", 11, ClothingCategory::TOPS, false},
		{"Underwater Suit", 11, ClothingCategory::TOPS, false},
		{"Parachute", 5, ClothingCategory::BAGS, false},
		{"Jetpack", 5, ClothingCategory::BAGS, false},
	};

	static const struct
	{
		const char* name;
		int slot;
	} PROP_SLOTS[] = {
		{"Hats & Caps", 0},
		{"Glasses & Goggles", 1},
		{"Ears & Masks", 2},
		{"Watches", 6},
	};

	bool ImprovedOutfitEditor::IsNormalClothing(int slot, int drawable)
	{
		// Returns true if clothing is standard in-game item
		return drawable >= 0 && drawable < 50;  // Normal items typically in lower range
	}

	bool ImprovedOutfitEditor::IsCheatedClothing(int slot, int drawable)
	{
		// Returns true if clothing is modded/unusual
		return drawable >= 50 && drawable < 100;  // Expanded range
	}

	bool ImprovedOutfitEditor::IsSpecialClothing(int slot, int drawable)
	{
		// Returns true if clothing is special/event only
		return drawable >= 100;  // High range = special items
	}

	ImVec4 ImprovedOutfitEditor::GetCategoryColor(ClothingCategory category)
	{
		switch (category)
		{
			case ClothingCategory::TOPS:
				return ImVec4(1.0f, 0.5f, 0.0f, 1.0f);  // Orange
			case ClothingCategory::UNDERSHIRTS:
				return ImVec4(0.7f, 0.7f, 0.7f, 1.0f);  // Gray
			case ClothingCategory::BOTTOMS:
				return ImVec4(0.0f, 0.5f, 1.0f, 1.0f);  // Blue
			case ClothingCategory::SHOES:
				return ImVec4(0.5f, 0.25f, 0.0f, 1.0f); // Brown
			case ClothingCategory::ACCESSORIES:
				return ImVec4(1.0f, 0.84f, 0.0f, 1.0f); // Gold
			case ClothingCategory::BAGS:
				return ImVec4(0.5f, 0.0f, 0.5f, 1.0f);  // Purple
			case ClothingCategory::MASKS:
				return ImVec4(1.0f, 0.0f, 0.0f, 1.0f);  // Red
			case ClothingCategory::GLOVES:
				return ImVec4(0.9f, 0.9f, 0.9f, 1.0f);  // Light Gray
			case ClothingCategory::ARMOR:
				return ImVec4(0.0f, 1.0f, 0.0f, 1.0f);  // Green
			case ClothingCategory::DECALS:
				return ImVec4(1.0f, 0.0f, 1.0f, 1.0f);  // Magenta
			default:
				return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);  // White
		}
	}

	void ImprovedOutfitEditor::RenderImprovedOutfitEditor()
	{
		if (!Self::GetPed())
		{
			ImGui::TextDisabled("Player ped not found");
			return;
		}

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 6.0f));

		// Tab Bar
		if (ImGui::BeginTabBar("OutfitEditorTabs", ImGuiTabBarFlags_None))
		{
			if (ImGui::BeginTabItem("Normal Clothes", nullptr))
			{
				m_CurrentTab = OutfitTab::NORMAL;
				RenderNormalClothesTab();
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Cheated Items", nullptr))
			{
				m_CurrentTab = OutfitTab::CHEATED;
				RenderCheatedClothesTab();
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Special Outfits", nullptr))
			{
				m_CurrentTab = OutfitTab::SPECIAL;
				RenderSpecialClothesTab();
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Props & Accessories", nullptr))
			{
				m_CurrentTab = OutfitTab::PROPS;
				RenderPropsTab();
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Presets", nullptr))
			{
				RenderOutfitPresets();
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}

		ImGui::PopStyleVar();
	}

	void ImprovedOutfitEditor::RenderNormalClothesTab()
	{
		ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "Normal In-Game Clothing");
		ImGui::Separator();

		if (ImGui::InputTextWithHint("##search_normal", "Search clothing...", m_SearchFilter, IM_ARRAYSIZE(m_SearchFilter)))
		{
			// Search updated
		}

		ImGui::BeginChild("NormalClothesChild", ImVec2(0, 300), true);

		// Organize by category
		for (int cat = 0; cat < static_cast<int>(ClothingCategory::DECALS) + 1; cat++)
		{
			ClothingCategory category = static_cast<ClothingCategory>(cat);
			ImGui::PushStyleColor(ImGuiCol_Text, GetCategoryColor(category));

			if (ImGui::CollapsingHeader(GetCategoryName(category), ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::PopStyleColor();

				// Show clothing items in this category
				for (const auto& slot : NORMAL_SLOTS)
				{
					if (slot.category == category && slot.is_normal)
					{
						// Show drawable/texture controls
						ImGui::Indent();
						ImGui::Text("%s", slot.name);
						ImGui::Unindent();
					}
				}
			}
			else
			{
				ImGui::PopStyleColor();
			}
		}

		ImGui::EndChild();
	}

	void ImprovedOutfitEditor::RenderCheatedClothesTab()
	{
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Cheated & Modded Items");
		ImGui::Separator();
		ImGui::TextDisabled("These items are modded or not normally obtainable");

		if (ImGui::InputTextWithHint("##search_cheated", "Search items...", m_SearchFilter, IM_ARRAYSIZE(m_SearchFilter)))
		{
			// Search updated
		}

		ImGui::BeginChild("CheatedClothesChild", ImVec2(0, 300), true);

		ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.5f, 1.0f), "Warning:");
		ImGui::TextDisabled("Using these items may flag your account.\nUse FSL for maximum safety.");

		if (ImGui::CollapsingHeader("Modded Tops", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::BulletText("Police Vest");
			ImGui::BulletText("Military Jacket");
			ImGui::BulletText("Heist Outfit");
			ImGui::BulletText("Custom Designs");
		}

		if (ImGui::CollapsingHeader("Modded Bottoms", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::BulletText("Police Pants");
			ImGui::BulletText("Military Cargo");
			ImGui::BulletText("Special Gear");
		}

		ImGui::EndChild();
	}

	void ImprovedOutfitEditor::RenderSpecialClothesTab()
	{
		ImGui::TextColored(ImVec4(0.2f, 1.0f, 1.0f, 1.0f), "Special & Event Outfits");
		ImGui::Separator();
		ImGui::TextDisabled("Limited-time and special event clothing");

		ImGui::BeginChild("SpecialClothesChild", ImVec2(0, 300), true);

		if (ImGui::CollapsingHeader("Holiday Outfits", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::BulletText("Christmas Sweater");
			ImGui::BulletText("Halloween Costume");
			ImGui::BulletText("Summer Outfit");
		}

		if (ImGui::CollapsingHeader("Job Uniforms", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::BulletText("Delivery Driver");
			ImGui::BulletText("Security Guard");
			ImGui::BulletText("Construction Worker");
		}

		if (ImGui::CollapsingHeader("Event Exclusive", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::BulletText("Diamond Casino Suit");
			ImGui::BulletText("Nightclub VIP");
			ImGui::BulletText("Executive Outfit");
		}

		ImGui::EndChild();
	}

	void ImprovedOutfitEditor::RenderPropsTab()
	{
		ImGui::TextColored(ImVec4(1.0f, 0.65f, 0.0f, 1.0f), "Props & Accessories");
		ImGui::Separator();

		ImGui::BeginColumns("PropsColumns", 2, 0);

		if (ImGui::CollapsingHeader("Hats & Caps", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::BulletText("Baseball Cap");
			ImGui::BulletText("Cowboy Hat");
			ImGui::BulletText("Beanie");
			ImGui::BulletText("Top Hat");
		}

		if (ImGui::CollapsingHeader("Glasses & Eyewear", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::BulletText("Sunglasses");
			ImGui::BulletText("Safety Goggles");
			ImGui::BulletText("Pilot Goggles");
			ImGui::BulletText("Aviators");
		}

		ImGui::NextColumn();

		if (ImGui::CollapsingHeader("Masks & Face Items", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::BulletText("Gas Mask");
			ImGui::BulletText("Ski Mask");
			ImGui::BulletText("Medical Mask");
		}

		if (ImGui::CollapsingHeader("Watches", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::BulletText("Gold Watch");
			ImGui::BulletText("Diamond Watch");
			ImGui::BulletText("Sports Watch");
		}

		ImGui::EndColumns();
	}

	void ImprovedOutfitEditor::RenderOutfitPresets()
	{
		ImGui::TextColored(ImVec4(0.5f, 1.0f, 0.5f, 1.0f), "Outfit Presets & Favorites");
		ImGui::Separator();

		if (ImGui::Button("Save Current Outfit"))
		{
			// Save current outfit
		}
		ImGui::SameLine();
		if (ImGui::Button("Load Outfit"))
		{
			// Load selected outfit
		}

		ImGui::Separator();

		ImGui::TextDisabled("Saved Presets:");

		if (ImGui::Selectable("Business Outfit", m_SelectedPreset == 0))
			m_SelectedPreset = 0;

		if (ImGui::Selectable("Casual Look", m_SelectedPreset == 1))
			m_SelectedPreset = 1;

		if (ImGui::Selectable("Street Style", m_SelectedPreset == 2))
			m_SelectedPreset = 2;

		if (ImGui::Selectable("Formal Attire", m_SelectedPreset == 3))
			m_SelectedPreset = 3;

		ImGui::Separator();

		if (ImGui::Button("Load Selected", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
		{
			// Load preset
		}
	}

	// Helper function
	static const char* GetCategoryName(ImprovedOutfitEditor::ClothingCategory category)
	{
		switch (category)
		{
			case ImprovedOutfitEditor::ClothingCategory::TOPS:
				return "Tops & Shirts";
			case ImprovedOutfitEditor::ClothingCategory::UNDERSHIRTS:
				return "Undershirts";
			case ImprovedOutfitEditor::ClothingCategory::BOTTOMS:
				return "Pants & Shorts";
			case ImprovedOutfitEditor::ClothingCategory::SHOES:
				return "Shoes & Footwear";
			case ImprovedOutfitEditor::ClothingCategory::ACCESSORIES:
				return "Belts & Accessories";
			case ImprovedOutfitEditor::ClothingCategory::BAGS:
				return "Bags & Backpacks";
			case ImprovedOutfitEditor::ClothingCategory::MASKS:
				return "Masks & Face Wear";
			case ImprovedOutfitEditor::ClothingCategory::GLOVES:
				return "Gloves & Hand Wear";
			case ImprovedOutfitEditor::ClothingCategory::ARMOR:
				return "Armor & Protection";
			case ImprovedOutfitEditor::ClothingCategory::DECALS:
				return "Decals & Tattoos";
			default:
				return "Other";
		}
	}
}

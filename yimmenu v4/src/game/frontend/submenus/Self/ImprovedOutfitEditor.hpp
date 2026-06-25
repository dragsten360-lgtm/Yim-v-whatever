#pragma once

// Enhanced Outfit Editor with Better UI and Organization
// Features:
// - Separated Normal, Cheated, and Special Clothing
// - Tabbed Interface (Normal/Cheated/Special)
// - Color-coded Categories
// - Quick Search & Filter
// - Outfit Presets
// - Visual Previews

namespace YimMenu::Features
{
	class ImprovedOutfitEditor
	{
	private:
		// Tab selections
		enum class OutfitTab
		{
			NORMAL,        // Legitimate in-game clothes
			CHEATED,       // Modded/unusual items
			SPECIAL,       // Event/limited items
			PROPS,         // Accessories (hats, glasses, etc)
		};

		enum class ClothingCategory
		{
			TOPS,           // Shirts, jackets
			UNDERSHIRTS,    // Base layers
			BOTTOMS,        // Pants, shorts
			SHOES,          // Footwear
			ACCESSORIES,    // Belts, vests
			BAGS,           // Backpacks, carriers
			MASKS,          // Face coverings
			GLOVES,         // Hands
			ARMOR,          // Protection gear
			DECALS,         // Tattoos, markings
		};

		static OutfitTab m_CurrentTab;
		static ClothingCategory m_CurrentCategory;
		static bool m_ShowAdvanced;
		static char m_SearchFilter[128];
		static int m_SelectedPreset;

		// Helper functions
		static bool IsNormalClothing(int slot, int drawable);
		static bool IsCheatedClothing(int slot, int drawable);
		static bool IsSpecialClothing(int slot, int drawable);
		static ImVec4 GetCategoryColor(ClothingCategory category);

	public:
		static void RenderImprovedOutfitEditor();
		static void RenderNormalClothesTab();
		static void RenderCheatedClothesTab();
		static void RenderSpecialClothesTab();
		static void RenderPropsTab();
		static void RenderOutfitPresets();
	};
}

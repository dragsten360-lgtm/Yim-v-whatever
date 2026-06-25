package com.example.examplemod;

import net.fabricmc.fabric.api.item.v1.FabricItemSettings;
import net.minecraft.entity.EquipmentSlot;
import net.minecraft.item.ArmorItem;
import net.minecraft.item.ArmorMaterial;
import net.minecraft.item.AxeItem;
import net.minecraft.item.ElytraItem;
import net.minecraft.item.HoeItem;
import net.minecraft.item.Item;
import net.minecraft.item.ItemGroup;
import net.minecraft.item.PickaxeItem;
import net.minecraft.item.Rarity;
import net.minecraft.item.ShieldItem;
import net.minecraft.item.ShovelItem;
import net.minecraft.item.SwordItem;
import net.minecraft.item.ToolMaterial;
import net.minecraft.item.Items;
import net.minecraft.recipe.Ingredient;
import net.minecraft.registry.Registries;
import net.minecraft.registry.Registry;
import net.minecraft.sound.SoundEvent;
import net.minecraft.sound.SoundEvents;
import net.minecraft.util.Identifier;

public class ModItems {
    public static final Item MYTHIC_BLADE = new SwordItem(MythicToolMaterial.INSTANCE, 6, -2.4F,
            new FabricItemSettings().group(ItemGroup.COMBAT).fireproof().rarity(Rarity.RARE));
    public static final Item MYTHIC_AXE = new AxeItem(MythicToolMaterial.INSTANCE, 5, -3.0F,
            new FabricItemSettings().group(ItemGroup.TOOLS).fireproof().rarity(Rarity.RARE));
    public static final Item MYTHIC_PICKAXE = new PickaxeItem(MythicToolMaterial.INSTANCE, 1, -2.8F,
            new FabricItemSettings().group(ItemGroup.TOOLS).fireproof().rarity(Rarity.RARE));
    public static final Item MYTHIC_SHOVEL = new ShovelItem(MythicToolMaterial.INSTANCE, 1.5F, -3.0F,
            new FabricItemSettings().group(ItemGroup.TOOLS).fireproof().rarity(Rarity.RARE));
    public static final Item MYTHIC_HOE = new HoeItem(MythicToolMaterial.INSTANCE, -2, new FabricItemSettings()
            .group(ItemGroup.TOOLS).fireproof().rarity(Rarity.RARE));
    
        // Reaper set: blade, tools, and armor
        public static final Item REAPER_BLADE = new SwordItem(ReaperToolMaterial.INSTANCE, 7, -2.2F,
            new FabricItemSettings().group(ItemGroup.COMBAT).fireproof().rarity(Rarity.EPIC));
        public static final Item REAPER_AXE = new AxeItem(ReaperToolMaterial.INSTANCE, 6, -3.0F,
            new FabricItemSettings().group(ItemGroup.TOOLS).fireproof().rarity(Rarity.EPIC));
        public static final Item REAPER_PICKAXE = new PickaxeItem(ReaperToolMaterial.INSTANCE, 1, -2.6F,
            new FabricItemSettings().group(ItemGroup.TOOLS).fireproof().rarity(Rarity.EPIC));
        public static final Item REAPER_SHOVEL = new ShovelItem(ReaperToolMaterial.INSTANCE, 2.0F, -3.0F,
            new FabricItemSettings().group(ItemGroup.TOOLS).fireproof().rarity(Rarity.EPIC));
        public static final Item REAPER_HOE = new HoeItem(ReaperToolMaterial.INSTANCE, -1, new FabricItemSettings()
            .group(ItemGroup.TOOLS).fireproof().rarity(Rarity.EPIC));

        public static final Item REAPER_HELMET = new ArmorItem(ReaperArmorMaterial.INSTANCE, EquipmentSlot.HEAD,
            new FabricItemSettings().group(ItemGroup.COMBAT).fireproof().rarity(Rarity.EPIC));
        public static final Item REAPER_CHESTPLATE = new ArmorItem(ReaperArmorMaterial.INSTANCE, EquipmentSlot.CHEST,
            new FabricItemSettings().group(ItemGroup.COMBAT).fireproof().rarity(Rarity.EPIC));
        public static final Item REAPER_LEGGINGS = new ArmorItem(ReaperArmorMaterial.INSTANCE, EquipmentSlot.LEGS,
            new FabricItemSettings().group(ItemGroup.COMBAT).fireproof().rarity(Rarity.EPIC));
        public static final Item REAPER_BOOTS = new ArmorItem(ReaperArmorMaterial.INSTANCE, EquipmentSlot.FEET,
            new FabricItemSettings().group(ItemGroup.COMBAT).fireproof().rarity(Rarity.EPIC));

        public static final Item MYTHIC_HELMET = new ArmorItem(MythicArmorMaterial.INSTANCE, EquipmentSlot.HEAD,
            new FabricItemSettings().group(ItemGroup.COMBAT).fireproof().rarity(Rarity.RARE));
    public static final Item MYTHIC_CHESTPLATE = new ArmorItem(MythicArmorMaterial.INSTANCE, EquipmentSlot.CHEST,
            new FabricItemSettings().group(ItemGroup.COMBAT).fireproof().rarity(Rarity.RARE));
    public static final Item MYTHIC_LEGGINGS = new ArmorItem(MythicArmorMaterial.INSTANCE, EquipmentSlot.LEGS,
            new FabricItemSettings().group(ItemGroup.COMBAT).fireproof().rarity(Rarity.RARE));
    public static final Item MYTHIC_BOOTS = new ArmorItem(MythicArmorMaterial.INSTANCE, EquipmentSlot.FEET,
            new FabricItemSettings().group(ItemGroup.COMBAT).fireproof().rarity(Rarity.RARE));
    public static final Item MYTHIC_SHIELD = new ShieldItem(new FabricItemSettings().group(ItemGroup.COMBAT)
            .fireproof().maxCount(1).rarity(Rarity.RARE));
    public static final Item MYTHIC_ELYTRA = new ElytraItem(new FabricItemSettings().group(ItemGroup.COMBAT)
            .fireproof().rarity(Rarity.RARE));
    
    public static final Item BOSS_HEART = new Item(new FabricItemSettings().group(ItemGroup.COMBAT)
            .fireproof().rarity(Rarity.EPIC).maxCount(64));

    // Heavenly set: blade, tools, and armor
    public static final Item HEAVENLY_BLADE = new SwordItem(HeavenlyToolMaterial.INSTANCE, 9, -2.1F,
            new FabricItemSettings().group(ItemGroup.COMBAT).fireproof().rarity(Rarity.EPIC));
    public static final Item HEAVENLY_AXE = new AxeItem(HeavenlyToolMaterial.INSTANCE, 8, -2.8F,
            new FabricItemSettings().group(ItemGroup.TOOLS).fireproof().rarity(Rarity.EPIC));
    public static final Item HEAVENLY_PICKAXE = new PickaxeItem(HeavenlyToolMaterial.INSTANCE, 2, -2.6F,
            new FabricItemSettings().group(ItemGroup.TOOLS).fireproof().rarity(Rarity.EPIC));
    public static final Item HEAVENLY_SHOVEL = new ShovelItem(HeavenlyToolMaterial.INSTANCE, 2.5F, -2.8F,
            new FabricItemSettings().group(ItemGroup.TOOLS).fireproof().rarity(Rarity.EPIC));
    public static final Item HEAVENLY_HOE = new HoeItem(HeavenlyToolMaterial.INSTANCE, -1, new FabricItemSettings()
            .group(ItemGroup.TOOLS).fireproof().rarity(Rarity.EPIC));
    
    public static final Item HEAVENLY_HELMET = new ArmorItem(HeavenlyArmorMaterial.INSTANCE, EquipmentSlot.HEAD,
            new FabricItemSettings().group(ItemGroup.COMBAT).fireproof().rarity(Rarity.EPIC));
    public static final Item HEAVENLY_CHESTPLATE = new ArmorItem(HeavenlyArmorMaterial.INSTANCE, EquipmentSlot.CHEST,
            new FabricItemSettings().group(ItemGroup.COMBAT).fireproof().rarity(Rarity.EPIC));
    public static final Item HEAVENLY_LEGGINGS = new ArmorItem(HeavenlyArmorMaterial.INSTANCE, EquipmentSlot.LEGS,
            new FabricItemSettings().group(ItemGroup.COMBAT).fireproof().rarity(Rarity.EPIC));
    public static final Item HEAVENLY_BOOTS = new ArmorItem(HeavenlyArmorMaterial.INSTANCE, EquipmentSlot.FEET,
            new FabricItemSettings().group(ItemGroup.COMBAT).fireproof().rarity(Rarity.EPIC));
    public static final Item HEAVENLY_SHIELD = new ShieldItem(new FabricItemSettings().group(ItemGroup.COMBAT)
            .fireproof().maxCount(1).rarity(Rarity.EPIC));
    public static final Item HEAVENLY_ELYTRA = new ElytraItem(new FabricItemSettings().group(ItemGroup.COMBAT)
            .fireproof().rarity(Rarity.EPIC));

    public static void registerModItems() {
        Registry.register(Registries.ITEM, new Identifier("examplemod", "mythic_blade"), MYTHIC_BLADE);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "mythic_axe"), MYTHIC_AXE);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "mythic_pickaxe"), MYTHIC_PICKAXE);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "mythic_shovel"), MYTHIC_SHOVEL);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "mythic_hoe"), MYTHIC_HOE);
        // Reaper set registration
        Registry.register(Registries.ITEM, new Identifier("examplemod", "reaper_blade"), REAPER_BLADE);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "reaper_axe"), REAPER_AXE);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "reaper_pickaxe"), REAPER_PICKAXE);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "reaper_shovel"), REAPER_SHOVEL);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "reaper_hoe"), REAPER_HOE);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "reaper_helmet"), REAPER_HELMET);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "reaper_chestplate"), REAPER_CHESTPLATE);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "reaper_leggings"), REAPER_LEGGINGS);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "reaper_boots"), REAPER_BOOTS);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "mythic_helmet"), MYTHIC_HELMET);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "mythic_chestplate"), MYTHIC_CHESTPLATE);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "mythic_leggings"), MYTHIC_LEGGINGS);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "mythic_boots"), MYTHIC_BOOTS);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "mythic_shield"), MYTHIC_SHIELD);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "mythic_elytra"), MYTHIC_ELYTRA);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "heavenly_blade"), HEAVENLY_BLADE);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "heavenly_axe"), HEAVENLY_AXE);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "heavenly_pickaxe"), HEAVENLY_PICKAXE);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "heavenly_shovel"), HEAVENLY_SHOVEL);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "heavenly_hoe"), HEAVENLY_HOE);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "heavenly_helmet"), HEAVENLY_HELMET);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "heavenly_chestplate"), HEAVENLY_CHESTPLATE);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "heavenly_leggings"), HEAVENLY_LEGGINGS);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "heavenly_boots"), HEAVENLY_BOOTS);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "heavenly_shield"), HEAVENLY_SHIELD);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "heavenly_elytra"), HEAVENLY_ELYTRA);
        Registry.register(Registries.ITEM, new Identifier("examplemod", "boss_heart"), BOSS_HEART);
    }

    private enum MythicToolMaterial implements ToolMaterial {
        INSTANCE;

        @Override
        public int getDurability() {
            return 2500;
        }

        @Override
        public float getMiningSpeedMultiplier() {
            return 12.0F;
        }

        @Override
        public float getAttackDamage() {
            return 4.0F;
        }

        @Override
        public int getMiningLevel() {
            return 4;
        }

        @Override
        public int getEnchantability() {
            return 22;
        }

        @Override
        public Ingredient getRepairIngredient() {
            return Ingredient.ofItems(Items.NETHERITE_INGOT);
        }
    }

    private enum MythicArmorMaterial implements ArmorMaterial {
        INSTANCE;

        private static final int[] BASE_DURABILITY = new int[] {13, 15, 16, 11};
        private static final int[] PROTECTION_VALUES = new int[] {3, 6, 8, 3};

        @Override
        public int getDurability(EquipmentSlot slot) {
            return BASE_DURABILITY[slot.getEntitySlotId()] * 37;
        }

        @Override
        public int getProtectionAmount(EquipmentSlot slot) {
            return PROTECTION_VALUES[slot.getEntitySlotId()];
        }

        @Override
        public int getEnchantability() {
            return 22;
        }

        @Override
        public SoundEvent getEquipSound() {
            return SoundEvents.ITEM_ARMOR_EQUIP_NETHERITE;
        }

        @Override
        public Ingredient getRepairIngredient() {
            return Ingredient.ofItems(Items.NETHERITE_INGOT);
        }

        @Override
        public String getName() {
            return "examplemod:mythic";
        }

        @Override
        public float getToughness() {
            return 3.0F;
        }

        @Override
        public float getKnockbackResistance() {
            return 0.1F;
        }
    }

    private enum ReaperToolMaterial implements ToolMaterial {
        INSTANCE;

        @Override
        public int getDurability() {
            return 3000;
        }

        @Override
        public float getMiningSpeedMultiplier() {
            return 14.0F;
        }

        @Override
        public float getAttackDamage() {
            return 5.0F;
        }

        @Override
        public int getMiningLevel() {
            return 4;
        }

        @Override
        public int getEnchantability() {
            return 25;
        }

        @Override
        public Ingredient getRepairIngredient() {
            return Ingredient.ofItems(Items.NETHERITE_INGOT);
        }
    }

    private enum ReaperArmorMaterial implements ArmorMaterial {
        INSTANCE;

        private static final int[] BASE_DURABILITY = new int[] {13, 15, 16, 11};
        private static final int[] PROTECTION_VALUES = new int[] {4, 7, 9, 4};

        @Override
        public int getDurability(EquipmentSlot slot) {
            return BASE_DURABILITY[slot.getEntitySlotId()] * 40;
        }

        @Override
        public int getProtectionAmount(EquipmentSlot slot) {
            return PROTECTION_VALUES[slot.getEntitySlotId()];
        }

        @Override
        public int getEnchantability() {
            return 28;
        }

        @Override
        public SoundEvent getEquipSound() {
            return SoundEvents.ITEM_ARMOR_EQUIP_NETHERITE;
        }

        @Override
        public Ingredient getRepairIngredient() {
            return Ingredient.ofItems(Items.NETHERITE_INGOT);
        }

        @Override
        public String getName() {
            return "examplemod:reaper";
        }

        @Override
        public float getToughness() {
            return 4.0F;
        }

        @Override
        public float getKnockbackResistance() {
            return 0.15F;
        }
    }

    private enum HeavenlyToolMaterial implements ToolMaterial {
        INSTANCE;

        @Override
        public int getDurability() {
            return 3800;
        }

        @Override
        public float getMiningSpeedMultiplier() {
            return 16.0F;
        }

        @Override
        public float getAttackDamage() {
            return 6.5F;
        }

        @Override
        public int getMiningLevel() {
            return 4;
        }

        @Override
        public int getEnchantability() {
            return 30;
        }

        @Override
        public Ingredient getRepairIngredient() {
            return Ingredient.ofItems(Items.GOLD_INGOT);
        }
    }

    private enum HeavenlyArmorMaterial implements ArmorMaterial {
        INSTANCE;

        private static final int[] BASE_DURABILITY = new int[] {13, 15, 16, 11};
        private static final int[] PROTECTION_VALUES = new int[] {3, 5, 7, 3};

        @Override
        public int getDurability(EquipmentSlot slot) {
            return BASE_DURABILITY[slot.getEntitySlotId()] * 35;
        }

        @Override
        public int getProtectionAmount(EquipmentSlot slot) {
            return PROTECTION_VALUES[slot.getEntitySlotId()];
        }

        @Override
        public int getEnchantability() {
            return 32;
        }

        @Override
        public SoundEvent getEquipSound() {
            return SoundEvents.ITEM_ARMOR_EQUIP_GOLD;
        }

        @Override
        public Ingredient getRepairIngredient() {
            return Ingredient.ofItems(Items.GOLD_INGOT);
        }

        @Override
        public String getName() {
            return "examplemod:heavenly";
        }

        @Override
        public float getToughness() {
            return 5.0F;
        }

        @Override
        public float getKnockbackResistance() {
            return 0.2F;
        }
    }
}

#pragma once

#include "RE/B/BSContainer.h"
#include "RE/B/BSTList.h"
#include "RE/F/FormTypes.h"
#include "RE/M/MemoryManager.h"
#include "RE/T/TESBoundObject.h"

namespace RE
{
	class ExtraDataList;
	class InventoryEntryData;
	class TESBoundObject;

	class InventoryChanges
	{
	public:
		struct ARMOR_SLOTS
		{
		public:
			enum class ArmorSlot : std::uint32_t
			{
				kHead = 30,
				kHair = 31,
				kBody = 32,
				kHands = 33,
				kForearms = 34,
				kAmulet = 35,
				kRing = 36,
				kFeet = 37,
				kCalves = 38,
				kShield = 39,
				kTail = 40,
				kLongHair = 41,
				kCirclet = 42,
				kEars = 43,
				kDecapitateHead = 50,
				kDecapitate = 51,
				kFX01 = 61
			};
		};
		using ArmorSlot = ARMOR_SLOTS::ArmorSlot;

		class IItemChangeVisitor
		{
		public:
			inline static constexpr auto RTTI = RTTI_InventoryChanges__IItemChangeVisitor;
			inline static constexpr auto VTABLE = VTABLE_InventoryChanges__IItemChangeVisitor;

			virtual ~IItemChangeVisitor();  // 00

			// add
			virtual BSContainer::ForEachResult Visit(InventoryEntryData* a_entryData) = 0;                                                                                // 01
			virtual bool                       ShouldVisit([[maybe_unused]] InventoryEntryData* a_entryData, [[maybe_unused]] TESBoundObject* a_object) { return true; }  // 02
			virtual BSContainer::ForEachResult Unk_03(InventoryEntryData* a_entryData, [[maybe_unused]] void* a_arg2, bool* a_arg3)                                       // 03
			{
				*a_arg3 = true;
				return Visit(a_entryData);
			}
		};
		static_assert(sizeof(IItemChangeVisitor) == 0x8);

		InventoryChanges();
		explicit InventoryChanges(TESObjectREFR* a_ref);
		~InventoryChanges();

		void           AddEntryData(InventoryEntryData* a_entry);
		TESObjectARMO* GetArmorInSlot(ArmorSlot a_slot);
		float          GetInventoryWeight();
		std::uint16_t  GetNextUniqueID();
		std::uint32_t  GetWornMask();
		void           InitFromContainerExtra();
		void           InitLeveledItems();
		void           InitOutfitItems(BGSOutfit* a_outfit, std::uint16_t a_npcLevel);
		void           InitScripts();
		void           RemoveFavorite(InventoryEntryData* a_entry, ExtraDataList* a_itemList);
		void           RemoveAllItems(TESObjectREFR* a_ref, TESObjectREFR* a_moveToRef, bool a_arg4, bool a_keepOwnership, bool a_arg6);
		void           SendContainerChangedEvent(ExtraDataList* a_itemExtraList, TESObjectREFR* a_fromRefr, TESForm* a_item, std::int32_t a_count);
		void           SetFavorite(InventoryEntryData* a_entry, ExtraDataList* a_itemList);
		void           SetUniqueID(ExtraDataList* a_itemList, TESForm* a_oldForm, TESForm* a_newForm);
		void           GenerateLeveledListChanges();
		std::int16_t   GetItemCount(RE::TESBoundObject* a_obj);
		void           VisitInventory(IItemChangeVisitor& visitor);
		void           VisitWornItems(IItemChangeVisitor& visitor);

		TES_HEAP_REDEFINE_NEW();

		// members
		BSSimpleList<InventoryEntryData*>* entryList{ nullptr };  // 00
		TESObjectREFR*                     owner{ nullptr };      // 08
		float                              totalWeight{ 0.0F };   // 10
		float                              armorWeight{ 0.0F };   // 14
		bool                               changed{ false };      // 18
		std::uint8_t                       unk19{ 0 };            // 19
		std::uint8_t                       unk1A{ 0 };            // 1A
		std::uint8_t                       unk1B{ 0 };            // 1B
		std::uint32_t                      unk1C{ 0 };            // 1C

	private:
		InventoryChanges* Ctor(TESObjectREFR* a_ref);
		void              Dtor();
	};
	static_assert(sizeof(InventoryChanges) == 0x20);
}

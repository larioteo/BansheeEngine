//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsEditorPrerequisites.h"
#include "Settings/BsSettings.h"
#include "Reflection/BsRTTIType.h"

namespace bs
{
	using namespace impl;

	/** @cond RTTI */
	/** @addtogroup RTTI-Impl-Editor
	 *  @{
	 */

	BS_ALLOW_MEMCPY_SERIALIZATION(SettingsPrimitiveValue)
	BS_ALLOW_MEMCPY_SERIALIZATION(SettingsKeyInfo)

	/**
	 * RTTIPlainType for TSettingsValue.
	 *
	 * @see		RTTIPlainType
	 */
	template<class T> struct RTTIPlainType<TSettingsValue<T>>
	{
		enum { id = TID_SettingsValue }; enum { hasDynamicSize = 1 };

		/** @copydoc RTTIPlainType::toMemory */
		static void toMemory(const TSettingsValue<T>& data, char* memory)
		{
			UINT32 size = sizeof(UINT32);
			char* memoryStart = memory;
			memory += sizeof(UINT32);

			UINT32 keySize = rttiGetElemSize(data.key);
			RTTIPlainType<String>::toMemory(data.key, memory);

			memory += keySize;
			size += keySize;

			UINT32 valueSize = rttiGetElemSize(data.value);
			RTTIPlainType<T>::toMemory(data.value, memory);

			memory += valueSize;
			size += valueSize;

			memcpy(memoryStart, &size, sizeof(UINT32));
		}

		/** @copydoc RTTIPlainType::fromMemory */
		static UINT32 fromMemory(TSettingsValue<T>& data, char* memory)
		{
			UINT32 size = 0;
			memcpy(&size, memory, sizeof(UINT32));
			memory += sizeof(UINT32);

			UINT32 keySize = RTTIPlainType<String>::fromMemory(data.key, memory);
			memory += keySize;

			UINT32 secondSize = RTTIPlainType<T>::fromMemory(data.value, memory);
			memory += secondSize;

			return size;
		}

		/** @copydoc RTTIPlainType::getDynamicSize */
		static UINT32 getDynamicSize(const TSettingsValue<T>& data)
		{
			UINT64 dataSize = sizeof(UINT32);
			dataSize += rttiGetElemSize(data.key);
			dataSize += rttiGetElemSize(data.value);

			assert(dataSize <= std::numeric_limits<UINT32>::max());

			return (UINT32)dataSize;
		}
	};

	namespace impl
	{
		class SettingsObjectValueRTTI : public RTTIType <SettingsObjectValue, IReflectable, SettingsObjectValueRTTI>
		{
		private:
			BS_BEGIN_RTTI_MEMBERS
				BS_RTTI_MEMBER_PLAIN(key, 0)
				BS_RTTI_MEMBER_REFLPTR(value, 1)
			BS_END_RTTI_MEMBERS
		public:
			const String& getRTTIName() override
			{
				static String name = "SettingsObjectValue";
				return name;
			}

			UINT32 getRTTIId() override
			{
				return TID_SettingsObjectValue;
			}

			SPtr<IReflectable> newRTTIObject() override
			{
				return bs_shared_ptr_new<SettingsObjectValue>();
			}
		};
	}

	class SettingsRTTI : public RTTIType <Settings, IReflectable, SettingsRTTI>
	{
	private:
		BS_BEGIN_RTTI_MEMBERS
			BS_RTTI_MEMBER_PLAIN(mKeyLookup, 17)
			BS_RTTI_MEMBER_PLAIN(mPrimitives, 18)
			BS_RTTI_MEMBER_PLAIN(mStrings, 19)
			BS_RTTI_MEMBER_REFL_ARRAY(mObjects, 20)
		BS_END_RTTI_MEMBERS
	public:
		const String& getRTTIName() override
		{
			static String name = "Settings";
			return name;
		}

		UINT32 getRTTIId() override
		{
			return TID_Settings;
		}

		SPtr<IReflectable> newRTTIObject() override
		{
			return bs_shared_ptr_new<Settings>();
		}
	};

	/** @} */
	/** @endcond */
}
//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsEditorPrerequisites.h"
#include "Settings/BsSettings.h"
#include "Reflection/BsRTTIType.h"
#include "Reflection/BsRTTIPlain.h"
#include "RTTI/BsStdRTTI.h"
#include "RTTI/BsStringRTTI.h"

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
		static uint32_t toMemory(const TSettingsValue<T>& data, Bitstream& stream, const RTTIFieldInfo& fieldInfo, bool compress)
		{
			return rtti_write_with_size_header(stream, [&data, &stream]()
			{
				uint32_t size = 0;
				size += rtti_write(data.key, stream);
				size += rtti_write(data.value, stream);

				return size;
			});
		}

		/** @copydoc RTTIPlainType::fromMemory */
		static uint32_t fromMemory(TSettingsValue<T>& data, Bitstream& stream, const RTTIFieldInfo& fieldInfo, bool compress)
		{
			uint32_t size = 0;
			rtti_read(size, stream);
			rtti_read(data.key, stream);
			rtti_read(data.value, stream);

			return size;
		}

		/** @copydoc RTTIPlainType::getSize */
		static uint32_t getSize(const TSettingsValue<T>& data)
		{
			uint64_t dataSize = sizeof(uint32_t);
			dataSize += rtti_size(data.key);
			dataSize += rtti_size(data.value);

			assert(dataSize <= std::numeric_limits<uint32_t>::max());

			return (uint32_t)dataSize;
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
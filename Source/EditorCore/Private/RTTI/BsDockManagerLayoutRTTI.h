//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsEditorPrerequisites.h"
#include "EditorWindow/BsDockManagerLayout.h"
#include "Reflection/BsRTTIType.h"
#include "Reflection/BsRTTIPlain.h"
#include "RTTI/BsStdRTTI.h"
#include "RTTI/BsStringRTTI.h"

namespace bs
{
	/** @cond RTTI */
	/** @addtogroup RTTI-Impl-Editor
	 *  @{
	 */

	class DockManagerLayoutRTTI : public RTTIType<DockManagerLayout, IReflectable, DockManagerLayoutRTTI>
	{
	private:
		DockManagerLayout::Entry& getRootEntry(DockManagerLayout* obj) { return obj->mRootEntry; }
		void setRootEntry(DockManagerLayout* obj, DockManagerLayout::Entry& val) { obj->mRootEntry = val; } 

		bool& getIsMaximized(DockManagerLayout* obj) { return obj->mIsMaximized; }
		void setIsMaximized(DockManagerLayout* obj, bool& val) { obj->mIsMaximized = val; }

		Vector<String>& getMaximizedWidgetNames(DockManagerLayout* obj) { return obj->mMaximizedWidgetNames; }
		void setMaximizedWidgetNames(DockManagerLayout* obj, Vector<String>& val) { obj->mMaximizedWidgetNames = val; }

	public:
		DockManagerLayoutRTTI()
		{
			addPlainField("mRootEntry", 0, &DockManagerLayoutRTTI::getRootEntry, &DockManagerLayoutRTTI::setRootEntry);
			addPlainField("mIsMaximized", 1, &DockManagerLayoutRTTI::getIsMaximized, &DockManagerLayoutRTTI::setIsMaximized);
			addPlainField("mMaximizedWidgetNames", 2, &DockManagerLayoutRTTI::getMaximizedWidgetNames, &DockManagerLayoutRTTI::setMaximizedWidgetNames);
		}

		void onDeserializationEnded(IReflectable* obj, SerializationContext* context) override
		{
			DockManagerLayout* layout = static_cast<DockManagerLayout*>(obj);

			Stack<DockManagerLayout::Entry*> todo;
			todo.push(&layout->mRootEntry);

			while (!todo.empty())
			{
				DockManagerLayout::Entry* current = todo.top();
				todo.pop();

				if (!current->isLeaf)
				{
					current->children[0]->parent = current;
					current->children[1]->parent = current;

					todo.push(current->children[0]);
					todo.push(current->children[1]);
				}
			}
		}

		const String& getRTTIName() override
		{
			static String name = "DockManagerLayout";
			return name;
		}

		UINT32 getRTTIId() override
		{
			return TID_DockManagerLayout;
		}

		SPtr<IReflectable> newRTTIObject() override
		{
			return bs_shared_ptr_new<DockManagerLayout>();
		}
	};

	template<> struct RTTIPlainType<bs::DockManagerLayout::Entry>
	{	
		enum { id = bs::TID_DockManagerLayoutEntry }; enum { hasDynamicSize = 1 };

		static uint32_t toMemory(const bs::DockManagerLayout::Entry& data, Bitstream& stream, const RTTIFieldInfo& info)
		{ 
			return rtti_write_with_size_header(stream, [&data, &stream]()
			{
				uint32_t size = 0;
				size += rttiWriteElem(data.isLeaf, stream);
				size += rttiWriteElem(data.horizontalSplit, stream);
				size += rttiWriteElem(data.splitPosition, stream);
				size += rttiWriteElem(data.widgetNames, stream);

				if (!data.isLeaf)
				{
					size += rttiWriteElem(*data.children[0], stream);
					size += rttiWriteElem(*data.children[1], stream);
				}

				return size;
			});
		}

		static uint32_t fromMemory(bs::DockManagerLayout::Entry& data, Bitstream& stream, const RTTIFieldInfo& info)
		{ 
			uint32_t size = 0;
			rttiReadElem(size, stream);

			rttiReadElem(data.isLeaf, stream);
			rttiReadElem(data.horizontalSplit, stream);
			rttiReadElem(data.splitPosition, stream);
			rttiReadElem(data.widgetNames, stream);

			if(!data.isLeaf)
			{
				data.children[0] = bs_new<bs::DockManagerLayout::Entry>();
				data.children[1] = bs_new<bs::DockManagerLayout::Entry>();

				rttiReadElem(*data.children[0], stream);
				rttiReadElem(*data.children[1], stream);
				
				data.children[0]->parent = &data;
				data.children[1]->parent = &data;
			}

			return size;
		}

		static uint32_t getDynamicSize(const bs::DockManagerLayout::Entry& data)	
		{ 
			uint64_t dataSize = sizeof(uint32_t) + rttiGetElemSize(data.isLeaf) + rttiGetElemSize(data.horizontalSplit) + 
				rttiGetElemSize(data.splitPosition) + rttiGetElemSize(data.widgetNames);

			if(!data.isLeaf)
			{
				dataSize += rttiGetElemSize(*data.children[0]);
				dataSize += rttiGetElemSize(*data.children[1]);
			}

#if BS_DEBUG_MODE
			if(dataSize > std::numeric_limits<uint32_t>::max())
			{
				__string_throwDataOverflowException();
			}
#endif

			return (uint32_t)dataSize;
		}	
	}; 

	/** @} */
	/** @endcond */
}
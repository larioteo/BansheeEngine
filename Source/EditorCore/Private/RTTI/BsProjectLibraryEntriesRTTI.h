//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsEditorPrerequisites.h"
#include "Reflection/BsRTTIType.h"
#include "Library/BsProjectLibraryEntries.h"
#include "String/BsUnicode.h"

namespace bs
{
	/** @cond RTTI */
	/** @addtogroup RTTI-Impl-Editor
	 *  @{
	 */

	class ProjectLibraryEntriesRTTI : public RTTIType<ProjectLibraryEntries, IReflectable, ProjectLibraryEntriesRTTI>
	{
	private:
		ProjectLibrary::DirectoryEntry& getRootElement(ProjectLibraryEntries* obj) { return *obj->mRootEntry; }
		void setRootElement(ProjectLibraryEntries* obj, ProjectLibrary::DirectoryEntry& val)
		{
			obj->mRootEntry = bs_ushared_ptr_new<ProjectLibrary::DirectoryEntry>(val);

			for(auto& child : obj->mRootEntry->mChildren)
				child->parent = obj->mRootEntry.get();
		} 

	public:
		ProjectLibraryEntriesRTTI()
		{
			addPlainField("mRootElement", 0, &ProjectLibraryEntriesRTTI::getRootElement, &ProjectLibraryEntriesRTTI::setRootElement);
		}

		virtual const String& getRTTIName()
		{
			static String name = "ProjectLibraryEntries";
			return name;
		}

		virtual UINT32 getRTTIId()
		{
			return TID_ProjectLibraryEntries;
		}

		virtual SPtr<IReflectable> newRTTIObject()
		{
			return ProjectLibraryEntries::createEmpty();
		}
	};

	template<> struct RTTIPlainType<ProjectLibrary::FileEntry>
	{	
		enum { id = TID_ProjectLibraryResEntry }; enum { hasDynamicSize = 1 };

		static void toMemory(const ProjectLibrary::FileEntry& data, char* memory)
		{ 
			UINT32 size = 0;
			char* memoryStart = memory;
			memory += sizeof(UINT32);
			size += sizeof(UINT32);

			// For compatibility, encoding the name as a wide string
			WString elemName = UTF8::toWide(data.elementName);

			UINT32 type = (UINT32)data.type;
			memory = rttiWriteElem(type, memory, size);
			memory = rttiWriteElem(data.path, memory, size);
			memory = rttiWriteElem(elemName, memory, size);
			memory = rttiWriteElem(data.lastUpdateTime, memory, size);

			memcpy(memoryStart, &size, sizeof(UINT32));
		}

		static UINT32 fromMemory(ProjectLibrary::FileEntry& data, char* memory)
		{ 
			UINT32 size = 0;
			memcpy(&size, memory, sizeof(UINT32));
			memory += sizeof(UINT32);

			UINT32 type;
			memory = rttiReadElem(type, memory);
			data.type = (ProjectLibrary::LibraryEntryType)type;

			memory = rttiReadElem(data.path, memory);

			WString elemName;
			memory = rttiReadElem(elemName, memory);
			data.elementName = UTF8::fromWide(elemName);
			data.elementNameHash = bs_hash(UTF8::toLower(data.elementName));

			memory = rttiReadElem(data.lastUpdateTime, memory);

			return size;
		}

		static UINT32 getDynamicSize(const ProjectLibrary::FileEntry& data)	
		{ 
			WString elemName = UTF8::toWide(data.elementName);

			UINT64 dataSize = sizeof(UINT32) + rttiGetElemSize(data.type) + rttiGetElemSize(data.path) + 
				rttiGetElemSize(elemName) + rttiGetElemSize(data.lastUpdateTime);

#if BS_DEBUG_MODE
			if(dataSize > std::numeric_limits<UINT32>::max())
			{
				__string_throwDataOverflowException();
			}
#endif

			return (UINT32)dataSize;
		}	
	}; 

	template<> struct RTTIPlainType<ProjectLibrary::DirectoryEntry>
	{	
		enum { id = TID_ProjectLibraryDirEntry }; enum { hasDynamicSize = 1 };

		static void toMemory(const ProjectLibrary::DirectoryEntry& data, char* memory)
		{ 
			UINT32 size = 0;
			char* memoryStart = memory;
			memory += sizeof(UINT32);
			size += sizeof(UINT32);

			// For compatibility, encoding the name as a wide string
			WString elemName = UTF8::toWide(data.elementName);

			memory = rttiWriteElem(data.type, memory, size);
			memory = rttiWriteElem(data.path, memory, size);
			memory = rttiWriteElem(elemName, memory, size);

			UINT32 numChildren = (UINT32)data.mChildren.size();
			memory = rttiWriteElem(numChildren, memory, size);

			for(auto& child : data.mChildren)
			{
				if(child->type == ProjectLibrary::LibraryEntryType::File)
				{
					auto* childResEntry = static_cast<ProjectLibrary::FileEntry*>(child.get());
					memory = rttiWriteElem(*childResEntry, memory, size);
				}
				else if(child->type == ProjectLibrary::LibraryEntryType::Directory)
				{
					auto* childDirEntry = static_cast<ProjectLibrary::DirectoryEntry*>(child.get());
					memory = rttiWriteElem(*childDirEntry, memory, size);
				}
			}

			memcpy(memoryStart, &size, sizeof(UINT32));
		}

		static UINT32 fromMemory(ProjectLibrary::DirectoryEntry& data, char* memory)
		{
			UINT32 size = 0;
			memcpy(&size, memory, sizeof(UINT32));
			memory += sizeof(UINT32);

			memory = rttiReadElem(data.type, memory);
			memory = rttiReadElem(data.path, memory);

			WString elemName;
			memory = rttiReadElem(elemName, memory);
			data.elementName = UTF8::fromWide(elemName);
			data.elementNameHash = bs_hash(UTF8::toLower(data.elementName));

			UINT32 numChildren = 0;
			memory = rttiReadElem(numChildren, memory);

			for (UINT32 i = 0; i < numChildren; i++)
			{
				ProjectLibrary::LibraryEntryType childType = ProjectLibrary::LibraryEntryType::File;
				rttiReadElem(childType, memory + sizeof(UINT32)); // Skip ahead to get type

				if (childType == ProjectLibrary::LibraryEntryType::File)
				{
					USPtr<ProjectLibrary::FileEntry> childResEntry = bs_ushared_ptr_new<ProjectLibrary::FileEntry>();
					// Note: Assumes that ProjectLibrary takes care of the cleanup
					memory = rttiReadElem(*childResEntry, memory);

					childResEntry->parent = &data;
					data.mChildren.push_back(childResEntry);
				}
				else if (childType == ProjectLibrary::LibraryEntryType::Directory)
				{
					USPtr<ProjectLibrary::DirectoryEntry> childDirEntry = bs_ushared_ptr_new<ProjectLibrary::DirectoryEntry>();
					// Note: Assumes that ProjectLibrary takes care of the cleanup
					memory = rttiReadElem(*childDirEntry, memory);

					childDirEntry->parent = &data;
					data.mChildren.push_back(childDirEntry);
				}
			}

			return size;
		}

		static UINT32 getDynamicSize(const ProjectLibrary::DirectoryEntry& data)
		{ 
			WString elemName = UTF8::toWide(data.elementName);
			UINT64 dataSize = sizeof(UINT32) + rttiGetElemSize(data.type) + rttiGetElemSize(data.path) + 
				rttiGetElemSize(elemName);

			dataSize += sizeof(UINT32);

			for(auto& child : data.mChildren)
			{
				if(child->type == ProjectLibrary::LibraryEntryType::File)
				{
					ProjectLibrary::FileEntry* childResEntry = static_cast<ProjectLibrary::FileEntry*>(child.get());
					dataSize += rttiGetElemSize(*childResEntry);
				}
				else if(child->type == ProjectLibrary::LibraryEntryType::Directory)
				{
					ProjectLibrary::DirectoryEntry* childDirEntry = static_cast<ProjectLibrary::DirectoryEntry*>(child.get());
					dataSize += rttiGetElemSize(*childDirEntry);
				}
			}

#if BS_DEBUG_MODE
			if(dataSize > std::numeric_limits<UINT32>::max())
			{
				__string_throwDataOverflowException();
			}
#endif

			return (UINT32)dataSize;
		}	
	};

	/** @} */
	/** @endcond */
}

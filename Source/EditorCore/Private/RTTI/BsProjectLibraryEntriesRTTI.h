//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsEditorPrerequisites.h"
#include "Reflection/BsRTTIType.h"
#include "Reflection/BsRTTIPlain.h"
#include "RTTI/BsPathRTTI.h"
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

		static uint32_t toMemory(const ProjectLibrary::FileEntry& data, Bitstream& stream, const RTTIFieldInfo& info)
		{ 
			return rtti_write_with_size_header(stream, [&data, &stream]()
				{
				uint32_t size = 0;

				// For compatibility, encoding the name as a wide string
				WString elemName = UTF8::toWide(data.elementName);

				auto type = (uint32_t)data.type;
				size += rttiWriteElem(type, stream);
				size += rttiWriteElem(data.path, stream);
				size += rttiWriteElem(elemName, stream);
				size += rttiWriteElem(data.lastUpdateTime, stream);

				return size;

			});
		}

		static uint32_t fromMemory(ProjectLibrary::FileEntry& data, Bitstream& stream, const RTTIFieldInfo& info)
		{ 
			uint32_t size = 0;
			rttiReadElem(size, stream);

			uint32_t type;
			rttiReadElem(type, stream);
			data.type = (ProjectLibrary::LibraryEntryType)type;

			rttiReadElem(data.path, stream);

			WString elemName;
			rttiReadElem(elemName, stream);
			data.elementName = UTF8::fromWide(elemName);
			data.elementNameHash = bs_hash(UTF8::toLower(data.elementName));

			rttiReadElem(data.lastUpdateTime, stream);

			return size;
		}

		static uint32_t getDynamicSize(const ProjectLibrary::FileEntry& data)	
		{ 
			WString elemName = UTF8::toWide(data.elementName);

			uint64_t dataSize = sizeof(uint32_t) + rttiGetElemSize(data.type) + rttiGetElemSize(data.path) + 
				rttiGetElemSize(elemName) + rttiGetElemSize(data.lastUpdateTime);

#if BS_DEBUG_MODE
			if(dataSize > std::numeric_limits<uint32_t>::max())
			{
				__string_throwDataOverflowException();
			}
#endif

			return (uint32_t)dataSize;
		}	
	}; 

	template<> struct RTTIPlainType<ProjectLibrary::DirectoryEntry>
	{	
		enum { id = TID_ProjectLibraryDirEntry }; enum { hasDynamicSize = 1 };

		static uint32_t toMemory(const ProjectLibrary::DirectoryEntry& data, Bitstream& stream, const RTTIFieldInfo& info)
		{ 
			return rtti_write_with_size_header(stream, [&data, &stream]()
			{
				uint32_t size = 0;

				// For compatibility, encoding the name as a wide string
				WString elemName = UTF8::toWide(data.elementName);

				size += rttiWriteElem(data.type, stream);
				size += rttiWriteElem(data.path, stream);
				size += rttiWriteElem(elemName, stream);

				uint32_t numChildren = (UINT32)data.mChildren.size();
				size += rttiWriteElem(numChildren, stream);

				for(auto& child : data.mChildren)
				{
					if(child->type == ProjectLibrary::LibraryEntryType::File)
					{
						auto* childResEntry = static_cast<ProjectLibrary::FileEntry*>(child.get());
						size = rttiWriteElem(*childResEntry, stream);
					}
					else if(child->type == ProjectLibrary::LibraryEntryType::Directory)
					{
						auto* childDirEntry = static_cast<ProjectLibrary::DirectoryEntry*>(child.get());
						size += rttiWriteElem(*childDirEntry, stream);
					}
				}

				return size;
			});
		}

		static uint32_t fromMemory(ProjectLibrary::DirectoryEntry& data, Bitstream& stream, const RTTIFieldInfo& info)
		{
			uint32_t size = 0;
			rttiReadElem(size, stream);

			rttiReadElem(data.type, stream);
			rttiReadElem(data.path, stream);

			WString elemName;
			rttiReadElem(elemName, stream);
			data.elementName = UTF8::fromWide(elemName);
			data.elementNameHash = bs_hash(UTF8::toLower(data.elementName));

			UINT32 numChildren = 0;
			rttiReadElem(numChildren, stream);

			for (UINT32 i = 0; i < numChildren; i++)
			{
				ProjectLibrary::LibraryEntryType childType = ProjectLibrary::LibraryEntryType::File;

				uint32_t prevLoc = stream.tell();
				stream.skipBytes(sizeof(uint32_t)); // Skip ahead to get the type
				rttiReadElem(childType, stream);
				stream.seek(prevLoc);

				if (childType == ProjectLibrary::LibraryEntryType::File)
				{
					USPtr<ProjectLibrary::FileEntry> childResEntry = bs_ushared_ptr_new<ProjectLibrary::FileEntry>();
					// Note: Assumes that ProjectLibrary takes care of the cleanup
					rttiReadElem(*childResEntry, stream);

					childResEntry->parent = &data;
					data.mChildren.push_back(childResEntry);
				}
				else if (childType == ProjectLibrary::LibraryEntryType::Directory)
				{
					USPtr<ProjectLibrary::DirectoryEntry> childDirEntry = bs_ushared_ptr_new<ProjectLibrary::DirectoryEntry>();
					// Note: Assumes that ProjectLibrary takes care of the cleanup
					rttiReadElem(*childDirEntry, stream);

					childDirEntry->parent = &data;
					data.mChildren.push_back(childDirEntry);
				}
			}

			return size;
		}

		static uint32_t getDynamicSize(const ProjectLibrary::DirectoryEntry& data)
		{ 
			WString elemName = UTF8::toWide(data.elementName);
			uint64_t dataSize = sizeof(uint32_t) + rttiGetElemSize(data.type) + rttiGetElemSize(data.path) + 
				rttiGetElemSize(elemName);

			dataSize += sizeof(uint32_t);

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

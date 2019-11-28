#include "stdafx.h"
#include "KPackageProjectFileData.h"
#include "KPackageProject.h"
#include <Kortex/Application.hpp>
#include "Utility/KAux.h"
#include <KxFramework/KxString.h>

namespace Kortex::PackageProject
{
	FileItem::FileItem()
		:m_Priority(FileDataSection::ms_DefaultPriority)
	{
	}
	FileItem::~FileItem()
	{
	}
	
	void FileItem::MakeUniqueID()
	{
		if (m_ID.IsEmpty())
		{
			m_ID = KxString::Format("0x%1", this);
		}
		else
		{
			m_ID = KxString::Format("%s!0x%1", this);
		}
	}
	
	bool FileItem::IsDefaultPriority() const
	{
		return m_Priority == FileDataSection::ms_DefaultPriority;
	}
	int32_t FileItem::GetPriority() const
	{
		return m_Priority;
	}
	void FileItem::SetPriority(int32_t value)
	{
		m_Priority = FileDataSection::CorrectPriority(value);
	}
}

namespace Kortex::PackageProject
{
	FolderItem::FolderItem()
	{
	}
	FolderItem::~FolderItem()
	{
	}
}

namespace Kortex::PackageProject
{
	bool FileDataSection::IsPriorityValid(int32_t value)
	{
		return value >= FileDataSection::ms_MinUserPriority && value <= FileDataSection::ms_MaxUserPriority;
	}
	int32_t FileDataSection::CorrectPriority(int32_t value)
	{
		return std::clamp(value, ms_MinUserPriority, ms_MaxUserPriority);
	}
	bool FileDataSection::IsFileIDValid(const wxString& id)
	{
		if (!id.IsEmpty() && !KAux::HasForbiddenFileNameChars(id))
		{
			wxString idLower = KxString::ToLower(id);
			return idLower != "fomod";
		}
		return false;
	}
	
	FileDataSection::FileDataSection(ModPackageProject& project)
		:ProjectSection(project)
	{
	}
	FileDataSection::~FileDataSection()
	{
	}
	
	FileItem* FileDataSection::FindEntryWithID(const wxString& id, size_t* index) const
	{
		const wxString idLower = KxString::ToLower(id);
		auto it = std::find_if(m_Data.cbegin(), m_Data.cend(), [&idLower](const FileItem::Vector::value_type& entry)
		{
			return KxString::ToLower(entry->GetID()) == idLower;
		});
	
		if (it != m_Data.cend())
		{
			if (index)
			{
				*index = std::distance(m_Data.cbegin(), it);
			}
			return it->get();
		}
		return nullptr;
	}
}

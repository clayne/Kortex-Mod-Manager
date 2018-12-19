#include "stdafx.h"
#include <Kortex/SaveManager.hpp>
#include <Kortex/GameInstance.hpp>
#include "DefaultSaveManager.h"
#include "BaseGameSave.h"
#include "EmptySaveFile.h"
#include "BethesdaSave/Morrowind.h"
#include "BethesdaSave/Oblivion.h"
#include "BethesdaSave/Skyrim.h"
#include "BethesdaSave/SkyrimSE.h"
#include "BethesdaSave/Fallout3.h"
#include "BethesdaSave/FalloutNV.h"
#include "BethesdaSave/Fallout4.h"
#include "Workspace.h"

namespace
{
	template<class T> bool TryCreateSaveObject(std::unique_ptr<Kortex::IGameSave>& ptr, const wxString& requestedInterface, const wxChar* name)
	{
		if (requestedInterface == name)
		{
			ptr = std::make_unique<T>();
			return true;
		}
		return false;
	}
}

namespace Kortex::SaveManager
{
	KWorkspace* DefaultSaveManager::CreateWorkspace(KMainWindow* mainWindow)
	{
		return new Workspace(mainWindow);
	}
	void DefaultSaveManager::OnSavesLocationChanged(GameInstance::ProfileEvent& event)
	{
		KWorkspace::ScheduleReloadOf<Workspace>();
	}

	void DefaultSaveManager::OnLoadInstance(IGameInstance& instance, const KxXMLNode& managerNode)
	{
		m_Config.OnLoadInstance(instance, managerNode);
	}
	void DefaultSaveManager::OnInit()
	{
		IEvent::Bind(Events::ProfileChanged, &DefaultSaveManager::OnSavesLocationChanged, this);
		IEvent::Bind(Events::ProfileSelected, &DefaultSaveManager::OnSavesLocationChanged, this);
	}
	void DefaultSaveManager::OnExit()
	{
	}

	KWorkspace* DefaultSaveManager::GetWorkspace() const
	{
		return Workspace::GetInstance();
	}
	std::unique_ptr<IGameSave> DefaultSaveManager::NewSave() const
	{
		const wxString requestedInterface = m_Config.GetSaveInterface();
		std::unique_ptr<IGameSave> object;

		TryCreateSaveObject<BethesdaSave::Morrowind>(object, requestedInterface, wxS("BethesdaMorrowind")) ||
		TryCreateSaveObject<BethesdaSave::Oblivion>(object, requestedInterface, wxS("BethesdaOblivion")) ||
		TryCreateSaveObject<BethesdaSave::Skyrim>(object, requestedInterface, wxS("BethesdaSkyrim")) ||
		TryCreateSaveObject<BethesdaSave::SkyrimSE>(object, requestedInterface, wxS("BethesdaSkyrimSE")) ||

		TryCreateSaveObject<BethesdaSave::Fallout3>(object, requestedInterface, wxS("BethesdaFallout3")) ||
		TryCreateSaveObject<BethesdaSave::FalloutNV>(object, requestedInterface, wxS("BethesdaFalloutNV")) ||
		TryCreateSaveObject<BethesdaSave::Fallout4>(object, requestedInterface, wxS("BethesdaFallout4")) ||
		TryCreateSaveObject<EmptySaveFile>(object, requestedInterface, wxS("Sacred2"));

		return object;
	}
}

namespace Kortex::SaveManager
{
	void Config::OnLoadInstance(IGameInstance& instance, const KxXMLNode& node)
	{
		m_SaveInterface = node.GetAttribute("SaveInterface");
		m_Location = node.GetFirstChildElement("Location").GetValue();

		// Load file filters
		for (KxXMLNode entryNode = node.GetFirstChildElement("FileFilters").GetFirstChildElement(); entryNode.IsOK(); entryNode = entryNode.GetNextSiblingElement())
		{
			m_FileFilters.emplace_back(entryNode.GetValue(), KVarExp(entryNode.GetAttribute("Label")));
		}

		// Multi-file save config
		m_PrimarySaveExt = node.GetFirstChildElement("PrimaryExtension").GetValue();
		m_SecondarySaveExt = node.GetFirstChildElement("SecondaryExtension").GetValue();
	}

	wxString Config::GetSaveInterface() const
	{
		return KVarExp(m_SaveInterface);
	}
	wxString Config::GetLocation() const
	{
		return KVarExp(m_Location);
	}
}
#pragma once
#include "stdafx.h"
#include "Events/KBroadcastEvent.h"
#include "KVariablesTable.h"
#include "KDynamicVariablesTable.h"
#include "KImageProvider.h"
#include "KProgramOptions.h"
#include <KxFramework/KxApp.h>
#include <KxFramework/KxImageList.h>
#include <KxFramework/KxImageSet.h>
#include <KxFramework/KxINI.h>
#include <wx/snglinst.h>
class KProfile;
class KLogEvent;
class KMainWindow;
class KModManager;
class KProgramManager;
class KSettingsWindowManager;
class KVirtualFileSystemService;
class KCMConfigEntryStd;
class KIPCClient;
enum KPGCFileID;

class KApp: public KxApp<wxApp, KApp>
{
	public:
		static wxString ExpandVariablesUsing(const wxString& variables, const KVariablesTable& variablesTable);
		static wxString ExpandVariables(const wxString& variables);

	private:
		wxSingleInstanceChecker m_SingleInstanceChecker;

		KxStringToStringUMap m_AvailableTranslations;
		wxString m_LoadedTranslationLocale;
		KxTranslation m_Translation;

		wxString m_UserSettingsFolder;
		wxWindow* m_InitProgressDialog = NULL;

		FILE* m_LogTargetFILE = NULL;
		wxLogStderr* m_LogTarget = NULL;

		KxImageList m_ImageList;
		KxImageSet m_ImageSet;

		KDynamicVariablesTable m_Variables;
		KProfile* m_CurrentProfile = NULL;
		KMainWindow* m_MainWindow = NULL;
		KProgramManager* m_RunManager = NULL;
		KModManager* m_ModManager = NULL;
		mutable KSettingsWindowManager* m_SettingsManager = NULL;
		bool m_AllowSaveSettinsgAtExit = true;
		
		KIPCClient* m_VFSServiceClient = NULL;
		KVirtualFileSystemService* m_VFSService = NULL;
		std::vector<std::pair<wxEvtHandler*, wxEventType>> m_BroadcastingRecievers;
		bool m_BroadcastingEnabled = true;

		wxString m_CurrentTemplateID;
		wxString m_CurrentConfigID;

		KProgramOption m_GeneralOptions;
		KProgramOption m_GeneralOptions_AppWide;
		KProgramOption m_ProfileOptions_AppWide;

	public:
		KApp();
		virtual ~KApp();

	public:
		const KxImageList* GetImageList() const
		{
			return &m_ImageList;
		}
		const KxImageSet* GetImageSet() const
		{
			return &m_ImageSet;
		}
		wxLogStderr* GetLogTarget() const
		{
			return m_LogTarget;
		}

		const wxString& GetRootFolder() const;
		const wxString& GetDataFolder() const;
		const wxString& GetUserSettingsFolder();
		const wxString& GetUserSettingsFile();

		wxString ExpandVariablesLocally(const wxString& variables) const
		{
			return ExpandVariablesUsing(variables, m_Variables);
		}
		KProfile* GetCurrentProfile() const;
		KProfile* SetCurrentProfile(KProfile* profile);
		bool IsProfileLoaded() const
		{
			return GetCurrentProfile() != NULL;
		}
		
		bool IsTranslationLoaded() const
		{
			return !m_LoadedTranslationLocale.IsEmpty() && !m_AvailableTranslations.empty();
		}
		const KxStringToStringUMap& GetAvailableTranslations() const
		{
			return m_AvailableTranslations;
		}
		const KxTranslation& GetTranslation() const
		{
			return m_Translation;
		}

		KSettingsWindowManager* GetSettingsManager() const;
		void SaveSettings() const;
		bool ShowChageProfileDialog();

		KProgramOption& GetOptionsGeneral()
		{
			return m_GeneralOptions_AppWide;
		}
		KProgramOption& GetOptionsProfile()
		{
			return m_ProfileOptions_AppWide;
		}

		KCMConfigEntryStd* GetSettingsEntry(KPGCFileID id, const wxString& section, const wxString& name) const;
		wxString GetSettingsValue(KPGCFileID id, const wxString& section, const wxString& name) const;
		void SetSettingsValue(KPGCFileID id, const wxString& section, const wxString& name, const wxString& value);
		wxString GetCurrentTemplateID() const;
		wxString GetCurrentConfigID() const;
		void SetCurrentTemplateID(const wxString& templateID);
		void SetCurrentConfigID(const wxString& configID);
		void ConfigureInternetExplorer(bool init);

		void BroadcastEvent(KBroadcastEvent& event);
		void SubscribeBroadcasting(wxEvtHandler* pHandler, wxEventType type);
		void SubscribeBroadcasting(wxWindow* window, wxEventType type);
		void SetBroadcastingEnabled(bool isEnabled)
		{
			m_BroadcastingEnabled = isEnabled;
		}

		bool ScheduleRestart();
		bool Uninstall();

	public:
		virtual bool OnInit() override;
		virtual int OnExit() override;
		virtual bool OnExceptionInMainLoop() override;
		virtual void OnUnhandledException() override;

	private:
		void LoadTranslation();
		void LoadImages();
		void ShowWorkspace();

		void InitSettings();
		bool IsPreStartConfigNeeded();
		bool ShowFirstTimeConfigDialog(wxWindow* parent);
		void InitProfilesData(wxWindow* parent);
		bool LoadProfile();
		void LoadCurrentTemplateAndConfig();

		void InitVFS();
		void UnInitVFS();
		void InitRunManager();
		void AddDownloadToAlreadyRunningInstance(const wxString& link);

	private:
		void OnErrorOccurred(KLogEvent& event);

		wxString GetLogsFolder();
		FILE* OpenLogFile();
		void CleanupLogs();
};

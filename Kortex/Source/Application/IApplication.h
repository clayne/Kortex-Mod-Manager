#pragma once
#include "stdafx.h"
#include "GameInstance/GameID.h"
#include "Options/Option.h"
#include <KxFramework/KxXML.h>
#include <KxFramework/KxSingleton.h>
#include <KxFramework/KxTranslation.h>
#include <KxFramework/KxVersion.h>
class KxImageList;
class KxImageSet;

namespace Kortex
{
	class LogEvent;
	class SystemApplication;
	class IVariableTable;

	enum class LoadTranslationStatus
	{
		Success = 0,
		NoTranslations,
		LoadingError
	};

	class IApplication:
		public KxSingletonPtr<IApplication>,
		public Application::WithOptions<IApplication>
	{
		friend class SystemApplication;

		public:
			static SystemApplication* GetSystemApp();

		protected:
			virtual void OnCreate() = 0;
			virtual void OnDestroy() = 0;
			virtual bool OnInit() = 0;
			virtual int OnExit() = 0;

			virtual void OnError(LogEvent& event) = 0;
			virtual bool OnGlobalConfigChanged(IAppOption& option) = 0;

			wxString RethrowCatchAndGetExceptionInfo() const;

			void InitGlobalManagers();
			void UnInitGlobalManagers();

		public:
			virtual wxString GetRootFolder() const = 0;
			virtual wxString GetDataFolder() const = 0;
			virtual wxString GetLogsFolder() const = 0;
			virtual wxString GetUserSettingsFolder() const = 0;
			virtual wxString GetUserSettingsFile() const = 0;
			virtual wxString GetInstancesFolder() const = 0;

			virtual GameID GetStartupGameID() const = 0;
			virtual wxString GetStartupInstanceID() const = 0;

			virtual bool IsTranslationLoaded() const = 0;
			virtual const KxTranslation& GetTranslation() const = 0;
			virtual KxTranslation::AvailableMap GetAvailableTranslations() const = 0;

			virtual const KxImageList& GetImageList() const = 0;
			virtual const KxImageSet& GetImageSet() const = 0;

			virtual IVariableTable& GetVariables() = 0;
			virtual wxString ExpandVariablesLocally(const wxString& variables) const = 0;
			virtual wxString ExpandVariables(const wxString& variables) const = 0;
		
			virtual bool OnException() = 0;
			virtual bool ScheduleRestart() = 0;
			virtual bool Uninstall() = 0;

		public:
			bool Is64Bit() const;
			bool IsSystem64Bit() const;

			bool IsAnotherRunning() const;
			bool QueueDownloadToMainProcess(const wxString& link);

			void EnableIE10Support();
			void DisableIE10Support();

			wxString GetID() const;
			wxString GetName() const;
			wxString GetDeveloper() const;
			KxVersion GetVersion() const;
			KxXMLDocument& GetGlobalConfig() const;

			wxCmdLineParser& GetCmdLineParser() const;
			bool ParseCommandLine();

			wxWindow* GetActiveWindow() const;
			wxWindow* GetTopWindow() const;
			void SetTopWindow(wxWindow* window);

			void ExitApp(int exitCode = 0);
			wxLog& GetLogger();
			LoadTranslationStatus TryLoadTranslation(KxTranslation& translation,
													 const KxTranslation::AvailableMap& availableTranslations,
													 const wxString& desiredLocale = wxEmptyString
			) const;
	};
}
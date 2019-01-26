#pragma once
#include "stdafx.h"
#include "Application/IModule.h"
#include <KxFramework/KxSingleton.h>

namespace Kortex
{
	class IGameConfigManager;

	namespace Internal
	{
		extern const SimpleModuleInfo GameConfigModuleTypeInfo;
	};

	class GameConfigModule:
		public ModuleWithTypeInfo<IModule, Internal::GameConfigModuleTypeInfo>,
		public KxSingletonPtr<GameConfigModule>
	{
		friend class KMainWindow;

		private:
			std::unique_ptr<IGameConfigManager> m_GameConfigManager;

		private:
			virtual void OnInit() override;
			virtual void OnExit() override;
			virtual void OnLoadInstance(IGameInstance& instance, const KxXMLNode& node) override;

		public:
			GameConfigModule();

		public:
			ManagerRefVector GetManagers() override;
	};
}

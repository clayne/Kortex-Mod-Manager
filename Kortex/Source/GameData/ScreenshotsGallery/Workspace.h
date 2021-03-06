#pragma once
#include "stdafx.h"
#include "Application/DefaultWorkspace.h"
#include <KxFramework/KxSingleton.h>
#include <KxFramework/KxPanel.h>
class KxTextBox;
class KxThumbView;

namespace Kortex
{
	class IScreenshotsGallery;
}
namespace Kortex::UI
{
	class ImageViewerEvent;
}

namespace Kortex::ScreenshotsGallery
{
	class Workspace: public Application::DefaultWindowWorkspace<KxPanel>, public KxSingletonPtr<Workspace>
	{
		private:
			wxBoxSizer* m_MainSizer = nullptr;
			KxThumbView* m_ViewPane = nullptr;
			KxStringVector m_LoadedImages;
			int m_CurrentImageIndex = -1;

		protected:
			bool OnCreateWorkspace() override;
			bool OnOpenWorkspace() override;
			bool OnCloseWorkspace() override;
			void OnReloadWorkspace() override;

		public:
			Workspace();
			~Workspace();

		private:
			void LoadData();
			void OnSelectItem(wxCommandEvent& event);
			void OnActivateItem(wxCommandEvent& event);
			void OnItemMenu(wxContextMenuEvent& event);
			void OnDialogNavigate(UI::ImageViewerEvent& event);
			void SetNavigationInfo(UI::ImageViewerEvent& event);

		public:
			wxString GetID() const override;
			wxString GetName() const override;
			ResourceID GetIcon() const override
			{
				return ImageResourceID::Pictures;
			}
			IWorkspaceContainer* GetPreferredContainer() const override;

		private:
			void DisplayInfo(const wxString& filePath);
			void ClearControls();
	};
}

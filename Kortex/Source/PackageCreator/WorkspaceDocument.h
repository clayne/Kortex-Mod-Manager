#pragma once
#include "stdafx.h"
#include "Application/IWorkspaceDocument.h"
#include "PackageProject/KPackageProject.h"

namespace Kortex
{
	class ModPackage;
	class IGameMod;
}
namespace Kortex::PackageProject
{
	class KPackageProjectSerializer;
}

namespace Kortex::PackageDesigner
{
	class Workspace;

	class WorkspaceDocument: public KxRTTI::ExtendInterface<WorkspaceDocument, IWorkspaceDocument>
	{
		public:
			static wxString GetNewProjectName();

		private:
			Workspace& m_Workspace;
			std::unique_ptr<KPackageProject> m_Project = nullptr;
			wxString m_ProjectFile;
			bool m_HasChanges = false;

		protected:
			wxString GetSaveConfirmationCaption() const override;
			wxString GetSaveConfirmationMessage() const override;

		public:
			WorkspaceDocument(Workspace& workspace)
				:m_Workspace(workspace)
			{
			}

		public:
			using KxIObject::QueryInterface;
			bool QueryInterface(const KxIID& iid, void*& ptr) noexcept override;

			KPackageProject* GetProject() const
			{
				return m_Project.get();
			}
			const wxString& GetProjectFilePath() const
			{
				return m_ProjectFile;
			}
			wxString GetProjectFileName() const;
			wxString GetProjectName() const;
			bool HasProjectFilePath() const
			{
				return !m_ProjectFile.IsEmpty();
			}

			void ChangeNotify();
			bool HasUnsavedChanges() const override
			{
				return m_HasChanges;
			}
			void SaveChanges() override;
			void DiscardChanges() override;

			void NewProject();
			void OpenProject(const wxString& filePath);
			void SaveProject();
			void SaveProject(const wxString& filePath);
			void ImportProjectFromPackage(const wxString& packagePath);
			void CreateProjectFromModEntry(const Kortex::IGameMod& modEntry);
			void ImportProject(PackageProject::KPackageProjectSerializer& serializer);
			void ExportProject(PackageProject::KPackageProjectSerializer& serializer);
			void BuildProject(bool buildPreview = false);

			void Reload();
			void LoadView();
			void ResetView();
	};
}

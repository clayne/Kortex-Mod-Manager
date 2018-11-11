#pragma once
#include "stdafx.h"
#include "PackageCreator/KPackageCreatorVectorModel.h"
#include "PackageProject/KPackageProjectComponents.h"
#include "PackageProject/KPackageProjectFileData.h"
#include "KProgramOptions.h"
#include <KxFramework/KxStdDialog.h>

class KPCCConditionalStepsModel: public KPackageCreatorVectorModel<KPPCConditionalStep::Vector>
{
	private:
		virtual void OnInitControl() override;

		virtual void GetValueByRow(wxAny& value, size_t row, const KxDataViewColumn* column) const override;
		virtual bool SetValueByRow(const wxAny& value, size_t row, const KxDataViewColumn* column) override;

		void OnActivateItem(KxDataViewEvent& event);
		void OnContextMenu(KxDataViewEvent& event);

		void OnAddStep();
		void OnRemoveStep(const KxDataViewItem& item);
		void OnClearList();
		virtual bool OnInsertItem(KxDataViewItem& currentItem, KxDataViewItem& droppedItem) override
		{
			OnInsertItemHelperUniquePtr(*GetDataVector(), currentItem, droppedItem);
			return true;
		}

	public:
		KPCCConditionalStepsModel(KPackageCreatorController* controller)
		{
			m_Controller = controller;
		}

	public:
		KPPCConditionalStep* GetDataEntry(size_t index) const
		{
			if (index < GetItemCount())
			{
				return GetDataVector()->at(index).get();
			}
			return NULL;
		}

		void SetDataVector();
		void SetDataVector(VectorType& data);
};

//////////////////////////////////////////////////////////////////////////
class KPCCConditionalStepsModelDialog: public KxStdDialog, public KPCCConditionalStepsModel
{
	private:
		wxWindow* m_ViewPane = NULL;
		KProgramOptionUI m_WindowOptions;
		KProgramOptionUI m_ViewOptions;

	private:
		wxWindow* GetDialogMainCtrl() const override
		{
			return m_ViewPane;
		}
		wxWindow* GetDialogFocusCtrl() const override
		{
			return GetView();
		}

	public:
		KPCCConditionalStepsModelDialog(wxWindow* parent, const wxString& caption, KPackageCreatorController* controller, bool isAutomatic);
		virtual ~KPCCConditionalStepsModelDialog();
};

#pragma once
#include "stdafx.h"
#include "PackageProject/ComponentsSection.h"
#include "PackageProject/ModPackageProject.h"

namespace Kortex::PackageDesigner
{
	class IDTracker
	{
		protected:
			void TrackID_ReplaceOrRemove(const wxString& trackedID, const wxString& newID, KxStringVector& list, bool remove) const
			{
				if (remove)
				{
					TrackID_RemoveFromStringVector(trackedID, list);
				}
				else
				{
					TrackID_ReplaceInStringVector(trackedID, newID, list);
				}
			}
			void TrackID_ReplaceInStringVector(const wxString& trackedID, const wxString& newID, KxStringVector& list) const;
			void TrackID_RemoveFromStringVector(const wxString& trackedID, KxStringVector& list) const;

			void TrackID_ReplaceOrRemove(const wxString& trackedID, const wxString& newID, PackageProject::FlagItem::Vector& list, bool remove) const
			{
				if (remove)
				{
					TrackID_RemoveFromFlagVector(trackedID, list);
				}
				else
				{
					TrackID_ReplaceInFlagVector(trackedID, newID, list);
				}
			}
			void TrackID_ReplaceInFlagVector(const wxString& trackedID, const wxString& newID, PackageProject::FlagItem::Vector& list) const;
			void TrackID_RemoveFromFlagVector(const wxString& trackedID, PackageProject::FlagItem::Vector& list) const;

		protected:
			virtual bool TrackChangeID(const wxString& trackedID, const wxString& newID) = 0;
			virtual bool TrackRemoveID(const wxString& trackedID) = 0;
			virtual bool TrackAddID(const wxString& trackedID)
			{
				return false;
			}
	};
}

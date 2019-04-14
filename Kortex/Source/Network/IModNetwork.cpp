#include "stdafx.h"
#include "IModNetwork.h"
#include <Kortex/NetworkManager.hpp>
#include "UI/KMainWindow.h"
#include "Utility/KAux.h"
#include <KxFramework/KxFile.h>
#include <KxFramework/KxTaskDialog.h>
#include <KxFramework/KxCredentialsDialog.h>

namespace Kortex
{
	KImageEnum IModNetwork::GetGenericIcon()
	{
		return KIMG_SITE_UNKNOWN;
	}

	void IModNetwork::Init()
	{
		KxFile(GetCacheFolder()).CreateFolder();
	}

	wxString IModNetwork::GetIPBModPageURL(ModID modID, const wxString& modSignature) const
	{
		return KxString::Format("%1/%2-%3", GetModPageBaseURL(), modID.GetValue(), modSignature.IsEmpty() ? wxS("x") : modSignature);
	}

	bool IModNetwork::IsDefault() const
	{
		return this == INetworkManager::GetInstance()->GetDefaultModNetwork();
	}
	wxString IModNetwork::GetCacheFolder() const
	{
		return INetworkManager::GetInstance()->GetCacheFolder() + '\\' + KAux::MakeSafeFileName(GetName());
	}
	
	wxString IModNetwork::TranslateGameIDToNetwork(const GameID& id) const
	{
		return id.IsOK() ? id : INetworkManager::GetInstance()->GetConfig().GetNexusID();
	}
}
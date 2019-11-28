#pragma once
#include "stdafx.h"

namespace Kortex::PackageProject
{
	enum KPPContentType
	{
		KPP_CONTENT_FILEDATA,
		KPP_CONTENT_IMAGES,
		KPP_CONTENT_DOCUMENTS,
	};
	enum KPPPackageType
	{
		KPP_PACCKAGE_UNKNOWN = -1,
	
		KPP_PACCKAGE_NATIVE,
		KPP_PACCKAGE_LEGACY,
		KPP_PACCKAGE_FOMOD_XML,
		KPP_PACCKAGE_FOMOD_CSHARP,
		KPP_PACCKAGE_BAIN,
		KPP_PACCKAGE_OMOD,
	};
	enum KPPOperator
	{
		KPP_OPERATOR_INVALID = -1,
		KPP_OPERATOR_NONE = 0,
	
		KPP_OPERATOR_EQ,
		KPP_OPERATOR_NOT_EQ,
		KPP_OPERATOR_GT,
		KPP_OPERATOR_GTEQ,
		KPP_OPERATOR_LT,
		KPP_OPERATOR_LTEQ,
	
		KPP_OPERATOR_AND,
		KPP_OPERATOR_OR,
	
		KPP_OPERATOR_COUNT,
		KPP_OPERATOR_COUNT_COMPARISON = KPP_OPERATOR_AND,
		KPP_OPERATOR_MIN = KPP_OPERATOR_NONE + 1,
	};
	enum class KPPReqState
	{
		Unknown = -1,
		True = 1,
		False = 0
	};
}

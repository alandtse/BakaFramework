#pragma once

#include "Misc/Fixes/OnStoryCraftItem.h"

namespace Fixes
{
	void Install()
	{
		if (!RuntimeCompat::IsNG() && *Config::Fixes::bEnableOnStoryCraftItem)
			OnStoryCraftItem::Install();
	}
}

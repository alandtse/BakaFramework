#pragma once

#include "Misc/Fixes/OnStoryCraftItem.h"

namespace Fixes
{
	void Install()
	{
		if (!REL::Module::IsNG() && *Config::Fixes::bEnableOnStoryCraftItem)
			OnStoryCraftItem::Install();
	}
}

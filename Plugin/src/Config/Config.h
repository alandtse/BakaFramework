#pragma once

class Config
{
public:
	class Fixes
	{
	public:
		inline static DKUtil::Alias::Boolean bEnableOnStoryCraftItem{ "bEnableOnStoryCraftItem", "Fixes" };
	};

	class Patches
	{
	public:
		inline static DKUtil::Alias::Boolean bEnableLoadingEditorIDs{ "bEnableLoadingEditorIDs", "Patches" };
		inline static DKUtil::Alias::Boolean bEnableEDIDConflictCheck{ "bEnableEDIDConflictCheck", "Patches" };
		inline static DKUtil::Alias::String sBetaCommentFileName{ "sBetaCommentFileName", "Patches" };
	};

	static void Load()
	{
		static auto Config = COMPILE_PROXY("BakaFramework.ini");
		Config.Bind(Fixes::bEnableOnStoryCraftItem, true);
		Config.Bind(Patches::bEnableLoadingEditorIDs, true);
		Config.Bind(Patches::bEnableEDIDConflictCheck, false);
		Config.Bind(Patches::sBetaCommentFileName, "BetaComment.txt");
		Config.Load();
	}
};

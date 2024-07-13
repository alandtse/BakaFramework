#include "Events/Events.h"
#include "Forms/Forms.h"
#include "Misc/Fixes.h"
#include "Misc/Patches.h"
#include "Scripts/ObScript.h"
#include "Scripts/Papyrus.h"
#include "Serialization/Serialization.h"

namespace
{
	void MessageHandler(F4SE::MessagingInterface::Message* a_msg)
	{
		if (!a_msg)
		{
			return;
		}

		switch (a_msg->type)
		{
		case F4SE::MessagingInterface::kPostLoad:
		{
			if (!REL::Module::IsVR()) Forms::Install();
			break;
		}
		case F4SE::MessagingInterface::kGameLoaded:
		{
			if (REL::Module::IsVR()) Forms::Install(); //VR crashes if this is too early
			break;
		}
		case F4SE::MessagingInterface::kGameDataReady:
		{
			if (static_cast<bool>(a_msg->data))
			{
				Events::Register();
			}
			else
			{
				ObScript::Help::ClearCellMap();
			}

			break;
		}

		default:
			break;
		}
	}
}

DLLEXPORT bool F4SEAPI F4SEPlugin_Query(const F4SE::QueryInterface* a_F4SE, F4SE::PluginInfo* a_info)
{
	a_info->infoVersion = F4SE::PluginInfo::kVersion;
	a_info->name = Plugin::NAME.data();
	a_info->version = Plugin::Version;

	const auto rtv = a_F4SE->RuntimeVersion();
	if (rtv < (REL::Relocate(F4SE::RUNTIME_1_10_163, F4SE::RUNTIME_LATEST, F4SE::RUNTIME_LATEST_VR)))
	{
		F4SE::stl::report_and_fail(
			fmt::format(
				FMT_STRING("{} does not support runtime v{}."sv),
				a_info->name,
				rtv.string()));
	}
	return true;
}

DLLEXPORT bool F4SEAPI F4SEPlugin_Load(const F4SE::LoadInterface* a_F4SE)
{
#ifndef NDEBUG
	MessageBoxA(NULL, "Loaded. You can now attach the debugger or continue execution.", Plugin::NAME.data(), NULL);
#endif

	Config::Load();

	F4SE::Init(a_F4SE);
	F4SE::AllocTrampoline(1u << 10);

	DKUtil::Logger::Init(Plugin::NAME, std::to_string(Plugin::Version));
	INFO("{} v{} loaded."sv, Plugin::NAME, Plugin::Version);

	Serialization::Register();

	const auto messaging = F4SE::GetMessagingInterface();
	if (!messaging || !messaging->RegisterListener(MessageHandler))
	{
		FATAL("Failed to register messaging handler, marking as incompatible."sv);
		return false;
	}

	const auto papyrus = F4SE::GetPapyrusInterface();
	if (!papyrus || !papyrus->Register(Papyrus::RegisterFunctions))
	{
		FATAL("Failed to register Papyrus functions, marking as incompatible."sv);
		return false;
	}

	Fixes::Install();
	Patches::Install();
	ObScript::Install();

	INFO("Plugin loaded successfully."sv);

	return true;
}

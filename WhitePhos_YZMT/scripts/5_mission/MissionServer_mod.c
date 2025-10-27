modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();
		// Ensure the server creates/loads its own config JSON
		WP_YZMT_Settings.Get();
	}

	override void OnClientReadyEvent(PlayerIdentity identity, PlayerBase player)
	{
		super.OnClientReadyEvent(identity, player);

		// Send server config to this client
		auto data = new WP_YZMT_SettingsSyncData;
		data.CopyFrom(WP_YZMT_Settings.Get());

		GetGame().RPCSingleParam(player, 50123, new Param1<ref WP_YZMT_SettingsSyncData>(data), true, identity);
	}
}

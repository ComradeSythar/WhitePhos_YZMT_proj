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
		WPY_BroadcastTo(player); // send current settings to this client
	}

	// --- Chat hook for #wp_reload ---
	override void OnEvent(EventType eventTypeId, Param params)
	{
		super.OnEvent(eventTypeId, params);

		if (eventTypeId == ChatMessageEventTypeID)
		{
			ChatMessageEventParams chat = ChatMessageEventParams.Cast(params);
			if (!chat) return;

			// Read all params as strings; different builds map text differently
			string p1 = "" + chat.param1;
			string p2 = "" + chat.param2;
			string p3 = "" + chat.param3;
			string p4 = "" + chat.param4;

			bool trigger = (p1 == "-wp_reload" || p2 == "-wp_reload" || p3 == "-wp_reload" || p4 == "-wp_reload");
			if (!trigger) return;

			if (!WP_YZMT_Settings.Get().AllowLiveEdits)
			{
				Print("[WP_YZMT] Reload ignored (AllowLiveEdits=false).");
				return;
			}

			Print("[WP_YZMT] Reloading config and broadcasting to all clients...");
			WP_YZMT_Settings.Get().Load();
			WPY_BroadcastAll();
			Print("[WP_YZMT] Broadcast complete.");

			// Confirmation to all players (no ChatPlayer; use PlayerBase.MessageStatus)
			array<Man> players = new array<Man>;
			GetGame().GetPlayers(players);
			for (int i = 0; i < players.Count(); i++)
			{
				PlayerBase pb = PlayerBase.Cast(players[i]);
				if (pb)
					pb.MessageStatus("[WP_YZMT] ✅ Config reloaded and synced to all players.");
			}
		}
	}
	// --- Helper: send current settings to a single player ---
	void WPY_BroadcastTo(PlayerBase player)
	{
		if (!player) return;
		PlayerIdentity id = player.GetIdentity();
		if (!id) return;

		auto data = new WP_YZMT_SettingsSyncData;
		data.CopyFrom(WP_YZMT_Settings.Get());

		GetGame().RPCSingleParam(player, 50123, new Param1<ref WP_YZMT_SettingsSyncData>(data), true, id);
	}

	// --- Helper: send current settings to all players ---
	void WPY_BroadcastAll()
	{
		array<Man> players = new array<Man>;
		GetGame().GetPlayers(players);

		for (int i = 0; i < players.Count(); i++)
		{
			PlayerBase pb = PlayerBase.Cast(players[i]);
			WPY_BroadcastTo(pb);
		}
	}

	// --- Helper: server-side reload and broadcast (guarded by AllowLiveEdits) ---
	void WPY_ServerReloadAndBroadcast()
	{
		if (!WP_YZMT_Settings.Get().AllowLiveEdits)
		{
			Print("[WP_YZMT] Live edits disabled (AllowLiveEdits=false). #wp_reload ignored.");
			return;
		}

		Print("[WP_YZMT] Reloading config and broadcasting to all clients...");
		WP_YZMT_Settings.Get().Load();
		WPY_BroadcastAll();
		Print("[WP_YZMT] Broadcast complete.");
	}
}

modded class MissionGameplay
{
	override void OnInit()
	{
		super.OnInit();
		Print("[WP_YZMT] MissionGameplay initialized on client.");
		WP_YZMT_Settings.Get(); // optional preload
	}
}

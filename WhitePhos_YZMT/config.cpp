class CfgPatches
{
	class WhitePhos_YZMT
	{
		requiredVersion = 0.1;
		units[] ={};
		requiredAddons[] ={"DZ_Scripts"};
	};
};

class CfgMods
{
	class WhitePhos_YZMT_Mod
	{
		dir = "WhitePhos_YZMT";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "White Phosphor NVGs";
		credits = "";
		author = "Comrade Sythar";
		authorID = "0";
		version = "0.95";
		extra = 0;
		type = "mod";
		dependencies[] = { "Game" };
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]={"WhitePhos_YZMT\scripts\3_game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = { "WhitePhos_YZMT\scripts\4_world" };
			};			
			class missionScriptModule 
			{
				value = "";
				files[] = {"WhitePhos_YZMT\scripts\5_mission"}; 
			};
		};
	};
};

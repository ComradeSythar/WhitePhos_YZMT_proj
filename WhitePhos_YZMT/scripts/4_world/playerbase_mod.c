modded class PlayerBase
{
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);

		if (rpc_type == 50123 && GetGame().IsClient())
		{
			Param1<ref WP_YZMT_SettingsSyncData> dataParam;
			if (!ctx.Read(dataParam)) return;

			ref WP_YZMT_SettingsSyncData newSettings = dataParam.param1;
			ref WP_YZMT_Settings localSettings = WP_YZMT_Settings.Get();

			bool changed = false;

			if (!CompareFloatArrays(localSettings.OverlayColor, newSettings.OverlayColor))                 { localSettings.OverlayColor = newSettings.OverlayColor; changed = true; }
			if (!CompareFloatArrays(localSettings.OverlayColor2ndLayer, newSettings.OverlayColor2ndLayer)) { localSettings.OverlayColor2ndLayer = newSettings.OverlayColor2ndLayer; changed = true; }
			if (!CompareFloatArrays(localSettings.OverlayColorDaytime, newSettings.OverlayColorDaytime))   { localSettings.OverlayColorDaytime = newSettings.OverlayColorDaytime; changed = true; }
			if (!CompareFloatArrays(localSettings.OverlayColorOptics, newSettings.OverlayColorOptics))     { localSettings.OverlayColorOptics = newSettings.OverlayColorOptics; changed = true; }

			changed |= CheckAndApplyFloat(localSettings.DesaturationAmt,            newSettings.DesaturationAmt);
			changed |= CheckAndApplyFloat(localSettings.DesaturationAmtDaytime,     newSettings.DesaturationAmtDaytime);
			changed |= CheckAndApplyFloat(localSettings.FilmGrainSharpness,         newSettings.FilmGrainSharpness);
			changed |= CheckAndApplyFloat(localSettings.FilmGrainSharpnessDaytime,  newSettings.FilmGrainSharpnessDaytime);
			changed |= CheckAndApplyFloat(localSettings.FilmGrainSize,              newSettings.FilmGrainSize);
			changed |= CheckAndApplyFloat(localSettings.FilmGrainSizeDaytime,       newSettings.FilmGrainSizeDaytime);
			changed |= CheckAndApplyFloat(localSettings.FilmGrainFrequency,         newSettings.FilmGrainFrequency);
			changed |= CheckAndApplyFloat(localSettings.FilmGrainFrequencyOptics,   newSettings.FilmGrainFrequencyOptics);
			changed |= CheckAndApplyFloat(localSettings.FilmGrainFrequencyDaytime,  newSettings.FilmGrainFrequencyDaytime);
			changed |= CheckAndApplyFloat(localSettings.LightIntensityAmp_NV,       newSettings.LightIntensityAmp_NV);
			changed |= CheckAndApplyFloat(localSettings.LightIntensityAmp_Daytime,  newSettings.LightIntensityAmp_Daytime);

			changed |= CheckAndApplyFloat(localSettings.DefaultGogglesContrast,     newSettings.DefaultGogglesContrast);

			if (!CompareFloatArrays(localSettings.Overlay1ColorMult, newSettings.Overlay1ColorMult))       { localSettings.Overlay1ColorMult = newSettings.Overlay1ColorMult; changed = true; }
			changed |= CheckAndApplyFloat(localSettings.Overlay1LightMultFact,      newSettings.Overlay1LightMultFact);
			changed |= CheckAndApplyFloat(localSettings.Overlay1LightMultNoise,     newSettings.Overlay1LightMultNoise);

			if (!CompareFloatArrays(localSettings.Overlay2ColorSet, newSettings.Overlay2ColorSet))         { localSettings.Overlay2ColorSet = newSettings.Overlay2ColorSet; changed = true; }
			changed |= CheckAndApplyFloat(localSettings.Overlay2OverlayFactor,      newSettings.Overlay2OverlayFactor);
			changed |= CheckAndApplyFloat(localSettings.ColorOffset2ndLayer,        newSettings.ColorOffset2ndLayer);
			changed |= CheckAndApplyFloat(localSettings.OverlayFactor2ndLayer,      newSettings.OverlayFactor2ndLayer);

			changed |= CheckAndApplyFloat(localSettings.DefaultNVOpticContrast,        newSettings.DefaultNVOpticContrast);
			changed |= CheckAndApplyFloat(localSettings.DefaultNVOpticLightMult,       newSettings.DefaultNVOpticLightMult);
			changed |= CheckAndApplyFloat(localSettings.DefaultNVOpticLightNoise,      newSettings.DefaultNVOpticLightNoise);
			changed |= CheckAndApplyFloat(localSettings.DefaultNVOpticLightOffset,     newSettings.DefaultNVOpticLightOffset);
			changed |= CheckAndApplyFloat(localSettings.DefaultNVOpticLightOverlayFac, newSettings.DefaultNVOpticLightOverlayFac);

			if (!CompareFloatArrays(localSettings.DaytimeNVOpticOverlayColor, newSettings.DaytimeNVOpticOverlayColor)) { localSettings.DaytimeNVOpticOverlayColor = newSettings.DaytimeNVOpticOverlayColor; changed = true; }
			changed |= CheckAndApplyFloat(localSettings.DaytimeNVOpticOverlayFactor,   newSettings.DaytimeNVOpticOverlayFactor);
			changed |= CheckAndApplyFloat(localSettings.DaytimeNVOpticLightOffset,     newSettings.DaytimeNVOpticLightOffset);
			changed |= CheckAndApplyFloat(localSettings.DaytimeNVOpticLightMult,       newSettings.DaytimeNVOpticLightMult);
			changed |= CheckAndApplyFloat(localSettings.DaytimeNVOpticLightNoise,      newSettings.DaytimeNVOpticLightNoise);

			if (changed)
			{
				MakeDirectory("$profile:WP_YZMT\\");
				JsonFileLoader<WP_YZMT_Settings>.JsonSaveFile("$profile:WP_YZMT\\WP_YZMT_config.json", localSettings);
				Print("✔ WP_YZMT_Settings updated from server.");
			}
		}
	}

	bool CheckAndApplyFloat(inout float currentValue, float incoming)
	{
		if (currentValue != incoming)
		{
			currentValue = incoming;
			return true;
		}
		return false;
	}

	bool CompareFloatArrays(array<float> a, array<float> b)
	{
		if (!a || !b || a.Count() != b.Count()) return false;
		for (int i = 0; i < a.Count(); i++)
		{
			if (a[i] != b[i]) return false;
		}
		return true;
	}
}

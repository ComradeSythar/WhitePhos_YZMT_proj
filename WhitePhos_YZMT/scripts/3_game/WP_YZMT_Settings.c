class WP_YZMT_Settings
{
	// ===== JSON-controlled variables =====
	bool AllowLiveEdits = false;

	ref array<float> OverlayColor;
	ref array<float> OverlayColor2ndLayer;
	ref array<float> OverlayColorDaytime;
	ref array<float> OverlayColorOptics;

	float DesaturationAmt;
	float DesaturationAmtDaytime;
	float FilmGrainSharpness;
	float FilmGrainSharpnessDaytime;
	float FilmGrainSize;
	float FilmGrainSizeDaytime;
	float FilmGrainFrequency;
	float FilmGrainFrequencyOptics;
	float FilmGrainFrequencyDaytime;
	float LightIntensityAmp_NV;
	float LightIntensityAmp_Daytime;

	float DefaultGogglesContrast;

	ref array<float> Overlay1ColorMult;
	float Overlay1LightMultFact;
	float Overlay1LightMultNoise;

	ref array<float> Overlay2ColorSet;
	float Overlay2OverlayFactor;
	float ColorOffset2ndLayer;
	float OverlayFactor2ndLayer;

	float DefaultNVOpticContrast;
	float DefaultNVOpticLightMult;
	float DefaultNVOpticLightNoise;
	float DefaultNVOpticLightOffset;
	float DefaultNVOpticLightOverlayFac;

	ref array<float> DaytimeNVOpticOverlayColor;
	float DaytimeNVOpticOverlayFactor;
	float DaytimeNVOpticLightOffset;
	float DaytimeNVOpticLightMult;
	float DaytimeNVOpticLightNoise;

	static ref WP_YZMT_Settings instance;
	static WP_YZMT_Settings Get()
	{
		if (!instance)
		{
			instance = new WP_YZMT_Settings;
			instance.Load();
		}
		return instance;
	}

	void Load()
	{
		string configPath = "$profile:WP_YZMT\\WP_YZMT_config.json";
		MakeDirectory("$profile:WP_YZMT\\");
		if (FileExist(configPath))
		{
			WP_YZMT_Settings loadedData = new WP_YZMT_Settings;
			JsonFileLoader<WP_YZMT_Settings>.JsonLoadFile(configPath, loadedData);

			AllowLiveEdits = loadedData.AllowLiveEdits;

			OverlayColor              = CopyOrDefault(loadedData.OverlayColor,              DefaultOverlayColor());
			OverlayColor2ndLayer      = CopyOrDefault(loadedData.OverlayColor2ndLayer,      DefaultOverlayColor2ndLayer());
			OverlayColorDaytime       = CopyOrDefault(loadedData.OverlayColorDaytime,       DefaultOverlayColorDaytime());
			OverlayColorOptics        = CopyOrDefault(loadedData.OverlayColorOptics,        DefaultOverlayColorOptics());

			DesaturationAmt           = SetOrDefault(loadedData.DesaturationAmt,            0.18);
			DesaturationAmtDaytime    = SetOrDefault(loadedData.DesaturationAmtDaytime,     0.3);
			FilmGrainSharpness        = SetOrDefault(loadedData.FilmGrainSharpness,         4.8);
			FilmGrainSharpnessDaytime = SetOrDefault(loadedData.FilmGrainSharpnessDaytime,  5.7);
			FilmGrainSize             = SetOrDefault(loadedData.FilmGrainSize,              2.0);
			FilmGrainSizeDaytime      = SetOrDefault(loadedData.FilmGrainSizeDaytime,       1.0);
			FilmGrainFrequency        = SetOrDefault(loadedData.FilmGrainFrequency,         1.0);
			FilmGrainFrequencyOptics  = SetOrDefault(loadedData.FilmGrainFrequencyOptics,   1.0);
			FilmGrainFrequencyDaytime = SetOrDefault(loadedData.FilmGrainFrequencyDaytime,  8.0);
			LightIntensityAmp_NV      = SetOrDefault(loadedData.LightIntensityAmp_NV,       4.1);
			LightIntensityAmp_Daytime = SetOrDefault(loadedData.LightIntensityAmp_Daytime,  2.5);

			DefaultGogglesContrast    = SetOrDefault(loadedData.DefaultGogglesContrast,     0.85);

			Overlay1ColorMult         = CopyOrDefault(loadedData.Overlay1ColorMult,         DefaultOverlay1ColorMult());
			Overlay1LightMultFact     = SetOrDefault(loadedData.Overlay1LightMultFact,      0.0);
			Overlay1LightMultNoise    = SetOrDefault(loadedData.Overlay1LightMultNoise,     0.0);

			Overlay2ColorSet          = CopyOrDefault(loadedData.Overlay2ColorSet,          DefaultOverlay2ColorSet());
			Overlay2OverlayFactor     = SetOrDefault(loadedData.Overlay2OverlayFactor,      0.3);
			ColorOffset2ndLayer       = SetOrDefault(loadedData.ColorOffset2ndLayer,        -0.030);
			OverlayFactor2ndLayer     = SetOrDefault(loadedData.OverlayFactor2ndLayer,      0.06);

			DefaultNVOpticContrast        = SetOrDefault(loadedData.DefaultNVOpticContrast,        1.3);
			DefaultNVOpticLightMult       = SetOrDefault(loadedData.DefaultNVOpticLightMult,       2.0);
			DefaultNVOpticLightNoise      = SetOrDefault(loadedData.DefaultNVOpticLightNoise,      0.35);
			DefaultNVOpticLightOffset     = SetOrDefault(loadedData.DefaultNVOpticLightOffset,     -0.045);
			DefaultNVOpticLightOverlayFac = SetOrDefault(loadedData.DefaultNVOpticLightOverlayFac, 0.070);

			DaytimeNVOpticOverlayColor = CopyOrDefault(loadedData.DaytimeNVOpticOverlayColor, DefaultDaytimeNVOpticOverlayColor());
			DaytimeNVOpticOverlayFactor   = SetOrDefault(loadedData.DaytimeNVOpticOverlayFactor,   0.6);
			DaytimeNVOpticLightOffset     = SetOrDefault(loadedData.DaytimeNVOpticLightOffset,     -0.1);
			DaytimeNVOpticLightMult       = SetOrDefault(loadedData.DaytimeNVOpticLightMult,       1.0);
			DaytimeNVOpticLightNoise      = SetOrDefault(loadedData.DaytimeNVOpticLightNoise,      0.6);
		}
		else
		{
			Print("WP_YZMT: Config not found. Creating with defaults.");
			SetDefaults();
			Save();
		}
	}

	void Save()
	{
		string configPath = "$profile:WP_YZMT\\WP_YZMT_config.json";
		MakeDirectory("$profile:WP_YZMT\\");
		JsonFileLoader<WP_YZMT_Settings>.JsonSaveFile(configPath, this);
	}

	void SetDefaults()
	{
		AllowLiveEdits          = true;

		OverlayColor            = DefaultOverlayColor();
		OverlayColor2ndLayer    = DefaultOverlayColor2ndLayer();
		OverlayColorDaytime     = DefaultOverlayColorDaytime();
		OverlayColorOptics      = DefaultOverlayColorOptics();

		DesaturationAmt           = 0.18;
		DesaturationAmtDaytime    = 0.3;
		FilmGrainSharpness        = 4.8;
		FilmGrainSharpnessDaytime = 5.7;
		FilmGrainSize             = 2.0;
		FilmGrainSizeDaytime      = 1.0;
		FilmGrainFrequency        = 1.0;
		FilmGrainFrequencyOptics  = 1.0;
		FilmGrainFrequencyDaytime = 8.0;
		LightIntensityAmp_NV      = 5.8;
		LightIntensityAmp_Daytime = 2.5;

		DefaultGogglesContrast    = 0.85;

		Overlay1ColorMult         = DefaultOverlay1ColorMult();
		Overlay1LightMultFact     = 0.0;
		Overlay1LightMultNoise    = 0.0;

		Overlay2ColorSet          = DefaultOverlay2ColorSet();
		Overlay2OverlayFactor     = 0.3;
		ColorOffset2ndLayer       = -0.030;
		OverlayFactor2ndLayer     = 0.06;

		DefaultNVOpticContrast        = 1.3;
		DefaultNVOpticLightMult       = 2.0;
		DefaultNVOpticLightNoise      = 0.35;
		DefaultNVOpticLightOffset     = -0.045;
		DefaultNVOpticLightOverlayFac = 0.070;

		DaytimeNVOpticOverlayColor = DefaultDaytimeNVOpticOverlayColor();
		DaytimeNVOpticOverlayFactor   = 0.6;
		DaytimeNVOpticLightOffset     = -0.1;
		DaytimeNVOpticLightMult       = 1.0;
		DaytimeNVOpticLightNoise      = 0.6;
	}

	// ===== Helpers =====
	float SetOrDefault(float value, float fallback)
	{
		if (value != value) return fallback; // NaN check
		return value;
	}

	array<float> CopyOrDefault(array<float> input, array<float> fallback)
	{
		if (!input || input.Count() != 4) return fallback;
		ref array<float> copied = new array<float>();
		for (int i = 0; i < input.Count(); i++)
			copied.Insert(input.Get(i));
		return copied;
	}

	// Default arrays
	ref array<float> DefaultOverlayColor()               { return { 0.0, 0.23, 0.28, 0.0 }; }
	ref array<float> DefaultOverlayColor2ndLayer()       { return { 0.0, 0.22, 0.27, 0.0 }; }
	ref array<float> DefaultOverlayColorDaytime()        { return { 0.0, 0.10, 0.27, 1.0 }; }
	ref array<float> DefaultOverlayColorOptics()         { return { 0.0, 0.24, 0.27, 0.0 }; }
	ref array<float> DefaultOverlay1ColorMult()          { return { 0.0, 0.02, 0.02, 0.0 }; }
	ref array<float> DefaultOverlay2ColorSet()           { return { 0.0, 0.0, 0.0, 0.0 }; }
	ref array<float> DefaultDaytimeNVOpticOverlayColor() { return { 0.0, 0.48, 0.55, 0.0 }; }
}

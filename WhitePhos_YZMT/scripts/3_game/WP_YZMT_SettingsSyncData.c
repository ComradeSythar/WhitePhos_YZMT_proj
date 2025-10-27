class WP_YZMT_SettingsSyncData
{
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

	void CopyFrom(WP_YZMT_Settings other)
	{
		OverlayColor              = new array<float>;
		foreach (float v0 : other.OverlayColor)              OverlayColor.Insert(v0);

		OverlayColor2ndLayer      = new array<float>;
		foreach (float v1 : other.OverlayColor2ndLayer)      OverlayColor2ndLayer.Insert(v1);

		OverlayColorDaytime       = new array<float>;
		foreach (float v2 : other.OverlayColorDaytime)       OverlayColorDaytime.Insert(v2);

		OverlayColorOptics        = new array<float>;
		foreach (float v3 : other.OverlayColorOptics)        OverlayColorOptics.Insert(v3);

		DesaturationAmt           = other.DesaturationAmt;
		DesaturationAmtDaytime    = other.DesaturationAmtDaytime;
		FilmGrainSharpness        = other.FilmGrainSharpness;
		FilmGrainSharpnessDaytime = other.FilmGrainSharpnessDaytime;
		FilmGrainSize             = other.FilmGrainSize;
		FilmGrainSizeDaytime      = other.FilmGrainSizeDaytime;
		FilmGrainFrequency        = other.FilmGrainFrequency;
		FilmGrainFrequencyOptics  = other.FilmGrainFrequencyOptics;
		FilmGrainFrequencyDaytime = other.FilmGrainFrequencyDaytime;
		LightIntensityAmp_NV      = other.LightIntensityAmp_NV;
		LightIntensityAmp_Daytime = other.LightIntensityAmp_Daytime;

		DefaultGogglesContrast    = other.DefaultGogglesContrast;

		Overlay1ColorMult         = new array<float>;
		foreach (float v4 : other.Overlay1ColorMult)         Overlay1ColorMult.Insert(v4);

		Overlay1LightMultFact     = other.Overlay1LightMultFact;
		Overlay1LightMultNoise    = other.Overlay1LightMultNoise;

		Overlay2ColorSet          = new array<float>;
		foreach (float v5 : other.Overlay2ColorSet)          Overlay2ColorSet.Insert(v5);

		Overlay2OverlayFactor     = other.Overlay2OverlayFactor;
		ColorOffset2ndLayer       = other.ColorOffset2ndLayer;
		OverlayFactor2ndLayer     = other.OverlayFactor2ndLayer;

		DefaultNVOpticContrast        = other.DefaultNVOpticContrast;
		DefaultNVOpticLightMult       = other.DefaultNVOpticLightMult;
		DefaultNVOpticLightNoise      = other.DefaultNVOpticLightNoise;
		DefaultNVOpticLightOffset     = other.DefaultNVOpticLightOffset;
		DefaultNVOpticLightOverlayFac = other.DefaultNVOpticLightOverlayFac;

		DaytimeNVOpticOverlayColor = new array<float>;
		foreach (float v6 : other.DaytimeNVOpticOverlayColor) DaytimeNVOpticOverlayColor.Insert(v6);

		DaytimeNVOpticOverlayFactor   = other.DaytimeNVOpticOverlayFactor;
		DaytimeNVOpticLightOffset     = other.DaytimeNVOpticLightOffset;
		DaytimeNVOpticLightMult       = other.DaytimeNVOpticLightMult;
		DaytimeNVOpticLightNoise      = other.DaytimeNVOpticLightNoise;
	}
}

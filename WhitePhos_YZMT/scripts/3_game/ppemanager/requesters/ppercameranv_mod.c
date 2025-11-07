modded class PPERequester_CameraNV extends PPERequester_GameplayBase
{

	static const int NV_VANILLA_GLASSES = 51;
	
	protected float UGExposureCoef = 1.0;
	
	override protected void SetNVMode(int mode)
	{
		SetTargetValueFloat(PPEExceptions.EYEACCOM,PPEEyeAccomodationNative.PARAM_INTENSITY,false,1.0,PPEEyeAccomodationNative.L_0_NVG_GENERIC,PPOperators.SET);
		
		//I had no idea I could call cfmods class like this. Huge thanks to Lads discord
		#ifdef Lads_LightingOverhaul
		SetTargetValueFloat(PPEExceptions.EYEACCOM,PPEEyeAccomodationNative.PARAM_INTENSITY,false,6.0 ,PPEEyeAccomodationNative.L_0_NVG_GENERIC,PPOperators.SET);
		#endif
		
		///////////////////////////////
		//Basic Configs
		
		autoptr array<float> m_OverlayColor = WP_YZMT_Settings.Get().OverlayColor;
		autoptr array<float> m_OverlayColor2ndLayer = WP_YZMT_Settings.Get().OverlayColor2ndLayer;
		autoptr array<float> m_OverlayColorDaytime = WP_YZMT_Settings.Get().OverlayColorDaytime;
		autoptr array<float> m_OverlayColorOptics = WP_YZMT_Settings.Get().OverlayColorOptics;
		
		float m_DesaturationAmt = WP_YZMT_Settings.Get().DesaturationAmt; 
		float m_DesaturationAmtDaytime = WP_YZMT_Settings.Get().DesaturationAmtDaytime;
		float m_FilmGrainSharpness = WP_YZMT_Settings.Get().FilmGrainSharpness;	
		float m_FilmGrainSharpnessDaytime = WP_YZMT_Settings.Get().FilmGrainSharpnessDaytime;
		float m_FilmGrainSize = WP_YZMT_Settings.Get().FilmGrainSize; 
		float m_FilmGrainSizeDaytime = WP_YZMT_Settings.Get().FilmGrainSizeDaytime;
		float m_FilmGrainFrequency = WP_YZMT_Settings.Get().FilmGrainFrequency; 
		float m_FilmGrainFrequencyOptics = WP_YZMT_Settings.Get().FilmGrainFrequencyOptics; 
		float m_FilmGrainFrequencyDaytime = WP_YZMT_Settings.Get().FilmGrainFrequencyDaytime;
		float m_LightIntensityAmp_NV = WP_YZMT_Settings.Get().LightIntensityAmp_NV;
		float m_LightIntensityAmp_Daytime = WP_YZMT_Settings.Get().LightIntensityAmp_Daytime;
				
		float m_DefaultGogglesContrast = WP_YZMT_Settings.Get().DefaultGogglesContrast;
		
		autoptr array<float> m_Overlay1ColorMult = WP_YZMT_Settings.Get().Overlay1ColorMult;
		float m_Overlay1LightMultFact = WP_YZMT_Settings.Get().Overlay1LightMultFact;
		float m_Overlay1LightMultNoise = WP_YZMT_Settings.Get().Overlay1LightMultNoise;
		
		autoptr array<float> m_Overlay2ColorSet = WP_YZMT_Settings.Get().Overlay2ColorSet;
		float m_Overlay2OverlayFactor = WP_YZMT_Settings.Get().Overlay2OverlayFactor;
		float m_ColorOffset2ndLayer = WP_YZMT_Settings.Get().ColorOffset2ndLayer;
		float m_OverlayFactor2ndLayer = WP_YZMT_Settings.Get().OverlayFactor2ndLayer;
		
		
		float m_DefaultNVOpticContrast = WP_YZMT_Settings.Get().DefaultNVOpticContrast;
		float m_DefaultNVOpticLightMult = WP_YZMT_Settings.Get().DefaultNVOpticLightMult;
		float m_DefaultNVOpticLightNoise = WP_YZMT_Settings.Get().DefaultNVOpticLightNoise;
		float m_DefaultNVOpticLightOffset = WP_YZMT_Settings.Get().DefaultNVOpticLightOffset;
		float m_DefaultNVOpticLightOverlayFac = WP_YZMT_Settings.Get().DefaultNVOpticLightOverlayFac;
		
		autoptr array<float> m_DaytimeNVOpticOverlayColor = WP_YZMT_Settings.Get().DaytimeNVOpticOverlayColor;
		float m_DaytimeNVOpticOverlayFactor = WP_YZMT_Settings.Get().DaytimeNVOpticOverlayFactor;
		float m_DaytimeNVOpticLightOffset = WP_YZMT_Settings.Get().DaytimeNVOpticLightOffset;
		float m_DaytimeNVOpticLightMult = WP_YZMT_Settings.Get().DaytimeNVOpticLightMult;
		float m_DaytimeNVOpticLightNoise = WP_YZMT_Settings.Get().DaytimeNVOpticLightNoise;
		
		switch (mode)
		{
			case NV_NO_BATTERY: //battery off
			//////////////////////
			//This essentially established the defaults. It is also what you see through unpowered night vision optics
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,m_Overlay1ColorMult,PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PostProcessEffectType.Glow,PPEGlow.PARAM_SATURATION,true,m_DesaturationAmt,PPEGlow.L_01_NVG_DESAT,PPOperators.LOWEST);	
				
				SetTargetValueFloatDefault(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY);
				SetTargetValueFloatDefault(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS);
				SetTargetValueFloatDefault(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE);
				SetTargetValueFloatDefault(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_FREQUENCY);
				
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,m_Overlay1LightMultFact,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,m_Overlay1LightMultNoise,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			/////////////////
			//secondary layer
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_OVERLAYCOLOR,m_Overlay2ColorSet,PPEGlow.L_03_NVG_OVERLAY2,PPOperators.SET); 
				SetTargetValueFloat(PostProcessEffectType.Glow,PPEGlow.PARAM_OVERLAYFACTOR,true,m_Overlay2OverlayFactor,PPEGlow.L_03_NVG_OVERLAY2,PPOperators.HIGHEST);
			break;
			
			case NV_DEFAULT_OPTICS: //NV optic (weapons etc) on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,m_OverlayColorOptics,PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PostProcessEffectType.Glow,PPEGlow.PARAM_CONTRAST,m_DefaultNVOpticContrast,PPEGlow.L_23_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PostProcessEffectType.Glow,PPEGlow.PARAM_SATURATION,true,m_DesaturationAmt,PPEGlow.L_01_NVG_DESAT,PPOperators.LOWEST); 
				
				SetTargetValueFloat(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY,false,m_LightIntensityAmp_NV * UGExposureCoef,PPEExposureNative.L_0_NVG_OPTIC,PPOperators.ADD); //Exposure parameter
				
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,m_FilmGrainSharpness,PPEFilmGrain.L_1_NVG,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,m_FilmGrainSize,PPEFilmGrain.L_2_NVG,PPOperators.SET);

				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,m_DefaultNVOpticLightMult,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,m_DefaultNVOpticLightNoise,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);//2
				
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,m_OverlayColorOptics,PPEGlow.L_02_NVG_OVERLAY1,PPOperators.ADD_RELATIVE);
				SetTargetValueFloat(PostProcessEffectType.Glow,PPEGlow.PARAM_OFFSET,false,m_DefaultNVOpticLightOffset,PPEGlow.L_02_NVG_OVERLAY1,PPOperators.SET);
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_OVERLAYCOLOR,m_OverlayColorOptics,PPEGlow.L_03_NVG_OVERLAY2,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.Glow,PPEGlow.PARAM_OVERLAYFACTOR,true,m_DefaultNVOpticLightOverlayFac,PPEGlow.L_03_NVG_OVERLAY2,PPOperators.HIGHEST);
			//
			break;
			
			case NV_DAYTIME_OPTICS: //NV optic in daytime mode
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,m_OverlayColorDaytime,PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PostProcessEffectType.Glow,PPEGlow.PARAM_OFFSET,false,m_DaytimeNVOpticLightOffset,PPEGlow.L_23_NVG,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.Glow,PPEGlow.PARAM_SATURATION,true,m_DesaturationAmtDaytime,PPEGlow.L_01_NVG_DESAT,PPOperators.LOWEST); 
				
				SetTargetValueFloat(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY,false,m_LightIntensityAmp_Daytime * UGExposureCoef,PPEExposureNative.L_0_NVG_OPTIC,PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,m_FilmGrainSharpnessDaytime,PPEFilmGrain.L_1_NVG,PPOperators.SET);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,m_FilmGrainSizeDaytime,PPEFilmGrain.L_2_NVG,PPOperators.SET);

				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,m_DaytimeNVOpticLightMult,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);//3
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,m_DaytimeNVOpticLightNoise,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);//1
				
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_OVERLAYCOLOR, m_DaytimeNVOpticOverlayColor,PPEGlow.L_03_NVG_OVERLAY2,PPOperators.SET); //0.0, 0.48, 0.55, 0
				SetTargetValueFloat(PostProcessEffectType.Glow,PPEGlow.PARAM_OVERLAYFACTOR,true,m_DaytimeNVOpticOverlayFactor,PPEGlow.L_03_NVG_OVERLAY2,PPOperators.HIGHEST);
			//	
			break;
			
			case NV_DEFAULT_GLASSES: //goggles on
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,m_OverlayColor,PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				
				SetTargetValueFloat(PostProcessEffectType.Glow,PPEGlow.PARAM_CONTRAST,m_DefaultGogglesContrast,PPEGlow.L_23_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PostProcessEffectType.Glow,PPEGlow.PARAM_SATURATION,true,m_DesaturationAmt,PPEGlow.L_01_NVG_DESAT,PPOperators.LOWEST); 			
				SetTargetValueFloat(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY,false,m_LightIntensityAmp_NV * UGExposureCoef,PPEExposureNative.L_0_NVG_GOGGLES,PPOperators.ADD);
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS,false,m_FilmGrainSharpness,PPEFilmGrain.L_1_NVG,PPOperators.SET);				
				SetTargetValueFloat(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE,false,m_FilmGrainSize,PPEFilmGrain.L_2_NVG,PPOperators.SET);
			////////////////////////
			//Light noise factors	
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,1.6,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);//1.7
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,0.09,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);//0.23
			
			/////////////////
			//secondary layer 			 			
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,m_OverlayColor2ndLayer,PPEGlow.L_02_NVG_OVERLAY1,PPOperators.ADD_RELATIVE);
				SetTargetValueFloat(PostProcessEffectType.Glow,PPEGlow.PARAM_OFFSET,false,m_ColorOffset2ndLayer,PPEGlow.L_02_NVG_OVERLAY1,PPOperators.SET);			
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_OVERLAYCOLOR,m_OverlayColor2ndLayer,PPEGlow.L_03_NVG_OVERLAY2,PPOperators.SET); //0.0, 0.48, 0.55, 0
				SetTargetValueFloat(PostProcessEffectType.Glow,PPEGlow.PARAM_OVERLAYFACTOR,true,m_OverlayFactor2ndLayer,PPEGlow.L_03_NVG_OVERLAY2,PPOperators.HIGHEST);
			//
			break;
			
			
			case NV_PUMPKIN: //pumpkin-o-vision
				SetTargetValueColor(PostProcessEffectType.Glow,PPEGlow.PARAM_COLORIZATIONCOLOR,{1.0,0.2,0.0,0.0},PPEGlow.L_23_NVG,PPOperators.MULTIPLICATIVE);
				SetTargetValueFloat(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY,false,5.5 * UGExposureCoef,PPEExposureNative.L_0_NVG_GOGGLES,PPOperators.ADD);
				SetTargetValueFloatDefault(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_SHARPNESS);
				SetTargetValueFloatDefault(PostProcessEffectType.FilmGrain,PPEFilmGrain.PARAM_GRAINSIZE);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_LIGHT_MULT,false,1.0,PPELightIntensityParamsNative.L_0_NVG,PPOperators.HIGHEST);
				SetTargetValueFloat(PPEExceptions.NVLIGHTPARAMS,PPELightIntensityParamsNative.PARAM_NOISE_MULT,false,0.0,PPELightIntensityParamsNative.L_1_NVG,PPOperators.HIGHEST);
			break;			
			case NV_TRANSITIVE: //camera transition
				
				SetTargetValueFloatDefault(PPEExceptions.EXPOSURE,PPEExposureNative.PARAM_INTENSITY);
			break;
		}
		
		m_CurrentMode = mode;
	}
	
}
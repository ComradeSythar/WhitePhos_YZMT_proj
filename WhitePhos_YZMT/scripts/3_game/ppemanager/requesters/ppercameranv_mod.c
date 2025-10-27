//https://chatgpt.com/share/68899f26-9bb4-800e-9d02-b887891d338b

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
		
		autoptr array<float> m_OverlayColor = { 0.0, 0.22, 0.27, 0 };
		autoptr array<float> m_OverlayColor2ndLayer = { 0.0, 0.22, 0.27, 0 };
		autoptr array<float> m_OverlayColorDaytime = { 0.0, 0.10, 0.27, 1 };
		autoptr array<float> m_OverlayColorOptics = { 0.0, 0.24, 0.27, 0 };
		
		float m_DesaturationAmt = 0.175; 
		float m_DesaturationAmtDaytime = 0.3;
		float m_FilmGrainSharpness = 4.8;	
		float m_FilmGrainSharpnessDaytime = 5.7;
		float m_FilmGrainSize = 2.0; 
		float m_FilmGrainSizeDaytime = 1;
		float m_FilmGrainFrequency = 1; 
		float m_FilmGrainFrequencyOptics = 1; 
		float m_FilmGrainFrequencyDaytime = 8;
		float m_LightIntensityAmp_NV = 5.8;
		float m_LightIntensityAmp_Daytime = 2.5;
				
		float m_DefaultGogglesContrast = 0.85;
		
		autoptr array<float> m_Overlay1ColorMult = { 0.0,0.02,0.02,0 };
		float m_Overlay1LightMultFact = 0;
		float m_Overlay1LightMultNoise = 0;
		
		autoptr array<float> m_Overlay2ColorSet = { 0.0,0.0,0.0,0 };
		float m_Overlay2OverlayFactor = 0.3;
		float m_ColorOffset2ndLayer = -0.030;
		float m_OverlayFactor2ndLayer = 0.06;
		
		
		float m_DefaultNVOpticContrast = 1.3;
		float m_DefaultNVOpticLightMult = 2.0;
		float m_DefaultNVOpticLightNoise = 0.35;
		float m_DefaultNVOpticLightOffset = -0.045;
		float m_DefaultNVOpticLightOverlayFac = 0.070;
		
		autoptr array<float> m_DaytimeNVOpticOverlayColor = { 0.0, 0.48, 0.55, 0 };
		float m_DaytimeNVOpticOverlayFactor = 0.6;
		float m_DaytimeNVOpticLightOffset = -0.1;
		float m_DaytimeNVOpticLightMult = 1.0;
		float m_DaytimeNVOpticLightNoise = 0.6;
		
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
#pragma once

namespace game {
    enum ClassID_t {
        CAI_BaseNPC = 0,
        CAK47,
        CBaseAnimating,
        CBaseAnimatingOverlay,
        CBaseAttributableItem,
        CBaseButton,
        CBaseCombatCharacter,
        CBaseCombatWeapon,
        CBaseCSGrenade,
        CBaseCSGrenadeProjectile,
        CBaseDoor,
        CBaseEntity,
        CBaseFlex,
        CBaseGrenade,
        CBaseParticleEntity,
        CBasePlayer,
        CBasePropDoor,
        CBaseTeamObjectiveResource,
        CBaseTempEntity,
        CBaseToggle,
        CBaseTrigger,
        CBaseViewModel,
        CBaseVPhysicsTrigger,
        CBaseWeaponWorldModel,
        CBeam,
        CBeamSpotlight,
        CBoneFollower,
        CBRC4Target,
        CBreachCharge,
        CBreachChargeProjectile,
        CBreakableProp,
        CBreakableSurface,
        CBumpMine,
        CBumpMineProjectile,
        CC4,
        CCascadeLight,
        CChicken,
        CColorCorrection,
        CColorCorrectionVolume,
        CCSGameRulesProxy,
        CCSPlayer,
        CCSPlayerResource,
        CCSRagdoll,
        CCSTeam,
        CDangerZone,
        CDangerZoneController,
        CDEagle,
        CDecoyGrenade,
        CDecoyProjectile,
        CDrone,
        CDronegun,
        CDynamicLight,
        CDynamicProp,
        CEconEntity,
        CEconWearable,
        CEmbers,
        CEntityDissolve,
        CEntityFlame,
        CEntityFreezing,
        CEntityParticleTrail,
        CEnvAmbientLight,
        CEnvDetailController,
        CEnvDOFController,
        CEnvGasCanister,
        CEnvParticleScript,
        CEnvProjectedTexture,
        CEnvQuadraticBeam,
        CEnvScreenEffect,
        CEnvScreenOverlay,
        CEnvTonemapController,
        CEnvWind,
        CFEPlayerDecal,
        CFireCrackerBlast,
        CFireSmoke,
        CFireTrail,
        CFish,
        CFists,
        CFlashbang,
        CFogController,
        CFootstepControl,
        CFunc_Dust,
        CFunc_LOD,
        CFuncAreaPortalWindow,
        CFuncBrush,
        CFuncConveyor,
        CFuncLadder,
        CFuncMonitor,
        CFuncMoveLinear,
        CFuncOccluder,
        CFuncReflectiveGlass,
        CFuncRotating,
        CFuncSmokeVolume,
        CFuncTrackTrain,
        CGameRulesProxy,
        CGrassBurn,
        CHandleTest,
        CHEGrenade,
        CHostage,
        CHostageCarriableProp,
        CIncendiaryGrenade,
        CInferno,
        CInfoLadderDismount,
        CInfoMapRegion,
        CInfoOverlayAccessor,
        CItem_Healthshot,
        CItemCash,
        CItemDogtags,
        CKnife,
        CKnifeGG,
        CLightGlow,
        CMapVetoPickController,
        CMaterialModifyControl,
        CMelee,
        CMolotovGrenade,
        CMolotovProjectile,
        CMovieDisplay,
        CParadropChopper,
        CParticleFire,
        CParticlePerformanceMonitor,
        CParticleSystem,
        CPhysBox,
        CPhysBoxMultiplayer,
        CPhysicsProp,
        CPhysicsPropMultiplayer,
        CPhysMagnet,
        CPhysPropAmmoBox,
        CPhysPropLootCrate,
        CPhysPropRadarJammer,
        CPhysPropWeaponUpgrade,
        CPlantedC4,
        CPlasma,
        CPlayerPing,
        CPlayerResource,
        CPointCamera,
        CPointCommentaryNode,
        CPointWorldText,
        CPoseController,
        CPostProcessController,
        CPrecipitation,
        CPrecipitationBlocker,
        CPredictedViewModel,
        CProp_Hallucination,
        CPropCounter,
        CPropDoorRotating,
        CPropJeep,
        CPropVehicleDriveable,
        CRagdollManager,
        CRagdollProp,
        CRagdollPropAttached,
        CRopeKeyframe,
        CSCAR17,
        CSceneEntity,
        CSensorGrenade,
        CSensorGrenadeProjectile,
        CShadowControl,
        CSlideshowDisplay,
        CSmokeGrenade,
        CSmokeGrenadeProjectile,
        CSmokeStack,
        CSnowball,
        CSnowballPile,
        CSnowballProjectile,
        CSpatialEntity,
        CSpotlightEnd,
        CSprite,
        CSpriteOriented,
        CSpriteTrail,
        CStatueProp,
        CSteamJet,
        CSun,
        CSunlightShadowControl,
        CSurvivalSpawnChopper,
        CTablet,
        CTeam,
        CTeamplayRoundBasedRulesProxy,
        CTEArmorRicochet,
        CTEBaseBeam,
        CTEBeamEntPoint,
        CTEBeamEnts,
        CTEBeamFollow,
        CTEBeamLaser,
        CTEBeamPoints,
        CTEBeamRing,
        CTEBeamRingPoint,
        CTEBeamSpline,
        CTEBloodSprite,
        CTEBloodStream,
        CTEBreakModel,
        CTEBSPDecal,
        CTEBubbles,
        CTEBubbleTrail,
        CTEClientProjectile,
        CTEDecal,
        CTEDust,
        CTEDynamicLight,
        CTEEffectDispatch,
        CTEEnergySplash,
        CTEExplosion,
        CTEFireBullets,
        CTEFizz,
        CTEFootprintDecal,
        CTEFoundryHelpers,
        CTEGaussExplosion,
        CTEGlowSprite,
        CTEImpact,
        CTEKillPlayerAttachments,
        CTELargeFunnel,
        CTEMetalSparks,
        CTEMuzzleFlash,
        CTEParticleSystem,
        CTEPhysicsProp,
        CTEPlantBomb,
        CTEPlayerAnimEvent,
        CTEPlayerDecal,
        CTEProjectedDecal,
        CTERadioIcon,
        CTEShatterSurface,
        CTEShowLine,
        CTesla,
        CTESmoke,
        CTESparks,
        CTESprite,
        CTESpriteSpray,
        CTest_ProxyToggle_Networkable,
        CTestTraceline,
        CTEWorldDecal,
        CTriggerPlayerMovement,
        CTriggerSoundOperator,
        CVGuiScreen,
        CVoteController,
        CWaterBullet,
        CWaterLODControl,
        CWeaponAug,
        CWeaponAWP,
        CWeaponBaseItem,
        CWeaponBizon,
        CWeaponCSBase,
        CWeaponCSBaseGun,
        CWeaponCycler,
        CWeaponElite,
        CWeaponFamas,
        CWeaponFiveSeven,
        CWeaponG3SG1,
        CWeaponGalil,
        CWeaponGalilAR,
        CWeaponGlock,
        CWeaponHKP2000,
        CWeaponM249,
        CWeaponM3,
        CWeaponM4A1,
        CWeaponMAC10,
        CWeaponMag7,
        CWeaponMP5Navy,
        CWeaponMP7,
        CWeaponMP9,
        CWeaponNegev,
        CWeaponNOVA,
        CWeaponP228,
        CWeaponP250,
        CWeaponP90,
        CWeaponSawedoff,
        CWeaponSCAR20,
        CWeaponScout,
        CWeaponSG550,
        CWeaponSG552,
        CWeaponSG556,
        CWeaponShield,
        CWeaponSSG08,
        CWeaponTaser,
        CWeaponTec9,
        CWeaponTMP,
        CWeaponUMP45,
        CWeaponUSP,
        CWeaponXM1014,
        CWeaponZoneRepulsor,
        CWorld,
        CWorldVguiText,
        DustTrail,
        MovieExplosion,
        ParticleSmokeGrenade,
        RocketTrail,
        SmokeTrail,
        SporeExplosion,
        SporeTrail,
    };

    enum CSWeaponID_t {
        WEAPON_NONE = 0,
        WEAPON_DEAGLE = 1,
        WEAPON_ELITE = 2,
        WEAPON_FIVESEVEN = 3,
        WEAPON_GLOCK = 4,
        WEAPON_AK47 = 7,
        WEAPON_AUG = 8,
        WEAPON_AWP = 9,
        WEAPON_FAMAS = 10,
        WEAPON_G3SG1 = 11,
        WEAPON_GALILAR = 13,
        WEAPON_M249 = 14,
        WEAPON_M4A1 = 16,
        WEAPON_MAC10 = 17,
        WEAPON_P90 = 19,
        WEAPON_ZONE_REPULSOR = 20,
        WEAPON_MP5SD = 23,
        WEAPON_UMP45 = 24,
        WEAPON_XM1014 = 25,
        WEAPON_BIZON = 26,
        WEAPON_MAG7 = 27,
        WEAPON_NEGEV = 28,
        WEAPON_SAWEDOFF = 29,
        WEAPON_TEC9 = 30,
        WEAPON_TASER = 31,
        WEAPON_HKP2000 = 32,
        WEAPON_MP7 = 33,
        WEAPON_MP9 = 34,
        WEAPON_NOVA = 35,
        WEAPON_P250 = 36,
        WEAPON_SHIELD = 37,
        WEAPON_SCAR20 = 38,
        WEAPON_SG553 = 39,
        WEAPON_SSG08 = 40,
        WEAPON_KNIFE_GG = 41,
        WEAPON_KNIFE = 42,
        WEAPON_FLASHBANG = 43,
        WEAPON_HEGRENADE = 44,
        WEAPON_SMOKEGRENADE = 45,
        WEAPON_MOLOTOV = 46,
        WEAPON_DECOY = 47,
        WEAPON_INCGRENADE = 48,
        WEAPON_C4 = 49,
        WEAPON_HEALTHSHOT = 57,
        WEAPON_KNIFE_T = 59,
        WEAPON_M4A1_SILENCER = 60,
        WEAPON_USP_SILENCER = 61,
        WEAPON_CZ75A = 63,
        WEAPON_REVOLVER = 64,
        WEAPON_TAGRENADE = 68,
        WEAPON_FISTS = 69,
        WEAPON_BREACHCHARGE = 70,
        WEAPON_TABLET = 72,
        WEAPON_MELEE = 74,
        WEAPON_AXE = 75,
        WEAPON_HAMMER = 76,
        WEAPON_SPANNER = 78,
        WEAPON_KNIFE_GHOST = 80,
        WEAPON_FIREBOMB = 81,
        WEAPON_DIVERSION = 82,
        WEAPON_FRAG_GRENADE = 83,
        WEAPON_SNOWBALL = 84,
        WEAPON_BUMPMINE = 85,
        WEAPON_KNIFE_BAYONET = 500,
        WEAPON_KNIFE_CSS = 503,
        WEAPON_KNIFE_FLIP = 505,
        WEAPON_KNIFE_GUT = 506,
        WEAPON_KNIFE_KARAMBIT = 507,
        WEAPON_KNIFE_M9_BAYONET = 508,
        WEAPON_KNIFE_TACTICAL = 509,
        WEAPON_KNIFE_FALCHION = 512,
        WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
        WEAPON_KNIFE_BUTTERFLY = 515,
        WEAPON_KNIFE_PUSH = 516,
        WEAPON_KNIFE_CORD = 517,
        WEAPON_KNIFE_CANIS = 518,
        WEAPON_KNIFE_URSUS = 519,
        WEAPON_KNIFE_GYPSY_JACKKNIFE = 520,
        WEAPON_KNIFE_OUTDOOR = 521,
        WEAPON_KNIFE_STILETTO = 522,
        WEAPON_KNIFE_WIDOWMAKER = 523,
        WEAPON_KNIFE_SKELETON = 525,
        GLOVE_STUDDED_BROKENFANG = 4725,
        GLOVE_STUDDED_BLOODHOUND = 5027,
        GLOVE_T_SIDE = 5028,
        GLOVE_CT_SIDE = 5029,
        GLOVE_SPORTY = 5030,
        GLOVE_SLICK = 5031,
        GLOVE_LEATHER_HANDWRAPS = 5032,
        GLOVE_MOTORCYCLE = 5033,
        GLOVE_SPECIALIST = 5034,
        GLOVE_STUDDED_HYDRA = 5035,
        SPECIAL_AGENT_BLUEBERRIES_BUCKSHOT = 4619,
        SPECIAL_AGENT_TWO_TIMES_MCCOY_TACP = 4680,
        SPECIAL_AGENT_COMMANDOR_MAE_JAMISON = 4711,
        SPECIAL_AGENT_1ST_LIEUTENANT_FARLOW,
        SPECIAL_AGENT_JOHN_KASK,
        SPECIAL_AGENT_BIO_HAZ_SPECIALIST,
        SPECIAL_AGENT_SERGEANT_BOMBSON,
        SPECIAL_AGENT_CHEM_HAZ_SPECIALIST,
        SPECIAL_AGENT_REZAN_THE_REDSHIRT = 4718,
        SPECIAL_AGENT_SIR_BLOODY_MIAMI_DARRYL = 4726,
        SPECIAL_AGENT_SAFECRACKER_VOLTZMANN,
        SPECIAL_AGENT_LITTLE_KEV,
        SPECIAL_AGENT_GETAWAY_SALLY = 4730,
        SPECIAL_AGENT_NUMBER_K = 4732,
        SPECIAL_AGENT_SIR_BLOODY_SILENT_DARRYL = 4733,
        SPECIAL_AGENT_SIR_BLOODY_SKULLHEAD_DARRYL,
        SPECIAL_AGENT_SIR_BLOODY_DARRYL_ROYALE,
        SPECIAL_AGENT_SIR_BLOODY_LOUDMOUTH_DARRYL,
        SPECIAL_AGENT_T = 5036,
        SPECIAL_AGENT_CT = 5037,
        SPECIAL_AGENT_GROUND_REBEL = 5105,
        SPECIAL_AGENT_OSIRIS,
        SPECIAL_AGENT_SHAHMAT,
        SPECIAL_AGENT_MUHLIK,
        SPECIAL_AGENT_SOLDIER = 5205,
        SPECIAL_AGENT_ENFORCER,
        SPECIAL_AGENT_SLINGSHOT,
        SPECIAL_AGENT_STREET_SOLDIER,
        SPECIAL_AGENT_OPERATOR = 5305,
        SPECIAL_AGENT_MARKUS_DELROW,
        SPECIAL_AGENT_MICHAEL_SYFERS,
        SPECIAL_AGENT_AVA,
        SPECIAL_AGENT_3RD_COMMANDO_COMPANY = 5400,
        SPECIAL_AGENT_SEAL_TEAM_6_SOLDIER,
        SPECIAL_AGENT_BUCKSHOT,
        SPECIAL_AGENT_TWO_TIMES_MCCOY_USAF,
        SPECIAL_AGENT_RICKSAW,
        SPECIAL_AGENT_DRAGOMIR = 5500,
        SPECIAL_AGENT_MAXIMUS,
        SPECIAL_AGENT_REZAN_THE_READY,
        SPECIAL_AGENT_BLACKWOLF = 5503,
        SPECIAL_AGENT_THE_DOCTOR,
        SPECIAL_AGENT_DRAGOMIR_FOOTSOLDIERS,
        SPECIAL_AGENT_B_SQUADRON_OFFICER = 5601
    };

    enum player_controls_t {
        IN_ATTACK = ( 1 << 0 ),
        IN_JUMP = ( 1 << 1 ),
        IN_DUCK = ( 1 << 2 ),
        IN_FORWARD = ( 1 << 3 ),
        IN_BACK = ( 1 << 4 ),
        IN_USE = ( 1 << 5 ),
        IN_CANCEL = ( 1 << 6 ),
        IN_LEFT = ( 1 << 7 ),
        IN_RIGHT = ( 1 << 8 ),
        IN_MOVELEFT = ( 1 << 9 ),
        IN_MOVERIGHT = ( 1 << 10 ),
        IN_ATTACK2 = ( 1 << 11 ),
        IN_RUN = ( 1 << 12 ),
        IN_RELOAD = ( 1 << 13 ),
        IN_ALT1 = ( 1 << 14 ),
        IN_ALT2 = ( 1 << 15 ),
        IN_SCORE = ( 1 << 16 ),
        IN_SPEED = ( 1 << 17 ),
        IN_WALK = ( 1 << 18 ),
        IN_ZOOM = ( 1 << 19 ),
        IN_WEAPON1 = ( 1 << 20 ),
        IN_WEAPON2 = ( 1 << 21 ),
        IN_BULLRUSH = ( 1 << 22 ),
    };
    struct input_t {
        char pad_0x00[ 0x8 ];
        bool m_fTrackIRAvailable;
        bool m_fMouseInitialized;
        bool m_fMouseActive;
        bool m_fJoystickAdvancedInit;
        char pad_0x08[ 0x2C ]; // [0x2C]
        uintptr_t m_pKeys;
        char pad_0x38[ 0x64 ];
        int pad_0x41;
        int pad_0x42;
        bool m_fCameraInterceptingMouse;
        bool m_fCameraInThirdPerson;
        bool m_fCameraMovingWithMouse;
        vec3_t m_vecCameraOffset;
        bool m_fCameraDistanceMove;
        int m_nCameraOldX;
        int m_nCameraOldY;
        int m_nCameraX;
        int m_nCameraY;
        bool m_CameraIsOrthographic;
        vec3_t m_angPreviousViewAngles;
        vec3_t m_angPreviousViewAnglesTilt;
        float m_flLastForwardMove;
        int m_nClearInputState;
        char pad_0xE4[ 0x4 ];
        uintptr_t m_pCommands;
        uintptr_t m_pVerifiedCommands;
    };
}

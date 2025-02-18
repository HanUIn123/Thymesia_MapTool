#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum MOUSEKEYSTATE { DIM_LB, DIM_RB, DIM_MB, DIM_END, DIM_LB_Release};
	enum MOUSEMOVESTATE { DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };

	enum class PROTOTYPE { TYPE_GAMEOBJECT, TYPE_COMPONENT };

	enum class GROUP_TYPE {
		PLAYER,	
		PLAYER_WEAPON,	
		MONSTER,		
		ENEMY,		
		OBJECT,		
		GROUP_END,
	};	

	enum class EVENT_TYPE{
		EVENT_1,	
		EVENT_2,	
		EVENT_3,	
		EVENT_4,		
		EVENT_5,		
	};

	enum CHANNELID
	{
		SOUND_BGM,
		SOUND_ACTION,
		SOUND_EFFECT,
		SOUND_MOREEFFECT,
		SOUND_SURROUNDING,
		SOUND_NATURAL,
		SOUND_ElectricEel,
		SOUND_ElectricEel_Collision,
		SOUND_RHINO,
		SOUND_STONE,
		MAXCHANNEL = 32,
	};
	
}
#endif // Engine_Enum_h__

#pragma once
#include "bw_python.hh"
#include "Vectors.hh"






struct Entity : public PyObject
{
	Vector3 position();

	
};
struct Avatar : public Entity
{
	Py_dicthead;
	Py_Attribute(Avatar,PyUnicodeObject*, name);

	Py_AttributePRIVATE(Avatar,PyINT8Object*, dead);

	bool is_dead()
	{
		auto isdeadproperty = this->dead();
		return isdeadproperty->get();
	}



/*Avatar.Entity.PyObjectPlus.object
{
INT8 lock_cancel_trade
INT64 DelayedPutOnItemID
FLOAT32 ItemsWeight
INT32 CreditNumber
UINT8 HushNotifications
INT64 ActiveItemID
 BLOB ActiveWeaponSet2
ARRAY ActiveGadgetList
ARRAY ActiveArtifactList
ARRAY FakeActiveGadgetList
ARRAY CarryingItems
ARRAY KnowingRecipes
INT8 CanShoot
INT8 CanUse
PYTHON neededIDFunction
 BLOB ExchangeProperties
MAILBOX ExchangeOpponentMB
INT32 LastExchangeID
ARRAY pendingItems
INT32 GoldCreditNumber
ARRAY ActiveItemPollutions
INT64 BellyItemID
INT64 flashLightID
ARRAY BatteryConsumers
ARRAY StoredItems
ARRAY coloriseEmblems
ARRAY colorDelegates
ARRAY myEmblems
UINT8 is_use_extractor
INT64 radio_working
UINT8 dead
UINT8 canTakeDamage
UINT8 invulnerable
UINT8 mobNoAggr
ARRAY allowedDamagers
ARRAY damage_restrictions
UINT8 canDamage
ARRAY effects
FLOAT32 HPKoeff
ARRAY effectsVisibleForAll
INT8 crouching_or_crawling
UINT8 binoculing
INT8 weaponStatus
UNICODE_STRING name
INT32 frags
INT32 deaths
ARRAY EquippedCond2
 BLOB EquippedArmor
 BLOB EquippedVisibleAttaches
 BLOB EquippedVisibleAttachesIDS
INT8 EquipModes
INT32 transport_seat
INT32 lastGlobalMessagesPoll
 BLOB TP_params
 BLOB TP_previous_position
UINT8 TP_params_changed
FLOAT32 chanceModCD
FLOAT32 powerModCD
INT16 sturdinessMod
UINT8 ExpCoefficient
UINT8 CharacterCombatLevel
UINT8 CharacterSurvivalLevel
UINT8 CharacterOtherLevel
INT8 CharacterClass
UINT32 CombatExperience
UINT32 SurvivalExperience
UINT32 OtherExperience
INT32 CombatSkillPoints
INT32 SurvivalSkillPoints
INT32 OtherSkillPoints
INT32 CombatPerkPoints
INT32 SurvivalPerkPoints
INT32 OtherPerkPoints
FLOAT32 PlayerDefaultCounter
ARRAY WeaponAdaptations
INT32 WeaponAdaptationCounter
ARRAY defences
INT32 SocialStatus
 BLOB CombatSkills
 BLOB SurvivalSkills
 BLOB OtherSkills
ARRAY mobs
INT8 mobsType
STRING mobs_subtype
FLOAT64 lastMobDeathTime
ARRAY st_avatars
INT8 pend_state
ARRAY CellQuestPersistProp
PYTHON QuestPersistentData
PYTHON pers_data_base
ARRAY questsPendingRemoval
ARRAY QuestsCounters
 BLOB PVPInfo
 BLOB QuestsList
ARRAY favoriteList
ARRAY CellQuests
ARRAY _effect_quests
 BLOB savePoint
ARRAY questTakenTime
ARRAY questScenariesOnTest
ARRAY questScenaries
ARRAY lastDialogs
INT64 restoreDialog
INT32 lastInterlocutorID
INT16 tutorial_phase
ARRAY quest_listeners
 BLOB autofailblob
ARRAY _visited_events
STRING clanName
ARRAY clanEnemies
ARRAY clanAlliancesIDs
INT32 clanEmblemID
INT64 clanID
INT64 cellClanID
INT64 localBaseClanID
INT64 clanRights
STRING nameBaseToCapture
STRING underatack_base_name
INT64 ownerBase
 BLOB base_tracker
 BLOB reinfp_tracker
INT8 show_tracker
MAILBOX party
ARRAY member_ids
ARRAY party_quests
ARRAY visited_npcs
 BLOB lastSpatialInfo
 BLOB ch_HitPoints
 BLOB ch_MaxHitPoints
 BLOB ch_CombatPoints
 BLOB ch_MaxCombatPoints
 BLOB ch_Stamina
 BLOB ch_MaxStamina
 BLOB ch_MoveSpeed
 BLOB ch_Accuracy
 BLOB ch_HitPointsRegeneration
 BLOB ch_StaminaRegeneration
 BLOB ch_CombatPointsRegeneration
 BLOB ch_MaxWeight
 BLOB ch_Defence
 BLOB ch_Penetration
 BLOB ch_DamageAbsorb
 BLOB ch_Strength
 BLOB ch_Agility
 BLOB ch_Perception
 BLOB ch_Intelligence
 BLOB ch_Endurance
 BLOB ch_Psy
ARRAY paint_items
ARRAY relations
ARRAY fraction_relations_copy
FLOAT32 lastWriteTime
ARRAY relationsWithFractions
ARRAY friends_list
ARRAY blackList
 BLOB __base_timer_controllers__
 BLOB __base_call_once_controllers__
PYTHON __base_args_by_user_data__
 BLOB __timer_controllers__
 BLOB __call_once_controllers__
PYTHON __args_by_user_data__
ARRAY instanceSave
UINT8 dungeon_id
INT8 teamID
UINT8 inPVPinstance
MAILBOX csRoom
MAILBOX csRoomCell
ARRAY gifts
ARRAY sentgifts
ARRAY mqWinner
UINT16 transformationID
ARRAY transformationProperty
ARRAY saved_pos
ARRAY saved_time
FLOAT32 last_maxspeed
FLOAT32 current_maxspeed
VECTOR3 _ring_disp
INT32 vacant_positions
ARRAY attackers_data
INT32 current_event_id
INT32 tmp_grenade_thr
UINT8 account_is_frod
 BLOB personality
MAILBOX specMBspace
UINT8 candle
UINT8 is_burning
 BLOB vert_ladder_info
UINT8 im_in_jail
INT8 usingGesture
UINT8 cellPrintDebug
INT8 CountWaitChetsResponse
STRING parentAccountName
INT32 randomKeyListProccess
STRING lastHWID
INT64 parentAccountDBID_cell
INT32 proximity_id
INT32 anomaly_proxy_id
INT8 prem_id
INT8 boost_id
INT8 ninjaMode
UINT8 isAdrenaline
PYTHON ListInvite
PYTHON friendsList
UINT8 AgrFlag
UNICODE_STRING HUNTER_killerName
STRING HUNTER_killerClanName
INT8 HUNTER_killerWanted
INT8 HUNTER_iWanted
INT8 HUNTER_iFiledHunting
INT32 HUNTER_killerKarma
ARRAY HUNTER_listOfWanted
ARRAY HUNTER_lostListOfWanted
FLOAT32 hungryValuePrivate
FLOAT32 thirstValuePrivate
UINT8 isPlayerInHotRegion
UINT8 speak_area_captured
FLOAT32 hungry
FLOAT32 thirst
UINT8 gun_invul
 BLOB last_shot
 BLOB shootFairness
ARRAY restrictions
INT64 dbID_on_cell
ARRAY mapNotes
ARRAY visitedSpaces
INT64 chat_off_until
UINT8 chat_off
UINT8 cell_chat_off
INT64 cell_chat_off_until
UINT8 haveWebClient
FLOAT64 userCommandLastUse
INT64 fPlayerWiped
INT64 parentAccountDBID
UNICODE_STRING nameOnBase
MAILBOX parentAccount
MAILBOX cellParentAccount
INT32 logoutTimer
MAILBOX spawnerBase
UINT8 createByDev
UINT8 baseAccessLevel
UINT8 cellAccessLevel
UINT8 UserFromMasterPassword
UINT8 baseUserFromMasterPassword
UINT8 clientAccessLevel
UINT8 sprinting
INT8 pvpFlag
UINT8 pvpFree
INT32 pvpCounter
FLOAT64 lastLogInTime
FLOAT64 lastLogOutTime
INT32 pkCounter
INT32 karma
INT32 worldLoadTimoutTimer
INT32 worldLoad
STRING lastSpace
INT64 groupID
UINT8 in_combat
FLOAT32 waterHeight
INT32 waterType
ARRAY visitedSpawnAreas
STRING mainSpawnArea
 BLOB mainSpawnAreaConfig
STRING prevSpawnArea
INT32 artifactVisionControllerID
ARRAY Possibilities
ARRAY quickSlotBars
INT32 quickSlotActiveLineNumber
 BLOB gps_teleport_info
UINT8 used_item_on_target
INT64 respawn_timer_type
ARRAY weather_stack_value
ARRAY weather_stack_id
INT8 lie_down_counter
FLOAT64 safe_exit_time
BLOB looting_info
ARRAY current_safe_info
INT64 filters
BLOB use_heal_item
UINT8 isMovingTest
FLOAT32 stamina_delta_usage
ARRAY converted_items_counters
UINT8 radio_talking
MAILBOX _cabman_seat
 BLOB lastTransportPos
INT32 base_space_id

}*/




};

struct CursorCamera : public PyObject // CursorCamera : BaseCamera : PyObjectPlus : object
{

};
struct CameraImpl  // CursorCamera : BaseCamera : PyObjectPlus : object
{
	bool ProjectWorldToScreen(Vector3 target, Vector2* screenpos);
	static CameraImpl* Instance();
};






struct PlayerAvatar : public Avatar
{
	Py_dicthead;
	Py_Attribute(PlayerAvatar, CursorCamera*, AvatarCam); // CursorCamera : BaseCamera : PyObjectPlus : object



};
struct Creature : public Entity
{
	Py_dicthead;
	Py_Attribute(Creature, PyUnicodeObject*, name);
	Py_AttributePRIVATE(Creature, PyINT8Object*, dead);
	bool is_dead()
	{
		auto isdeadproperty = this->dead();
		return isdeadproperty->get();
	}


};
struct NPC : public Avatar
{
	


};
struct EntityMapEntry
{
	EntityMapEntry* next();
	Entity* entity();
	int entityID();
};
struct EntityMap
{
	EntityMapEntry* iter;
	int num;
};

struct EntityManager
{
	static EntityManager* instance(); //  https://github.com/v2v3v4/BigWorld-Engine-2.0.1/blob/master/src/client/entity_manager.hpp#L48
	EntityMap Entities();
};
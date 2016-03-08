// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_Asset_Paths.h"

// bot items
const FString FAIE_Asset_Paths::DefaultBotMesh = FString("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'");
const FString FAIE_Asset_Paths::DefaultBotAnim = FString("AnimBlueprint'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C'");
const FString FAIE_Asset_Paths::DefaultBotUI = FString("WidgetBlueprint'/Game/AI_Example/UI/StatBox.StatBox_C'");
const FString FAIE_Asset_Paths::DefaultBotVoice = FString("DialogueVoice'/Game/AI_Example/Blueprints/AI/Audio/Voices/MaleSing.MaleSing'");

// bot behavior
const FString FAIE_Asset_Paths::BotHealthBehavior = FString("BehaviorTree'/Game/AI_Example/Blueprints/AI/BehaviorTrees/StatBehaviors/Health_BT.Health_BT'");
const FString FAIE_Asset_Paths::BotStaminaBehavior = FString("BehaviorTree'/Game/AI_Example/Blueprints/AI/BehaviorTrees/StatBehaviors/Stamina_BT.Stamina_BT'");

// audio
const FString FAIE_Asset_Paths::DefaultDialogVoice = FString("DialogueVoice'/Game/AI_Example/Blueprints/AI/Audio/Voices/NeutSing.NeutSing'");
const FString FAIE_Asset_Paths::BotFoundItWave = FString("DialogueWave'/Game/AI_Example/Blueprints/AI/Audio/Waves/FoundStuff_DW.FoundStuff_DW'");

// Food items
const FString FAIE_Asset_Paths::DefaultFoodMesh = FString("StaticMesh'/Game/InfinityBladeGrassLands/Environments/Misc/Exo_Deco01/StaticMesh/SM_WoodenBarrel_Intact.SM_WoodenBarrel_Intact'");
const FString FAIE_Asset_Paths::PlantFoodMesh = FString("StaticMesh'/Game/AI_Example/Assets/Meshes/Apple.Apple'");
const FString FAIE_Asset_Paths::PoisonFoodMesh = FString("StaticMesh'/Game/InfinityBladeGrassLands/Environments/Plains/Env_Plains_Statues/StaticMesh/SM_Plains_Angel_Statue_01.SM_Plains_Angel_Statue_01'");

const FString FAIE_Asset_Paths::TreeMesh = FString("StaticMesh'/Game/AI_Example/Assets/Meshes/Tree.Tree'");
#pragma once
#include "CRPGCoreTypes.generated.h"

UENUM(BlueprintType)
enum class EScreenMode : uint8
{
	Field = 0,
	Battle, 
	GamePause,
	GameOver
};

UENUM(BlueprintType)
enum class ETurnUser : uint8
{
	Player = 0,
	Enemy
};

USTRUCT(BlueprintType)
struct FSkillData
{
	GENERATED_USTRUCT_BODY()

	int32 SkillIndex = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill")
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill")
	int32 MaxCount;
	int32 LeftCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill")
	int32 CoolTime;
	int32 LeftCool;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill")
	bool Limited;
};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill")
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill")
	bool IsUsable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill")
	bool IsHealing;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill")
	float HealAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill")
	int32 MaxCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Skill")
	int32 LeftCount;
};


//Animation

class AnimUtils
{
public:
	template <typename T>
	static T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		if (!Animation) return nullptr;

		const auto NotifyEvents = Animation->Notifies;
		for (auto NotifyEvent : NotifyEvents)
		{
			auto AnimNotify = Cast<T>(NotifyEvent.Notify);
			if (AnimNotify)
			{
				return AnimNotify;
			}
		}
		return nullptr;
	}
};
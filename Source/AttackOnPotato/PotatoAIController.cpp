// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackOnPotato.h"
#include "PotatoAIController.h"



APotatoAIController::APotatoAIController(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BehaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTree>(this, TEXT("BehaviorComp"));
	BlackboardComp = ObjectInitializer.CreateDefaultSuboject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	// Match with the BadPotatoBlackboard
	//CurrentWaypointKeyName = "CurrentWaypoint";
	BotTypeKeyName = "BotType";
	TargetEnemyKeyName = "TargetEnemy";

	//init playerstate so we can assign a team index to Ai
	bWantsPlayerState = true;
}

void APotatoAIController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);

	ABadPotato* PotatoBot = Cast<Character>(InPawn);

	if (PotatoBot)
	{
		if (PotatoBot->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*PotatoBot->BeehaviorTree->BlackBoardAsset);

			SetBlackBoardBotType(PotatoBot->BotType);
		}

		BehaviorComp->StartTree(*PotatoBot->BehaviorTree);
	}


}

void APotatoAIController::UnPossess()
{
	Super::UnPosses();

	//stop behavior

	BehaviorComp->StopTree();
}

//need to implement the waypoint class
/*APotatoWayPoint * APotatoAIController::GetWaypoint()
{
	if (BlackboardComp)
	{
		return Cast<APotatoWayPoint>(BlackboardComp->GetValueAsObject(CurrentWaypointKeyName)); // returns the current waypoint of the enemy
	}

	return nullptr;
}*/
// need to implement the character class
/*ABaseCharacter* APotatoAIController::GetTargetEnemy()
{
	if (BlackboardComp)
	{
		return Cast<ABaseCharacter>(BlackboardComp->GetValueAsObject(TargetEnemyKeyName)); // returns the current target
	}
	
	return nullptr;
}*/

/*void APotatoAIController::SetWaypoint(APotatoWaypoint * NewWayPoint)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(CuyrrentWaypointKeyName, NewWaypoint); // sets the updated waypoint to the new waypoint, gives this the label of CurrentwaypointKeyname
	}
}*/

void APotatoAIController::SetTargetEnemy(APawn * NewTarget)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(TargetEnemyKeyName, NewTarget);  // sets the new enemy to the pawn object given, gives this the label of TargetEnemyKeyName
	}
}

void APotatoAIController::SetBlackboardBotType(EBotBehaviorType newType)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsEnum(BotTypeKeyName, (unit8)NewType);
	}
}
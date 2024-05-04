// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MonoGrinding/AllyComponent.h"
#include "MonoGrinding/DefaultUnitOrchestrator.h"
#include "MonoGrindingCharacter.h"
#include "UObject/ObjectMacros.h"

#include "DefaultPlayer.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FManaChanged, int, NewValue);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class MONOGRINDING_API ADefaultPlayer : public AMonoGrindingCharacter {
    GENERATED_BODY()

protected:
    bool TryUseMana(int Amount);

    void Move(const FInputActionValue &Value);

    void Look(const FInputActionValue &Value);
    void MoveAllies();
    void SummonOrEnlistUnit();
    void CreateAllyAtPosition(FVector Position);

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = Camera,
              meta = (AllowPrivateAccess = "true"))
    USpringArmComponent *CameraBoom;

    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = Camera,
              meta = (AllowPrivateAccess = "true"))
    UCameraComponent *FollowCamera;

    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = Input,
              meta = (AllowPrivateAccess = "true"))
    UInputMappingContext *DefaultMappingContext;

    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = Input,
              meta = (AllowPrivateAccess = "true"))
    UInputAction *JumpAction;

    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = Input,
              meta = (AllowPrivateAccess = "true"))
    UInputAction *MoveAction;

    /** Look Input Action */
    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = Input,
              meta = (AllowPrivateAccess = "true"))
    UInputAction *LookAction;

    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = Input,
              meta = (AllowPrivateAccess = "true"))
    UInputAction *MoveAlliesAction;

    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = Input,
              meta = (AllowPrivateAccess = "true"))
    UInputAction *SummonAllyAction;

public:
    ADefaultPlayer();

    void Tick(float DeltaTime) override;

    FORCEINLINE class USpringArmComponent *GetCameraBoom() const {
        return CameraBoom;
    }

    FORCEINLINE class UCameraComponent *GetFollowCamera() const {
        return FollowCamera;
    }

    UPROPERTY(BlueprintAssignable, Category = "Player|Mana")
    FManaChanged ManaChanged;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Mana")
    int AllyManaCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player|Mana")
    int MaxMana;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Mana")
    int CurrentMana;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ally")
    TArray<UAllyComponent *> Allies;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Debug")
    APlayerController *PlayerController;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ally")
    TSubclassOf<ADefaultUnitOrchestrator> AllyBlueprint;

    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

    void BeginPlay();
    void Enlist(ADefaultUnitOrchestrator *Unit);
};

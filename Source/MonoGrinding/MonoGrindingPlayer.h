// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonoGrindingCharacter.h"
#include "UnitComponent.h"

#include "MonoGrindingPlayer.generated.h"

UCLASS()

class MONOGRINDING_API AMonoGrindingPlayer : public AMonoGrindingCharacter {
    GENERATED_BODY()
protected:
    /** Called for movement input */
    void Move(const FInputActionValue &Value);

    /** Called for looking input */
    void Look(const FInputActionValue &Value);
    void MoveUnits();
    void SummonOrEnlistUnit();
    void CreateAllyAtPosition(FVector Position);

    // APawn interface
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

    /** Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = Camera,
              meta = (AllowPrivateAccess = "true"))
    USpringArmComponent *CameraBoom;

    /** Follow camera */
    UPROPERTY(VisibleAnywhere,
              BlueprintReadOnly,
              Category = Camera,
              meta = (AllowPrivateAccess = "true"))
    UCameraComponent *FollowCamera;

    /** MappingContext */
    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = Input,
              meta = (AllowPrivateAccess = "true"))
    UInputMappingContext *DefaultMappingContext;

    /** Jump Input Action */
    UPROPERTY(EditAnywhere,
              BlueprintReadOnly,
              Category = Input,
              meta = (AllowPrivateAccess = "true"))
    UInputAction *JumpAction;

    /** Move Input Action */
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

    /** MoveAllies Input Action */
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
    /** Returns CameraBoom subobject **/
    FORCEINLINE class USpringArmComponent *GetCameraBoom() const {
        return CameraBoom;
    }

    /** Returns FollowCamera subobject **/
    FORCEINLINE class UCameraComponent *GetFollowCamera() const {
        return FollowCamera;
    }

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ally")
    TArray<UUnitComponent *> Allies;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ally")
    TSubclassOf<AActor> AllyBlueprint;

    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    AMonoGrindingPlayer();

    void BeginPlay();
    void Enlist(UUnitComponent *Unit);
};

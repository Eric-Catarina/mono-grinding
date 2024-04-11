// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/OutputDeviceNull.h"
#include "MonoGrindingCharacter.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent() {
    PrimaryComponentTick.bCanEverTick = true;

    MaxHealth = 100.f;
    Current = MaxHealth;
}

void UHealthComponent::BeginPlay() {
    Super::BeginPlay();

    MovementComponent = GetOwner()->GetComponentByClass<UCharacterMovementComponent>();
    SkeletalMeshComponent = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
    HealthBarWidget = GetOwner()->GetComponentByClass<UWidgetComponent>();
}

void UHealthComponent::TakeDamage(float DamageAmount) {
    SetCurrent(Current - DamageAmount);
}

void UHealthComponent::Heal(float HealAmount) {
    SetCurrent(Current + HealAmount);
}

void UHealthComponent::SetMax(float NewMaxHealth) {
    MaxHealth = NewMaxHealth;
    SetCurrent(MaxHealth);
}

void UHealthComponent::SetCurrent(float NewHealth) {
    if (IsDead)
        return;

    Current = FMath::Clamp(NewHealth, 0.f, MaxHealth);

    if (Current <= 0) {
        DieInternal();
    }

    if (!HealthBarWidget || !HealthBarWidget->GetWidget()) {
        UE_LOG(LogTemp, Warning, TEXT("No HealthBarWidget found on %s"), *GetOwner()->GetName());
        return;
    }

    float HealthPercent = GetPercent();
    FString Command = FString::Printf(TEXT("UpdateHealthBar %f"), HealthPercent);
    FOutputDeviceNull Ar;

    HealthBarWidget->GetWidget()->CallFunctionByNameWithArguments(*Command, Ar, nullptr, true);
}

void UHealthComponent::SetByPercent(float NewHealthPercent) {
    SetCurrent(NewHealthPercent * MaxHealth);
}

float UHealthComponent::GetPercent() const {
    return Current / MaxHealth;
}

void UHealthComponent::Die() {
    SetCurrent(0);
}

void UHealthComponent::DieInternal() {
    IsDead = true;
    OnDeath.Broadcast();

    if (SkeletalMeshComponent) {
        // UAnimInstance *AnimInstance = MeshComp->GetAnimInstance();
        // if (AnimInstance) {
        //         AnimInstance->Montage_Play(TPoseMontage);
        //     MeshComp->SetAnimationMode(EAnimationMode::AnimationCustomMode); //
        // }

        SkeletalMeshComponent->SetAnimationMode(EAnimationMode::AnimationCustomMode); //
    }

    if (MovementComponent) {
        MovementComponent->DisableMovement();
    }

    if (DeathSound) {
        UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetOwner()->GetActorLocation());
    }
}

void UHealthComponent::Revive() {
    ReviveInternal();
    SetCurrent(MaxHealth);
}

void UHealthComponent::ReviveInternal() {
    IsDead = false;

    if (MovementComponent) {
        MovementComponent->SetMovementMode(MOVE_Walking);
    }

    if (SkeletalMeshComponent) {
        SkeletalMeshComponent->SetAnimationMode(EAnimationMode::AnimationBlueprint);
    }
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/WeaponClass.h"
#include "Characters/SoulLikeCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AWeaponClass::AWeaponClass()
{
	WeaponBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Box"));
	WeaponBoxComponent->SetupAttachment(GetRootComponent());
	WeaponBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponBoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	WeaponBoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	BoxTraceCollisionStart = CreateDefaultSubobject<USceneComponent>(FName("Box Trace Start"));
	BoxTraceCollisionStart->SetupAttachment(GetRootComponent());

	BoxTraceCollisionEnd = CreateDefaultSubobject<USceneComponent>(FName("Box Trace End"));
	BoxTraceCollisionEnd->SetupAttachment(GetRootComponent());
}

void AWeaponClass::BeginPlay()
{
	Super::BeginPlay();

	WeaponBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AWeaponClass::OnBeginBoxCollisionOverlap);
}

void AWeaponClass::OnBeginSphereCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginSphereCollisionOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeaponClass::OnEndSphereCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndSphereCollisionOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AWeaponClass::OnBeginBoxCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FVector StartBoxTrace = BoxTraceCollisionStart->GetComponentLocation();
	const FVector EndBoxTrace = BoxTraceCollisionEnd->GetComponentLocation();

	FHitResult BoxHitResult;

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	UKismetSystemLibrary::BoxTraceSingle(
		this, StartBoxTrace, EndBoxTrace, FVector(2.5f, 2.5f, 2.5f), BoxTraceCollisionStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, BoxHitResult, true);
}

void AWeaponClass::AttachMeshToSocket(USceneComponent* InParent, FName SocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	StaticMeshComponent->AttachToComponent(InParent, TransformRules, SocketName);
}

void AWeaponClass::SetWeaponBoxCollision(const ECollisionEnabled::Type CollisionEnabled)
{
	if (WeaponBoxComponent)
	{
		WeaponBoxComponent->SetCollisionEnabled(CollisionEnabled);
	}
}

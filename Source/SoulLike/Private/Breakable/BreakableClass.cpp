#include "Breakable/BreakableClass.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

ABreakableClass::ABreakableClass()
{
	PrimaryActorTick.bCanEverTick = false;

	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryCollectionEngine"));
	SetRootComponent(GeometryCollection);
	GeometryCollection->SetGenerateOverlapEvents(true);
	GeometryCollection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
}

void ABreakableClass::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABreakableClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


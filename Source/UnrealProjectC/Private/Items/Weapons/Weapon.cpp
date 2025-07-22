// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Weapon.h"
#include "./Character/SlashCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Intefaces/HitInterface.h"
#include "NiagaraComponent.h"

AWeapon::AWeapon()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(GetRootComponent());
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);


	StartTraceComponent = CreateDefaultSubobject<USceneComponent>(TEXT("StartTraceComponent"));
	StartTraceComponent->SetupAttachment(GetRootComponent());

	EndTraceComponent = CreateDefaultSubobject<USceneComponent>(TEXT("EndTraceComponent"));
	EndTraceComponent->SetupAttachment(GetRootComponent());


}

void AWeapon::Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewIstigator)
{
	SetOwner(NewOwner);
	SetInstigator(NewIstigator);
	AttachMeshToSocket(InParent, InSocketName);
	ItemState = EItemState::EIS_Equipped;
	if (EquipSound) {
		UGameplayStatics::PlaySoundAtLocation(
			this,
			EquipSound,
			GetActorLocation()
		);
	}
	if (SphereComponent) {
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	if (EmbersEffect)
	{
		EmbersEffect->Deactivate();
	}

}

void AWeapon::Unequied(USceneComponent* InParent, const FName& InSocketName)
{
	AttachMeshToSocket(InParent, InSocketName);
	ItemState = EItemState::EIS_Unequipped;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnBoxEndOverlap);
}

void AWeapon::AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName)
{

	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(InParent, TransformRules, InSocketName);
}


void AWeapon::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	const FVector Start = StartTraceComponent->GetComponentLocation();
	const FVector End = EndTraceComponent->GetComponentLocation();

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	for (AActor* actor : IgnoreActors) {
		ActorsToIgnore.AddUnique(actor);
	}

	FHitResult BoxHit;
	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		FVector(5.f, 5.f, 5.f),
		StartTraceComponent->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		BoxHit,
		true
	);
	if (BoxHit.GetActor()) {
		UGameplayStatics::ApplyDamage(BoxHit.GetActor(), Damage, GetInstigator()->GetController(), this, UDamageType::StaticClass());
		IHitInterface* HitInterface = Cast<IHitInterface>(BoxHit.GetActor());
		if (HitInterface) {
			//HitInterface->GetHit(BoxHit.ImpactPoint);
			HitInterface->Execute_GetHit(BoxHit.GetActor(),BoxHit.ImpactPoint);
		}
		IgnoreActors.AddUnique(BoxHit.GetActor());
		CreateFields(BoxHit.ImpactPoint);
	}
	
}

void AWeapon::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void AWeapon::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

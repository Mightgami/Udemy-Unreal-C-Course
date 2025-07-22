// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

class USoundBase;
class UBoxComponent;
class USceneComponent;
/**

 * 
 */
UCLASS()
class UNREALPROJECTC_API AWeapon : public AItem
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	AWeapon();

	void Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewIstigator);
	void Unequied(USceneComponent* InParent, const FName& InSocketName);


	TArray<AActor*> IgnoreActors;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(BlueprintReadOnly)
	USceneComponent* StartTraceComponent;

	UPROPERTY(BlueprintReadOnly)
	USceneComponent* EndTraceComponent;

	UFUNCTION(BlueprintImplementableEvent)
	void CreateFields(const FVector& FieldLocation);
private:
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	USoundBase* EquipSound;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	float Damage = 20.f;

public:
	FORCEINLINE UBoxComponent* GetWeaponBox() const { return BoxComponent; }

};

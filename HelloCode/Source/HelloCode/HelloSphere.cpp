// Fill out your copyright notice in the Description page of Project Settings.


#include "HelloSphere.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AHelloSphere::AHelloSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//구체 콜라젼 생성
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent")); //텍스트를 쓸 경우 항상 TEXT 사용할 것
	//SphereComponent를 RootComponent로 만든다.
	RootComponent = SphereComponent; 
	//SphereComponent의 반지름 생서
	SphereComponent->InitSphereRadius(220.0f);
	//SphereComponent의 콜리젼 프리셋 지정
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic")); 


	//StaticMeshComponent로 SphereVisual 생성
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	//SphereVisual을 RootComponent에 붙인다.
	SphereVisual->AttachTo(RootComponent);
	//Shape_Sphere 에셋을 찾아서 SphereAsset에 넣는다.
	ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

	ConstructorHelpers::FObjectFinder<UMaterial> SphereMaterial(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel'"));

	if (SphereAsset.Succeeded()&& SphereMaterial.Succeeded())
	{
		//SphereVisual에 SphereAsset 적용
		SphereVisual->SetStaticMesh(SphereAsset.Object);
		//SphereVisual에 SphereMaterial 적용
		SphereVisual->SetMaterial(0, SphereMaterial.Object);
		// SphereVisual에 위치값 적용
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	}
	//ParticleSystemComponent로 FireParticles 생성
	UParticleSystemComponent* FireParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticles"));

	//FireParticles을 SphereVisual에 붙인다.
	FireParticles->AttachTo(SphereVisual);
	//FireParticles을 시작할 떄 자동으로 활성화 시킨다.
	FireParticles->bAutoActivate = true;

	//P_Fire에셋을 찾아서 FireVisual에 넣는다.
	ConstructorHelpers::FObjectFinder<UParticleSystem> FireVisual(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'")); //오브젝트 파인더는 에셋을 찾는 것

	if (FireVisual.Succeeded())
	{
		//FireParticales에 FireVisual 에셋을 적용시킨다.
		FireParticles->SetTemplate(FireVisual.Object); // set template은 에셋을 적용하는 것
	}
	//UTextRenderComponent형의 TextRenderComponent를 생성
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	//TextRenderComponent를 SphereVisual에 붙인다.
	TextRenderComponent->AttachTo(SphereVisual);
	//TextRenderComponent의 위치 설정
	TextRenderComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));	
	//TextRenderComponent의 정렬
	TextRenderComponent->SetHorizontalAlignment(EHTA_Center);
	//TextRenderComponent의 크기 설정
	TextRenderComponent->SetYScale(2.0f);
	TextRenderComponent->SetXScale(2.0f);
	//TextRenderComponent의 Visibility 설정
	TextRenderComponent->SetVisibility(true);
	//TextRenderComponent의 텍스트 적용(NSLOCTEXT 매크로를 통해서 AnyNs 네임스페이스에 Any키에 HelloWorld 텍스트 지정)
	TextRenderComponent->SetText(NSLOCTEXT("AnyNs", "Any", "HelloWorld")); //현지화 처리 구문
	//key = Any를 가지고
	//한글 = 안녕 세상아로 바뀐다.
	//anyns라는 네임스페이스로 구분해 주겠다.

	//바인딩
	OnActorBeginOverlap.AddDynamic(this, &AHelloSphere::MyOnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AHelloSphere::MyOnEndOverlap);

}

// Called when the game starts or when spawned
void AHelloSphere::BeginPlay()
{
	Super::BeginPlay(); //super는 부모함수의 구현부를 실행
	
}

// Called every frame
void AHelloSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHelloSphere::MyOnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString outputString;
	outputString = "Hello" + OtherActor->GetName() + "!"; 
	TextRenderComponent->SetText(FText::FromString(outputString));
}

void AHelloSphere::MyOnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	TextRenderComponent->SetText(NSLOCTEXT("AnyNs", "Any", "HelloWorld"));

}

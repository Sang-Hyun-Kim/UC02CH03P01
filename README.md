# UC02CH03P01
 First project assignment for third chapter of Unreal Engine Camp 02


## 프로젝트 설명
과제 06 | 회전 발판과 움직이는 장애물 퍼즐 스테이지 제작하기

### 과제 요구 사항
- 필수
  1.서로 다른 Actor 클래스 2개 이상 구현, 다른 동작 수행
  2. Tick 함수 기반 Transform 변경
  3. 언리얼 리플랙션 함수를 통한 Unreal Editor 에서 접근 가능 여부 
- 도전
  1. FTimeHandle을 활용한 시간 제한과 카운트 다운
  2.랜덤한 퍼즐 생성 
---
### 프로젝트 흐름도
![Image](https://github.com/user-attachments/assets/507a3cc8-5f9c-4c04-9bf8-88369bf4ede4)

처음 과제 프로젝트를 구상할 때 도전과제까지 반영한 게임의 예상 흐름도

---

### 주요 기능 설명

#### PuzzleManager(퍼즐 매니저)

##### 개요
퍼즐 매니저는  레벨 시작시 생성 되어 레벨에 배치된 Puzzle Sector를 찾아 저장 한 다음, 저장된 PuzzleSet(퍼즐 도안)들을 랜덤하게 Puzzle Sector에 전달하며, 플레이어 클리어시(또는 실패 시) 플레이어를 다시 시작 위치로 옮기며 이미 생성된 퍼즐을 정리 및 랜덤하게 재생성합니다.
랜덤 좌표가 아닌 랜덤한 도안을 각 Puzzle Sector의 위치에 맞게 생성하기 위해 만들어 보았습니다.

##### 기능


```C++
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzles|PuzzleSectors")
	TArray<APuzzleSectorBase*> PuzzleSectors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzles|PuzzleSets")
	TArray<TSubclassOf<UPuzzleSetBase>> PuzzleSets;

	TArray<UPuzzleSetBase*> PuzzleSetObjects;
```
멤버 변수:
- PuzzleSectors: 레벨 실행시 퍼즐 구역들이 저장되는 컨테이너 입니다.
- PuzzleSets: Editor에서 BP로 생성한 PuzzleSetBase 서브 클래스들을 저장합니다.
- PuzzleSetObjects:  Unreal Editor에서 수정 가능한 PuzzleSet을 받아 BeginPlay() 단계에서 객체들을 생성한 다음 퍼즐이 초기화 될 때 마다 해당 객체들을 재사용합니다.
```C++
	UFUNCTION(BlueprintCallable, Category = "Puzzles")
	void RandomPuzzleGenerator();
	// 레벨의 모든 PuzzleSector를 찾아서 추가하는 함수
	UFUNCTION(BlueprintCallable, Category = "Puzzles")
	void FindAllPuzzleSectors();
	UFUNCTION(BlueprintCallable, Category = "Puzzles")
	void ClearCurrentPuzzlesFromAllSectors();
```

멤버 함수:
- FindAllPuzzleSectors: 레벨에 배치된 모든 PuzzleSector를 찾아 멤버 변수 컨테이너에 저장합니다.
- ClearCurrentPuzzlesFromAllSectors: 저장된 Sector들에게 현재 저장된 퍼즐을 삭제하라고 전달합니다.
- RandomPuzzleGenerator: 현재 저장된 Sector들에게 퍼즐을 재생성하라고 지시합니다.

---

#### PuzzleSetBase(퍼즐 도안)

##### 개요
PuzzleSetBase는 특정 퍼즐을 어떤 좌표에 배치할지에 대한 정보를 들고 있기 위한 클래스 입니다. 해당 클래스를 상속받는 클래스들은 필요에 맞게 각각 다른 퍼즐 종류와 좌표를 가지고 있습니다.

```C++
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzles")
	TArray<TSubclassOf<AProjectPuzzlePlatform01>> Puzzles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzlesLocations")
	TArray<FVector> PuzzleLocations;
```

멤버 변수:
- Puzzles: UE Editor를 통해 퍼즐 BP들이 저장될 컨테이너입니다.
- PuzzleLocations: 위와 동일한 방식으로 퍼즐들의 좌표를 저장합니다.

##### 상속하는 서브 클래스들 

- BP_PSet01_RotatingPlatforms:  회전하는 플랫폼들에서 떻어지지 않고 점프해 건너는 퍼즐 도안입니다.
- BP_PSet02_Bridge : 회전하는 통나무를 피하면서 떨어지지 않게 플랫폼 사이를 건너는 퍼즐 도안입니다.
- BP_PSet03_ElevatingPlatforms: 위아래로 반복 운동하는 플랫폼을 타고 건너는 퍼즐 도안입니다.
- BP_PSet04_BlinkingSet: 3초마다 비활성화되는 플랫폼을 타고 건너는 퍼즐 도안입나다.

 ---
#### ProjectPuzzlePlatform01(퍼즐 플랫폼 베이스)

##### 개요
해당 클래스는 모든 Puzzle Platform 들이 상속받는 부모 클래스입니다. 처음 만들 때 모든 퍼즐의 Base가 될 줄 몰라 단순 퍼즐1번이란 의미로 이름을 지었다가, 결국 모든 퍼즐종류가 상속받는 부모클래스가 되었습니다. **다음부턴 꼭 설계를 제대로하고 이름을 짓자**라는 반성의 의미로 그대로 남겨 사용하였습니다,
다만, 추가 확장을 위해 위치와 크기를 저장하도록 멤버 변수를 구현해놨습니다.
```C++
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzlePosition")
	FVector PRLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzlePosition")
	FVector PRScale;
```


##### 상속하는 서브 클래스들

- Puzzle01Rotatingatform 
	- 회전하는 플랫폼입니다. 프레임 단위로 회전하되, Gimbal Lock 현상이 발생해 해당 오류를 해결하기 위해 쿼터니안으로 회전을 하는 방법을 찾아 도입하였습니다. 또한 BeginPlay시 FMath::RandRange()로 랜덤한 속도를 생성해 각 퍼즐들이 랜덤한 속도로 회전하도록 구현했습니다.
```C++
//header
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle|RotationSpeed")
	float RotationSpeed;
// cpp
void APuzzle03RotatingLog::Tick(float DeltatTime)
{
	Super::Tick(DeltatTime);
	RotatingRoot(DeltatTime);
}

void APuzzle03RotatingLog::RotatingRoot(float DeltaTime)
{
	FQuat QuatRotation = FQuat(FRotator(0.0f, RotationSpeed * DeltaTime,0.0f ));
	AddActorLocalRotation(QuatRotation);
}

```

- Puzzle02BridgePlatform
	- 단순 건너기위한 발판입니다. 다만 추가 확장을 위해 상속받아 사용했습니다.
- Puzzle03RotatingLogPlatform
	- 위의 발판 플랫폼을 건너는 것을 방해하는 Yaw 축으로 회전하는 플랫폼입니다. 해당 플랫폼은 중심만 구현하였고, 이를 상속받는 BP에서 통나무를 달아 플레이어를 방해합니다. 해당 플랫폼 또한 게임 시작시 부여받은 랜덤한 속도로 회전합니다.
- Puzzle044MovingAndPushingObstacle
	- 위, 아래로 반복운동하는 플랫폼입니다. 처음 시작시 생성된 랜덤한 속도로 Y축을 엘레베이터 발판처럼 이동합니다. **이 또한 처음 잘못 지은 이름을 반성**하는 의미로 사용했고 상속 받는 BP는 제대로 ElevatingPlatform 이란 이름으로 생성했습니다.
```C++
// hearder
	UFUNCTION()
	virtual void Moving(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle|MovementSpeed")
    float MovementSpeed = 200.0f;

	int movementflag = 1;

    /** 왕복 거리 */
    UPROPERTY(EditAnywhere, Category = "Movement")
    float TravelDistance = 500.0f; // 500 유닛 왕복

    /** 이동 방향 */
    FVector MoveDirection = FVector(0.0f, 0.0f, 1.0f); // X축 방향 이동

    /** 시작 위치 */
    FVector StartLocation;

//cpp
void APuzzle04MovingAndPushingObstacle::BeginPlay()
{
	Super::BeginPlay();

	float NewMovementSpeed = FMath::RandRange(20.0f, 200.0f);
	MovementSpeed = NewMovementSpeed;

	StartLocation = GetActorLocation(); // 시작 위치 저장
}

void APuzzle04MovingAndPushingObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Moving(DeltaTime);
}

void APuzzle04MovingAndPushingObstacle::Moving(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();

	// 목표 위치 도달 시 방향 반전
	if (FVector::Dist(StartLocation, CurrentLocation) >= TravelDistance)
	{
		MoveDirection *= -1.0f;
	}

	// 이동 처리
	FVector MoveOffset = MoveDirection * MovementSpeed * DeltaTime;
	SetActorLocation(CurrentLocation + MoveOffset);
}

```

- Puzzle05BlinkPlatform
	- 특정 주기로 가시성, 충돌 여부를 반전시켜 플레이어의 시야에서 사라짐과 동시에 떨어트리는 목적으로 제작된 Platform 입니다. 해당 플랫폼은 Tick을 사용하지 않고 FTimerHandle과 TimerManager를 사용하여 특정 주기로 변경되도록 만든 것이 특징입니다. 각 설정값들은 UE Editor에서 변경 및 수정 가능합니다.

```C++
//header
	APuzzle05BlinkPlatform();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ToggleTimer = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsActive;

	virtual void BeginPlay() override;
public:

	// 타이머 핸들
	FTimerHandle TimerHandle;



	UFUNCTION()
	void TogglePlatformState();
//cpp
	PrimaryActorTick.bCanEverTick = false;
void APuzzle05BlinkPlatform::BeginPlay()
{
	Super::BeginPlay();
	TogglePlatformState();
	// 타이머 설정: 5초마다 상태를 변경
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APuzzle05BlinkPlatform::TogglePlatformState, ToggleTimer, true);


}

void APuzzle05BlinkPlatform::TogglePlatformState()
{
	// 상태를 반전시킵니다
	if (bIsActive)
	{
		bIsActive = false;
	}
	else
	{
		bIsActive = true;
	}

	Root->SetVisibility(bIsActive);
	SetActorEnableCollision(bIsActive); // 충돌을 활성화/비활성화
}
```
---
#### PuzzlESectorBase(퍼즐 구역)

##### 개요
PuzzleSectorBase는 퍼즐이 생성될 구역을 구현한 클래스입니다. 해당 클래스를 상속받는 BP 클래스는 레벨에 배치되어 PuzzleManager에 관리하에 퍼즐 랜덤 생성, 삭제를 수행합니다.


```C++
	APuzzleSectorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ActorSpawnByPuzzleSet(UPuzzleSetBase* set);
	void ClearSector();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Puzzles|Components")
	TArray<TSubclassOf<AProjectPuzzlePlatform01>> PuzzleArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzles|Components")
	TArray<FVector> PuzzleLocations;
	
	TArray<AProjectPuzzlePlatform01*> CurSpawnedPlatforms;
```
클래스 특징으로는 생성되는 퍼즐들을 컨테이너에 보관한 다음 삭제하는 것으로 메모리 관리에 신경썼습니다.

```C++
void APuzzleSectorBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APuzzleSectorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuzzleSectorBase::ActorSpawnByPuzzleSet(UPuzzleSetBase* set)
{
	// 넘겨받은 도면에 대해 랜덤 생성
	if (set->PuzzleLocations.Num() != set->Puzzles.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("퍼즐 개수와 퍼즐 좌표 개수가 맞지 않습니다"));
		return;
	}
	else
	{
		UWorld* pworld = GetWorld();
		if (!pworld)
		{
			UE_LOG(LogTemp, Warning, TEXT("No World Error"));
			return;
		}
		INT32 PuzzleNum = set->Puzzles.Num();
		FTransform CurSectorBaseTransform = GetActorTransform();
		for (int i = 0; i < PuzzleNum; ++i)
		{
			FVector CurPuzzleLocation = CurSectorBaseTransform.GetLocation() + set->PuzzleLocations[i];

			AProjectPuzzlePlatform01* CurPuzzle = pworld->SpawnActor<AProjectPuzzlePlatform01>(
				set->Puzzles[i], CurPuzzleLocation, FRotator::ZeroRotator
			);
			if (CurPuzzle)
			{
				CurSpawnedPlatforms.Add(CurPuzzle);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No PlatformData in Set_Array so No Platform Spawned"));
			}
		}
	}
}

void APuzzleSectorBase::ClearSector()
{
	for (AProjectPuzzlePlatform01* CurSpawnedPlatform : CurSpawnedPlatforms)
	{
		CurSpawnedPlatform->Destroy();
	}
}
```
---
#### 시연 영상

---

#### 후기
- 단순 C++에서 Unreal Engine을 응용하는 법에서 막혀 도움될 자료들을 많이 찾아보았다. BP로 만든 클래스를 C++ 코드에서 활용하려면 기본 클래스를 받아와 객체를 생성해서 활용하든 레벨의 구석진 곳에 배치에 활용하든 방법은 굉장히 많았다.
- 액터를 회전시키면서 발생했던 Gimbal Lock 현상은 추후 이동, 회전 등에서 활용할 게임 수학 및 언리얼 제공 라이브러리에 추가적인 공부가 필요하다고 느꼈다.
- 레벨 블루프린트와 레벨에 배치된 객체를 레벨 BP로 블러와 각 객체의 이벤트를 활용한 게임 흐름 제작이 꽤 재밌었다.



---

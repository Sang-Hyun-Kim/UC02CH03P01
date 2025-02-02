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

### 프로젝트 흐름도
![Image](https://github.com/user-attachments/assets/507a3cc8-5f9c-4c04-9bf8-88369bf4ede4)
처음 과제 프로젝트를 구상할 때 도전과제까지 반영한 게임의 예상 흐름도



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

##### 상속받는 각 서브 클래스들 

- BP_PSet01_RotatingPlatforms: 
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

 회전하는 플랫폼들에서 떻어지지 않고 점프해 건너는 퍼즐 도안입니다. 프레임 단위로 회전하되, Gimbal Lock 현상이 발생해 해당 오류를 해결하기 위해 쿼터니안으로 회전을 하는 방법을 찾아 도입하였습니다.

- BP_PSet02_Bridge : 회전하는 통나무를 피하면서 떨어지지 않게 플랫폼 사이를 건너는 퍼즐 도안입니다. 
- BP_PSet03_ElevatingPlatforms: 위아래로 반복 운동하는 플랫폼을 타고 건너는 퍼즐 도안입니다. 
- BP_PSet04_BlinkingSet: 3초마다 비활성화되는 플랫폼을 타고 건너는 퍼즐 도안입나다.
  
#### ProjectPuzzlePlatform01(퍼즐 플랫폼 베이스)

##### 개요
해당 클래스는 모든 Puzzle Platform 들이 상속받는 부모 클래스입니다. 처음 만들 때 모든 퍼즐의 Base가 될 줄 몰라 단순 퍼즐1번이란 의미로 이름을 지었다가, 결국 모든 퍼즐종류가 상속받는 부모클래스가 되었습니다. **다음부턴 꼭 설계를 제대로하고 이름을 짓자**라는 반성의 의미로 그대로 남겨 사용하였습니다,

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






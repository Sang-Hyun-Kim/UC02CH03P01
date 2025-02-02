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

---C++

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzles|PuzzleSectors")
	TArray<APuzzleSectorBase*> PuzzleSectors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzles|PuzzleSets")
	TArray<TSubclassOf<UPuzzleSetBase>> PuzzleSets;

---

sdas


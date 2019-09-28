# TEAM-Visual_Bat

*TEAM-Visual_Bat*

2019/06/15
----------
> update chaptor12, class_dynamic_memory


# -TEAM-Visual_Bat

## 컨벤션
- 아직 없음
----------
> update chaptor12, class_dynamic_memory

## 커밋 예시
```
9/20 <update>
HEADER / Include 폴더정리
Resource 폴더 생성
System 헤더 cpp파일 생성
- 추가사항 -
현재 .vcxproj 파일에는 존재하나 추가되지 못한 헤더와 cpp가 있음.

9/27 <update>
RAY, SPHERE struct 추가
CScene과 중복되는 StateObj 비활성화 (변경 이전 코드는 주석처리 하였음)
Picking용으로 사용되었던 Mouse.h 비활성화, MousePicker.h 생성
CInputManager 맴버로 CMousePicker 생성
CheckPickingOnSphere() / CheckPickingOnTriangle() 생성
CBoundingSphere 생성
GameCamera 비활성화
- 추가 사항 -
원인을 모르겠으나 BoundingBox, BoundingSphere 출력X

9/28 <update>
map 리소스 추가
map 이름 summon terrain으로 일괄 변경
Initiate() 이름 일괄 변경
- 추가 사항 -
원인을 모르겠으나 BoundingBox, BoundingSphere 출력X
```
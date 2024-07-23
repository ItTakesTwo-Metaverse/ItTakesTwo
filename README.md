# ItTakesTwo

---

**일정 : 2024.06.18 ~ 2024. 07.22**

**마일스톤으로 큰단위의 작업을 설정해 주세요**

**마일스톤 컨벤션**
**마일스톤 컨벤션 예시**

**이슈 작성 후 작업 진행 바랍니다.**

**이슈 예**

**[Feat] 블록골램 걷기 구현**

### ISSUE

- Type: feat
- Detail: c++ 블록골램에 모션 기능 추가

### TODO

- [ ]  팔 모션 주기
- [ ]  다리 모션 주기
- [ ]  실제 물리 공간 이동

**작은 변경사항이라도 꼭 중간마다 커밋, 푸쉬 부탁드립니다.**
**push 전에는 서로 공유 부탁드립니다.**

**브렌치명 컨벤션**
- 브렌치 명 : <자기이니셜>_<기능>

- **브렌치명 컨벤션 예**

- csr_PlayerJump
- hsu-ClickButtonAndExecSomething

**커밋 컨벤션**

- <유형> : <내용> #이슈번호
- Feat : 새로운 기능을 추가할 경우
- Fix : 버그를 고친 경우
- !HOTFIX : 치명적인 버그를 고친 경우
- Style : Norm 규정, 세미콜론 누락, 코드수정이 없는 경우
- Refactor : 리팩토링
- Comment : 주석 추가 및 변경
- Docs : 문서를 수정한 경우
- Test : 테스트 추가
- Rename : 파일 혹은 폴더명을 수정하거나 옮기는 작업만인 경우
- Remove : 파일을 삭제하는 경우

**커밋 컨벤션 예**

- Feat: tokenizer 구현 - minseok2
- Fix: tokenizer 문자열 파싱 버그 수정 - junlee2
- Remove: test.txt 임시파일 삭제 - tyi
- Rename: test.txt → operator.txt - jincpark

**코드 컨벤션**

- 파스칼 켄벤션 (int ShootingPlayer)
- 블루프린트 생성 접두어 BP_
- 클래스 만들 시 접두어 G
- 엑터 클래스 만들 시 접두어 A

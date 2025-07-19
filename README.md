MineSweeper 리팩토링 
1. GameManager
   - 게임판(Board)을 관리하는 관리자 클래스
   - 입력을 받아 게임이 진행되도록 합니다
   - Singleton을 상속하여 객체가 한번만 생성되도록 합니다
   - 사용자의 게임 진행에 따라 지뢰를 밟거나 지뢰를 모두 찾을 경우 게임을 종료합니다

2. Board
   - 게임판을 만들고 지뢰를 셋팅한 후 지뢰칸들의 상태를 셋팅합니다
   - vector를 사용하여 board 관리가 수월하도록 하였습니다
   - FCell struct를 사용하여 지뢰칸 상태를 표현하였습니다

3. Main
   - GameManager를 통해 게임을 실행합니다

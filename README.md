# Camera_Detect_PIANO

피아노가 없는 환경에서도 피아노를 칠 수 있게끔 하는 프로젝트
라즈베리/아두이노/스마트폰/노트북의 카메라를 이용하여 손의 모션 인식으로 피아노를 칠 수 있게끔 함.

OpenCV를 이용하였고 카메라에서 영상을 받아와 흑백,이진화 수행.
새로 받아온 영상이 이전 영상과 차이가 나는 부분(모션 발생) 시 흰색으로 표현이 됨 -> 이는 나중에 모션 감지로 사용해도 될듯.(CCTV)
화면 하단에 구역을 건반 모양으로 여러개 나눠서 특정 구역에 모션 발생 시 특정 음이 발생하도록 함
ex) a1 구역에 음 발생시 C4 음계 출력

C++랑 python3 에서 각자 따로 테스트중

python3 

![image](https://user-images.githubusercontent.com/66546156/124938935-afb16000-e043-11eb-9c9f-3862bceb5c7b.png)


C++ OpenCV로 이식 확인, 탐지된 구역에 소리만 나게 하면됨

![cap](https://user-images.githubusercontent.com/66546156/124938088-f3f03080-e042-11eb-9135-a2c482d138ee.PNG)

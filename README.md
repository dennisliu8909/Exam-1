# Exam-1
main3.cpp為最終版
FFT.py為numpy的檢測

我的打法是利用按鈕的interrupt決定slew_rate，button_up增加、button_down減少、button_select選定slew_rate並印出結果。
波型的製造是由while迴圈內每1ms產生一個波點，然後上升的區段由slope_width(80 * slew_rate)所決定。
最後ADC的output以每2ms取一點，一秒內共500點，再藉由numpy做取樣波點的還原。

輸出結果
![Screenshot from 2021-04-07 01-54-39](https://user-images.githubusercontent.com/76942544/113856383-bf66a180-97d3-11eb-9b1c-940cfda4b48f.png)
![Screenshot from 2021-04-07 01-51-37](https://user-images.githubusercontent.com/76942544/113856392-c097ce80-97d3-11eb-85ce-ebbee73c7b66.png)
![Screenshot from 2021-04-07 01-51-40](https://user-images.githubusercontent.com/76942544/113856396-c1c8fb80-97d3-11eb-9489-5a88e5246a77.png)
![Screenshot from 2021-04-07 01-53-28](https://user-images.githubusercontent.com/76942544/113856399-c2619200-97d3-11eb-8226-fa711bc9f207.png)
![Screenshot from 2021-04-07 01-53-32](https://user-images.githubusercontent.com/76942544/113856401-c2fa2880-97d3-11eb-8a10-0c364dbd3ee7.png)
![Screenshot from 2021-04-07 01-53-48](https://user-images.githubusercontent.com/76942544/113856402-c392bf00-97d3-11eb-8d35-3fa8034c48cf.png)
![Screenshot from 2021-04-07 01-54-14](https://user-images.githubusercontent.com/76942544/113856406-c42b5580-97d3-11eb-819a-b5962cf08820.png)
![Screenshot from 2021-04-07 01-54-36](https://user-images.githubusercontent.com/76942544/113856409-c42b5580-97d3-11eb-94f5-2361ae6592ff.png)

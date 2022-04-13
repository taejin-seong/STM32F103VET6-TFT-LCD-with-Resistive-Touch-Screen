## 개발 환경<br>
### IDE
* STM32CubeIDE 1.6.0 <br>
* STM32CubeMX <br>

<br>

### 개발 보드
* **STM32F103VET6 Custom Development Board** <br>
  + :pushpin: [이미지 링크 및 구매처](https://ko.aliexpress.com/item/32693544239.html?gatewayAdapt=glo2kor&srcSns=sns_KakaoTalk&spreadType=socialShare&bizType=ProductDetail&social_params=20527276655&aff_fcid=6a92134b6f66447fb4e5392261410de1-1649825428883-09137-_mMqvBK2&tt=MG&aff_fsk=_mMqvBK2&aff_platform=default&sk=_mMqvBK2&aff_trace_key=6a92134b6f66447fb4e5392261410de1-1649825428883-09137-_mMqvBK2&shareId=20527276655&businessType=ProductDetail&platform=AE&terminal_id=62559df8374f42348f14bc09e497c7f3&afSmartRedirect=y)<br>
  + :pushpin: [개발보드 회로도](https://github.com/taejin-seong/STM32F103VET6-TFT-LCD-with-Resistive-Touch-Screen/blob/master/STM32F103VET6%20Dev%20Board%20Schematic/0001.jpg)<br>
    - 제공되는 개발보드 회로도를 확인해 본 결과, 회로도에 표기되어있는 커넥터 및 핀 헤더명이 실제 보드의 커넥터 및 핀 헤더명과 서로 다른 것을 확인하였습니다. **이를 주의하시고** 회로도를  보시길 바랍니다. <br>
    - 사용된 개발보드에서는 FSMC 인터페이스의 TFT LCD를 쉽게 사용할 수 있게 핀을 매핑하여 16X2 헤더로 따로 빼놓았습니다. 아래 그림을 참고하시길 바랍니다.<br>
 
    -<img src="https://user-images.githubusercontent.com/70312248/163129584-df167919-aa90-44d1-8b6c-c36210542ddc.png" width="450" height="330"/>     
     <img src="https://user-images.githubusercontent.com/70312248/163130781-470699c0-dcd2-41bd-8334-20412fc8dda7.png" width="400" height="300"/><br>
<br>
 
### TFT LCD 모듈 
* **3.2inch 16BIT Module ILI9341 SKU-MRB3205** <br>
  + :pushpin: [이미지 링크 및 구매처](https://a.aliexpress.com/_mPmlxdu) <br>
  
  + :pushpin: [해당 TFT LCD관련 자료 종합](http://www.lcdwiki.com/3.2inch_16BIT_Module_ILI9341_SKU:MRB3205)<br>
    - 해당 LCD 위키 사이트로 가는 링크입니다. 링크를 접속하시면 해당 TFT LCD모듈에 대한 간단한 Overview 부터 User Manual. ILI9341 driver 데이터 시트, XPT2406 IC 데이터 시트 그리고 예제 등을 확인해보실 수 있습니다. <br>
    
  + :pushpin: 사용한 TFT LCD 모듈의 아주 간단한 스펙은 다음과 같습니다. (자세한 스펙은 데이터시트를 참고하시길 바랍니다.)<br>
    - 8-bit/16-bit의 FSMC 인터페이스를 지원하여 ILI9341 드라이버 (LCD 드라이버)를 제어할 수 있습니다. 기본으로 16-bit Data Bus이며, 아래와 같이 R8의 저항을
    - <img src="https://user-images.githubusercontent.com/70312248/163130781-470699c0-dcd2-41bd-8334-20412fc8dda7.png" width="400" height="300"/><br>  
    
  
<br>

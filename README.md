## 개발 환경<br>
### IDE
* STM32CubeIDE 1.6.0 <br>
* STM32CubeMX <br>

### 개발 보드
* **STM32F103VET6 Custom Development Board** <br>
  + :pushpin: [이미지 링크 및 구매처](https://ko.aliexpress.com/item/32693544239.html?gatewayAdapt=glo2kor&srcSns=sns_KakaoTalk&spreadType=socialShare&bizType=ProductDetail&social_params=20527276655&aff_fcid=6a92134b6f66447fb4e5392261410de1-1649825428883-09137-_mMqvBK2&tt=MG&aff_fsk=_mMqvBK2&aff_platform=default&sk=_mMqvBK2&aff_trace_key=6a92134b6f66447fb4e5392261410de1-1649825428883-09137-_mMqvBK2&shareId=20527276655&businessType=ProductDetail&platform=AE&terminal_id=62559df8374f42348f14bc09e497c7f3&afSmartRedirect=y)<br>
  
  + :pushpin: [개발보드 회로도](https://github.com/taejin-seong/STM32F103VET6-TFT-LCD-with-Resistive-Touch-Screen/blob/master/STM32F103VET6%20Dev%20Board%20Schematic/0001.jpg)<br>
    - 제공되는 개발보드 회로도를 확인해 본 결과, 회로도에 표기되어있는 커넥터 및 핀 헤더명이 실제 보드의 커넥터 및 핀 헤더명과 서로 다른 것을 확인하였습니다. **이를 주의하시고** 회로도를  보시길 바랍니다. <br><br>
    - 사용된 개발보드에서는 FSMC 인터페이스의 TFT LCD를 쉽게 사용할 수 있게 핀을 매핑하여 16X2 헤더로 따로 빼놓았습니다. 아래 그림을 참고하시길 바랍니다.<br><br>
     <p align="center">
     <img src="https://user-images.githubusercontent.com/70312248/163129584-df167919-aa90-44d1-8b6c-c36210542ddc.png" width="450" height="330"/>     
     <img src="https://user-images.githubusercontent.com/70312248/163130781-470699c0-dcd2-41bd-8334-20412fc8dda7.png" width="400" height="300"/> </p><br>
 
### 320*240 TFT LCD 모듈 
* **3.2inch 16BIT Module ILI9341 SKU-MRB3205** <br>
  + :pushpin: [이미지 링크 및 구매처](https://a.aliexpress.com/_mPmlxdu) <br>
  
  + :pushpin: [해당 TFT LCD관련 자료 종합](http://www.lcdwiki.com/3.2inch_16BIT_Module_ILI9341_SKU:MRB3205)<br>
    - 해당 LCD 위키 사이트로 가는 링크입니다. 링크를 접속하시면 해당 TFT LCD모듈에 대한 간단한 Overview 부터 User Manual. ILI9341 driver IC 데이터 시트, XPT2406 touch IC 데이터 시트 그리고 예제 등 까지 확인해보실 수 있습니다. <br>
    
  + 사용한 TFT LCD 모듈의 **간단한 스펙 설명**은 다음과 같습니다. (자세한 스펙은 데이터시트를 참고하시길 바랍니다.)<br>
    - 들어가기 앞서 FSMC는 FMC라고도 불리며 Flexible Static Memory Controller를 의미합니다. FSMC는 NOR/SRAM, NAND/PC CARD 같은 외부 메모리 칩들을 병렬 인터페이스하여 컨트롤 하는 페리페럴입니다. 참고로 LCD의 직렬 인터페이스 방식에서는 SPI가 많이 쓰이며, 병렬 인터페이스 방식에서는 FSMC가 많이 쓰입니다. 병렬 인터페이스가 직렬 인터페이스보다는 고속이게 됩니다.
    - STM32F10X FSMC에 상세한 내용은 아래 문서명을 참고하세요
      +  ***TFT LCD interfacing with the high-density STM32F10xxx FSMC*** 
      +  ***RM0008 Reference Manual 507p~565p*** <br>
      + 사실 FSMC 인터페이스의 적용은 TFT LCD 뿐만 아니라 다양하므로 그에 따라 제공되는 확장 기능이나 파라미터가 달라집니다. 본 프로젝트에서는 FSMC 인터페이스가 TFT LCD에 적용되므로 ***TFT LCD interfacing with the high-density STM32F10xxx FSMC*** 문서만 보셔도 STM32F10XX MCU를 이용한 전반적인 FSMC 인터페이스의 TFT LCD제어의 흐름을 이해하실 수 있습니다.
  
   
    - TFT LCD모듈은 레귤레이터가 있기 때문에 VDD Pin에 3.3V 뿐만 아니라 5V로 전원공급이 가능합니다.<br>
    - 해당 TFT LCD모듈은 8-bit/16-bit 데이터 버스의 **인텔 808 (I80) 인터페이스**를 지원하며 이를 통해 MCU의 FSMC 컨트롤러로 ILI9341 driver IC (LCD 드라이버)를 병렬 제어할 수 있습니다. **기본적으로 16-bit 데이터 버스** 이며 아래 그림과 같이 R8, R16 저항을 통해 8-bit로 FSMC 인터페이스 시킬 수 있습니다. <br><br>
    
    <p align="center">
    <img src="https://user-images.githubusercontent.com/70312248/163138148-869e9ddc-a826-4a44-9d43-6ede85dcafac.png" width="650" height="450"/> </p><br>  

    - 해당 TFT LCD모듈은 **감압식** 터치 패널이며 이는 누른 좌표점을 얻어내어 터치를 제어하는 형식입니다. (보통 정전식을 더 많이 사용합니다.) 이를 위해 SPI 인터페이스의 XPT2406 touh IC를 이용하여 터치스크린을 제어합니다.<br><br>
    - 또한 TFT LCD모듈에는 SDCS (SD카드 선택제어핀)이 있으므로 SD카드의 프로토콜 방식인 SDIO/SPI 중 SPI를 이용해 XPT2406에 SPI 슬레이브를 하나더 추가하여 SD카드를 사용한 비트맵, JPEG 출력 등을 시도해 볼 수 있습니다. **본 프로젝트에서는 SD카드 관련 제어를 구현하지 않았습니다.** <br>
  + 해당 TFT LCD 모듈의 User Manual을 통해 Pin Description를 이해하기 전에 **FSMC 인터페이스에 대한 학습이 필요합니다.**<br><br>

  
<br>

## TFT LCD 모듈과 STM32F103VET6 하드웨어 연결<br>

* **해당 초록색 박스 부분**은 LCD의 인텔 808 인터페이스와 MCU의 FSMC 인터페이스 부분입니다. 이를 통해 ILI9341 Driver IC를 제어합니다. <br>

  - FSMC [D0:D15] = FSMC **16bit** 데이터 버스
  - FSMC NEx      = FSMC **C**hip **S**elect 
  - FSMC NOE      = FSMC **O**utput **E**nable
  - FSMC NWE      = FSMC **W**rite **E**nable
  - FSMC Ax       = LCD Register와 LCD Data를 선택하기 위한 **Address line (0~25)** (LCD의 RS핀과 연결) High일떄 레지스터 / Low일떄 데이터 <br>
    
* NEx, NOE, NWE 앞에 붙은 **N은 Active Low**를 의미합니다.<br>
* 본 프로젝트에서는 STM32F103VET6의 FSMC 컨트롤러의 **NE1에 A16**을 사용합니다. 즉, FSMC bank1 NOR/PSRAM 1을 사용하며, 서브 뱅크에 따라 주소 매핑은 아래와과 같습니다.
* 참고로 뱅크1은 서브뱅크4개로 나눠지며 이와 관련된 자세한 사항은 ***RM0008 Reference Manual 511p*** 부터 참고하세요.<br><br>

```C
#define LCD_BASE0        		((uint32_t)0x60000000) //ILI9341_CMD_ADDR
#define LCD_BASE1        		((uint32_t)0x60020000) //ILI9341_DATA_ADDR
``` 

* **해당 주황색 박스 부분**은 SPI 인터페이스 부분입니다. SPI2를 사용하며, 이를 통해  XPT2406 touh IC를 제어합니다. <br>
  - PEN Pin은 터치 스크린의 인터럽트를 감지하며, 터치가 발생했을 때 Low로 떨어집니다.<br>
  
  
* **해당 노란색 색칠 부분**은 SD 카드를 선택하여 제어하는 핀입니다. <br>
  - 즉, SPI CS Pin 으로 사용 가능합니다. 만약 SD카드를 이용하여 확장 기능을 추가하고 싶다면 이 핀을 SPI2 CS 기능을 하는 핀으로 GPIO 셋팅을 하여 XPT2406과 같은 SPI 버스 라인에 슬레이브를 추가시키세요.<br>
  - SD_CS Pin이 Low가 되면 SD카드가 선택됩니다.<br>  
  - 본 프로젝트에서는 SD카드를 이용하지 않습니다.<br>

* **BL Pin**은 LCD의 백라이트 핀으로 상태가 set이 되어야 켜집니다. 추가적으로 PWM을 지원하는 핀을 이용하여 BL핀을 연결한다면 백라이트의 밝기를 조절할 수 있습니다.

<br>

 [크게 보기](https://github.com/taejin-seong/STM32F103VET6-TFT-LCD-with-Resistive-Touch-Screen/blob/master/imgs/%ED%95%80%20%EC%97%B0%EA%B2%B0.png)<br>
<p align="center"><img src="https://github.com/taejin-seong/STM32F103VET6-TFT-LCD-with-Resistive-Touch-Screen/blob/master/imgs/%ED%95%80%20%EC%97%B0%EA%B2%B0.png"> </p>
<br><br>

# CTKey
Open-source osu! keyboard with a WinForm RGB LED controller

Để compile được file Arduino, các bạn cần có các file thư viện sau:

thijse's EEPROMex: https://github.com/thijse/Arduino-EEPROMEx

Adafruit's Neopixel: https://github.com/adafruit/Adafruit_NeoPixel

Bounce2: https://github.com/thomasfredericks/Bounce2

SoftPWM: https://github.com/bhagman/SoftPWM

WS2812fx modified đã có ở bên trên.

Tất cả library đều copy vào thư mục libaries trong Documents/Arduino.

PCB đã được xuất sẵn ra các file GERBER để tiện đem đi làm mạch luôn nằm trong folder Project Outputs for Cherry_MX.

# Những thứ cần chuẩn bị sau khi có PCB

+ 2 switch tùy chọn

+ 3 nút bấm cao 6x6x8

+ 2 đèn led 0805 RGB V1 hàn hướng mũi tên ra ngoài (cả 2 đầu)

+ 2 đèn WS2812 hàn với điểm khuyết như hình: 

![WS2812 Indicator](https://raw.githubusercontent.com/gazer000/CTKey/master/ws2812indicator.JPG)

+ Arduino Pro Micro hàn mặt chip hướng xuống dưới

+ 3 con trở dán 0805 100 ở vị trí R1 R2 R4 và 4 con trở dán 0805 200 (dán ở đâu update sau :D )

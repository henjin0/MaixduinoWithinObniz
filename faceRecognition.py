import sensor
import image
import lcd
from fpioa_manager import fm
from machine import UART
from board import board_info
import KPU as kpu
import json

lcd.init()
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.run(1)

fm.register (6, fm.fpioa.UART1_RX)
fm.register (7, fm.fpioa.UART1_TX)
uart = UART (UART.UART1, 115200, 8, None, 1, timeout=1000, read_buf_len = 4096)


task = kpu.load(0x300000) # you need put model(face.kfpkg) in flash at address 0x300000
# task = kpu.load("/sd/face.kmodel")
anchor = (1.889, 2.5245, 2.9465, 3.94056, 3.99987, 5.3658, 5.155437, 6.92275, 6.718375, 9.01025)
a = kpu.init_yolo2(task, 0.5, 0.3, 5, anchor)

while(True):
   img = sensor.snapshot()
   code = kpu.run_yolo2(task, img)
   if code:
       for i in code:
           uart.write(json.dumps(i)+'\n')
           a = img.draw_rectangle(i.rect())
   a = lcd.display(img)
a = kpu.deinit(task)
uart.deinit()
del uart

# Snapshot Example
#
# Note: You will need an SD card to run this example.
#
# You can use your OpenMV Cam to save image files.

import sensor, image, pyb

RED_LED_PIN = 1
BLUE_LED_PIN = 3

sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.GRAYSCALE) # or sensor.GRAYSCALE
sensor.set_framesize(sensor.B128X128) # or sensor.QQVGA (or others)
sensor.set_windowing((92,112))
sensor.skip_frames(10) # Let new settings take affect.
sensor.skip_frames(time = 2000)

num = 1 #设置被拍摄者序号，第一个人的图片保存到s1文件夹，第二个人的图片保存到s2文件夹，以此类推。每次更换拍摄者时，修改num值。

n = 20 #设置每个人拍摄图片数量。

#连续拍摄n张照片，每间隔3s拍摄一次。
while(n):
    #红灯亮
    pyb.LED(RED_LED_PIN).on()
    sensor.skip_frames(time = 3000) # Give the user time to get ready.等待3s，准备一下表情。

    #红灯灭，蓝灯亮
    pyb.LED(RED_LED_PIN).off()
    pyb.LED(BLUE_LED_PIN).on()

    #保存截取到的图片到SD卡
    print(n)
    sensor.snapshot().save("singtown/s%s/%s.pgm" % (num, n) ) # or "example.bmp" (or others)

    n -= 1

    pyb.LED(BLUE_LED_PIN).off()
    print("Done! Reset the camera to see the saved image.")

print("finished!")

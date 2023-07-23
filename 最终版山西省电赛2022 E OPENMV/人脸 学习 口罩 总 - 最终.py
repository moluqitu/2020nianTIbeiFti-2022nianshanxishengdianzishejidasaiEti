import sensor, time, image, pyb , math, lcd, os, tf, uos, gc
from pyb import UART, Pin, Timer
threshold_index = 0
thresholds = [(37, 69, -23, 3, -41, -4),
              (30, 100, -64, -8, -32, 32),#·
              (3, 53, -7, 4, -3, 11)]
RED_LED_PIN = 1
GREEN_LED_PIN = 2
BLUE_LED_PIN = 3


uart = UART(3,115200,timeout_char=1000)
data=bytes([0x0d,0x0a])
pixels_max=3300
face_max=7700
facenum=3
sensor.reset() # Initialize the camera sensor.
sensor.set_pixformat(sensor.RGB565) # or sensor.GRAYSCALE
sensor.set_framesize(sensor.QQVGA2) # Special 128x160 framesize for LCD Shield.
lcd.init() # Initialize the lcd screen.
#lcd初始化
light = Timer(2, freq=50000).channel(1, Timer.PWM, pin=Pin("P6"))
light.pulse_width_percent(10) # 控制亮度 0~100

def face_recognition(facemax,facenum):
    sensor.reset() # Initialize the camera sensor.
    sensor.set_pixformat(sensor.GRAYSCALE) # or sensor.GRAYSCALE
    sensor.set_framesize(sensor.B128X128) # or sensor.QQVGA (or others)
    sensor.set_windowing((92,112))
    sensor.skip_frames(10) # Let new settings take affect.
    sensor.skip_frames(time = 1000) #等待5s
    #SUB = "s1"
    NUM_SUBJECTS = facenum #图像库中不同人数，一共6人
    NUM_SUBJECTS_IMGS = 20 #每人有20张样本图片   拍摄当前人脸。
    img = sensor.snapshot()
    d0 = img.find_lbp((0, 0, img.width(), img.height()))    #d0为当前人脸的lbp特征
    img = None
    pmin = 999999
    num=0
    for s in range(1, NUM_SUBJECTS+1):
        dist = 0
        for i in range(2, NUM_SUBJECTS_IMGS+1):
            img = image.Image("singtown/s%d/%d.pgm"%(s, i))
            d1 = img.find_lbp((0, 0, img.width(), img.height())) #d1为第s文件夹中的第i张图片的lbp特征
            dist += image.match_descriptor(d0, d1)#计算d0 d1即样本图像与被检测人脸的特征差异度。
        print("Average dist for subject %d: %d"%(s, dist/NUM_SUBJECTS_IMGS))#pmin = min(pmin, dist/NUM_SUBJECTS_IMGS, s)#特征差异度越小，被检测人脸与此样本更相似更匹配。
        if (dist/NUM_SUBJECTS_IMGS)<pmin:
            pmin=(dist/NUM_SUBJECTS_IMGS)
            num=s
        print(pmin)
    pmin_data='%d' %pmin
    if pmin > facemax :
        uart.write('0')
    elif pmin <= facemax :
        print(num) # num为当前最匹配的人的编号
        if num==1:
            uart.write('3')
        elif num==2:
            uart.write('4')
        elif num==3:
            uart.write('5')
        elif num==4:
            uart.write('7')
        elif num==5:
            uart.write('8')
        elif num==6:
            uart.write('9')
def take_photos(num2):#第(num2)个人
    sensor.reset() # Initialize the camera sensor.
    sensor.set_pixformat(sensor.GRAYSCALE) # or sensor.GRAYSCALE
    sensor.set_framesize(sensor.B128X128) # or sensor.QQVGA (or others)
    sensor.set_windowing((92,112))
    sensor.skip_frames(10) # Let new settings take affect.
    sensor.skip_frames(time = 2000)

    #num2 = 9 #设置被拍摄者序号，第一个人的图片保存到s1文件夹，第二个人的图片保存到s2文件夹，以此类推。每次更换拍摄者时，修改num值。

    n = 20 #设置每个人拍摄图片数量。
    while(n!=-1):
        #红灯亮
        pyb.LED(RED_LED_PIN).on()
        sensor.skip_frames(time = 500) # Give the user time to get ready.等待3s，准备一下表情。
        #红灯灭，蓝灯亮
        pyb.LED(RED_LED_PIN).off()
        pyb.LED(BLUE_LED_PIN).on()
        #保存截取到的图片到SD卡
        print(n)
        n1='%d' %n
        if(n==1):
            uart.write('6')
        if(n>0):
            sensor.snapshot().save("singtown/s%s/%s.pgm" % (num2, n) ) # or "example.bmp" (or others)
        n -= 1
        pyb.LED(BLUE_LED_PIN).off()
        print("Done! Reset the camera to see the saved image.")
def Mask_recognition():
    sensor.reset()                         # Reset and initialize the sensor.
    sensor.set_pixformat(sensor.RGB565)    # Set pixel format to RGB565 (or GRAYSCALE)
    sensor.set_framesize(sensor.QVGA)      # Set frame size to QVGA (320x240)
    sensor.set_windowing((240, 240))       # Set 240x240 window.
    sensor.skip_frames(time=2000)          # Let the camera adjust.

    net = None
    labels = None

    try:
        # load the model, alloc the model file on the heap if we have at least 64K free after loading
        net = tf.load("trained.tflite", load_to_fb=uos.stat('trained.tflite')[6] > (gc.mem_free() - (64*1024)))
    except Exception as e:
        print(e)
        raise Exception('Failed to load "trained.tflite", did you copy the .tflite and labels.txt file onto the mass-storage device? (' + str(e) + ')')

    try:
        labels = [line.rstrip('\n') for line in open("labels.txt")]
    except Exception as e:
        raise Exception('Failed to load "labels.txt", did you copy the .tflite and labels.txt file onto the mass-storage device? (' + str(e) + ')')

    clock = time.clock()
    clock.tick()

    img = sensor.snapshot()

    # default settings just do one detection... change them to search the image...
    for obj in net.classify(img, min_scale=1.0, scale_mul=0.8, x_overlap=0.5, y_overlap=0.5):
        print("**********\nPredictions at [x=%d,y=%d,w=%d,h=%d]" % obj.rect())
        img.draw_rectangle(obj.rect())
        # This combines the labels and confidence values into a list of tuples
        predictions_list = list(zip(labels, obj.output()))

    if(predictions_list[0][1]<0.5):
        uart.write('1')
    else:
        uart.write('2') #未识别到
        #uart.write(threshold_index)

#uart.write(str(num))
if __name__=='__main__':
    while(1):
        num3 = 0
        lcd.display(sensor.snapshot()) # Take a picture and display the image.
        #for n1 in range(1,8):
            #for n2 in range(1,40):
                #os.remove("singtown/s%s/%s.pgm" % (n1, n2) )
                #print(face_max)
        if uart.any():            #检测接收缓冲区数据
            num1 =uart.readline().decode()
            #num1 = int(num1)
            if(num1=='1'):       #队内检测
                pyb.LED(GREEN_LED_PIN).on()
                print(num1)
                face_recognition(face_max,facenum)
                pyb.LED(GREEN_LED_PIN).off()
                #print(face_max)
            elif(num1=='2'):     #录入信息stanger1
                pyb.LED(GREEN_LED_PIN).on()
                print(num1)
                if(num3==0):
                    take_photos(4)
                    facenum = 4

                if (num3 == 1):
                    take_photos(5)
                    facenum = 5

                if (num3 == 2):
                    take_photos(6)
                    facenum = 6
                num3 = num3 + 1
                pyb.LED(GREEN_LED_PIN).off()
            elif (num1 == 'B'):  # 录入信息stanger1
                pyb.LED(GREEN_LED_PIN).on()
                print(num1)
                Mask_recognition()
                pyb.LED(GREEN_LED_PIN).off()
                #print(stanger_num)
                #if   facenum==6:
                     #facenum=7
                #elif facenum==7:
                     #facenum=8
                #take_photos(facenum)

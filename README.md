# moluqitu-first
简易无接触温度测量与体温识别装置
本题选用GY906DCI（测量范围1米）红外测温模块读取人体和物体温度；STM32F103单片机进行数据处理和报警控制，并配合OLED屏和独立按键搭建了可实时显示温度相关信息的GUI；利用OpenMV模组进行识别，实现识别被测者身份、是否符合防疫要求（如佩戴口罩）功能及学习被测者身份。人脸识别通过Haar-Like特征和Adaboost算法相结合的级联分类器实现，口罩检测通过基于edge impulse训练的神经网络模型来实现。测试表明，在题目所给定的要求下，本系统能实现误差范围内温度测量及超标报警，身份识别模块等要求。装置具有价格低廉、功能多样的优势，测试中人脸识别、口罩检测、体温检测的准确率都较高。

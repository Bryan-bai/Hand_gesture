# ����ʶ����ָ�

- ����fhog������������ȡ��ʶ��

- �������Ƶ�bouding box�������������㶨λ�ﵽ�ָ��Ŀ��
- ����MedianFlow��׷���㷨��֤boudingbox׷�ٵ��ȶ���

# Requirements

- [OpenCV3.1 + contribute](http://opencv.org/downloads.html)

- [dlib19.9](http://dlib.net/)




## ��������չʾ

- ���г����������


![Demo](/snapshot/main2.png)

- ������Ƶ��ʾdemo

[��ƵDemo](/snapshot/video_demo.avi)

- �����㶨λЧ��
����
![palm](/snapshot/palm.png)
ȭͷ
![fist](/snapshot/fist.png)
ʤ��
![scissor](/snapshot/scissor.png)
����
![thumb](/snapshot/thumb.png)

## �������˵��

- ����̨������Ƶ����Ŀ¼
- ����������ִ򿪶�Ӧ��ŵ�����ͷ
- ESC�˳�

## ��������˵��
- Threshold: ������⵽�������Ƶ���ֵ
- 2X��3X��4X: ��ͬͼƬ�߶��Լ���ͼƬ����ʱ��
- show time: �Ƿ���ʾÿ��ͼƬ����ʱ��
- Bouding: �Ƿ���ʾbouding box
- Recognition: �Ƿ���ʾ�����
- Segmentation: �Ƿ���ʾ���Ʒָ��������½ǣ�
- Points: �Ƿ���ʾ���Ƶ�������

## ��������
������ͼ��ʾ
- ����ʼʱ����fHog�����������Զ�������ģ�ͽ���ƥ�䣬�õ���ֵ��ߵ����ƺ����ڵ�bouding box
- ����ǰ��box��ͼ���ʼ��MedianFlow׷���㷨
- ׷���㷨�õ���ͼ�����ڵ�bouding box�����������ع�ģ��õ�������
- ������Ϊ�����Ƶ������㣬�̶����Էָ��������������
- ׷��ʧ��ʱ���������ü��Ľ����ʼ׷���㷨
- ���⣬�����ģ���׷���㷨��ʶ������ͬ����bouding box�غ�����С��70%ʱ�ж�׷��ʧ��
![Flowchart](/snapshot/flowchart.png)

## �㷨�ص�
- fHog�������Ժܺõر����ֵ���������
- ����������˼���߶ȵ�����
- ����ֵ�����������
- ͼƬ���ſ���һ���̶��ϼ������ͼƬ��ʱ������
- MedianFlow�㷨����һ���̶����жϳ�׷�ٶ�ʧ����ʧ��
- MedianFlow�㷨Ч�ʽϸߣ������ŵ�ͼƬ��֡׷��ʱ��������10ms
- ����bouding box��������ع���Զ�λ���������ض�λ�ã����絥��ָ�⡢���ĵȵ�
- ����������ķָ�����ڻ��ڷ�ɫ�ķָ���Ը�³����Ӧ�Թ�������


## Reference

1. [dlib��������](http://blog.csdn.net/zmdsjtu/article/details/53454071)

2. [OpenCV contribute��������](http://blog.csdn.net/zmdsjtu/article/details/78069739)

3. Object detection with discriminatively trained partbased models. IEEE Trans. PAMI, 32(9):1627�C1645, 2010.�����ƶ�λ��ʶ��fHog������
4. One Millisecond Face Alignment with an Ensemble of Regression Trees by Vahid Kazemi and Josephine Sullivan, CVPR 2014.�������㶨λ��
5. [Opencv3_contribute׷���㷨��װ](https://www.learnopencv.com/object-tracking-using-opencv-cpp-python/)
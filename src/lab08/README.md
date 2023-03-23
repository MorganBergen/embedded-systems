# real time dnn inferencing

<!--- <img src="./assets/car.png" width="300px" align="right"> -->
<img src="./assets/nn.png" style="padding: 60px;" width="700px" align="right">

**contents**
-  [intro](#intro)
-  [tensorflow framework](#tensorflow-framework)
-  [`dnn.py`](#dnn-py)
-  [notes](#notes)
-  [final task](#final-task) 

## intro

DeepPicar is a "low-cost" deep nural network based autonomous car. this a mirrored small scale and stupid replication of a real self-driving car called [DAVE-2 by NVIDIA](https://developer.nvidia.com/blog/deep-learning-self-driving-cars/).  the objective is to load a machine learning algorithm load a [deep neural network](https://en.wikipedia.org/wiki/Deep_learning#Deep_neural_networks) **dnn** model and perform inferencing operations on the [rasberry pi 4](https://www.raspberrypi.com/documentation/).  note that all references will be dervied from [deeppicar project](https://github.com/dctian/DeepPiCar).

convolutional neural network CNN for short takes images front facing camera as input and produces car steering angles as output.  DeepPicar network architecture consists of - **9 layers - 27 million connections - 250k parameters** and can self drive in real-time using web camera and raspberry pi 3 quad-core platform.  using deeppicar we analyze the pi's computing capabilities to support end to end deep learning based real-time control of autonomous vehicles and look at the embedded computing platforms using DeepPicar cnn-based real time control workflow.

**directory tree**

```
❯ tree
.
├── dnn.py
├── epoch-1.avi
├── image.png
├── model
│   ├── model.ckpt.data-00000-of-00001
│   ├── model.ckpt.index
│   └── model.ckpt.meta
└── model.py

2 directories, 7 files
```

in the folder we already provided a pre-trained dnn model `model.py`, and `model/`, a sample video file `epoch-1.avi`, and inferference code `dnn.py`. the dnn model in `model.py` is designed to take a camera image as input and produce a steering angle to stay in the lane as output.  the sample video file was originally created from the camera of an rc car driven by a human pilot.  this video will be used as input to the dnn model instead of using an actual camera.  a series of frames will be individually analyzed and then will make an inference on what behavior is to take next.  if you wanted to make a self driving car using a camera system instead of radar expenses ratio is present, system will rely mostly on the camera and they run a suite of complex and sophisticated machine learning algoritms for each convolutional layer.

## tensorflow framework

### `dnn.py`
```python
from __future__ import division
import tensorflow as tf
```

tensorflow a very popular deep learning framework developed by google is requisit to run a dnn based application.  in order to run a neural network tensorflow uses sessions

## notes

-  is the inference going down
-  what was the difference when going from 1 to 2 or 3 to 4
-  are there diminishing returns

## final task


run the DNN inference code for CPU core numbers 1, 2 , 3 and 4.
Your task is to measure the performance---especially mean, which represents the average, and max, which represents the worst-case---of the inferencing operations while varying the number of CPU cores being used from 1 to 4.  Prepare a table showing the CPU core numbers, the mean and max time of inferencing operations (shown below) and write a comment on the result. (for example: how the inferencing operation time is varying with the CPU core, you can show your result using a graph as well.)

what is the time difference between 1 to 2 and 2 to 3 and 3 to 4

### conv1 convolutional layer completed inference

```
---------- Processing video for epoch 1 ----------
performing inference...
pred: -6.98 deg. took: 50.31 ms | cam=7.29 prep=2.94 pred=40.08
pred: -7.25 deg. took: 25.42 ms | cam=0.66 prep=1.17 pred=23.58
...
pred: -29.11 deg. took: 24.71 ms | cam=0.67 prep=1.09 pred=22.96
pred: -22.35 deg. took: 24.62 ms | cam=0.64 prep=1.08 pred=22.90
completed inference, total frames: 1000, average fps: 19.3 Hz
count: 999
mean: 26.2203142569
max: 58.3357810974
99.999pct: 58.1613650417
99.99pct: 56.5916205406
99.9pct: 40.8941755295
99pct: 37.037358284
min: 24.570941925
median: 24.8510837555
stdev: 3.47506702438
```
### conv2 convolutional layer completed inference

```
---------- Processing video for epoch 1 ----------
performing inference...
pred: -6.98 deg. took: 45.26 ms | cam=7.29 prep=2.89 pred=35.08
pred: -7.25 deg. took: 20.32 ms | cam=0.66 prep=1.15 pred=18.50
...
pred: -29.11 deg. took: 28.65 ms | cam=0.92 prep=1.60 pred=26.14
pred: -22.35 deg. took: 27.23 ms | cam=0.90 prep=1.60 pred=24.73
completed inference, total frames: 1000, average fps: 19.9 Hz
count: 999
mean: 26.8364902493
max: 36.1139774323
99.999pct: 36.1094850922
99.99pct: 36.0690540314
99.9pct: 35.6647434235
99pct: 33.7034082413
min: 19.3250179291
median: 27.5340080261
stdev: 3.79996037867
```

### conv3 convolutional layer completed inference

```
---------- Processing video for epoch 1 ----------
performing inference...
pred: -6.98 deg. took: 41.64 ms | cam=7.03 prep=2.98 pred=31.64
pred: -7.25 deg. took: 17.19 ms | cam=0.67 prep=1.14 pred=15.38
...
pred: -29.11 deg. took: 24.36 ms | cam=0.87 prep=1.82 pred=21.67
pred: -22.35 deg. took: 24.37 ms | cam=0.96 prep=1.80 pred=21.60
completed inference, total frames: 1000, average fps: 19.9 Hz
count: 999
mean: 23.2169482562
max: 29.3099880219
99.999pct: 29.3095311737
99.99pct: 29.3054195404
99.9pct: 29.2643032074
99pct: 25.9509801865
min: 15.9211158752
median: 22.5110054016
stdev: 1.37844835858

```

### conv4 convolutional layer completed inference

```
---------- Processing video for epoch 1 ----------
performing inference...
pred: -6.98 deg. took: 41.64 ms | cam=7.03 prep=2.98 pred=31.64
pred: -7.25 deg. took: 17.19 ms | cam=0.67 prep=1.14 pred=15.38
...
pred: -29.11 deg. took: 21.31 ms | cam=0.98 prep=1.77 pred=18.56
pred: -22.35 deg. took: 20.01 ms | cam=0.97 prep=1.76 pred=17.28
completed inference, total frames: 1000, average fps: 19.9 Hz
count: 999
mean: 21.1903220779
max: 25.6199836731
99.999pct: 25.6160219431
99.99pct: 25.5803663731
99.9pct: 25.2238106728
99pct: 24.5365142822
min: 14.2619609833
median: 21.3599205017
stdev: 1.17142166239
```

| cpu core |   meantime    |     maxtime   |
|:--------:|:-------------:|:-------------:|
| conv1    | 24.570941925  | 58.3357810974 |
| conv2    | 19.3250179291 | 36.1139774323 |
| conv3    | 15.9211158752 | 29.3099880219 |
| conv4    | 14.2619609833 | 25.6199836731 |

## conclusion

based on emperical analysis of running all cores we can observe that as the number of cpu cores in increased from 1 to 4, the mean and max times of inferencing operations for each convolutional layer decreases.  this indicates that increasing the number of cpu cores results in faster execution of the inferencing operations.  

the difference between the time for using 1 and 2 cores is higher for the conv1 layer compared to the other layers, indicating that this layer is more computationally intensive than the others.  

the time difference between 2 to 3 cores and 3 to 4 cores are relatively small for all layers, suggesting that further increasing the number of cores may not provide a significant improvement in performance.  however, this can only be confirmed by testing with a higher `N` of cores.

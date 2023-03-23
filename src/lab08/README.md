# real time dnn inferencing

**contents**

1.  [intro](#intro)
2.  [tensorflow framework](#tensorflow framework)

## intro

the objective is to load a machine learning algorithm load a [deep neural network](https://en.wikipedia.org/wiki/Deep_learning#Deep_neural_networks) **dnn** model and perform inferencing operations on the [rasberry pi 4](https://www.raspberrypi.com/documentation/)

[deeppicar project](https://github.com/dctian/DeepPiCar)

![image](./image.png)

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

in the folder we already provided a pre-trained dnn model `model.py`, and `model/`, a sample video file `epoch-1.avi`, and inferference code `dnn.py`

the dnn model in `model.py` is designed to take a camera image as input and produce a steering angle to stay in the lane as output.  the sample video file was originally created from the camera of an rc car driven by a human pilot.  this video will be used as input to the dnn model instead of using an actual camera.  a series of frames will be individually analyzed and then will make an inference on what behavior is to take next.

if you wanted to make a self driving car using a camera system instead of ladar.  they rely mostly on the camera and they run a suite of complex and sophisticated machine learning algoritms.


## notes

`python dnn py`


-  is the inference going down
-  what was the difference when going from 1 to 2 or 3 to 4
-  are there diminishing returns

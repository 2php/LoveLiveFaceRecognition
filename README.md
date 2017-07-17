# LoveLiveFaceRecognition
A simple toy of how to use caffe to train CNN on Windows

## Usage

### Data Preparation
The dataset can be download from [School Idol Tomodachi - Cards Album](http://schoolido.lu/cards/).

Or you can also use a download tool [LoveLiveCardsAlbum - GitHub](https://github.com/inlmouse/LoveLiveCardsAlbum) which is able to download all of images in the album automatically. 

Crop the images you download into 128*128 and put them into .\complete_data

We provied a uncropped dataset, download: [Mu's Dataset - BaiduYunPan](http://pan.baidu.com/s/1eRkRjb0)

**New**  Now we provide a detected and manual cleaned dataset, download: [Mu's Detected Dataset - BaiduYunPan](http://pan.baidu.com/s/1boIDDKF)

You can use the anime face detection program in [lbpcascade_animeface.Net - GitHub](https://github.com/inlmouse/lbpcascade_animeface.Net) to crop ypur dataset.

**New** A pure C++ detection and dataset/label building script has been provide in .\main.cpp.

The label marking is very simple, take .\label\train.txt as example:
<pre><code>
    data\train\image_name.png label_num
</code></pre>
Just format every line as the expression above, do NOT add your project root.

The label_num indexed 0 instead of 1. And the processing of val.txt is all the same as train.txt.

### Convert Data Structure
Excute .\setup\BatBuilder.exe to build 3 .bat files:
- convertimage2ldb_train.bat
- convertimage2ldb_val.bat
- Train.bat

If the excution end without any problem, then excute convertimage2ldb_train.bat and convertimage2ldb_val.bat to get the LEVELDB structure train/val dataset in .\trainLevelDB and .\valLevelDB.

After data converting then excute computeMean_train.bat and computeMean_val.bat to the compute the mean of the dataset, the results will be saved in .\model as train_mean.binaryproto and val_mean.binaryproto

### Add Data to Net and Train
We used a modified [Light-CNN](https://github.com/AlfredXiangWu/face_verification_experiment) for training. In order to reducing overfitting and accelerating convergence, this model will be very small. As the results, this toy model CANNOT be taken a serious use.

Open .\model\train_val.prototxt to change the path and the same to .\model\solver.prototext.

Check all the roots is filled correcttly, you can excute .\setup\Train.bat to train this net.

After training, you will get caffemodel in the .\snapshot saved like "lovelive_lightcnn_train_iter_1000.caffemodel".

### Prediction/Recogition
Open Prediction.py in the root, change the path you need. And just have fun...

## Some Results
We use 648 images as training dataset and rest 152 images as validation dataset, the train-val partition is in random. Considered that there are only 9 girls in the dataset, the results will occourd a considerable degree of overfitting.

Result1:
![result1](https://raw.githubusercontent.com/inlmouse/LoveLiveFaceRecognition/master/results/res3.png)

In the following picture, the Test Image1 is old character design version of Honoka(rarely show up in the dataset), the probability of correct recogition will fall to under 90%.

Due to an unknown reason(currenttly), when it comes to Kotori, it's very hard to get a stable and precise prediction.

Result2:
![result2](https://raw.githubusercontent.com/inlmouse/LoveLiveFaceRecognition/master/results/res2.png)

So we guess that it caused by the training images of Kotori in the dataset in considerable probability own the same/similar facial expression with other's. The following error may validate this problem: here Kotori(Test Image1) shows a very similar facial expression as Hanayo, and the prediction result recogized Kotori as Hanayo directly.

Error1:
![err1](https://raw.githubusercontent.com/inlmouse/LoveLiveFaceRecognition/master/results/err1.png)

## Some Test
The next 2 poster does not show up in the train-val dataset, so we choosed them as test images.
![test1](https://raw.githubusercontent.com/inlmouse/LoveLiveFaceRecognition/master/results/movieposter.jpg)
Here Umi is recognized as Nozomi.

![test2](https://raw.githubusercontent.com/inlmouse/LoveLiveFaceRecognition/master/results/posteresults.jpg)
Kotori is recognized as Hanayo, the same error as Error1.

## Some Anaylsis
The parameters of our training net are copied from bvlc_alexnet directly, so the results cannot be very good.

Validation Accrency and Training Loss fig has paste below:

Acc:
![Acc](https://raw.githubusercontent.com/inlmouse/LoveLiveFaceRecognition/master/results/Acc.png)

Loss:
![Loss](https://raw.githubusercontent.com/inlmouse/LoveLiveFaceRecognition/master/results/Loss.png)

Apparently, the model has been overfitted.

The intersting fact is that even human beings are difficult to distinguish these 9 girls by face(in the strict sense) in greyscale images. So we guess that the features that CNN learned will be eye colors, hair colors, hairstyles and facial exppressions. The following fig is visualized features in the caffemodel, it may be confirmed our guess from another side:

Visualized Feature:
![Con1](https://raw.githubusercontent.com/inlmouse/LoveLiveFaceRecognition/master/results/con1.png)


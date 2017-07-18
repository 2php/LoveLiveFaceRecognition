caffe_model_path = 'D:/Research/LoveLiveFaceRecognition';
prototxt_dir =strcat(caffe_model_path,'/model/deploy.prototxt');
model_dir = strcat(caffe_model_path,'/snapshot/lovelive_lightcnn_train_iter_500.caffemodel');
LightCNN = caffe.Net(prototxt_dir,model_dir,'test');
img1 = imread(strcat(caffe_model_path,'/complete_data/Ruby/794idolizedRuby.png'));
result1 = prediction(LightCNN, img1, 'prob');
img2 = imread(strcat(caffe_model_path,'/complete_data/Yoshiko/791idolizedYoshiko.png'));
result2 = prediction(LightCNN, img2, 'prob');

subplot(2,2,1);
imshow(img1);
title('Test Image 1');
subplot(2,2,2);
imshow(img2);
title('Test Image 2');
subplot(2,2,[3,4]);
plot(1:9,result1,'-b',1:9,result2,'-r');
title('Softmax Output');

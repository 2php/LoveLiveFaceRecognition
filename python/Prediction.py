import numpy as np 
import matplotlib.pyplot as plt 
import cv2
import os.path
 
caffe_root = '<your caffe root>\\'# this file is expected to be in {caffe_root}/examples 
import sys 
sys.path.insert(0, caffe_root + 'python') 
import caffe 
# Set the right path to your model definition file, pretrained model weights, 

# and the image you would like to classify. 
MODEL_FILE = '<your project root>\model/deploy.prototxt' 
PRETRAINED = '<your project root>\caffemodel/lovelive_alexnet_train_iter_1000.caffemodel' 
IMAGE_FILE1 = '<your project root>\data/val/556idolizedHanayo.png' 
IMAGE_FILE2 = '<your project root>\data/val/poster-84988.png' 


names=('Eli', 'Hanayo', 'Honoka', 'Kotori', 'Maki',  'Nico',  'Nozomi',  'Rin', 'Umi')
colors=["#feec96","#d5a532",'#de9a31',"#dbc09d","#de5959","#58565d","#8b78a1","#eb8855","#5556a5"]
Decolors=[(150,236,254),(50,165,231),(49,154,222),(157,192,189),(89,89,222),(93,86,88),(161,120,139),(86,136,235),(165,86,85)]


def GetPrediction(image):
    binary_file='<your project root>\model/train_mean.binaryproto'
    mean_file='<your project root>\model/train_mean.npy'
    blob = caffe.proto.caffe_pb2.BlobProto()
    data = open( binary_file , 'rb' ).read()
    blob.ParseFromString(data)
    arr = np.array( caffe.io.blobproto_to_array(blob) )
    out = arr[0]
    np.save( mean_file , out )

    mean_file='<your project root>\model/train_mean.npy'
    Net = caffe.Classifier(MODEL_FILE, PRETRAINED,
                           mean=np.load(mean_file).mean(1).mean(1),
                           channel_swap=(2,1,0),
                           raw_scale=255,
                           image_dims=(256, 256))
    input_image = caffe.io.load_image(image) 
    prediction = Net.predict([input_image],oversample=False)
    Results=[0,0,0,0,0,0,0,0,0]
    for i in range(0,9):
		Results[i]=prediction[0][i]
    return Results

    
def Plot(image1,image2):
    plt.figure 
    ax1 = plt.subplot(221)
    ax3=plt.subplot(222)
    ax2 = plt.subplot(212)
    plt.sca(ax1) 
    plt.title('Test Image1', size=14)
    plt.axis('off')
    plt.imshow(caffe.io.load_image(image1)) 



    plt.sca(ax2) 
    plt.title('Softmaxied Output', size=14)
    plt.ylabel('Probability', size=14)
    plt.xlabel('\mu\'s Member', size=14)

    Results1=GetPrediction(image1)
    Results2=GetPrediction(image2)
    
    plt.plot(Results1,color=colors[Results1.index(max(Results1))],label=names[Results1.index(max(Results1))]) 
    plt.plot(Results2,color=colors[Results2.index(max(Results2))],label=names[Results2.index(max(Results2))]) 
    plt.legend(loc='upper right')
    ax=plt.gca()  
    
    ax.set_xticklabels(names)

    plt.sca(ax3)
    plt.title('Test Image2', size=14)
    plt.axis('off')
    plt.imshow(caffe.io.load_image(image2)) 
    plt.show() 

if __name__=='__main__':
	Plot(IMAGE_FILE1,IMAGE_FILE2)



function ResultsMatrix = Prediction(CaffeNet, image, layer)
    gpu_id=0;
    caffe.set_mode_gpu();	
    caffe.set_device(gpu_id);
    %caffe.reset_all();
    image = imresize(image, [128,128]);
    image=single(image);
    im_data=zeros(size(image));
    im_data(:,:,1)=(image(:,:,3)-104)*0.0078125;
    im_data(:,:,2)=(image(:,:,2)-117)*0.0078125;
    im_data(:,:,3)=(image(:,:,1)-124)*0.0078125;
    CaffeNet.blobs('data').reshape([128 128 3 1]);
    CaffeNet.forward({im_data});
    ResultsMatrix = CaffeNet.blobs(layer).get_data();
end
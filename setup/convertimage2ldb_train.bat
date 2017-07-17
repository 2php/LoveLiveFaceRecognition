SET GLOG_logtostderr=1
%CaffeRoot%\convert_imageset.exe --resize_height=132 --resize_width=132 --shuffle --backend="leveldb" D:\Research\LoveLiveFaceRecognition\ D:\Research\LoveLiveFaceRecognition\label\train.txt D:\Research\LoveLiveFaceRecognition\trainLevelDB
pause

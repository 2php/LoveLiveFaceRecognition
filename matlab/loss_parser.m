% log file of caffe model
logName = 'D:\Research\LoveLiveFaceRecognition\setup\log\INFO.txt20170718-033131.7116';

fid = fopen(logName, 'r');
accuracy=[0];
accuracy_iter=[0];
loss=[0];
loss_iter=[0];
test_loss=[0];

tline = fgetl(fid);

while ischar(tline)
    % First find the accuracy line
    k = strfind(tline, 'Test net output');
    if (k)
        k = strfind(tline, 'accuracy');
        if (k)
            % If the string contain test and accuracy at the same time
            % The bias from 'accuracy' to the float number
            indexStart = k + 16; 
            indexEnd = size(tline);
            str = tline(indexStart : indexEnd(2));
            accuracy=[accuracy;str2double(str)];
        end
    end
     % Get the number of index
     k = strfind(tline, 'solver.cpp:341]');
     if (k)
        indexStart = k + 25;
      	indexEnd = strfind(tline, ',');
        str2 = tline(indexStart : indexEnd - 1);
        accuracy_iter=[accuracy_iter;str2num(str2)];
     end
     k = strfind(tline, 'Test net output #1: softmax_loss');
     if (k)
        indexStart = k + 35;
      	indexEnd = strfind(tline, '*');
        str2 = tline(indexStart : indexEnd - 2);
        test_loss=[test_loss;str2double(str2)];
     end
    % Then find the loss line
    k1 = strfind(tline, 'Iteration');
    if (k1)
       k2 = strfind(tline, 'loss');
       if (k2)
           indexStart = k2 + 7;
           indexEnd = size(tline);
           str1 = tline(indexStart:indexEnd(2));
           indexStart = k1 + 10;
           indexEnd = strfind(tline, ',') - 1;
           str2 = tline(indexStart:indexEnd);
           res_str1 = strcat(str2, '/', str1);
           loss=[loss;str2double(str1)];
           loss_iter=[loss_iter;str2num(str2)];
       end
    end
    tline = fgetl(fid);
end
loss=loss(2:length(loss),1);
loss_iter=loss_iter(2:length(loss_iter),1);
test_loss(1,1) = loss(1,1);
[hAx,hLine1,hLine2]  = plotyy(loss_iter,loss,accuracy_iter,accuracy);
ylabel(hAx(2),'Accuracy');
hold on
plot(accuracy_iter, test_loss);
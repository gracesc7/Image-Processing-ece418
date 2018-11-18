fileID = fopen('histogram-part4_baboon.txt','r');
formatSpec = '%f';
A = transpose(fscanf(fileID,formatSpec));
len = length(A);
C = 0:(len-1);
bar(C,A);
xlim([0 len]);
title('Histogram of difference pixel values (part 4)');
xlabel('pixel intensity ');
ylabel('probability of occurrence');


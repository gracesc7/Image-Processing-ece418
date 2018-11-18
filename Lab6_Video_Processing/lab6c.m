clear;clc;

% Reading Tank images
for j=1:9
 s=sprintf('video_database/tank_0%d.raw',j);
 fid=fopen(s,'r');
 tank(:,:,j)=(fread(fid,[486,486],'uchar'));
 fclose(fid);
end

% Pyramid decomposition
%Desampling and interpolate 2,4,6,8th img to get 4 diff img
for j=1:9
  if mod(j,2)~=1
    diff(:,:,j)= tank(:,:,j)-(tank(:,:,j-1)+tank(:,:,j+1))/2  ;
    fprintf('1st:%d \n',j);
  end
end

%downsample and interpolate 3,7th img to get 2 diff image
for j=1:9
   %fprintf('%d \n',j);
   if mod(j,2)~=0 && mod(j-1,4)~=0 && j~=9
     diff(:,:,j) = tank(:,:,j)-(tank(:,:,j-2) +tank(:,:,j+2))/2 ;
     fprintf('2nd:%d \n',j);
   end
end

%Reconstruct by interpolate 3 and 7th tank img
for j=1:9
   if mod(j+1,4)==0
      fprintf('3rd:%d \n', j);
      temp(:,:,j) = (tank(:,:,j-2) +tank(:,:,j+2))/2;
      out(:,:,j) = temp(:,:,j) + diff(:,:,j);   
   else 
      out(:,:,j) = tank(:,:,j);
   end
end

%Reconstruct by interpolating 2,4,6,8th img
for j=1:9
    if mod(j,2)~=1
       temp(:,:,j)= (out(:,:,j-1)+ out(:,:,j+1))/2;
       out(:,:,j) = temp(:,:,j)+diff(:,:,j);
       fprintf('4th:%d \n',j);
    end
end



       
      
    
     



       
     
    

%*******************************************************************************
% Your code goes in here.
% Generate the coded and diff images and display them 
% after appropriate intensity rescaling
%*******************************************************************************

% Conceptually, if images have to be transmitted, the following frames will be sent:
% coded(:,:,k); k=1,5,9 and diff(:,:,k); k=2,3,4,6,7,8.

%*******************************************************************************
% Your code goes in here
% Getting back the data (decoding)
% recon=coded+diff;
% Check for Perfect Reconstruction by computing MSE:
%*******************************************************************************

%out = recon
MSE=0;
for j=1:9
 diff = out(:,:,j)- tank(:,:,j);
 MSE=MSE+norm(out(:,:,j)-tank(:,:,j),'fro')^2;
end
MSE % Should be zero

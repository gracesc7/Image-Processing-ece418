clear;clc;

% Open raw image file and read in the image

fid=fopen('lena.raw','r');
lena=fread(fid,[512,512]);

% Close the opened raw image file 

fclose(fid);

% Matlab reads the image into the matrix columnwise 

lena=lena';

% Display the read image to make sure it looks ok

figure;colormap gray;imagesc(lena,[0 255]);
title('Lena');

% Create the 3 X 3 seperable bluring filter 

a=[0.1414 0.7071,0.1414];

% Plot the frequency response of the horizontal (same as vertical) filter

H = fft(a,1023);
H = fftshift(H);
W = (2*pi/1023).*[0:1:1023-1] - pi;
figure; plot(W,abs(H));grid;
xlabel('frequency in radians --->');
ylabel('magnitude of filter dtft  --->');
title('Magnitude resposne of horizontal bluring filter');

h=a'*a;
% Plot the dsft of the 2-D bluring kernel

H = fft2(h,127,127);
H = fftshift(H);
W = (2*pi/127).*[0:1:127-1] - pi;
figure;mesh(W,W,abs(H));
xlabel('Wx --->');
ylabel('Wy --->');
zlabel('abs(H(Wx,Wy)) --->');
title('2D DSFT of bluring kernel');

lena_blur=filter2(h,lena);
figure;colormap gray;imagesc(lena_blur,[0 255]);
title('Lena blur');


%% PART B
% Change the value of sigma for different parts

sigman = 0;
lena_blur = sigman*randn(512,512) + lena_blur;

% Compute the mse between the original and blured images

% Compute the horizontal least squares inverse filter
% and apply it to the blured image to obtain an estimate 
% of the original image

% Be very careful with what columns and rows need to be used
% and how they have to be arranged into a matrix so as to 
% perform the horizontal filtering by an appropriate matrix 
% multiplication
% I'm going to do this for you only for the horizontal filter
% You will need to figure things out for the vertical filter.

% First extract the right columns of the original image 
% (which has to be estimated from the blured image) 

var=lena(1:512,2:511);
var=var';
x =var(:);

% Then set up the Y matrix from the blured image

var=lena_blur(1:512,1:510);
var=var';
col1=var(:);
var=lena_blur(1:512,2:511);
var=var';
col2=var(:);
var=lena_blur(1:512,3:512);
var=var';
col3=var(:);
Y=[col1 col2 col3];   

% Finally we can compute the linear least squares 
% solution for the horizontal filter c:

c=inv(Y'*Y)*Y'*x;


% plot the frequency response of c 

% see code above to do this ....
% scz
H_c = fft(c,1023);
H_c = fftshift(H_c);
W_c = (2*pi/1023).*[0:1:1023-1] - pi;
figure; plot(W_c,abs(H_c));grid;

xlabel('frequency in radians --->');
ylabel('magnitude of filter dtft  --->');
title('Magnitude response of horizontal least squares inverse filter');


% Having known c, we can compute the horizontal linear least
% squares estimate:

xhat_hor = Y*c;   %partially restored img
fprintf('size of xhor %i\n',size(xhat_hor));
% and also compute the resulting mse:

mse_hor =(norm((x-xhat_hor),'fro')^2)/(512*510);
fprintf('mse after horizontal i%\n',mse_hor);

% Follow the same procedure as above but now on xhat_hor instead of
% on lena_blur. Again one needs to set up the matrices properly.

% First set up the image to be estimated:

x = reshape(x,510,512);
var=x(1:510,2:511);
var = var';
x = var(:);

% Then set up the Y matrix 
%scz
xhat_hor = reshape(xhat_hor,510,512);
var=xhat_hor(1:510,1:510);
var=var';
col1=var(:);
var=xhat_hor(1:510,2:511);
var=var';
col2=var(:);
var=xhat_hor(1:510,3:512);
var=var';
col3=var(:);

% refer to the hor filter part to do this...

Y=[col1 col2 col3];

% We can now obtain the linear least squares vertical filter:

d=inv(Y'*Y)*Y'*x;

% plot the frequency response of d


% ....insert code ....
% scz
H_d = fft(d,1023);
H_d = fftshift(H_d);
W_d = (2*pi/1023).*[0:1:1023-1] - pi;
figure; plot(W_d,abs(H_d));grid;

xlabel('frequency in radians --->');
ylabel('magnitude of filter dtft  --->');
title('Magnitude response of vertical least squares inverse filter');

%%
% We can then apply this least squares vertical filter 
% to the horizontal least squares filtered image to obtain the 
% the final estimate:

xhat_hor_ver =  Y*d;

% and also compute the resulting error.

mse_vert =(norm((x - xhat_hor_ver),'fro')^2)/(512*512);
fprintf('mse after vertical %i\n',mse_vert);

% Create the 2-D separable filter
% and apply it directly onto the blured image. The resulting MSE should
% be almost the same as the one computed above (there will be a small difference
% because the above mse values were not calculated on the entire 512 X 512 image).

invfilt=d*c'

% plot the 2-D frequency response of the inverse filter

% see how this was done for the bluring kernel....
H_inv = fft2(invfilt,127,127);
H_inv = fftshift(H_inv);
W_inv = (2*pi/127).*[0:1:127-1] - pi;
figure;mesh(W_inv,W_inv,abs(H_inv));

xlabel('Wx --->');
ylabel('Wy --->');
zlabel('abs(H(Wx,Wy)) --->');
title('2D DSFT of separable least squares inverse filter');

% Apply the inverse filter to the blured noisy image

lena_reconst=filter2(invfilt,lena_blur);
figure;colormap gray;imagesc(lena_blur,[0 255]);
title('Lena reconst');

% and compute the mse

MseReconst=(norm((lena-lena_reconst),'fro')^2)/(512*512);

%%
% Compute Matlab's adaptive wiener3() solution and the 
% resulting MSE. Type: help wiener2 to find out how to use
% this function. Note that noise power = variance of noise 
% and not its standard deviation. Try 3 X 3, 5 X 5, and 7 X 7 neighborhoods.
%lena_blur=filter2(h,lena);

%PART B 
% apply filter obtained from Part A to reconstruct lena_blur + random gaussian noise:
g_noise = sigman*randn(512,512);
lena_gauss_noise = lena_blur + g_noise;  % Y 
lena_reconst_g=filter2(h,lena_gauss_noise);
figure;colormap gray;imagesc(lena_reconst_g,[0 255]);
title('reconstructed lenablur+gaussiannoise');
mse_g =(norm((lena - lena_reconst_g),'fro')^2)/(512*512);
fprintf('mse for reconst lenablur+gaussian noise %i\n',mse_g);


%%

wiener_3x3 = wiener2(lena_gauss_noise,[3 3],sigman*sigman);
err_3 = immse(wiener_3x3, lena);
figure;colormap gray;imagesc(wiener_3x3,[0 255]);
title('lena with wiener window size 3x3');
%%
wiener_5x5 = wiener2(lena_gauss_noise,[5 5],sigman*sigman);
err_5 = immse(wiener_5x5, lena);
figure;colormap gray;imagesc(wiener_5x5,[0 255]);
title('lena with wiener window size 5x5');

wiener_7x7 = wiener2(lena_gauss_noise,[7 7],sigman*sigman);
err_7 = immse(wiener_7x7, lena);
figure;colormap gray;imagesc(wiener_7x7,[0 255]);
title('lena with wiener window size 7x7');
% ...insert code...

% Skeleton code for lab6a:
%---------------------------
% General comments:
%---------------------------
%
% In matlab, a line beginning with a % sign is a commented line
% type:
%
% matlab -nodesktop 
%
% at the command prompt and hit enter to invoke matlab without fancy user 
% interfaces. We recommend that you open matlab in this manner. At the matlab 
% prompt type:
%
% help topic_name
%
% and hit enter to get more information about the topic. 
% Help without arguments provides a list of available help topics.
%
% Use help to find out more about the following image and video processing
% commands that will be used in this lab:
%
% clear, clc, fopen, fread, fclose, colormap, ', for, imagesc, getframe, end, 
% fprintf, pause, movie, if, else, sprintf, : , ~, mod, norm, zeros, ones.
%
% Most of lab6a has been implemented for you below. Please spend time
% to understand what this code does and how the different matlab functions work.
%-----------------------------------------------------------------------------

% clear all previous variables, clear the matlab work screen
clear;clc;

% Open the raw files with read permission and read the data into image arrays. 
% Then close the files

fid=fopen('video_database/tank_01.raw','r');
X=fread(fid,[486,486],'uchar');
fclose(fid);
fid=fopen('video_database/tank_10.raw','r');
Y=fread(fid,[486,486],'uchar');
fclose(fid);

% Matlab reads in data and puts them into the image array columnwise instead of rowwise
X=X';
Y=Y';

% at this stage X contains your first image and Y the 21st image. 
% you need to generate 21 intermediate images by linearly interpolating the 
% first and last images:
frac = 1/21;
for j=1:21
    Z = zeros(486,486);
    for m = 1:486
        for n = 1:486
            Z(m,n) = (1-frac*j)*X(m,n)+frac*j*Y(m,n);
%***************************************************************
% you write this line of code. Z should contain the jth interpolated image:
%***************************************************************
%EDIT HERE

        end
    end
   
% display the interpolated image as grayscale images 
colormap gray;
 imagesc(Z);

% Create a moovie deck of image frames. Please read the Coding section of the lab
% and use Matlab's help to find out more. The function getframe captures the current
% image being displayed.
 %load('video_database/tank_10.raw');
 %image(Z);
 M(:,j)=getframe;
end
movie(M);
fprintf(1,'Strike a key for movie show...\n');
pause

% Display the moovie at 12 frames per second repeating the moovie 4 times
% forwards and backwards
colormap gray; movie(M,-4,12);

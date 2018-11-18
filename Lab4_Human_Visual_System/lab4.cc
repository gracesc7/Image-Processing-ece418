/*===
lab4-skeleton.cc

Abstract: Skeleton for Lab 4
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "image.h"
using namespace std;

int main (int argc, char* argv[])
{
	Image inputImage;
	inputImage.LoadPng("day-name-b_sin.png");
	for(int j = 0; j<50; j++){
		//for (int i = 0; i<512; i++){
			cout<< inputImage.Pixel(j,510)<<endl;
		//}
	}

	//Part A1:mach Bands  vertical
	double pix;
	Image image;
	image.Resize (512, 512);
	int w = image.Width();
	int h = image.Height();
	int band = w/8; //width of the band
	//255 218 182 145 109 72 36
	//int pix_diff = int(255/7);
	for(int i = 0; i<8; i++){
		double idx = (double)((double)(7-i)/(double)7);
		double idx1 = (double)i/(double)7;
		//cout<<idx<<endl;
		pix = double(int(idx1*255)) +double((int(idx* (double)0)));
		//cout<<pix<<endl;
		for (int j = 0; j<h; j++){
				for(int k = 0; k<band; k++){
					image.Pixel(i*band+k, j) = pix;
				}
		}
	}
		image.SavePng ("day-name-test_A1.png");

//Part A2: mach bands  horizontal
	Image image2  ;
	image2.Resize (512, 512);
	for (int i = 0 ; i <w; i++){
		for (int j = 0; j<h; j++){
			image2.Pixel(i,j) = image.Pixel(j,511-i);
		}
		}
		image2.SavePng("day-name-test_A2.png");

//Part B:512x1024  sinusoidal grating
double pi = 3.1415926;
Image image3;
image3.Resize(1024,512);
w = image3.Width();
h = image3.Height();
for(int i =0; i< w; i++){
	double idx = double(i)/double((w-1));
	double freq = double(pi/3)*idx;
	//cout <<"freq"<<freq <<endl;
	for(int j = 0; j<h; j++){
		double amp = 127.5*double((h-1-j))/double(h-1);
		image3.Pixel(i,j)= amp*sin(i*freq);
		//cout<<"pix"<<image3.Pixel(i,j)<<endl;
		//cout<<image3.Pixel(i,j) <<endl;
		//double a = double(sin(i*freq/(2*pi)));
		//cout<< "/freq"<<sin(i/freq)<<endl;
		//cout<<a<<endl;		//sin(pi)
	}
}

image3.SavePng ("day-name-test_3.png");


//Part C Boxes:
Image imagebox;
imagebox.Resize(1024,512);
double width, height;
width = imagebox.Width();
height = imagebox.Height();
double S1,S2; //the pixel intensity of two large background squares.
double X;  //the pixel intensity of small squares
//set the pixel intensity for background square 1.
X = double(255);
S1 = double(0);
S2 = double(128);
for( int i = 0; i<width/2; i++){
	for (int j = 0; j<height; j++){
		imagebox.Pixel(i,j)= S1;
	}
}
for(int i =width/2; i<width; i++){
	for(int j = 0; j<height; j++){
		imagebox.Pixel(i,j) = S2;
	}
}
for (int k = width/4 - 64/2 +1; k<width/4 +64/2+1; k++){
	for(int p = height/2 - 64/2+1 ; p<height/2 +64/2 +1; p++){
		imagebox.Pixel(k,p) = X;
	}
}
for(int k = 3*width/4 - 64/2+1 ; k< 3*width/4 +64/2 +1; k++ ){
	for (int p = height/2 - 64/2+1 ; p<height/2+64/2 +1; p++){
		imagebox.Pixel(k,p) = X;
	}
}
imagebox.SavePng("day-name-test-C_255_0_128.png");


//Part D: More Boxes:

Image imagebox2;
imagebox2.Resize(512,512);
double I;  //surround intensity
double F;  //forground intensity
F = double(20);
I = double(10) ;
double dI = F-I;
width = imagebox2.Width();
height = imagebox2.Height();
for (int i =0; i<width; i++){
	for (int j =0; j<height; j++){
		imagebox2.Pixel(i,j) = I;
	}
}

for (int k = width/2 - 8/2 +1; k<width/2 +8/2+1; k++){
	for(int p = height/2 - 8/2+1 ; p<height/2 +8/2 +1; p++){
		imagebox2.Pixel(k,p) = F;
	}
}
cout<<"dI:"<<endl;
imagebox2.SavePng("day-name-test-D_160");
}

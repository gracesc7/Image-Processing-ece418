/*===
lab2c-skeleton.cc

Abstract: Skeleton for Lab 2 part (c)
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "image.h"
#include "fft.h"
using namespace std;

int main (int argc, char* argv[])
{
	// check parameters' correctness
	if (argc != 4)
	{
		cerr << "Usage: " << argv[0] << " in.png out.png frequency" << endl;
		return 1;
	}
	double frequency = atof (argv[3]);
	if (frequency < 0 || frequency > 0.5)
	{
		cerr << "Cutoff frequency must be in [0,0.5]" << endl;
		return 1;
	}

	// load the image
	ComplexImage image;
	image.LoadPng (argv[1]);

	/*===

	Insert Lab 2 code here:

	1. Compute the 2D FFT of the image
	2. Perform the frequency domain operation
	3. Compute the inverse 2D FFT of the image
	4. Re-normalize the image

	===*/

	//FIrst Compute FFT for each row
	for(int i=0; i< image.Height(); i++){
		vector<Complex> signal;
		signal.resize(image.Width());
		for(int j=0; j<image.Width(); j++){
			signal[j]=image.Pixel(j,i);
		}
		FFT::Transform(signal);
		for(int w=0; w<image.Width();w++){
			image.Pixel(w,i)=signal[w];
		}
	}

	// Then Compute FFT for each column
	for(int w=0; w<image.Width();w++){
		vector<Complex> signal2;
		signal2.resize(image.Height());
		for(int j=0; j<image.Height();j++){
			signal2[j]=image.Pixel(w,j);
		}
		FFT::Transform(signal2);
		for(int k=0; k<image.Height();k++){
			image.Pixel(w,k)=signal2[k];

		}
	}

  // Apply low pass filter to the fourier domain
	int w = image.Width();
	int h = image.Height();
	for (int i=0; i < w; i++){
		for (int j =0; j < h; j++){
			//in fourier domain, keep four corner square with size (x_size*frequency)^2
			if( (i<=frequency*w && j<=frequency*h )|| (i>=w-frequency*w && j>= h-frequency*h)
				|| (i<=frequency*w && j>= h-frequency*h)|| (i>=w-frequency*w && j<= frequency*h))
				{}
			else {
				//set pixels in areas(outside cutoff frequency) other than the four corner squares to 0
				image.Pixel(i,j)=0;
			}
		}
	}


for(int w=0; w<image.Width();w++){
	vector<Complex> signal2;
	signal2.resize(image.Height());
	for(int j=0; j<image.Height();j++){
		signal2[j]=image.Pixel(w,j);
	}
	FFT::InverseTransform(signal2);
	for(int k=0; k<image.Height();k++){
		image.Pixel(w,k)=signal2[k];
	}
}

for(int i=0; i< image.Height(); i++){
	vector<Complex> signal;
	signal.resize(image.Width());
	for(int j=0; j<image.Width(); j++){
		signal[j]=image.Pixel(j,i);
	}
	FFT::InverseTransform(signal);
	for(int w=0; w<image.Width();w++){
		image.Pixel(w,i)=signal[w];
	}
}

//Calculate the largest and smallest real part of inverse FFTs for scaling purpose
double m=0;
double M=0;

	for(int w=0; w<image.Width(); w++){
		for(int h=0; h<image.Height();h++){
			if(image.Pixel(w,h).real()<m){
				m=image.Pixel(w,h).real();
			}
			if(image.Pixel(w,h).real()>M){
				M=image.Pixel(w,h).real();
			}
		}
	}

//scale the image pixel so that each pixel is within (0,255) range
	for(int i=0; i<image.Height(); i++){
		for(int j=0; j<image.Width(); j++){
			image.Pixel(j,i)=(image.Pixel(j,i)-m)*((double)255)/(M-m);
		}
	}


	// save the image
	image.SavePng (argv[2]);

	return 0;
}

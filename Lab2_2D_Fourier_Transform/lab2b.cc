/*===
lab2ab-skeleton.cc

Abstract: Skeleton for Lab 2 parts (a) and (b).
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
//#include <algorithm>
#include "image.h"
#include "fft.h"
using namespace std;

int main (int argc, char* argv[])
{
	// check parameters' correctness
	if (argc != 3)
	{
		cerr << "Usage: " << argv[0] << " in.png out.png" << endl;
		return 1;
	}

	// load the image
	ComplexImage image;
	image.LoadPng (argv[1]);

	/*===

	Insert Lab 2 code here:

	1. Compute the 2D FFT of the image
	2. Perform the frequency domain operation(s)
	3. Compute the inverse 2D FFT of the image
	4. For parts (b) and (c), re-normalize the image

	===*/

	//set magnitude of complex frequency after FT to 1, preserve the phase.
	double m=0;
	double M=0;

	// Compute FFT for each row
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
	// Compute FFT for each column
	for(int w=0; w<image.Width();w++){
		vector<Complex> signal2;
		signal2.resize(image.Height());
		for(int j=0; j<image.Height();j++){
			signal2[j]=image.Pixel(w,j);
		}
		FFT::Transform(signal2);
		for(int k=0; k<image.Height();k++){
			double a=abs(signal2[k]);
			//set magnitude to 1
			image.Pixel(w,k)=signal2[k]/a;
		}
}

//Compute Inverse transform for each column
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

//COmpute Inverse transform for each row
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
 	// Find the maximum and minimum real part of inverse FFTs
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

	// scale image pixel so that each pixel value is within (0,255) range
	for(int i=0; i<image.Height(); i++){
		for(int j=0; j<image.Width(); j++){
			image.Pixel(j,i)=(image.Pixel(j,i)-m)*((double)255)/(M-m);

		}
	}

	//modified_value: the M and m is found from the signal vector for each row or from the entire image?



	// save the image
	image.SavePng (argv[2]);

	return 0;
}

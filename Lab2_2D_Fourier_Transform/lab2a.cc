/*===
lab2ab-skeleton.cc

Abstract: Skeleton for Lab 2 parts (a) and (b).
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

	=*/


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
			image.Pixel(w,k)=abs(signal2[k]);
		}
}

// First compute Inverse FFT for columns
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

// Then Compute inverse FFT for each row
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

	// save the image
	image.SavePng (argv[2]);

	return 0;
}

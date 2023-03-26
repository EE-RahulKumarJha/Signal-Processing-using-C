#include <stdio.h>
#include <math.h>

#define PI 3.14159265

int main() {
   float signal[8] = {0.5, 0.7, 0.8, 0.9, 1.0, 0.9, 0.8, 0.7};
   float filtered_signal[8] = {0};
   float frequency = 10.0;
   float sampling_rate = 50.0;
   float dt = 1.0 / sampling_rate;
   float omega = 2.0 * PI * frequency;
   int i, k,n;

   // Perform low-pass filtering using a moving average filter
   for ( i = 0; i < 8; i++) {
      if (i < 2 || i > 5) {
         filtered_signal[i] = signal[i];
      } else {
         filtered_signal[i] = (signal[i-2] + signal[i-1] + signal[i] + signal[i+1] + signal[i+2]) / 5.0;
      }
   }

   // Perform frequency domain analysis using a discrete Fourier transform (DFT)
   float real_part[8] = {0};
   float imag_part[8] = {0};
   float magnitude[8] = {0};
   float phase[8] = {0};

   for (k = 0; k < 8; k++) {
      for ( n = 0; n < 8; n++) {
         real_part[k] += signal[n] * cos(omega * n * dt * k);
         imag_part[k] -= signal[n] * sin(omega * n * dt * k);
      }
      magnitude[k] = sqrt(real_part[k] * real_part[k] + imag_part[k] * imag_part[k]);
      phase[k] = atan2(imag_part[k], real_part[k]) * 180.0 / PI;
   }

   // Display the results
   printf("Original signal:\n");
   for ( i = 0; i < 8; i++) {
      printf("%.2f ", signal[i]);
   }
   printf("\n");

   printf("Filtered signal:\n");
   for ( i = 0; i < 8; i++) {
      printf("%.2f ", filtered_signal[i]);
   }
   printf("\n");

   printf("Frequency domain analysis:\n");
   for ( k = 0; k < 8; k++) {
      printf("Frequency: %.2f Hz, Magnitude: %.2f, Phase: %.2f degrees\n", k * frequency, magnitude[k], phase[k]);
   }

   return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
int main()
{
    int hight = 50;
    int width = 120;
    float z[hight * width]; //расстояние
    char b[hight * width];  //символ
    char gradient[]=" .,-~:;=!*#$@";
    memset(b, '\0', hight * width);
    float aspect = (float)width/hight*(11.0f/24.0f);
   	int t=0;
    while (1)
    {
		    for (int i = 0; i < width; i++)
		    {
		        for (int j = 0; j < hight; j++)
		        {
		            float x = (float)i/width*2.0f-1.0f;
		            float y = (float)j/hight*2.0f-1.0f;
		            char pixel = ' ';
		            x=x*aspect;
					x+=sin((t*t-1)/(t*t+1));
					y+=sin((t*t-1)/(t*t+1));
					float dist = x*x+y*y;
					int color = (int)(1.0f/dist);
					if (color<0) color =0;
					else if (color>12) color =12;
		            pixel = gradient[color];
		            b[i + j * width] = pixel;
		        }
		    }
		    printf("\x1b[H");
		    for (int k = 0; k < width * hight; k++)
		    {
		        if ((k) % width == 0)
		            putchar('\n');
		        putchar(b[k]);
		    }
		    t++;
		    usleep(100);
		}

    return 0;
}

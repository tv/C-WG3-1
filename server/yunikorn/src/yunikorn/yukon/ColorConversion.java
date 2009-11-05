package yunikorn.yukon;

public class ColorConversion {
public static int[] I420toARGB(byte[] yuv, int width, int height)
{

boolean invertHeight=false;
if (height<0)
{
height=-height;
invertHeight=true;
}

boolean invertWidth=false;
if (width<0)
{
width=-width;
invertWidth=true;
}



int iterations=width*height;
//if ((iterations*3)/2 > yuv.length){throw new IllegalArgumentException();}
int[] rgb = new int[iterations];

for (int i = 0; i<iterations;i++)
{
	/*int y = yuv[i] & 0x000000ff;
	int u = yuv[iterations+(i/4)] & 0x000000ff;
	int v = yuv[iterations + iterations/4 + (i/4)] & 0x000000ff;*/
	int nearest = (i/width)/2 * (width/2) + (i%width)/2;
	
	int y = yuv[i] & 0x000000ff;
	int u = yuv[iterations+nearest] & 0x000000ff;
	
	
	int v = yuv[iterations + iterations/4 + nearest] & 0x000000ff;
	
	//int b = (int)(1.164*(y-16) + 2.018*(u-128));
	//int g = (int)(1.164*(y-16) - 0.813*(v-128) - 0.391*(u-128));
	//int r = (int)(1.164*(y-16) + 1.596*(v-128));
	
	//double Y = (y/255.0);
	//double Pr = (u/255.0-0.5);
	//double Pb = (v/255.0-0.5);
	

	
	/*int b = (int)(1.164*(y-16)+1.8556*(u-128));
	
	int g = (int)(1.164*(y-16) - (0.4681*(v-128) + 0.1872*(u-128)));

	int r = (int)(1.164*(y-16)+1.5748*(v-128));*/

	int b = (int)(y+1.8556*(u-128));
	
	int g = (int)(y - (0.4681*(v-128) + 0.1872*(u-128)));

	int r = (int)(y+1.5748*(v-128));
	
	
	/*double B = Y+1.8556*Pb;
	
	double G = Y - (0.4681*Pr + 0.1872*Pb);

	double R = Y+1.5748*Pr;*/
	
	//int b = (int)B*255;
	//int g = (int)G*255;
	//int r = (int)R*255;
	

	
	
	
	if (b>255){b=255;}
	else if (b<0 ){b = 0;}
	if (g>255){g=255;}
	else if (g<0 ){g = 0;}
	if (r>255){r=255;}
	else if (r<0 ){r = 0;}
	
	/*rgb[i]=(byte)b;
	rgb[i+1]=(byte)g;
	rgb[i+2]=(byte)r;*/
	int targetPosition=i;
	
	if (invertHeight)
	{
		targetPosition=((height-1)-targetPosition/width)*width   +   (targetPosition%width);
	}
	if (invertWidth)
	{
		targetPosition=(targetPosition/width)*width    +    (width-1)-(targetPosition%width);
	}
	
	
	rgb[targetPosition] =  (0xff000000) | (0x00ff0000 & r << 16) | (0x0000ff00 & g << 8) | (0x000000ff & b);
}
return rgb;
	
}



public static byte[] I420toRGB(byte[] yuv, int width, int height)
{

	boolean invertHeight=false;
	if (height<0)
	{
	height=-height;
	invertHeight=true;
	}

	boolean invertWidth=false;
	if (width<0)
	{
	width=-width;
	invertWidth=true;
	}
	
	
	
	
	
	
	
int iterations=width*height;
byte[] rgb = new byte[iterations*3];

for (int i = 0; i<iterations;i++)
{

	int nearest = (i/width)/2 * (width/2) + (i%width)/2;
	
	int y = yuv[i] & 0x000000ff;
	int u = yuv[iterations+nearest] & 0x000000ff;
	int v = yuv[iterations + iterations/4 + nearest] & 0x000000ff;
	

	int b = (int)(y+1.8556*(u-128));
	int g = (int)(y - (0.4681*(v-128) + 0.1872*(u-128)));
	int r = (int)(y+1.5748*(v-128));
	
	if (b>255){b=255;}
	else if (b<0 ){b = 0;}
	if (g>255){g=255;}
	else if (g<0 ){g = 0;}
	if (r>255){r=255;}
	else if (r<0 ){r = 0;}
	
	
	
	int targetPosition=i;
	
	if (invertHeight)
	{
		targetPosition=((height-1)-targetPosition/width)*width   +   (targetPosition%width);
	}
	if (invertWidth)
	{
		targetPosition=(targetPosition/width)*width    +    (width-1)-(targetPosition%width);
	}
	
	rgb[targetPosition*3] = (byte)r;
	rgb[targetPosition*3+1] = (byte)g;
	rgb[targetPosition*3+2] = (byte)b;
	
	
	//Banded
	/*rgb[targetPosition] = (byte)r;
	rgb[iterations+targetPosition] = (byte)g;
	rgb[2*iterations+targetPosition] = (byte)b;*/
	
}
return rgb;
	
}

}

package yunikorn.yukon;

import java.io.*;
import java.awt.image.*;
//import java.awt.geom.*;
import java.awt.*;
import java.awt.color.*;
//import java.awt.Dimension;
import javax.imageio.ImageIO;
//import javax.media.format.*;

import yunikorn.core.packet.VideoFrame;

public class YukonVideoFrame implements VideoFrame {
YukonVideoHeader header;
long timestamp;
byte[] buffer;
BufferedImage image;
//BufferedImage compatibleImage;




public long getTimestamp() {
	return timestamp;
}
public YukonVideoFrame(YukonVideoHeader header, long timestamp, byte[] buffer) {
	super();
	this.header = header;
	this.timestamp = timestamp;
	this.buffer = buffer;
	image=null;
	//compatibleImage=null;
}
public int getFps() {
	return header.getFps();
}
public int getHeight() {
	return header.getHeight();
}
public int getWidth() {
	return header.getWidth();
}
public byte[] getBuffer() {
	return buffer;
}
public YukonVideoHeader getHeader() {
	return header;
}

public String toString()
{
return "VideoFrame(" + header.toString() + ", Timestamp(" + timestamp + "), Buffersize(" + buffer.length + "))";
}

public void writeJpg(File jpgfile) throws IOException
{

ImageIO.write(getBufferedImage(), "jpeg", jpgfile);
}
/*public BufferedImage getBufferedImage()
{
	if (image==null) {
	int[] rgbBuffer = ColorConversion.I420toARGB(buffer, getWidth(), -getHeight());
	WritableRaster raster = Raster.createWritableRaster(new SinglePixelPackedSampleModel(DataBuffer.TYPE_INT,getWidth(),getHeight(),new int[] {0x00ff0000,0x0000ff00,0x000000ff,0xff000000}), new DataBufferInt(rgbBuffer,rgbBuffer.length), new Point(0,0));
	image = new BufferedImage(ColorModel.getRGBdefault(), raster, false, new java.util.Hashtable<Object, Object>());
	}
	return image;
}*/

public BufferedImage getBufferedImage()
{
	if (image==null)
	{
		byte[] rgbBuffer = ColorConversion.I420toRGB(buffer, getWidth(), -getHeight());
		WritableRaster raster = Raster.createInterleavedRaster(new DataBufferByte(rgbBuffer,rgbBuffer.length), getWidth(), getHeight(), getWidth()*3,3,new int[] {0,1,2}, new Point(0,0));
		ComponentColorModel model = new ComponentColorModel(new ICC_ColorSpace(ICC_Profile.getInstance(ColorSpace.CS_LINEAR_RGB)),false,false,ComponentColorModel.OPAQUE,DataBuffer.TYPE_BYTE);
		image = new BufferedImage(model, raster, false, new java.util.Hashtable<Object, Object>());
	}
	return image;
	
}
public int[] getARGBBuffer() {
	// TODO Auto-generated method stub
	return ColorConversion.I420toARGB(buffer, getWidth(), -getHeight());
}
/*public VideoFormat getARGBFormat() {
	// TODO Auto-generated method stub
	return new RGBFormat(new Dimension(getWidth(),getHeight()), (buffer.length/3)*2, RGBFormat.intArray, getFps(), 24, 0x00ff0000, 0x0000ff00, 0x000000ff); 
	 
}*/

/* (non-Javadoc)
 * It is unlikely that this method returns useful information. Instead we concentrate on RGB/BGR
 * 
 * @see yunikorn.core.VideoFrame#getFormat()
 */
/*public VideoFormat getFormat() {
	return new YUVFormat(new Dimension(getWidth(),-getHeight()),buffer.length,VideoFormat.byteArray,getFps(),YUVFormat.YUV_420,getWidth(),getWidth()/4,0,0,0);
}*/




}

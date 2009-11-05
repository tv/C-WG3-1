package yunikorn.yukon;

//import java.awt.Dimension;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

//import javax.media.format.*;

import yunikorn.core.packet.VideoFrame;
import yunikorn.yukon.factory.*;

public class SilentYukonVideoFrame implements VideoFrame {

	YukonVideoHeader header;
	RawCompressedPacket packet;
	boolean decompressed;
	YukonVideoFrame decorate;
	
	public SilentYukonVideoFrame(YukonVideoHeader header, RawCompressedPacket packet) {
		super();
		this.header = header;
		this.packet = packet;
		decompressed=false;
		decorate=null;
	}

	public BufferedImage getBufferedImage() throws IOException {
		// TODO Auto-generated method stub

			try {
			decompress();
			}catch (YukonException ex){throw new IOException(ex);} //Users risk
		return decorate.getBufferedImage();
	}

	public int getHeight() {
		// TODO Auto-generated method stub
		return header.getHeight();
	}

	public int getWidth() {
		// TODO Auto-generated method stub
		return header.getWidth();
	}

	public void writeJpg(File jpgfile) throws IOException {

			try {
			decompress();
			} catch(YukonException ex)
			{
				
                            throw new IOException(ex);
                            //return; //Silently return. The interface doesn't allow us to throw an exception. This is taken into account by the user.
			}
		
		decorate.writeJpg(jpgfile);
	}

	public long getTimestamp() {
		// TODO Auto-generated method stub
		if (!decompressed)
		{
			return packet.getTime();
		} else {
			return decorate.getTimestamp();
		}
	}
	public byte[] getBuffer() throws IOException
	{
		try {
			decompress();
		
		}
		catch (YukonException ex){
			//return new byte[0];
                        throw new IOException(ex);
		}
		return decorate.getBuffer();
	}
	public void decompress() throws YukonException
	{
		if (decompressed){return;}
		decorate = VideoFrameFactory.createVideoFrame(header, UncompressedPacketFactory.createPacket(packet));
		
		
		decompressed=true;
		packet=null;
		
	}



	public int[] getARGBBuffer() throws IOException {
		// TODO Auto-generated method stub
		try {
			decompress();
		}catch (YukonException ex){ throw new IOException(ex);}
		return decorate.getARGBBuffer();
	}

	/*public VideoFormat getARGBFormat() {
		// TODO Auto-generated method stub
		if (!decompressed) {
			return new RGBFormat(new Dimension(getWidth(),getHeight()), (int)(packet.getDecompressedSize()/3)*2, RGBFormat.intArray, header.getFps(), 24, 0x00ff0000, 0x0000ff00, 0x000000ff);
		}
		return decorate.getARGBFormat();
	}*/

	/* (non-Javadoc)
	 * It is unlikely that this method returns useful information. Instead we concentrate on RGB/BGR
	 * 
	 * @see yunikorn.core.VideoFrame#getFormat()
	 */
	/*public VideoFormat getFormat() {
		if (!decompressed) {
		return new YUVFormat(new Dimension(getWidth(),-getHeight()),(int)packet.getDecompressedSize(),VideoFormat.byteArray,header.getFps(),YUVFormat.YUV_420,getWidth(),getWidth()/4,0,0,0);
		}
		return decorate.getFormat();
	}*/

	/*public BufferedImage getCompatibleBufferedImage() {
		try {
		decompress();
		}catch(YukonException ex){return null;}
		return decorate.getCompatibleBufferedImage();
	}*/
	
	
	

}

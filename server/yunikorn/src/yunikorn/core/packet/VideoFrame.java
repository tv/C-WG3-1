package yunikorn.core.packet;
import java.io.*;
import java.awt.image.BufferedImage;

//import javax.media.format.VideoFormat;

public interface VideoFrame extends DataPacket {

	
	public int getWidth();
	public int getHeight();
	
	public BufferedImage getBufferedImage() throws IOException;
	public void writeJpg(File jpgfile) throws IOException;
	public byte[] getBuffer() throws IOException;
	public int[] getARGBBuffer() throws IOException;
	//public VideoFormat getFormat();
	//public VideoFormat getARGBFormat();
	
}

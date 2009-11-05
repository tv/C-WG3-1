package yunikorn.multipart;

import java.io.OutputStream;


//import yunikorn.core.*;
import yunikorn.core.chunkstream.StreamEvent;
import yunikorn.core.packet.VideoFrame;
import yunikorn.utils.*;
import yunikorn.sink.*;

import javax.imageio.*;
import java.io.*;
import java.awt.image.BufferedImage;

/**
 * @author testi
 * Converts a VideoFrame-object to JPEG and acts efficiently if there are multiple consumers for this object.
 */
public class JPEGProxyStreamEvent implements StreamEvent {

	VideoFrame frame;
	ImageWriter writer;
	ImageWriteParam param;
	BufferedImage image;
	boolean writeToBuffer; //Will probably avoid bad performance in case there is more than one instance consuming that event
	byte[] buffer;

	



	public JPEGProxyStreamEvent(VideoFrame frame, ImageWriter writer,
			ImageWriteParam param, int listenerCount) {
		super();
		this.frame = frame;
		this.writer = writer;
		this.param = param;
		image = null;
		writeToBuffer = (listenerCount>1);
		buffer = null;
	}






	public JPEGProxyStreamEvent(VideoFrame frame,int listenerCount) {
		this(frame,null,null, listenerCount);
	}


	public boolean prepare()
	{
		if (image != null)
		{return true;}
                try {
		image = frame.getBufferedImage();
                } catch (IOException ex) {
                return false;
                }
		/*if (image == null){
			return false;
		}*/
		return true;
	}
        

        
        /*public byte[] getBuffer() {
        return null;
        }*/



	public void write(OutputStream out) throws IOException {
		
		if (!prepare()) {return;} //Close out? No, uncoupled
		ProxyImageOutputStream imageStream;
		ByteArrayOutputStream bostream=null;
		if (writeToBuffer)
		{
			if (buffer != null)
			{
				out.write(buffer);
				return;

			}
			DynamicOutputStreamMulticaster cast = new DynamicOutputStreamMulticaster();
			cast.addStream(out);
			bostream = new ByteArrayOutputStream();
			cast.addStream(bostream);
			imageStream = new ProxyImageOutputStream(cast);
		}
		else {
			imageStream = new ProxyImageOutputStream(out);
		}
		
		
		if (writer == null) {
			
			ImageIO.write(image, "jpeg", imageStream);
		
		}else {
			writer.setOutput(imageStream);
			writer.write(null,new IIOImage(image,null,null),param);
		}
		if (writeToBuffer)
		{
			buffer = bostream.toByteArray();
		}
		
		
		
	}




}

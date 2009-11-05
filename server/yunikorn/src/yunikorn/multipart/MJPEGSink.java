package yunikorn.multipart;

//import java.awt.image.BufferedImage;
import java.io.IOException;
import java.io.OutputStream;

import yunikorn.sink.*;


import javax.imageio.*;


//import yunikorn.utils.ProxyImageOutputStream;

import java.util.*;
import javax.imageio.plugins.jpeg.*;

public class MJPEGSink extends ImageSink {
	
	
	

	
	
	

	@Override
	protected void writeEnd(OutputStream ostream) throws IOException {
		ostream.write(("--\n").getBytes());
	}

	/*@Override
	protected void writeImage(BufferedImage image, OutputStream ostream)
			throws IOException {
		
		
		
		
		ProxyImageOutputStream imageStream = new ProxyImageOutputStream(ostream);
		if (writer == null) {
			
			ImageIO.write(image, "jpeg", imageStream);
		
		}else {
			writer.setOutput(imageStream);
			writer.write(null,new IIOImage(image,null,null),params);
		}
		
		
		
	}*/




	
	ImageWriter writer;
	ImageWriteParam params;
	//PacketObservable<?,?> observable;

	public MJPEGSink() {
		super();
		//this.stream = new ProxyImageOutputStream(dynamicMultiplexer);
		writer=null;
		params=null;
		Iterator<ImageWriter> i = ImageIO.getImageWritersByFormatName("jpeg");
		if (i.hasNext())
		{
			writer=i.next();
			params = new JPEGImageWriteParam(Locale.getDefault());
			params.setCompressionMode(ImageWriteParam.MODE_EXPLICIT);
			params.setCompressionQuality(0.75f);
		}
		
		//this.observable=observable;
		//this.observable.addListener(this); //I don't think that's good style. TODO: Check yunikorn.mjpeg design
	}

	@Override
	protected void writeIntro(OutputStream stream) throws IOException {
		// TODO Auto-generated method stub
		stream.write(("\n--" + MJPEGHttpHandler.BOUNDARY).getBytes());
	}

	@Override
	protected void writeFrameEnd(OutputStream stream) throws IOException {
		// TODO Auto-generated method stub
		stream.write(("\n--" + MJPEGHttpHandler.BOUNDARY).getBytes());
	}

	@Override
	protected void writeFrameStart(OutputStream stream) throws IOException {
		// TODO Auto-generated method stub
		stream.write("\nContent-Type: image/jpeg\n\n".getBytes());
	}
	
	

}
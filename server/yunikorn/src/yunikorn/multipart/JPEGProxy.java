package yunikorn.multipart;

//import yunikorn.core.*;
import yunikorn.core.chunkstream.StreamEventListener;
import yunikorn.core.packet.AudioSequence;
import yunikorn.core.packet.VideoFrame;
import yunikorn.sink.*;
import java.util.*;
import yunikorn.utils.*;

import javax.imageio.ImageIO;
import javax.imageio.ImageWriteParam;
import javax.imageio.ImageWriter;
import javax.imageio.plugins.jpeg.JPEGImageWriteParam;

public class JPEGProxy implements PacketProxyStreamObservable {

	Set<StreamEventListener> observers;
	ImageWriter writer;
	ImageWriteParam params;
	
	
	
	public JPEGProxy() {
		super();
		observers = new ConcurrentHashSet<StreamEventListener>();
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
		// TODO Auto-generated constructor stub
	}

	public void onAudioSequence(AudioSequence sequence) {
		// TODO Auto-generated method stub

	}

	public void onEndOfStream() {
		for (StreamEventListener t : observers)
		{
			t.onEndOfStream();
		}

	}

	public void onVideoFrame(VideoFrame frame) {
		JPEGProxyStreamEvent event = new JPEGProxyStreamEvent(frame, writer, params, observers.size());
		
		for (StreamEventListener t : observers)
		{
			t.onStreamEvent(event);
		}
		
	}

	public void addStreamEventListener(StreamEventListener listener) {
		observers.add(listener);

	}
	public void removeStreamEventListener(StreamEventListener listener) {
		observers.remove(listener);

	}

}

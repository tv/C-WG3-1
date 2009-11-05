package yunikorn.yukon;

//import yunikorn.core.StreamListener;
import yunikorn.core.chunkstream.StreamEventListener;
import yunikorn.core.chunkstream.StreamEventObservable;
import yunikorn.yukon.event.*;
import java.util.*;
import yunikorn.utils.*;

public class YukonStreamRepeater implements CompressedPacketStreamListener, StreamEventObservable {

	RawCompressedPacket videoHeader;
	RawCompressedPacket audioHeader;
	Set<StreamEventListener> listeners;
	
boolean closed;
	public YukonStreamRepeater()
	{
		closed=false;
		videoHeader = null;
		audioHeader = null;
		listeners = new ConcurrentHashSet<StreamEventListener>();
	}
	
	public void onEndOfStream() {
		
		synchronized(listeners) {
		closed=true;
		for (StreamEventListener t : listeners)
	{
		
		t.onEndOfStream();
	}
		}
	}
	
	public void onPacket(RawCompressedPacket packet) {

		CompressedPacketStreamEvent event = new CompressedPacketStreamEvent(packet);
		synchronized(listeners) {
		closed=false;
		//TODO: (Highest priority (before any work in yunikorn continues)) Cloning the iterable everywhere is a bad idea (Performance), replace HashSet with a single-threaded, but ConcurrentModification-safe implementation (Decorator or Subclassing) and use it for all Observable classes in this API
	for (StreamEventListener t : listeners) {
	t.onStreamEvent(event);
}
}


if (packet.getType() == RawCompressedPacket.VIDEO_HEADER)
{
	videoHeader = packet;
}
else if (packet.getType() == RawCompressedPacket.AUDIO_HEADER)
{
	audioHeader = packet;
}
	}

	public void addStreamEventListener(StreamEventListener listener) {

		synchronized (listeners) {
			if (closed){listener.onEndOfStream();return;}
		if (videoHeader!= null) {
			listener.onStreamEvent(new CompressedPacketStreamEvent(videoHeader));
			//System.out.println("video header first");
		}
		if (audioHeader!= null) {
			listener.onStreamEvent(new CompressedPacketStreamEvent(audioHeader));
			//System.out.println("audio header first");

		}
		
		listeners.add(listener);
		}


//TODO: if stream already started (video, audio headers not null)

	}

	public void removeStreamEventListener(StreamEventListener listener) {
		// TODO Auto-generated method stub
		synchronized(listeners) {
		listeners.remove(listener);
		}
	}

}

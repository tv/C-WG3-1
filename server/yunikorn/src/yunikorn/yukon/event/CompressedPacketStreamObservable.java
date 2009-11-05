package yunikorn.yukon.event;

import java.io.InputStream;

import yunikorn.yukon.*;
import yunikorn.yukon.io.*;
import yunikorn.core.StreamListener;
import yunikorn.core.StreamParser;

import yunikorn.core.packet.metainterfaces.PacketObservable;
import java.util.*;
import yunikorn.utils.*;


public class CompressedPacketStreamObservable implements PacketObservable<CompressedPacketStreamListener>,
		StreamParser {

Set<CompressedPacketStreamListener> listeners;
Set<StreamListener> streamListeners;
	public CompressedPacketStreamObservable()
	{
		listeners = new ConcurrentHashSet<CompressedPacketStreamListener>();
		streamListeners = new ConcurrentHashSet<StreamListener>();
	}

	public void addListener(CompressedPacketStreamListener listener) {
		listeners.add(listener);
		
	}

	public void removeListener(CompressedPacketStreamListener listener) {
		listeners.remove(listener);
		
	}

	public void addStreamListener(StreamListener listener) {
		// TODO Auto-generated method stub
		streamListeners.add(listener);
	}

	public void readStream(InputStream source) {
		YukonStreamReader reader = new YukonStreamReader(source);
		while (reader.hasNext())
		{
			notifyListeners(reader.next());
		}
		notifyEndOfStream();

	}
	private void notifyListeners(RawCompressedPacket packet)
	{
		for (CompressedPacketStreamListener t : listeners )
		{
			t.onPacket(packet);
		}
	}
	
	private void notifyEndOfStream()
	{

		for (CompressedPacketStreamListener t : listeners )
		{
			t.onEndOfStream();
		}
		
		for (StreamListener t : streamListeners )
		{
			t.onEndOfStream();
		}
	}

	public void removeStreamListener(StreamListener listener) {
		// TODO Auto-generated method stub
		streamListeners.remove(listener);
	}

}

package yunikorn.yukon.event;

import java.util.*;
import java.io.*;

import yunikorn.core.*;
import yunikorn.core.packet.*;
import yunikorn.core.packet.metainterfaces.DataPacketListener;
import yunikorn.yukon.InvalidTypeException;
import yunikorn.yukon.RawCompressedPacket;
import yunikorn.yukon.RawUncompressedPacket;
import yunikorn.yukon.YukonAudioHeader;
import yunikorn.yukon.YukonAudioSequence;
import yunikorn.yukon.YukonException;
import yunikorn.yukon.YukonVideoFrame;
import yunikorn.yukon.YukonVideoHeader;
import yunikorn.yukon.factory.*;
import yunikorn.yukon.io.YukonStreamReader;
import yunikorn.utils.*;

public class YukonPacketObservable
		implements MediaStreamObservable<YukonVideoFrame, YukonAudioSequence>, StreamParser {


	
	Set<MediaStreamListener<? super YukonVideoFrame,? super YukonAudioSequence>> observers;
	Set<StreamListener> streamListener;
	public YukonPacketObservable() {
		super();

		observers = new ConcurrentHashSet<MediaStreamListener<? super YukonVideoFrame,? super YukonAudioSequence>>();
		streamListener = new ConcurrentHashSet<StreamListener>();
	}

	public void readStream(InputStream source) {
		
		YukonVideoHeader currentVideoHeader=null;
		YukonAudioHeader currentAudioHeader=null;
		
		YukonStreamReader reader = new YukonStreamReader(source);
		while (reader.hasNext()) {
			RawCompressedPacket current = reader.next();
			try {
			RawUncompressedPacket rawUPacket = UncompressedPacketFactory
					.createPacket(current);
			
				try {
					currentVideoHeader = VideoHeaderFactory
							.createVideoHeader(rawUPacket);
					// TODO If we enhance the PacketObserver to be able to
					// receive VideoHeaders, here comes the code

					continue;
				} catch (InvalidTypeException ex) {
				}
				try {
					if (currentVideoHeader != null) {
						
					 // skip this step as we have no video header
					notifyObservers(VideoFrameFactory.createVideoFrame(
							currentVideoHeader, rawUPacket));
					continue;
					}
				} catch (InvalidTypeException ex) {
					
				}
				try {
					currentAudioHeader = AudioHeaderFactory.createAudioHeader(rawUPacket);
					//TODO notify an enhanced PacketObserver
					continue;
				}
				catch (InvalidTypeException ex){}
				try {
					if (currentAudioHeader != null) {
					notifyObservers(AudioSequenceFactory.createAudioSequence(currentAudioHeader, rawUPacket));
					continue;
					}
					
				}
				catch (InvalidTypeException ex){}


			} catch (YukonException ex) {
				// We land here if we have more serious problems (thrown from
				// the factories)
			}

		}
		notifyEndOfStream();

	}
	
	
	private void notifyEndOfStream() {
		synchronized (observers) {
			for (MediaStreamListener<? super YukonVideoFrame, ? super YukonAudioSequence> t : observers) {
				t.onEndOfStream();
			}
		}
		synchronized(streamListener)
		{
			for (StreamListener t : streamListener)
			{
				t.onEndOfStream();
			}
		}
	}
	
	private void notifyObservers(YukonVideoFrame frame)
	{
		synchronized (observers) {
		for (MediaStreamListener<? super YukonVideoFrame,? super YukonAudioSequence> t : observers)
		{
			t.onVideoFrame(frame);
		}
		}
	}
	private void notifyObservers(YukonAudioSequence sample)
	{
		synchronized (observers) {
		for (DataPacketListener<? super YukonVideoFrame,? super YukonAudioSequence> t : observers)
		{
			t.onAudioSequence(sample);
		}
		}
	}

	public void addListener(MediaStreamListener<? super YukonVideoFrame,? super YukonAudioSequence> observer) {
		synchronized(observers) {
		observers.add(observer);
		}
	}

	public void removeListener(MediaStreamListener<? super YukonVideoFrame,? super YukonAudioSequence> observer) {
		synchronized(observers) {
		observers.remove(observer);
		}
	}
	
	public void addStreamListener(StreamListener listener) {
		streamListener.add(listener);
		
	}
	public void removeStreamListener(StreamListener listener) {
		streamListener.remove(listener);
		
	}
	
	

}

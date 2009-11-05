package yunikorn.yukon.event;

import java.util.*;
import java.io.*;
import yunikorn.core.*;
import yunikorn.core.packet.*;
import yunikorn.yukon.InvalidTypeException;
import yunikorn.yukon.RawCompressedPacket;
import yunikorn.yukon.SilentYukonAudioSequence;
import yunikorn.yukon.SilentYukonVideoFrame;
import yunikorn.yukon.YukonAudioHeader;
import yunikorn.yukon.YukonException;
import yunikorn.yukon.YukonVideoHeader;
import yunikorn.yukon.factory.*;
import yunikorn.yukon.io.YukonStreamReader;
import yunikorn.utils.*;

public class SilentYukonPacketObservable implements MediaStreamObservable<SilentYukonVideoFrame, SilentYukonAudioSequence>, StreamParser {

	Set<MediaStreamListener<? super SilentYukonVideoFrame, ? super SilentYukonAudioSequence>> observers;
	Set<StreamListener> streamListener;
	public SilentYukonPacketObservable() {
		super();

		observers = new ConcurrentHashSet<MediaStreamListener<? super SilentYukonVideoFrame, ? super SilentYukonAudioSequence>>();
		streamListener = new ConcurrentHashSet<StreamListener>();
	}

	public void readStream(InputStream source) {

		YukonVideoHeader currentVideoHeader = null;
		YukonAudioHeader currentAudioHeader = null;

		YukonStreamReader reader = new YukonStreamReader(source);
		while (reader.hasNext()) {
			RawCompressedPacket current = reader.next();

			try {
				try {
					currentVideoHeader = VideoHeaderFactory
							.createVideoHeader(current);
					// TODO If we enhance the PacketObserver to be able to
					// receive VideoHeaders, here comes the code

					continue;
				} catch (InvalidTypeException ex) {
				}
				try {
					if (currentVideoHeader != null) {

						// skip this step as we have no video header
						notifyObservers(SilentVideoFrameFactory
								.createVideoFrame(currentVideoHeader, current));
					continue;
					}
				} catch (InvalidTypeException ex) {

				}
				try {
					currentAudioHeader = AudioHeaderFactory
							.createAudioHeader(current);
					// TODO notify an enhanced PacketObserver
					continue;
				} catch (InvalidTypeException ex) {
				}
				try {
					if (currentAudioHeader != null) {
						notifyObservers(SilentAudioSequenceFactory
								.createAudioSequence(currentAudioHeader,
										current));
					continue;
					}
					
				} catch (InvalidTypeException ex) {
				}

			} catch (YukonException ex) {
				// We land here if we have more serious problems (thrown from
				// the factories)
			}

		}
		notifyEndOfStream();

	}

	private void notifyEndOfStream() {
		synchronized (observers) {
			for (MediaStreamListener<? super SilentYukonVideoFrame, ? super SilentYukonAudioSequence> t : observers) {
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

	private void notifyObservers(SilentYukonVideoFrame frame) {
		synchronized (observers) {
			for (MediaStreamListener<? super SilentYukonVideoFrame, ? super SilentYukonAudioSequence> t : observers) {
				t.onVideoFrame(frame);
			}
		}
	}

	private void notifyObservers(SilentYukonAudioSequence sample) {
		synchronized (observers) {
			for (MediaStreamListener<? super SilentYukonVideoFrame, ? super SilentYukonAudioSequence> t : observers) {
				t.onAudioSequence(sample);
			}
		}
	}

	public void addListener(
			MediaStreamListener<? super SilentYukonVideoFrame, ? super SilentYukonAudioSequence> observer) {
		synchronized (observers) {
			observers.add(observer);
		}
	}

	/*public void removeListener(
			StreamDataPacketListener<SilentYukonVideoFrame, SilentYukonAudioSequence> listener) {
		// TODO Auto-generated method stub
		
	}*/

	public void removeListener(
			MediaStreamListener<? super SilentYukonVideoFrame, ? super SilentYukonAudioSequence> observer) {
		synchronized (observers) {
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

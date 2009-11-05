package yunikorn.core.packet.metainterfaces;

import yunikorn.core.packet.AudioSequence;
import yunikorn.core.packet.VideoFrame;

/**
 * @author testi
 * Use StreamDataPacketListener if you read from a video stream.
 * @param <T>
 * @param <E>
 */
public interface DataPacketListener<T extends VideoFrame, E extends AudioSequence> extends PacketListener {


public void onVideoFrame(T frame);
public void onAudioSequence(E sequence);
//public void onEndOfStream();
}

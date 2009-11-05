package yunikorn.core.packet;

import yunikorn.core.StreamParser;
import yunikorn.core.packet.metainterfaces.DataPacketObservable;

public interface MediaStreamObservable<E extends VideoFrame,M extends AudioSequence> extends StreamParser,
		DataPacketObservable<E,M,MediaStreamListener<? super E,? super M>> {

}

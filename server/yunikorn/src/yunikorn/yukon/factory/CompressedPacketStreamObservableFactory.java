package yunikorn.yukon.factory;


import yunikorn.core.packet.metainterfaces.PacketObservableFactory;
import yunikorn.yukon.event.*;

public class CompressedPacketStreamObservableFactory implements
		PacketObservableFactory<CompressedPacketStreamObservable> {

	public CompressedPacketStreamObservable createPacketObservable() {
		// TODO Auto-generated method stub
		return new CompressedPacketStreamObservable();
	}

}

package yunikorn.yukon.factory;
import yunikorn.core.packet.*;
import yunikorn.core.packet.metainterfaces.PacketObservableFactory;
import yunikorn.yukon.*;
import yunikorn.yukon.event.SilentYukonPacketObservable;
public class SilentYukonPacketObservableFactory implements PacketObservableFactory<MediaStreamObservable<SilentYukonVideoFrame,SilentYukonAudioSequence>> {

	public  MediaStreamObservable<SilentYukonVideoFrame,SilentYukonAudioSequence> createPacketObservable() {
		// TODO Auto-generated method stub
		return new SilentYukonPacketObservable();
	}




}

package yunikorn.yukon;
import java.util.*;


import yunikorn.core.packet.metainterfaces.Packet;
import yunikorn.yukon.factory.UncompressedPacketFactory;
import yunikorn.yukon.factory.VideoFrameFactory;
import yunikorn.yukon.factory.VideoHeaderFactory;
import yunikorn.yukon.io.YukonStreamReader;

@Deprecated
public class YukonPacketIterator implements Iterator<Packet> {
	YukonStreamReader packetSource;
	YukonVideoHeader currentVideoHeader;
	
	
	
	
	public YukonPacketIterator(YukonStreamReader packetSource) {
		super();
		this.packetSource = packetSource;
		currentVideoHeader = null;
	}

	public boolean hasNext() {
		// TODO Auto-generated method stub
	return packetSource.hasNext();
	}

	public Packet next() {
		// TODO Auto-generated method stub
		RawCompressedPacket rawCPacket = packetSource.next();
		//if (rawCPacket == null){return null;}
		
		try {
		RawUncompressedPacket rawUPacket = UncompressedPacketFactory.createPacket(rawCPacket);
		
		try {
			currentVideoHeader = VideoHeaderFactory.createVideoHeader(rawUPacket);
			return currentVideoHeader;
		}
		catch (InvalidTypeException ex){}
		try {
			if (currentVideoHeader == null){throw new InvalidTypeException();} //skip this step as we have no video header
			return VideoFrameFactory.createVideoFrame(currentVideoHeader,rawUPacket);
		}
		catch (InvalidTypeException ex){}
		}
		catch (YukonException ex)
		{
			//We land here if we have more serious problems (thrown from the factories)
		}
		return null; //Invalid or unhandled packet
		
	}

	public void remove() {
		// TODO Auto-generated method stub
		
	}

	
	
	
	
}

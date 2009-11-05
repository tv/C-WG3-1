package yunikorn.core.packet;
import java.util.*;

import yunikorn.core.packet.metainterfaces.Packet;
import yunikorn.yukon.YukonPacketIterator;
import yunikorn.yukon.io.YukonStreamReader;

@Deprecated
public class ValidPacketIterator implements Iterator<Packet> {
Iterator<Packet> packetIterator;
Packet currentPacket;


public ValidPacketIterator(Iterator<Packet> packetIterator) {
	super();
	this.packetIterator = packetIterator;
	currentPacket=null;
}
public ValidPacketIterator(YukonStreamReader yukonStream) {
	super();
	packetIterator = new YukonPacketIterator(yukonStream);
	currentPacket=null;
}

public boolean hasNext() {
if (currentPacket != null){return true;}
while (packetIterator.hasNext())
{
currentPacket = packetIterator.next();
if (currentPacket != null)
{
return true;
}
}
return false;
}

public Packet next() {
if (hasNext())
{
	Packet tempPacket=currentPacket;
	currentPacket=null;
	return tempPacket;

}
throw new NoSuchElementException();
}

public void remove() {
	packetIterator.remove();
}



}

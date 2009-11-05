package yunikorn.core.packet;

import yunikorn.core.packet.metainterfaces.Packet;


public interface DataPacket extends Packet {

	public long getTimestamp();
}

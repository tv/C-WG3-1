package yunikorn.yukon.io;
import java.io.*;

import yunikorn.yukon.RawCompressedPacket;
public class YukonStreamWriter {
OutputStream sink;

public YukonStreamWriter(OutputStream sink) {
	super();
	this.sink = sink;
}

public void close() throws IOException {
	sink.close();
}
public void write(RawCompressedPacket packet) throws IOException
{
	
	/*if (packet.getType() == RawCompressedPacket.VIDEO_HEADER)
	{
		System.out.println("Sending video header: " + packet);
	}*/
	
	DataOutputStream out = new DataOutputStream(sink);
	out.writeByte(packet.getType());
	out.writeLong(Long.reverseBytes(packet.getTime()));
	out.writeLong(Long.reverseBytes(packet.getDecompressedSize()));
	out.writeLong(Long.reverseBytes(packet.getCompressedSize()));
	sink.write(packet.getBuffer());
}

}

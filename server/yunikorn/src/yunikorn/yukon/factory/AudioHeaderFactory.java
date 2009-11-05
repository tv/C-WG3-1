package yunikorn.yukon.factory;
import java.nio.ByteBuffer;
import java.nio.IntBuffer;

import yunikorn.yukon.*;
public class AudioHeaderFactory {
	
	public static final int DEFAULT_RATE=48000;
	public static final int DEFAULT_CHANNELS=2;
	public static YukonAudioHeader createAudioHeader(RawUncompressedPacket packet) throws YukonException
	{
		if (packet.getType() != AbstractRawPacket.AUDIO_HEADER) { throw new InvalidTypeException();}
		return create(packet);
		
	}
	public static YukonAudioHeader createAudioHeader(RawCompressedPacket packet) throws YukonException
	{
		if (packet.getType() != AbstractRawPacket.AUDIO_HEADER) { throw new InvalidTypeException();}
		return create(UncompressedPacketFactory.createPacket(packet));
	}
	
	private static YukonAudioHeader create(RawUncompressedPacket packet) throws YukonException
	{
		if (packet.getBuffer().length != 4) {throw new YukonException();}
		IntBuffer intBuf = ByteBuffer.wrap(packet.getBuffer()).asIntBuffer();
		int bytesPerSample = Integer.reverseBytes(intBuf.get());
		return new YukonAudioHeader(packet.getTime(),bytesPerSample, DEFAULT_RATE, DEFAULT_CHANNELS);
	}
}

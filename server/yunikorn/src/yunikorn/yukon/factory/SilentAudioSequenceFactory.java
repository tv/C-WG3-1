package yunikorn.yukon.factory;

import yunikorn.yukon.*;

public class SilentAudioSequenceFactory {

	
	public static SilentYukonAudioSequence createAudioSequence(YukonAudioHeader header, RawCompressedPacket packet) throws YukonException
	{
		if (packet.getType() != AbstractRawPacket.AUDIO_SAMPLES) { throw new InvalidTypeException();}
		/*if (packet.getBuffer().length % (header.getBytesPerSample()*header.getChannels()) != 0)
		{
			//Invalid packet size
			throw new YukonException();
		}*/
		return new SilentYukonAudioSequence(header,packet);
	}
	
	
	
}

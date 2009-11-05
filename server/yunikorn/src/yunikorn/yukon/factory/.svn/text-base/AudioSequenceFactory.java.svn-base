package yunikorn.yukon.factory;
import yunikorn.yukon.*;
public class AudioSequenceFactory {

	public static YukonAudioSequence createAudioSequence(YukonAudioHeader header, RawUncompressedPacket packet) throws YukonException
	{
		if (packet.getType() != AbstractRawPacket.AUDIO_SAMPLES) { throw new InvalidTypeException();}
		if (packet.getBuffer().length % (header.getBytesPerSample()*header.getChannels()) != 0)
		{
			//Invalid packet size
			throw new YukonException();
		}
		return new YukonAudioSequence(header,packet.getTime(), packet.getBuffer());
	}
	
	
}

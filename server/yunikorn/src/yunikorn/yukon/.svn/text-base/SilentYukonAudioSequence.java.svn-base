package yunikorn.yukon;

//import javax.media.format.AudioFormat;
//import javax.sound.sampled.AudioInputStream;

import yunikorn.core.packet.AudioSequence;
import yunikorn.yukon.factory.*;

public class SilentYukonAudioSequence implements AudioSequence {

	
	YukonAudioHeader header;
	RawCompressedPacket packet;
	boolean decompressed;
	YukonAudioSequence decorate;
	
	
	public SilentYukonAudioSequence(YukonAudioHeader header, RawCompressedPacket packet) {
		super();
		this.header = header;
		this.packet = packet;
		decompressed=false;
		decorate=null;
	}

	public int getChannels() {
		// TODO Auto-generated method stub
		return header.getChannels();
	}

	public int getFramecount() {
		// TODO Auto-generated method stub

			try {
				decompress();
			} catch (YukonException ex)
			{
				return 0; //This is more or less valid
			}
		
		return decorate.getFramecount();
	}

	public int getRate() {
		// TODO Auto-generated method stub
		return header.getRate();
	}

	/*public AudioInputStream getStream() {
		// TODO Auto-generated method stub
		try {
		decompress();
		}
		catch (YukonException ex){
			return null;
		}
		return decorate.getStream();
	}*/

	public long getTimestamp() {
		// TODO Auto-generated method stub
		if (!decompressed)
		{
			return packet.getTime();
		} else {
			return decorate.getTimestamp();
		}
	}
	public byte[] getBuffer()
	{
		try {
			decompress();
		
		}
		catch (YukonException ex){
			return new byte[0];
		}
		return decorate.getBuffer();
	}
	
	
	
	/*public AudioFormat getFormat() {
		// TODO Auto-generated method stub
		if (!decompressed)
		{
			return new AudioFormat(AudioFormat.LINEAR,(double)getRate(),header.getBytesPerSample()*8,getChannels(),AudioFormat.LITTLE_ENDIAN,AudioFormat.SIGNED,getChannels()*header.getBytesPerSample()*8,(double)getRate(),AudioFormat.byteArray);
		}
		return decorate.getFormat();
	}*/

	public void decompress() throws YukonException
	{
		if (decompressed){return;}
		decorate = AudioSequenceFactory.createAudioSequence(header, UncompressedPacketFactory.createPacket(packet));
		
		
		decompressed=true;
		packet=null;
		
	}

}

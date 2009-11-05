package yunikorn.yukon;

import yunikorn.core.packet.AudioSequence;
//import javax.sound.sampled.AudioInputStream;
//import yunikorn.utils.*;
//import javax.media.format.*;
//import javax.media.*;
public class YukonAudioSequence implements AudioSequence {
	
	YukonAudioHeader header;
	long timestamp;
	byte [] buffer;
	
	


	public byte[] getBuffer() {
		return buffer;
	}




	public YukonAudioHeader getHeader() {
		return header;
	}




	public YukonAudioSequence(YukonAudioHeader header, long timestamp, byte[] buffer) {
		super();
		this.header = header;
		this.timestamp = timestamp;
		this.buffer = buffer;
	}




	public long getTimestamp() {
		return timestamp;
	}




	public int getBytesPerSample() {
		return header.getBytesPerSample();
	}




	public int getChannels() {
		return header.getChannels();
	}




	public int getRate() {
		return header.getRate();
	}
	public int getFramecount()
	{
		return buffer.length/(getBytesPerSample()*getChannels());
	}
	
	/*public AudioInputStream getStream()
	{
		AudioFormat format = new javax.sound.sampled.AudioFormat(javax.sound.sampled.AudioFormat.Encoding.PCM_SIGNED,getRate()*getChannels(),getBytesPerSample()*8,getChannels(),getBytesPerSample()*getChannels(),getRate(),false);
		return new AudioInputStream(new ByteArrayInputStream(buffer),format,getFramecount());
	}*/




	/*public AudioFormat getFormat() {
		// TODO Auto-generated method stub
		return new AudioFormat(AudioFormat.LINEAR,(double)getRate(),getBytesPerSample()*8,getChannels(),AudioFormat.LITTLE_ENDIAN,AudioFormat.SIGNED,getChannels()*getBytesPerSample()*8,(double)getRate(),AudioFormat.byteArray);
	}*/
	
	

}

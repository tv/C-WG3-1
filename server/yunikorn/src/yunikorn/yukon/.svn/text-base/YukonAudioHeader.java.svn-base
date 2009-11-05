package yunikorn.yukon;

//import yunikorn.core.*;
import yunikorn.core.packet.AudioHeader;

public class YukonAudioHeader implements AudioHeader {

	long timestamp;
	int bytesPerSample;
	int rate;
	int channels;
	
	
	public int getBytesPerSample() {
		return bytesPerSample;
	}


	public void setBytesPerSample(int bytesPerSample) {
		this.bytesPerSample = bytesPerSample;
	}


	public int getChannels() {
		return channels;
	}


	public void setChannels(int channels) {
		this.channels = channels;
	}


	public int getRate() {
		return rate;
	}


	public void setRate(int rate) {
		this.rate = rate;
	}


	public void setTimestamp(long timestamp) {
		this.timestamp = timestamp;
	}


	public YukonAudioHeader(long timestamp, int bytesPerSample, int rate, int channels) {
		super();
		this.timestamp = timestamp;
		this.bytesPerSample = bytesPerSample;
		this.rate = rate;
		this.channels = channels;
	}


	public long getTimestamp() {
		return timestamp;
	}
	
}

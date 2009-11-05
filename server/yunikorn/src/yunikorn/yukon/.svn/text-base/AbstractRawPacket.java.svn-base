package yunikorn.yukon;
import java.util.*;
public class AbstractRawPacket {

public static final byte VIDEO_HEADER=0x00;
public static final byte YUV_FRAME=0x01;
public static final byte AUDIO_HEADER=0x02;
public static final byte AUDIO_SAMPLES=0x03;

	
	
private byte type;
private long time;
private long decompressedSize;
private long compressedSize;
private byte[] buffer;
public AbstractRawPacket(byte type, long time, long decompressedSize, long compressedSize, byte[] buffer) {
	super();
	this.type = type;
	this.time = time;
	this.decompressedSize = decompressedSize;
	this.compressedSize = compressedSize;
	this.buffer = buffer;
}

public String toString()
{
return "Type: " + type + "\nTime: " + time + " - " + new Date(time/1000) + "\nDecompressed size: " + decompressedSize + "\nCompressed size: " + compressedSize + "\nbuffer.length == " + buffer.length + "\n";
}

public AbstractRawPacket()
{
type=0;
time=0;
decompressedSize=0;
compressedSize=0;
buffer=null;
}
public byte[] getBuffer() {
	return buffer;
}
public void setBuffer(byte[] buffer) {
	this.buffer = buffer;
}
public long getCompressedSize() {
	return compressedSize;
}
public void setCompressedSize(long compressedSize) {
	this.compressedSize = compressedSize;
}
public long getDecompressedSize() {
	return decompressedSize;
}
public void setDecompressedSize(long decompressedSize) {
	this.decompressedSize = decompressedSize;
}
public long getTime() {
	return time;
}
public void setTime(long time) {
	this.time = time;
}
public byte getType() {
	return type;
}
public void setType(byte type) {
	this.type = type;
}
}

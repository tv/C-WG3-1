package yunikorn.yukon;

import yunikorn.core.packet.VideoHeader;

public class YukonVideoHeader implements VideoHeader {
	long timestamp;
	int fps;
	int width;
	int height;
	int scale;
	public int getScale() {
		return scale;
	}
	public void setScale(int scale) {
		this.scale = scale;
	}
	public int getFps() {
		return fps;
	}
	public void setFps(int fps) {
		this.fps = fps;
	}
	public int getHeight() {
		return height;
	}
	public void setHeight(int height) {
		this.height = height;
	}
	public int getWidth() {
		return width;
	}
	public void setWidth(int width) {
		this.width = width;
	}
	public YukonVideoHeader(long timestamp, int fps, int width, int height, int scale) {
		super();
		this.timestamp = timestamp;
		this.fps = fps;
		this.width = width;
		this.height = height;
		this.scale = scale;
	}
	public long getTimestamp() {
		return timestamp;
	}
	public void setTimestamp(long timestamp) {
		this.timestamp = timestamp;
	}
	
	
	public String toString()
	{
		return "VideoHeader(Timestamp(" + timestamp + "), Fps(" + fps + "), Width(" + width + "), Height(" + height + "), Scale(" + scale + "))";
	}
}

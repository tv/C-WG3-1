package yunikorn.yukon.factory;

import yunikorn.yukon.AbstractRawPacket;
import yunikorn.yukon.InvalidTypeException;
import yunikorn.yukon.RawUncompressedPacket;
import yunikorn.yukon.YukonException;
import yunikorn.yukon.YukonVideoFrame;
import yunikorn.yukon.YukonVideoHeader;

public class VideoFrameFactory {

	public static YukonVideoFrame createVideoFrame(YukonVideoHeader header, RawUncompressedPacket packet) throws YukonException
	{
		if (packet.getType() != AbstractRawPacket.YUV_FRAME) { throw new InvalidTypeException();}
		
		//TODO: Shall we throw an exception if the header has a newer timestamp than this packet?

		//TODO: Throw an exception if the buffer size of the current frame is not (width*height*3)/2
		if ((header.getWidth()*header.getHeight()*3)/2 != packet.getBuffer().length)
		{
			throw new YukonException();
		}
		
		return new YukonVideoFrame(header,packet.getTime(), packet.getBuffer());
	}
}

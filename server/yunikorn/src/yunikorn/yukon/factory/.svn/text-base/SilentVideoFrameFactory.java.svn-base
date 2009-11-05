package yunikorn.yukon.factory;

import yunikorn.yukon.*;

public class SilentVideoFrameFactory {
	public static SilentYukonVideoFrame createVideoFrame(YukonVideoHeader header, RawCompressedPacket packet) throws YukonException
	{
		if (packet.getType() != AbstractRawPacket.YUV_FRAME) { throw new InvalidTypeException();}
		
		//TODO: Shall we throw an exception if the header has a newer timestamp than this packet?

		//TODO: Throw an exception if the buffer size of the current frame is not (width*height*3)/2

		
		return new SilentYukonVideoFrame(header, packet);
	}
}

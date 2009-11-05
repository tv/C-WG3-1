package yunikorn.yukon.factory;

import yunikorn.yukon.RawCompressedPacket;
import yunikorn.yukon.RawUncompressedPacket;
import yunikorn.yukon.YukonException;
public class UncompressedPacketFactory {

	
	public static RawUncompressedPacket createPacket(RawCompressedPacket rawpacket) throws YukonException
	{
		
		int size = (int)rawpacket.getDecompressedSize();
		if (size<0){throw new YukonException("target decompressed packet size too large");}
		byte[] unCompressedBytes = new byte[(int)rawpacket.getDecompressedSize()];
		long decompressed=rawpacket.getDecompressedSize();
		//System.out.println(testing.testing.byteArrayToString(rawpacket.getBuffer()));
			try {
			seomCodecDecode(unCompressedBytes,rawpacket.getBuffer(),rawpacket.getDecompressedSize());
			}
			catch (ArrayIndexOutOfBoundsException ex){ //TODO: "legacy" code crash safe without catching runtime exception
				unCompressedBytes = new byte[0];
				decompressed=0;
			}
			//byte[] unCompressedBytes = SeomCompression.decode(rawpacket.getBuffer(), (int)rawpacket.getDecompressedSize());
			//System.out.println(testing.testing.byteArrayToString(unCompressedBytes));
			RawUncompressedPacket uncompressedPacket=new RawUncompressedPacket();
			uncompressedPacket.setBuffer(unCompressedBytes);
			uncompressedPacket.setCompressedSize(rawpacket.getCompressedSize());
			uncompressedPacket.setDecompressedSize(decompressed);
			uncompressedPacket.setTime(rawpacket.getTime());
			uncompressedPacket.setType(rawpacket.getType());
			return uncompressedPacket;
	}
	
	
	
	

	
	private static void memcpy(byte[] dst, byte src[], int dstoffset, int srcoffset, int length)
	{
		//System.out.println(testing.testing.byteArrayToString(dst));
		if (src == dst && srcoffset + length > dstoffset){	
		for (int i = 0;i<length;i++)
		{
			dst[i+dstoffset]=src[i+srcoffset];
		}
		}
		else {
		System.arraycopy(src, srcoffset, dst, dstoffset, length);
		}
		//System.out.println(testing.testing.byteArrayToString(dst));
	}
	private static void memset(byte[] dst, int offset, byte value, int len)
	{
		//System.out.println(testing.testing.byteArrayToString(dst));
		for (int i = 0;i<len;i++)
		{
			dst[offset+i]=value;
		}
		//System.out.println(testing.testing.byteArrayToString(dst));
	}
	
	
	private static byte[] seomCodecDecode(byte[] dst, byte[] src, long size)
	{
		//long time = System.nanoTime();
		//const void *end = dst + size;
		char counter = 8;
		int dstindex=0;
		int srcindex=0;
		int cbyte = unsignByte(src[srcindex++]);

		while (dstindex < size - 4) {
			if (counter == 0) { /* fetch control byte */
				cbyte = unsignByte(src[srcindex++]);
				//System.out.println("cbyte-60: " + cbyte);
				counter = 8;
			}

			if ((0x000000ff & cbyte & (1 << 7)) != 0) { /* LZ match or RLE sequence */
				cbyte = unsignByte((byte)((cbyte << 1) | 1));
				//System.out.println("cbyte-66: " + cbyte);
				--counter;
				if ((src[srcindex] & 0x80) == 0) { /* 7bits offset */
					
					int offset = unsignByte(src[srcindex]);
					memcpy(dst, dst, dstindex, dstindex - offset, 3); //here we are
					dstindex += 3;
					srcindex += 1;
				} else if ((unsignByte(src[srcindex]) & 0x60) == 0) { /* 13bits offset */
					
					int offset = ((unsignByte(src[srcindex]) & 0x1f) << 8) | unsignByte(src[srcindex + 1]);
					memcpy(dst, dst, dstindex, dstindex - offset, 3);
					dstindex += 3;
					srcindex += 2;
				} else if ((unsignByte(src[srcindex]) & 0x40) == 0) { /* 10bits offset, 3bits length */
					
					int len = ((unsignByte(src[srcindex]) >>> 2) & 7) + 4;
					int offset = ((unsignByte(src[srcindex]) & 0x03) << 8) | unsignByte(src[srcindex + 1]);
					memcpy(dst,dst, dstindex, dstindex - offset, len);
					dstindex += len;
					srcindex += 2;
				} else if ((unsignByte(src[srcindex]) & 0x20) == 0) { /* 16bits offset, 5bits length */
					
					int len = (unsignByte(src[srcindex]) & 0x1f) + 4;
					int offset = (unsignByte(src[srcindex+1]) << 8) | unsignByte(src[srcindex+2]);
					memcpy(dst, dst,dstindex, dstindex - offset, len);
					dstindex += len;
					srcindex += 3;
				} else if ((unsignByte(src[srcindex]) & 0x10) == 0) { /* 17bits offset, 11bits length */
					
					int len = (((unsignByte(src[srcindex]) & 0x0f) << 7) | (unsignByte(src[srcindex+1]) >>> 1)) + 4;
					int offset = ((unsignByte(src[srcindex+1]) & 0x01) << 16) | (unsignByte(src[srcindex+2]) << 8) | (unsignByte(src[srcindex+3]));
					//System.out.println("memcpy(dst,dst," + dstindex + " - " + offset + ", " + len + ");");
					memcpy(dst,dst,dstindex,dstindex - offset, len);
					dstindex += len;
					srcindex += 4;
				} else { /* RLE sequence */
					
					int len = (((unsignByte(src[srcindex]) & 0x0f) << 8) | unsignByte(src[srcindex+1])) + 5;
					memset(dst,dstindex, src[srcindex+2], len);
					dstindex += len;
					srcindex += 3;
					//System.out.println("105-" + srcindex + " " + dstindex);
				}
			} else { /* literal */
				byte[][] map = { { 4, 0x0f }, { 3, 0x07 }, { 2, 0x03 }, { 2, 0x03 }, { 1, 0x01 }, { 1, 0x01 }, { 1, 0x01 }, { 1, 0x01 } };
				//System.out.println("cbyte: " + cbyte + " unsigned: " + unsignByte(cbyte));
				int index = unsignByte(cbyte) >>> 4;
					//System.out.println("index: " + index);
				
				memcpy(dst, src, dstindex, srcindex,unsignByte(map[index][0]));
				dstindex += unsignByte(map[index][0]);
				srcindex += unsignByte(map[index][0]);
				//System.out.println("114-" + srcindex);
				counter -= unsignByte(map[index][0]);
				cbyte = unsignByte((byte)((cbyte << unsignByte(map[index][0])) | unsignByte(map[index][1])));
				//System.out.println("cbyte-112: " + cbyte);
			}
		}
		
		while (dstindex < size) {
			if (counter == 0) {
				counter = 8;
				++srcindex;
			}
			dst[dstindex++] = src[srcindex++];
			//System.out.println("126-" + srcindex);
			--counter;
		}
		//System.out.println("Elapsed: " + (System.nanoTime()-time));
		return dst;
	}
	
	private static int unsignByte(int sign)
	{
		
		return 0x000000ff & sign;
		/*int toReturn = sign;
		if (toReturn<0){toReturn+=256;}
		return toReturn;*/
	}
}

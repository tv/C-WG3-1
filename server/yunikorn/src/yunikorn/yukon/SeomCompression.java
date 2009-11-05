package yunikorn.yukon;

public class SeomCompression {
	
	private static void memcpy(byte[] dst, byte src[], int dstoffset, int srcoffset, int length)
	{

		for (int i = 0;i<length;i++)
		{
			dst[i+dstoffset]=src[i+srcoffset];
		}

	}
	private static void memset(byte[] dst, int offset, byte value, int len)
	{

		for (int i = 0;i<len;i++)
		{
			dst[offset+i]=value;
		}

	}
	public static byte [] decode(byte[] src, int size)
	{
		byte[] dst = new byte[size];
		int srcindex=0;
		int dstindex=0;
		char counter = 8;

		byte cbyte = src[srcindex++];
		while (dstindex < dst.length-4)
		{
			if (counter == 0) {
				cbyte = (byte)((cbyte << 1) | 1);
				--counter;
			}
			
			if ((0x000000ff & cbyte & (1 << 7)) != 0) {
				if ((src[srcindex] & 0x00000080) == 0)
				{
				int offset = 0x000000ff & src[srcindex];
				System.out.println(offset);
				memcpy(dst,dst,dstindex,dstindex-offset,3);
				dstindex+=3;
				srcindex+=1;
				}
				else if ((src[srcindex] & 0x00000060) == 0)
				{
				int offset = (((src[srcindex] & 0x0000001f) << 8) | (0x000000ff & src[srcindex+1]));
				memcpy(dst,dst,0,dstindex-offset,3);
				dstindex+=3;
				srcindex+=2;
				}
				else if((src[srcindex] & 0x00000040) == 0)
				{
				int len = (0x000000ff & (src[srcindex] >>> 2) & 7) + 4;
				int offset = ((src[srcindex] & 0x00000003) << 8 | 0x000000ff & src[srcindex + 1]);
				memcpy(dst,dst,0,dstindex-offset,len);
				dstindex+=len;
				srcindex+=2;
				}
				else if((src[srcindex] & 0x00000020) == 0)
				{
					int len = (src[srcindex] & 0x0000001f) + 4;
					int offset = ((src[srcindex+1] & 0x000000ff) << 8 | 0x000000ff & src[srcindex + 2]);
					memcpy(dst,dst,0,dstindex-offset,len);
					dstindex+=len;
					srcindex+=3;
					
				}
				else if((src[srcindex] & 0x00000010) == 0)
				{
					int len = (((src[srcindex] & 0x0000000f) << 7) | ((src[srcindex+1] & 0x000000ff) >>> 1)) + 4;
					int offset = ((src[srcindex+1] & 0x00000001) << 16 | ((src[srcindex] & 0x000000ff) << 8) | (src[srcindex+3] & 0x000000ff));
					memcpy(dst,dst,0,dstindex-offset,len);
					dstindex+=len;
					srcindex+=4;
				}
				else {
					int len = (((src[srcindex] & 0x0000000f) << 8) | (src[srcindex+1] & 0x000000ff)) + 5;
					memset(dst,dstindex,src[srcindex+2],len);
					dstindex+=len;
					srcindex+=3;
					
				}
			}
			else {
				byte[][] map = { { 4, 0x0f }, { 3, 0x07 }, { 2, 0x03 }, { 2, 0x03 }, { 1, 0x01 }, { 1, 0x01 }, { 1, 0x01 }, { 1, 0x01 } };
				byte index = (byte)(cbyte >>> 4);
				memcpy(dst,src,dstindex,srcindex,map[index][0]);
				dstindex+=map[index][0];
				srcindex+=map[index][0];
				counter-=map[index][0];
				cbyte = (byte)((cbyte << map[index][0]) | map[index][1]);
			}
				

		}
		
		//Fill up the missing 4 bytes
		while (dstindex < dst.length) {
			if (counter == 0)
			{
				counter=8;
				++srcindex;
			}
			dst[dstindex++] = src[srcindex++];
			counter--;
		}
		return dst;
		
		
	}
	
}

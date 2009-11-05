package yunikorn.yukon.io;

import java.io.*;
import java.util.*;

import yunikorn.yukon.RawCompressedPacket;

public class YukonStreamReader implements Iterator<RawCompressedPacket> {
	InputStream source;

	RawCompressedPacket current;

	public YukonStreamReader(InputStream source) {
		super();
		this.source = source;
		current = null;
		// readHeader();
	}

	public boolean hasNext() // For "private" use, this method assures
								// current != null if true
	{
		if (current != null) {
			return true;
		}
		DataInputStream readProxy = new DataInputStream(source);
		RawCompressedPacket frame = new RawCompressedPacket();
		try {
			frame.setType(readProxy.readByte());
			frame.setTime(Long.reverseBytes(readProxy.readLong()));
			frame.setDecompressedSize(Long.reverseBytes(readProxy.readLong()));
			long compressedSize = Long.reverseBytes(readProxy.readLong());
			if (compressedSize < 0 || compressedSize > Integer.MAX_VALUE) {
				// System.out.println("Unexpected compressed size: " +
				// compressedSize);
				current = null;
				try {
					source.close();
					}catch(IOException ex){}
				return false;
			}
			frame.setCompressedSize(compressedSize);
			byte[] buffer = new byte[(int) compressedSize];

			/*
			 * for (int i = 0 ; i<buffer.length;i++) {
			 * buffer[i]=readProxy.readByte(); }
			 */
			int bytesConsumed = 0;
			while (bytesConsumed < buffer.length) {
				int read = readProxy.read(buffer, bytesConsumed, buffer.length
						- bytesConsumed);
				if (read < 0) {
					throw new EOFException();
				}
				bytesConsumed += read;
			}

			frame.setBuffer(buffer);
			current = frame;
			return true;
		} catch (IOException ex) {
			// System.out.println(ex);
			current = null;
			try {
			source.close();
			}catch(IOException ex2){}
			return false;
		}

	}

	public RawCompressedPacket next() {
		if (hasNext()) {
			RawCompressedPacket toReturn = current;
			current = null;
			return toReturn;
		}
		throw new NoSuchElementException();
	}

	public void remove() {
		// stub
	}

}

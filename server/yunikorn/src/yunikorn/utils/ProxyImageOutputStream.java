package yunikorn.utils;

import java.io.*;


import javax.imageio.stream.*;

public class ProxyImageOutputStream extends ImageOutputStreamImpl {

	OutputStream sink;
	
	
	boolean coupled;
	public ProxyImageOutputStream(OutputStream sink) {
		this(sink,false);
	}
	public ProxyImageOutputStream(OutputStream sink, boolean coupled) {
		super();
		this.sink = sink;
		this.coupled=coupled;
	}

	@Override
	public void write(byte[] b, int off, int len) throws IOException {
		sink.write(b,off,len);
		
	}

	@Override
	public void write(int b) throws IOException {
		sink.write(b);
		
	}

	@Override
	public int read() throws IOException {
		//Not supported
		return -1;
	}

	@Override
	public int read(byte[] b, int off, int len) throws IOException {
		//Not supported
		return 0;
	}
        @Override
	public void close() throws IOException
	{
		if (coupled) {
		sink.close();
		}
	}



}

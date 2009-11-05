package yunikorn.sink;

import java.io.IOException;
import java.io.OutputStream;

public class CopyThreadedOutputStream extends ThreadedOutputStream {

	public CopyThreadedOutputStream(OutputStream out, boolean standalone) {
		super(out, standalone);
		// TODO Auto-generated constructor stub
	}

	@Override
	public void write(byte[] b, int off, int len) throws IOException {
		byte[] newb = new byte[len];
		System.arraycopy(b, off, newb, 0, len);
		super.write(newb);
	}

	@Override
	public void write(byte[] b) throws IOException {
		byte[] newb = new byte[b.length];
		System.arraycopy(b, 0, newb, 0, b.length);
		super.write(newb);
	}

}
